#pragma once
#include <iostream>
#include <tuple>
#include "pch.h"
class MyCallFun
{
public:
	static void test();
	 template<typename FuncPtr, typename ...Args>
	 static auto call_function(FuncPtr func_ptr, Args ...args);
};

