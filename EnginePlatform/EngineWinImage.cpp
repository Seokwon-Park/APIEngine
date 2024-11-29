#include "aepch.h"
#include "EngineWinImage.h"
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineStringHelper.h>

#include <objidl.h>
#include <gdiplus.h>

#pragma comment(lib, "Msimg32.lib") // bmp
#pragma comment(lib, "Gdiplus.lib") // png

const std::string PngExt = ".PNG";
const std::string BmpExt = ".BMP";


UEngineWinImage::UEngineWinImage()
	: ImageDC(nullptr), hBitmap(nullptr), Info(BITMAP())
{
}

UEngineWinImage::~UEngineWinImage()
{
	if (nullptr != hBitmap)
	{
		DeleteObject(hBitmap);
		hBitmap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
}

void UEngineWinImage::Create(HDC _DC)
{
	ImageDC = _DC;
}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage, FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("_TargetImage�� nullptr�Դϴ�.");
		return;
	}

	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));

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

void UEngineWinImage::ChangeToGrayscale()
{
	// ��Ʈ�� ���� ��������
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    // ��Ʈ�� ������ ������ ���� ����ü �غ�
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bmp.bmWidth;
    bmi.bmiHeader.biHeight = -bmp.bmHeight; // ���� ������ ���� ����
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = bmp.bmBitsPixel; // 24��Ʈ(RGB)
    bmi.bmiHeader.biCompression = BI_RGB;

    // �ȼ� �����͸� ������ �޸� �Ҵ�
    int pixelArraySize = bmp.bmWidthBytes* bmp.bmHeight;
    BYTE* pPixels = new BYTE[pixelArraySize];

    // ��Ʈ�� �����͸� ��������
    if (GetDIBits(ImageDC, hBitmap, 0, bmp.bmHeight, pPixels, &bmi, DIB_RGB_COLORS)) 
	{
		for (int y = 0; y < bmp.bmHeight; ++y) 
		{
			for (int x = 0; x < bmp.bmWidthBytes; x+=4)
			{
				int index = y * bmp.bmWidthBytes + x;
				BYTE gray = static_cast<BYTE>(
					0.333 * pPixels[index] +
					0.333 * pPixels[index + 1] +
					0.334 * pPixels[index + 2]);
				pPixels[index] =gray;
				pPixels[index + 1] = gray;
				pPixels[index + 2] = gray;
				pPixels[index + 3] = 0;
			}
		}
		SetDIBits(ImageDC, hBitmap, 0, bmp.bmHeight, pPixels, &bmi, DIB_RGB_COLORS);
    }

    // �޸� ����
    delete[] pPixels;
}

void UEngineWinImage::ChangeToSepia(float _Alpha)
{
	// ��Ʈ�� ���� ��������
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	// ��Ʈ�� ������ ������ ���� ����ü �غ�
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bmp.bmWidth;
	bmi.bmiHeader.biHeight = -bmp.bmHeight; // ���� ������ ���� ����
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = bmp.bmBitsPixel; // 24��Ʈ(RGB)
	bmi.bmiHeader.biCompression = BI_RGB;

	// �ȼ� �����͸� ������ �޸� �Ҵ�
	int pixelArraySize = bmp.bmWidthBytes * bmp.bmHeight;
	BYTE* pPixels = new BYTE[pixelArraySize];

	// ��Ʈ�� �����͸� ��������
	if (GetDIBits(ImageDC, hBitmap, 0, bmp.bmHeight, pPixels, &bmi, DIB_RGB_COLORS))
	{
		for (int y = 0; y < bmp.bmHeight; ++y)
		{
			for (int x = 0; x < bmp.bmWidthBytes; x += 4)
			{
				int index = y * bmp.bmWidthBytes + x;
				float sepiaR = (pPixels[index+2] * 0.393f) + (pPixels[index + 1] * 0.769f) + (pPixels[index] * 0.189f);
				float sepiaG = (pPixels[index+2] * 0.349f) + (pPixels[index + 1] * 0.686f) + (pPixels[index] * 0.168f);
				float sepiaB = (pPixels[index+2] * 0.272f) + (pPixels[index + 1] * 0.534f) + (pPixels[index] * 0.131f);
				pPixels[index] = static_cast<BYTE>((1 - _Alpha) * pPixels[index] + _Alpha * FEngineMath::Min(sepiaB, 255.0f));
				pPixels[index + 1] = static_cast<BYTE>((1 - _Alpha) * pPixels[index+1] + _Alpha * FEngineMath::Min(sepiaG, 255.0f));
				pPixels[index + 2] = static_cast<BYTE>((1 - _Alpha) * pPixels[index+2] + _Alpha * FEngineMath::Min(sepiaR, 255.0f));
				pPixels[index + 3] = 0;
			}
		}
		SetDIBits(ImageDC, hBitmap, 0, bmp.bmHeight, pPixels, &bmi, DIB_RGB_COLORS);
	}

	// �޸� ����
	delete[] pPixels;
}

