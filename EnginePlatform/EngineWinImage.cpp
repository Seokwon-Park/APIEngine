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
		MSGASSERT("_TargetImage�� nullptr�Դϴ�.")
		return;
	}

	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC() , _Scale.iX(), _Scale.iY()));

	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());
	//HDC�� ����⸸ �ص� 1,1 �̹����� �����Ѵ�.

	//SelectObject�� HDC�� ���� ����Ǿ� �ִ� HBITMAP�� ��ȯ�Ѵ�?
	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	// �װ� �����.
	DeleteObject(OldBitmap);

	hBitmap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitmap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _Target, const FTransform& _Transform)
{
	if (nullptr == _Target)
	{
		MSGASSERT("���縦 ���� ����� �������� �ʽ��ϴ�.");
		return;
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _Target->ImageDC;
	// HDC���� Copy�� ���� ��� �Լ��� ����
	
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

