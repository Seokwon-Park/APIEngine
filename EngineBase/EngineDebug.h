#pragma once
#include <assert.h>

#define MSGASSERT(VALUE)	std::string ErrorText = VALUE; \
							MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK);\
							assert(false);

#define	DBGPRINT(VALUE)		std::string ResultText = VALUE + "\n";\
							OutputDebugStringA(ResultText.c_str());