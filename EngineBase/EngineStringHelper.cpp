#include "aepch.h"
#include "EngineStringHelper.h"

std::string UEngineStringHelper::ToUpper(std::string_view _String)
{
	std::string Result = _String.data();
	Result.resize(_String.size());

	for (size_t i = 0; i < _String.size(); i++)
	{
		Result[i] = std::toupper(_String[i]);
	}

	return Result;
}

std::wstring UEngineStringHelper::AnsiToUnicode(std::string_view _String)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), static_cast<int>(_String.size()), nullptr, 0);

	if (0 == Size)
	{
		MSGASSERT("���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(_String));
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), static_cast<int>(_String.size()), Result.data(), Size);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar ���ڿ� ��ȯ�� �����߽��ϴ�" + std::string(_String));
		return L"";
	}

	return Result;
}

std::string UEngineStringHelper::UnicodeToAnsi(std::wstring_view _WString)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _WString.data(), static_cast<int>(_WString.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		MSGASSERT("���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _WString.data(), static_cast<int>(_WString.size()), Result.data(), Size, nullptr, nullptr);

	if (0 == Size)
	{
		MSGASSERT("WideCharToMultiByte ���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	return Result;
}

UEngineStringHelper::UEngineStringHelper()
{
}

UEngineStringHelper::~UEngineStringHelper()
{
}
