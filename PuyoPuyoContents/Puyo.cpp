#include "aepch.h"
#include "Puyo.h"

APuyo::APuyo()
	:Color(Red)
{
	SetActorLocation({ 48, 48 });
	SetActorScale({ 32, 32 });

	Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	Sr->SetSprite("PUYO_R.CNS.BMP", 0);
	Sr->SetComponentScale({ 32, 32 });
	//SetSprite("test.png");
}

APuyo::~APuyo()
{
}

void APuyo::BeginPlay()
{
	Super::BeginPlay();
}

void APuyo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
