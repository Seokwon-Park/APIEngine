#include "aepch.h"
#include "Puyo.h"

APuyo::APuyo()
	: IsAnimationEnd(false), IsDropComplete(false), Color(Red), SpriteIndex(0)
{
	SetActorLocation({ 48, 48 });
	SetActorScale({ 32, 32 });

	Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	Animator = CreateDefaultSubObject<UAnimatorComponent>();
	ColorSprites.push_back("PUYO_R.CNS.BMP");
	ColorSprites.push_back("PUYO_G.CNS.BMP");
	ColorSprites.push_back("PUYO_B.CNS.BMP");
	ColorSprites.push_back("PUYO_P.CNS.BMP");
	ColorSprites.push_back("PUYO_Y.CNS.BMP");
	Sr->SetSprite("PUYO_R.CNS.BMP", 0);
	Sr->SetComponentScale({ 32, 32 });
	// MainPuyoIdle Animation
	for (int i = 0; i < ColorSprites.size(); i++)
	{
		Animator->CreateAnimation("AxisPuyoIdle" + std::to_string(i), ColorSprites[i], { 0,19 }, .1f);
	}

	// PuyoPlaceCompleteAnimation
	for (int i = 0; i < ColorSprites.size(); i++)
	{
		Animator->CreateAnimation("PlaceComplete" + std::to_string(i), ColorSprites[i], { 0,16,0,17,0,16,0,17,0 }, .1f, false);
		Animator->SetAnimationEvent("PlaceComplete" + std::to_string(i), 8, std::bind(&APuyo::AnimationEndTrigger, this));
	}
	/*Animator->CreateAnimation("DropComplete0", "PUYO_R.CNS.BMP", { 0,16,0,17,0,16,0,17,0 }, .1f, false);
	Animator->CreateAnimation("DropComplete1", "PUYO_G.CNS.BMP", { 0,16,0,17,0,16,0,17,0 }, .1f, false);
	Animator->CreateAnimation("DropComplete2", "PUYO_B.CNS.BMP", { 0,16,0,17,0,16,0,17,0 }, .1f, false);
	Animator->CreateAnimation("DropComplete3", "PUYO_Y.CNS.BMP", { 0,16,0,17,0,16,0,17,0 }, .1f, false);
	Animator->CreateAnimation("DropComplete4", "PUYO_P.CNS.BMP", { 0,16,0,17,0,16,0,17,0 }, .1f, false);*/
	//Animator->ChangeAnimation("Test");
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

void APuyo::SetupPuyo(FVector2D _Location, int _Color)
{
	SetActorLocation(_Location);
	Color = _Color;
	Sr->SetSprite(ColorSprites[_Color], 0);
}

void APuyo::SetSprite(int _Index)
{
	Animator->CancelAnimation();
	Sr->SetSprite(ColorSprites[Color], _Index);
}

void APuyo::PlayAnimation(std::string _Name)
{
	IsAnimationEnd = false;
	Animator->ChangeAnimation(_Name + std::to_string(Color));
}
