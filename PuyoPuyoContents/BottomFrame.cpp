#include "aepch.h"
#include "BottomFrame.h"

ABottomFrame::ABottomFrame()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("LVBOTFR");
	Sr->SetComponentScale({ 32, 64 });
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetOrder(ERenderLayer::BottomCover);
}

ABottomFrame::~ABottomFrame()
{
}

void ABottomFrame::SetFrame(EPuyoGameMode _Mode, int _StageIndex)
{
	switch (_Mode)
	{
	case EPuyoGameMode::Solo:
		Sr->SetSprite("LVBOTFR", _StageIndex);
		break;
	case EPuyoGameMode::Versus:
		Sr->SetSprite("VSBOTFR", _StageIndex);
		break;
	case EPuyoGameMode::Training:
		Sr->SetSprite("TRBOTFR1", _StageIndex);
		Sr->SetSprite("TRBOTFR2", _StageIndex);
		break;
	default:
		break;
	}
}

void ABottomFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABottomFrame::BeginPlay()
{
	Super::BeginPlay();
}

