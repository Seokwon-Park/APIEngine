#include "aepch.h"
#include "Puyo.h"

APuyo::APuyo()
	: IsAnimationEnd(false), IsDropComplete(false), Color(EPuyoColor::Red), SpriteIndex(0)
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PuyoSpriteRenderer");
	Animator = CreateDefaultSubobject<UAnimatorComponent>("PuyoAnimator");
	ColorSprites.push_back("PUYO_R.CNS.BMP");
	ColorSprites.push_back("PUYO_G.CNS.BMP");
	ColorSprites.push_back("PUYO_B.CNS.BMP");
	ColorSprites.push_back("PUYO_P.CNS.BMP");
	ColorSprites.push_back("PUYO_Y.CNS.BMP");
	Sr->SetSprite("PUYO_R.CNS.BMP", 0);
	Sr->SetComponentScale({ 32, 32 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetAnimator(Animator);
	// MainPuyoIdle Animation
	for (int i = 0; i < ColorSprites.size(); i++)
	{
		Animator->CreateAnimation("AxisPuyoIdle" + std::to_string(i), ColorSprites[i], { 0,19 }, .1f);
	}
	Animator->CreateAnimation("AxisPuyoIdle5", "GARBAGE", { 0, 0 }, .1f);


	// PuyoPlaceCompleteAnimation
	for (int i = 0; i < ColorSprites.size(); i++)
	{
		Animator->CreateAnimation("PlaceComplete" + std::to_string(i), ColorSprites[i], { 0,16,0,17,0,16,0,17,0 }, .05f, false);
		Animator->CreateAnimation("Boom" + std::to_string(i), ColorSprites[i], { 0,16,17,18,20,21,22 }, .05f, false);
		Animator->CreateAnimation("CountDown" + std::to_string(i), ColorSprites[i], { 0,16,0,17,0,16,0,17,0, 0,16,17,18,20,21,22 }, .05f, false);
		Animator->SetAnimationEvent("PlaceComplete" + std::to_string(i), 8, std::bind(&APuyo::AnimationEndTrigger, this));
		Animator->SetAnimationEvent("Boom" + std::to_string(i), 6, std::bind(&APuyo::AnimationEndTrigger, this));
		Animator->SetAnimationEvent("CountDown" + std::to_string(i), 15,
			[=]()
			{
				UAudioManager::SoundPlay(DestroySound[i+1]);
				SetActive(false);
				Animator->ChangeAnimation("AxisPuyoIdle" + std::to_string(i));
			});
	}
	Animator->CreateAnimation("PlaceComplete5", "GARBAGE", { 0, 0, 0, 0 }, 0.1f, false);
	Animator->CreateAnimation("Boom5", "GARBAGE", 0, 3, .05f, false);
	Animator->SetAnimationEvent("PlaceComplete5", 1, std::bind(&APuyo::AnimationEndTrigger, this));
	Animator->SetAnimationEvent("Boom5", 3, std::bind(&APuyo::AnimationEndTrigger, this));



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

void APuyo::SetupPuyo(FVector2D _Location, EPuyoColor _Color)
{
	SetActorLocation(_Location);
	Color = _Color;
	ColorIndex = static_cast<int>(_Color);
	if (ColorIndex < ColorSprites.size())
	{
		Sr->SetSprite(ColorSprites[ColorIndex], 0);
	}
	else
	{
		Sr->SetSprite("GARBAGE", 0);
	}
	Sr->SetRemoveBackground(true);
}


void APuyo::SetSprite(int _Index)
{
	Animator->CancelAnimation();
	SpriteIndex = _Index;
	if (ColorIndex < ColorSprites.size())
	{
		Sr->SetSprite(ColorSprites[ColorIndex], _Index);
	}
}

void APuyo::PlayAnimation(std::string _Name)
{
	IsAnimationEnd = false;
	Animator->ChangeAnimation(_Name + std::to_string(ColorIndex));
}
