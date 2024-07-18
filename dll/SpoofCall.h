#include <type_traits>
#include <winscard.h>
#include <Psapi.h>
#include "safecall.h"
#include "EncStr.h"
#include <string>

namespace Util {

	inline BOOLEAN MaskCompare(PVOID buffer, LPCSTR pattern, LPCSTR mask) {
		for (auto b = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++b) {
			if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *b) {
				return FALSE;
			}
		}

		return TRUE;
	}

	inline PBYTE FindPattern(PVOID base, DWORD size, LPCSTR pattern, LPCSTR mask) {
		size -= static_cast<DWORD>(strlen(mask));
		for (auto i = 0UL; i < size; ++i) {
			auto addr = reinterpret_cast<PBYTE>(base) + i;
			if (MaskCompare(addr, pattern, mask)) {
				return addr;
			}
		}
		return NULL;
	}

	inline PBYTE FindPatternPtr(const char* Pattern, const wchar_t* Module) {
		// find pattern utils
#define InRang(x, a, b) (x >= a && x <= b)
#define GetBits(x) (InRang(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
#define GetByt(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

	// get module range
		PBYTE ModuleStart = (PBYTE)LoadLibrary(Module);
		if (!ModuleStart)
			return nullptr;
		PIMAGE_NT_HEADERS NtHeader = ((PIMAGE_NT_HEADERS)(ModuleStart + ((PIMAGE_DOS_HEADER)ModuleStart)->e_lfanew));
		PBYTE             ModuleEnd = (PBYTE)(ModuleStart + NtHeader->OptionalHeader.SizeOfImage - 0x1000);
		ModuleStart += 0x1000;

		// scan pattern main
		PBYTE       FirstMatch = nullptr;
		const char* CurPatt = Pattern;
		for (; ModuleStart < ModuleEnd; ++ModuleStart) {
			bool SkipByte = (*CurPatt == '\?');
			if (SkipByte || *ModuleStart == GetByt(CurPatt)) {
				if (!FirstMatch)
					FirstMatch = ModuleStart;
				SkipByte ? CurPatt += 2 : CurPatt += 3;
				if (CurPatt[-1] == 0)
					return FirstMatch;
			}

			else if (FirstMatch) {
				ModuleStart = FirstMatch;
				FirstMatch = nullptr;
				CurPatt = Pattern;
			}
		}

		return nullptr;
	}

	inline BOOL Compare(CONST BYTE* pData, CONST BYTE* bMask, CONST CHAR* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return FALSE;
		return (*szMask) == NULL;
	}

	inline uintptr_t FindPatternForModule(uintptr_t dwModule, BYTE* bMask, std::string szMask)
	{
		PIMAGE_DOS_HEADER pImageDos = (PIMAGE_DOS_HEADER)dwModule;

		PIMAGE_NT_HEADERS32 pImageNt = (PIMAGE_NT_HEADERS32)(dwModule + pImageDos->e_lfanew);

		ULONG ImageLen = pImageNt->OptionalHeader.SizeOfImage;

		INT MaskLen = (INT)szMask.length();

		for (ULONG i = 0; i < ImageLen - MaskLen; i++)
		{
			if (IsBadHugeReadPtr((PVOID)(dwModule + i), 1) == 0)
			{
				if (Compare((BYTE*)(dwModule + i), bMask, szMask.c_str()))
				{
					return (uintptr_t)(dwModule + i);
				}
			}
		}

		return 0;
	}

}

namespace _SpoofCallInternal {

	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	inline Ret Wrapper(PVOID shell, Args... args) {
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}


	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(const void* shell, void* shell_param, First first, Second second,
				Third third, Fourth fourth, Pack... pack) -> Ret
		{
			return shellcode_stub_helper< Ret, First, Second, Third, Fourth, void*, void*, Pack... >(shell, first, second, third, fourth, shell_param, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};

	template <std::size_t Argc, typename>
	struct Remapper {
		template<typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
		static Ret Call(PVOID shell, PVOID shell_param, First first, Second second, Third third, Fourth fourth, Pack... pack) {
			return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID, Pack...>(shell, first, second, third, fourth, shell_param, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct Remapper<Argc, std::enable_if_t<Argc <= 4>> {
		template<typename Ret, typename First = PVOID, typename Second = PVOID, typename Third = PVOID, typename Fourth = PVOID>
		static Ret Call(PVOID shell, PVOID shell_param, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{}) {
			return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID>(shell, first, second, third, fourth, shell_param, nullptr);
		}
	};
}

template <typename Ret, typename... Args>
Ret SpoofCall(Ret(*fn)(Args...), Args... args) {
	static PVOID trampoline = nullptr;
	if (!trampoline) {

		trampoline = (PVOID)Util::FindPatternPtr(Enc("FF 23"), Enc(L"kguix64.dll"));
	//	MyTrace(L"trampoline 0x%I64X", trampoline);
		if (!trampoline) {
			MyTrace(L"Œ¥’“µΩ trampoline");
			ExitProcess(0);
		}
	}
	struct {
		PVOID Trampoline;
		PVOID Function;
		PVOID Reg;
	} params = {
		trampoline,
		reinterpret_cast<void*>(fn),
	};

	return _SpoofCallInternal::Remapper<sizeof...(Args), void>::template Call<Ret, Args...>(&_SpoofCallInternal::_spoofer_stub, &params, args...);
}

template<typename Ret = void, typename... Args>
__forceinline Ret VCall(PVOID Class, int Index, Args... AddArgs) {
	typedef Ret(__fastcall* __vtabecall)(PVOID, Args...);
	__vtabecall v = (__vtabecall)(*(PVOID**)Class)[Index];
	return SpoofCall(v, Class, AddArgs...);
}

template< typename ReturnType = void, typename... Args >
ReturnType CALL(uintptr_t ufn, Args... Arguments)
{
	return reinterpret_cast<ReturnType(*)(Args...)>(ufn)(Arguments...);
}