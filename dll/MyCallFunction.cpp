#include "MyCallFunction.h"

template <typename FuncPtr, typename... Args>

auto MyCallFun::call_function(FuncPtr func_ptr, Args... args) {
    return (*func_ptr)(args...);
}

int add(int a, int b)
{
    return a + b;
}
void MyCallFun::test()
{
    auto ptr = &add;
    auto result = call_function(ptr, 3, 10);
    //MyTrace(L"result: %d", result);
}