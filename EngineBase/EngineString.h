#pragma once

// 설명 : 문자열 관련 static 함수
class UEngineString
{
public:
	// constrcuter destructer
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	static std::string ToUpper(std::string_view _String);
	static std::wstring AnsiToUnicode(std::string_view _String);
	static std::string UnicodeToAnsi(std::wstring_view _WString);
	
protected:

private:
	UEngineString();

};

