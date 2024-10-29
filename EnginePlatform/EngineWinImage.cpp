#include "aepch.h"
#include "EngineWinImage.h"


UEngineWinImage::UEngineWinImage()
	:/*Scale(FVector2D::ZERO),*/ ImageDC(nullptr), hBitmap(nullptr), Info(BITMAP())
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(HDC _DC)
{
	ImageDC = _DC;
}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage, FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("_TargetImage가 nullptr입니다.")
		return;
	}

	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC() , _Scale.iX(), _Scale.iY()));

	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());
	//HDC를 만들기만 해도 1,1 이미지와 연결한다.

	//SelectObject는 HDC에 원래 연결되어 있던 HBITMAP을 반환한다?
	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	// 그걸 지운다.
	DeleteObject(OldBitmap);

	hBitmap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitmap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _Target, const FTransform& _Transform)
{
	if (nullptr == _Target)
	{
		MSGASSERT("복사를 받을 대상이 존재하지 않습니다.");
		return;
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _Target->ImageDC;
	// HDC간의 Copy를 위한 몇가지 함수가 존재
	
	FVector2D LeftTop = _Transform.CenterLeftTop();
	FVector2D Scale = _Transform.Scale;

	BitBlt(
		TargetDC, 
		LeftTop.iX(), 
		LeftTop.iY(),
		Scale.iX(),
		Scale.iY(),
		CopyDC, 
		0,
		0,
		SRCCOPY);

}

