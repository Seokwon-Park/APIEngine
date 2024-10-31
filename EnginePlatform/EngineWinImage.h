#pragma once
#include <EngineBase/Object.h>

// Ό³Έν :
class UEngineWinImage : public UObject
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

	inline HDC GetDC() const
	{
		return ImageDC;
	}

	void Create(HDC _DC);
	void Create(UEngineWinImage* _TargetImage, FVector2D _ScaleS);
	void CopyToBit(UEngineWinImage* _Dst, const FTransform& _Transform);
	void CopyToTransparent(UEngineWinImage* _TargetImage, const FTransform& _TargetTransform,
		const FTransform& _CopyTransform, UColor _Color = UColor(255,0,255,0));
	void Load(UEngineWinImage* _TargetImage, std::string_view _Path);

	FVector2D GetImageSize()
	{
		return { Info.bmWidth, Info.bmHeight };
	}
protected:

private:
	//FVector2D Scale;
	HDC ImageDC;
	HBITMAP hBitmap;
	BITMAP Info;
};

