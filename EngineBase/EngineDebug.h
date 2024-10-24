#pragma once
#include <assert.h>

#define MSGASSERT(VALUE)	std::string ErrorText = VALUE; \
							MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);\
							assert(false);
