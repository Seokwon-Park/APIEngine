#include "aepch.h"
#include "TrainingBackground.h"

ATrainingBackground::ATrainingBackground()
{
	FVector2D WindowSize = UEngineAPICore::GetEngineWindow().GetWindowSize();
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("TOKO_BG2.CNS.BMP");
	Sr->SetComponentScale(WindowSize);
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetOrder(ERenderLayer::BACKGROUND);
}

ATrainingBackground::~ATrainingBackground()
{
}


void ATrainingBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ATrainingBackground::BeginPlay()
{
	Super::BeginPlay();
}
