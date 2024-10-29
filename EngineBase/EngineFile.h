#pragma once
#include <io.h>
#include "EnginePath.h"

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	UEngineFile();
	UEngineFile(std::string_view _Path);
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

	//파일에 _Ptr 쓰기
	void Write(const void* _Ptr, size_t _Size);
	//파일 읽기
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExist();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

