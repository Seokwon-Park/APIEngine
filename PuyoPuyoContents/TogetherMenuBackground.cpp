#include "aepch.h"
#include "TogetherMenuBackground.h"

ATogetherMenuBackground::ATogetherMenuBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("sel_9.cns.bmp");
	Sr->SetComponentScale({ 640,480 });
}

ATogetherMenuBackground::~ATogetherMenuBackground()
{
}


void ATogetherMenuBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ATogetherMenuBackground::BeginPlay()
{
	Super::BeginPlay();
}
