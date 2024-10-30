#include "aepch.h"
#include "EngineString.h"

std::string UEngineString::ToUpper(std::string_view _String)
{
	std::string Result = _String.data();
	Result.resize(_String.size());

	for (size_t i = 0; i < _String.size(); i++)
	{
		Result[i] = std::toupper(_String[i]);
	}

	return Result;
}

std::wstring UEngineString::AnsiToUnicode(std::string_view _Name)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Name.data(), static_cast<int>(_Name.size()), nullptr, 0);

	if (0 == Size)
	{
		MSGASSERT("���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(_Name));
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Name.data(), static_cast<int>(_Name.size()), Result.data(), Size);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar ���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(_Name));
		return L"";
	}

	return Result;
}

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}
