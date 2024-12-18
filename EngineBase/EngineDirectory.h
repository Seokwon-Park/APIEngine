#pragma once
#include "EnginePath.h"

// ���� :
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(std::string_view _Path);
	~UEngineDirectory();

	// delete Function
	UEngineDirectory(const UEngineDirectory& _Other) = delete;
	UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	std::vector<class UEngineFile> GetAllFile(bool _IsRecur = true);
protected:

private:
	void GetAllFileRecur(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result);

};

