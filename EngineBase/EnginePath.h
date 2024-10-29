#pragma once
#include <filesystem>

// ���� :
class UEnginePath
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
	bool IsExists();
	bool IsDirectory();
	bool IsFile();
	void MoveParent();

	//Ư�� ���丮�� ���ö����� ���������� �̵�
	bool MoveParentToDirectory(std::string_view _Path);
protected:
	std::filesystem::path Path;

private:

};

