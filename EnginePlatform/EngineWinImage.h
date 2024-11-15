#pragma once

// Ό³Έν :
class UEngineWinImage : public UEngineResource
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

	inline HDC GetDC() const { return ImageDC; }
	inline FVector2D GetImageSize() const { return { Info.bmWidth, Info.bmHeight }; }

	void Create(HDC _DC);
	void Create(UEngineWinImage* _TargetImage, FVector2D _ScaleS);
	void CopyToBit(UEngineWinImage* _Dst, const FTransform& _Transform);
	void CopyToTransparent(UEngineWinImage* _TargetImage, const FTransform& _TargetTransform,
		const FTransform& _CopyTransform, UColor _Color = UColor(255, 0, 255, 0));
	void CopyToAlphaBlend(UEngineWinImage* _TargetImage,const FTransform& _RenderTrans,
		const FTransform& _LTImageTrans,unsigned char _Alpha);
	void Load(UEngineWinImage* _TargetImage, std::string_view _Path);
	UColor GetPixelColor(FIntPoint _Point, UColor _DefaultColor);
	void CreateBitmap32(UEngineWinImage* _TargetImage, FVector2D _Transform, UColor _Color = UColor(0,0,0,255));
protected:

private:
	//FVector2D Scale;
	HDC ImageDC;
	HBITMAP hBitmap;
	BITMAP Info;
};

