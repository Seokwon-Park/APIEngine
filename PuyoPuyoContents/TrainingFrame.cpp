#include "aepch.h"
#include "TrainingFrame.h"

ATrainingFrame::ATrainingFrame()
{
	Sr1 = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr2 = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr1->SetSprite("TOKO_1A.CNS.BMP");
	Sr1->SetComponentScale({ 640, 480 });
	Sr1->SetPivot(EPivotType::TopLeft);
	Sr1->SetRemoveBackground(true);
	Sr1->SetOrder(ERenderLayer::Frame);


	Sr2->SetSprite("TOKO_2A.CNS.BMP");
	Sr2->SetRemoveBackground(true);
	Sr2->SetRemoveColor({ 64,64 });
	Sr2->SetComponentScale({ 640, 480 });
	Sr2->SetPivot(EPivotType::TopLeft);
	Sr2->SetRemoveBackground(true);
	Sr2->SetOrder(ERenderLayer::Frame);
}

ATrainingFrame::~ATrainingFrame()
{
}


void ATrainingFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ATrainingFrame::BeginPlay()
{
	Super::BeginPlay();
}
