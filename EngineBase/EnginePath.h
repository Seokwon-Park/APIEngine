#pragma once
#include <filesystem>

// 설명 :
class UEnginePath : public UObject
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	// delete Function
	UEnginePath(const UEnginePath& _Other);
	UEnginePath(UEnginePath&& _Other) noexcept= delete;
	UEnginePath& operator=(const UEnginePath& _Other) = delete;
	UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	std::string ToString();
	std::string GetPathName();
	std::string GetFileExtension();
	bool IsFile();
	bool IsExists();
	bool IsDirectory();
	void MoveParent();
	void AppendDirectory(std::string_view _AppendName);

	//특정 디렉토리가 나올때까지 상위폴더로 이동
	bool MoveParentToDirectory(std::string_view _Path);
protected:
	std::filesystem::path Path;

private:

};

