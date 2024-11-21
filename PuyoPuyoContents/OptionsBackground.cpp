#include "aepch.h"
#include "OptionsBackground.h"

AOptionsBackground::AOptionsBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("OPTION.CNS.BMP");
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetOrder(ERenderLayer::Background);

}

AOptionsBackground::~AOptionsBackground()
{
}


void AOptionsBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOptionsBackground::BeginPlay()
{
	Super::BeginPlay();
}
