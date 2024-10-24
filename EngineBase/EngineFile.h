#pragma once
#include <io.h>

const int MAXPATH = 256;

class UEngineFile
{
public:
	UEngineFile();
	~UEngineFile();

	//파일 경로를 설정
	inline void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}

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

