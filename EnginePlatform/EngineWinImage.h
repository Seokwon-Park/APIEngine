#pragma once

// Ό³Έν :
class UEngineWinImage
{
public:
	// constrcuter destructer
	UEngineWinImage();
	~UEngineWinImage();

	// delete Function
	UEngineWinImage(const UEngineWinImage& _Other) = delete;
	UEngineWinImage(UEngineWinImage&& _Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& _Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& _Other) noexcept = delete;

	HDC GetDC()
	{
		return ImageDC;
	}
	//void Create(std::string_view _Path);
	void Create(HDC _DC)
	{
		ImageDC = _DC;
	}

	void Create(UEngineWinImage* _TargetImage, FVector2D _ScaleS);

	void CopyToBit(UEngineWinImage* _Dst, const FTransform& _Transform);

protected:

private:
	//FVector2D Scale;
	HDC ImageDC;
	HBITMAP hBitmap;
	BITMAP Info;
};