void UEngineWinImage::InvertImage()
{
	FVector2D Scale = GetImageSize();

	BitBlt(
		ImageDC,
		0,
		0,
		Scale.iX(),
		Scale.iY(),
		ImageDC,
		0,
		0,
		NOTSRCCOPY);
}

void UEngineWinImage::CopyToTransparent(UEngineWinImage* _TargetImage, const FTransform& _TargetTransform,
	const FTransform& _CopyTransform, UColor _Color)
{
	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

	FVector2D LeftTop = _TargetTransform.CenterLeftTop();

	TransparentBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_TargetTransform.Scale.iX(),
		_TargetTransform.Scale.iY(),
		CopyDC,
		_CopyTransform.Location.iX(),
		_CopyTransform.Location.iY(),
		_CopyTransform.Scale.iX(),
		_CopyTransform.Scale.iY(),
		_Color.Color
	);
}

void UEngineWinImage::CopyToAlphaBlend(UEngineWinImage* _TargetImage, const FTransform& _RenderTransform,
	const FTransform& _CopyTransform, unsigned char _Alpha)
{
	BLENDFUNCTION BlendFunc;
	BlendFunc.BlendOp = AC_SRC_OVER;
	BlendFunc.BlendFlags = 0;
	BlendFunc.AlphaFormat = AC_SRC_ALPHA;
	BlendFunc.SourceConstantAlpha = _Alpha;

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;
	FVector2D LeftTop = _RenderTransform.CenterLeftTop();

	AlphaBlend(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTransform.Scale.iX(),
		_RenderTransform.Scale.iY(),
		CopyDC,
		_CopyTransform.Location.iX(),
		_CopyTransform.Location.iY(),
		_CopyTransform.Scale.iX(),
		_CopyTransform.Scale.iY(),
		BlendFunc
	);
}

void UEngineWinImage::Load(UEngineWinImage* _TargetImage, std::string_view _Path)
{
	UEnginePath Path = _Path;

	std::string Ext = UEngineStringHelper::ToUpper(Path.GetFileExtension());

	HBITMAP NewBitmap = nullptr;

	if (PngExt == Ext)
	{
		ULONG_PTR GdiplusToken = 0;

		Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&GdiplusToken, &StartupInput, nullptr);

		std::wstring WidePath = UEngineStringHelper::AnsiToUnicode(_Path);

		// FromFile() returns new => �Ҵ� ���� �ʿ�
		Gdiplus::Image* GdiplusImage = Gdiplus::Image::FromFile(WidePath.c_str());

		// Clone() returns new => �Ҵ� ���� �ʿ�
		Gdiplus::Bitmap* GdiplusBitmap = reinterpret_cast<Gdiplus::Bitmap*>(GdiplusImage->Clone());
		Gdiplus::Status Stat = GdiplusBitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &NewBitmap);

		if (Gdiplus::Status::Ok != Stat)
		{
			MSGASSERT(PngExt + " �̹��� �ε忡 �����߽��ϴ�." + std::string(_Path));
			return;
		}

		delete GdiplusBitmap;
		delete GdiplusImage;
	}
	else if (BmpExt == Ext)
	{
		HANDLE NewHandle = LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		NewBitmap = reinterpret_cast<HBITMAP>(NewHandle);
	}
	else
	{
		MSGASSERT("�̹��� ������ �ƴմϴ�.");
	}

	if (nullptr == NewBitmap)
	{
		MSGASSERT("�̹��� �ε��� �����߽��ϴ�.");
		return;
	}

	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());
	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));

	if (nullptr != OldBitmap)
	{
		DeleteObject(OldBitmap);
	}

	hBitmap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitmap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CreateBitmap32(UEngineWinImage* _TargetImage, FVector2D _Scale, UColor _Color)
{
	HBITMAP NewBitmap = nullptr;

	// �ȼ� ������ ������
	DWORD* PixelData = new DWORD[_Scale.iX()*_Scale.iY()];

	//DWORD color = (255 << 24) | 0x000000; // ARGB: ���� ���� ������
	DWORD color = _Color; // ARGB: ���� ���� ������

	for (int i = 0; i < _Scale.iX() * _Scale.iY(); ++i) {
		PixelData[i] = color;
	}

	// 32��Ʈ ��Ʈ�� ����
	NewBitmap = CreateBitmap(_Scale.iX(), _Scale.iY(), 1, 32, PixelData);
	delete[] PixelData;

	if (nullptr == NewBitmap)
	{
		MSGASSERT("�̹��� ������ �����߽��ϴ�.");
		return;
	}


	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());
	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));

	if (nullptr != OldBitmap)
	{
		DeleteObject(OldBitmap);
	}


	hBitmap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitmap, sizeof(BITMAP), &Info);

}

UColor UEngineWinImage::GetPixelColor(FIntPoint _Point, UColor _DefaultColor)
{
	if (0 > _Point.X) { return _DefaultColor; }
	if (0 > _Point.Y) { return _DefaultColor; }
	if (Info.bmWidth <= _Point.X) { return _DefaultColor; }
	if (Info.bmHeight <= _Point.Y) { return _DefaultColor; }

	UColor ResultColor = ::GetPixel(ImageDC, _Point.X, _Point.Y);
	return ResultColor;
}

