#include "aepch.h"
#include "PuyoWarn.h"
#include <EngineCore/ImageManager.h>

APuyoWarn::APuyoWarn()
{
	// 예고 뿌요
	Warnings.resize(6, nullptr);
	for (int i = 0; i < 6; i++)
	{
		Warnings[i] = CreateDefaultSubobject<USpriteRendererComponent>("Warn" + std::to_string(i));
		Warnings[i]->SetSprite("Warning");
		Warnings[i]->SetActive(false);
		Warnings[i]->SetComponentLocation(FVector2D(0.0f, 32.0f));
		Warnings[i]->SetRemoveBackground(true);
		Warnings[i]->SetOrder(ERenderLayer::Warn);
	}
}

APuyoWarn::~APuyoWarn()
{
}


void APuyoWarn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Timer += _DeltaTime;
	switch (State)
	{
	case EWarningState::Idle:
		break;
	case EWarningState::Gathering:
		for (int i = 0; i < 6; i++)
		{
			Warnings[i]->SetComponentLocation(FVector2D::Lerp(StartPos[i], TargetPos[i], Timer / Duration));
		}
		if (Timer >= Duration)
			State = EWarningState::Calculate;
		break;
	case EWarningState::Calculate:
	{
		for (int i = 0; i < 6; i++)
		{
			Warnings[i]->SetActive(false);
		}
		int CurIndex = 0;
		int Temp = WarnNum;
		FVector2D CurLocation = FVector2D(0.0f, 32.0f);
		// i = WarUnitIndex ?머라할지 모르겠다 코드 복잡해짐.
		for (int i = 5; i >= 0; i--)
		{
			if (CalcWarn(i, CurLocation, CurIndex, Temp))
			{
				break;
			}
		}
		for (int i = 0; i < 6; i++)
		{
			StartPos[i] = FVector2D(96.0f, 32.0f);
		}
		Timer = 0.0f;
		State = EWarningState::Returning;
		break;
	}
	case EWarningState::Returning:
		for (int i = 0; i < 6; i++)
		{
			Warnings[i]->SetComponentLocation(FVector2D::Lerp(StartPos[i], TargetPos[i], Timer / Duration));
		}
		if (Timer >= Duration)
			State = EWarningState::Idle;
		break;
	default:
		break;
	}
}
void APuyoWarn::BeginPlay()
{
	Super::BeginPlay();
}

void APuyoWarn::UpdateWarning()
{
	for (int i = 0; i < 6; i++)
	{
		StartPos[i] = Warnings[i]->GetComponentLocation();
		TargetPos[i] = FVector2D(96.0f, 32.0f);
	}
	Timer = 0.0f;
	State = EWarningState::Gathering;


}

// 만약 6자리가 다찼으면 true를 리턴한다.
bool APuyoWarn::CalcWarn(const int _SpriteIndex, FVector2D& _Offset, int& _CurIndex, int& _Left)
{
	while (_Left >= WarnUnit[_SpriteIndex])
	{
		UEngineSprite::USpriteData CurData = UImageManager::GetInstance().FindSprite("Warning")->GetSpriteData(_SpriteIndex);
		Warnings[_CurIndex]->SetSprite("Warning", _SpriteIndex);
		Warnings[_CurIndex]->SetPivot(EPivotType::BottomLeft);
		//Warnings[_CurIndex]->SetComponentLocation(_Offset);
		Warnings[_CurIndex]->SetComponentScale(CurData.Transform.Scale);
		Warnings[_CurIndex]->SetActive(true);
		TargetPos[_CurIndex] = _Offset;
		_Left -= WarnUnit[_SpriteIndex];
		_CurIndex++;
		_Offset += FVector2D(CurData.Transform.Scale.X, 0.0f);
		if (_CurIndex == 6)
		{
			return true;
			break;
		}
	}
	return false;

}