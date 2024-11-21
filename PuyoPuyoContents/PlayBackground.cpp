#include "aepch.h"
#include "PlayBackground.h"

APlayBackground::APlayBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("SoloBackground");
	Sr->SetSprite("LVBG");
	Sr->SetOrder(ERenderLayer::Background);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(EPivotType::TopLeft);
}

APlayBackground::~APlayBackground()
{
}


void APlayBackground::SetBackground(EPuyoGameMode _Mode, int _StageIndex)
{
	std::string SpriteName;
	switch (_Mode)
	{
	case EPuyoGameMode::Solo:
		Sr->SetSprite("LVBG", _StageIndex);
		break;
	case EPuyoGameMode::Versus:
		Sr->SetSprite("VSBG", _StageIndex);
		break;
	case EPuyoGameMode::Training:
		Sr->SetSprite("TRBG", _StageIndex);
		break;
	default:
		break;
	}
}

void APlayBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void APlayBackground::BeginPlay()
{
	Super::BeginPlay();
}
