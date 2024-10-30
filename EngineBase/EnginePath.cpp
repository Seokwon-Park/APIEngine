#include "aepch.h"
#include "EnginePath.h"

UEnginePath::UEnginePath() 
	:Path(std::filesystem::current_path())
{

}

UEnginePath::UEnginePath(std::string_view _Path)
	:Path(_Path)
{

}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	:Path(_Path)
{

}

UEnginePath::~UEnginePath()
{
}

UEnginePath::UEnginePath(const UEnginePath& _Other)
{
	Path = _Other.Path;
}

std::string UEnginePath::ToString()
{
	return Path.string();
}

std::string UEnginePath::GetFileName()
{
	return Path.filename().string();
}

std::string UEnginePath::GetFileExtension()
{
	return Path.extension().string();
}

bool UEnginePath::IsFile()
{
	return false == IsDirectory();
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}



void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}


bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("설정된 경로가 폴더 경로가 아닙니다.");
		return false;
	}

	bool Result = false;
	std::filesystem::path CurPath;
	do
	{
		CurPath = DummyPath.Path;
		CurPath.append(_Path);
		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		DummyPath.MoveParent();
	} while (DummyPath.Path != DummyPath.Path.root_path());

	return Result;
}
