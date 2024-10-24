#pragma once
#include <io.h>

const int MAXPATH = 256;

class UEngineFile
{
public:
	UEngineFile();
	~UEngineFile();

	//���� ��θ� ����
	inline void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}

	//���Ͽ� _Ptr ����
	void Write(const void* _Ptr, size_t _Size);
	//���� �б�
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExist();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

