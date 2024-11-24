#include "aepch.h"
#include "BottomBackground.h"

ABottomBackground::ABottomBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("SoloBackground");
	Sr->SetSprite("LVBOTBG");
	Sr->SetOrder(ERenderLayer::BottomBackground);
	Sr->SetComponentScale({192,64});
	Sr->SetPivot(EPivotType::TopLeft);
}

ABottomBackground::~ABottomBackground()
{
}

void ABottomBackground::BeginPlay()
{
	Super::BeginPlay();
}

void ABottomBackground::SetBackground(EPuyoGameMode _Mode, int _StageIndex, bool _IsLeft)
{
	switch (_Mode)
	{
	case EPuyoGameMode::Solo:
		Sr->SetSprite("LVBOTBG", _StageIndex);
		break;
	case EPuyoGameMode::Versus:
		Sr->SetSprite("VSBOTBG", _StageIndex);
		break;
	case EPuyoGameMode::Training:
		Sr->SetSprite("TRBOTBG", _StageIndex);
		break;
	default:
		break;
	}
}

void ABottomBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
