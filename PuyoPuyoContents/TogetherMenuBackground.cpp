#include "aepch.h"
#include "TogetherMenuBackground.h"

ATogetherMenuBackground::ATogetherMenuBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("sel_9.cns.bmp");
	Sr->SetComponentScale({ 640,480 });
	Sr->SetOrder(ERenderLayer::Background);
	Sr->SetPivot(EPivotType::TopLeft);

}

ATogetherMenuBackground::~ATogetherMenuBackground()
{
}

void ATogetherMenuBackground::BeginPlay()
{
	Super::BeginPlay();
	

}



void ATogetherMenuBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

