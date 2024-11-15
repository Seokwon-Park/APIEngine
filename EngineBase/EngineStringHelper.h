#pragma once

// 설명 : 문자열 관련 static 함수
class UEngineStringHelper : public UObject
{
public:
	// constrcuter destructer
	~UEngineStringHelper();

	// delete Function
	UEngineStringHelper(const UEngineStringHelper& _Other) = delete;
	UEngineStringHelper(UEngineStringHelper&& _Other) noexcept = delete;
	UEngineStringHelper& operator=(const UEngineStringHelper& _Other) = delete;
	UEngineStringHelper& operator=(UEngineStringHelper&& _Other) noexcept = delete;

	static std::string ToUpper(std::string_view _String);
	static std::wstring AnsiToUnicode(std::string_view _String);
	static std::string UnicodeToAnsi(std::wstring_view _WString);
	
protected:

private:
	UEngineStringHelper();
};

