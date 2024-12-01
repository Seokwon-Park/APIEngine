#include "aepch.h"
#include "GameOverPuyo.h"

AGameOverPuyo::AGameOverPuyo()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Anim = CreateDefaultSubobject<UAnimatorComponent>("");
	Sr->SetAnimator(Anim);
	Sr->SetSprite("GameOverPuyo");
	Sr->SetComponentScale({ 224, 144 });
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetRemoveBackground(true);
}

AGameOverPuyo::~AGameOverPuyo()
{
}

void AGameOverPuyo::BeginPlay()
{
	Super::BeginPlay();
}

void AGameOverPuyo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
