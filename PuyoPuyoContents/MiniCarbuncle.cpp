#include "aepch.h"
#include "MiniCarbuncle.h"

#include "StarParticle.h"

AMiniCarbuncle::AMiniCarbuncle()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PuyoSpriteRenderer");
	Anim = CreateDefaultSubobject<UAnimatorComponent>("PuyoAnimator");

	Sr->SetSprite("MiniCar", 0);
	Sr->SetComponentScale({ 32, 32 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopRight);
	Sr->SetOrder(ERenderLayer::Text);
	Sr->SetAnimator(Anim);
	// MainPuyoIdle Animation
	Anim->CreateAnimation("Idle", "MiniCar", { 0,1 }, { 0.1f, 0.1f }, true);
	Anim->CreateAnimation("Start", "MiniCar", { 0, 1,0,1,2,3,4,5,6,7,8,9,10 }, .2f, false);
	Anim->SetAnimationEvent("Start", 0, [this]() {Sr->SetComponentScale({ 32,32 }); });
	Anim->SetAnimationEvent("Start", 4, [this](){Sr->SetComponentScale({ 48,32 }); });
	Anim->SetAnimationEvent("Start", 6, [this](){Sr->SetComponentScale({ 40,32 }); });
	Anim->SetAnimationEvent("Start", 8, [this](){Sr->SetComponentScale({ 56,32 }); });
	Anim->SetAnimationEvent("Start", 11, [this](){Sr->SetComponentScale({ 32,32 }); });	

	
	Anim->ChangeAnimation("Start");


	// PuyoPlaceCompleteAnimation
	//Anim->CreateAnimation("PlaceComplete" + std::to_string(i), ColorSprites[i], { 0,16,0,17,0,16,0,17,0 }, .05f, false);
	//Anim->CreateAnimation("Boom" + std::to_string(i), ColorSprites[i], { 0,16,17,18,20,21,22 }, .05f, false);
	//Anim->SetAnimationEvent("PlaceComplete" + std::to_string(i), 8, std::bind(&APuyo::AnimationEndTrigger, this));
	//Anim->SetAnimationEvent("Boom" + std::to_string(i), 6, std::bind(&APuyo::AnimationEndTrigger, this));
	//Anim->CreateAnimation("PlaceComplete5", "GARBAGE", { 0, 0, 0, 0 }, 0.1f, false);
	//Anim->CreateAnimation("Boom5", "GARBAGE", 0, 3, .05f, false);
	//Anim->SetAnimationEvent("PlaceComplete5", 1, std::bind(&APuyo::AnimationEndTrigger, this));
	//Anim->SetAnimationEvent("Boom5", 3, std::bind(&APuyo::AnimationEndTrigger, this));
}

AMiniCarbuncle::~AMiniCarbuncle()
{
}


void AMiniCarbuncle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AMiniCarbuncle::BeginPlay()
{
	Super::BeginPlay();
	Anim->SetAnimationEvent("Start", 12, [this]()
		{
			UAudioManager::SoundPlay("StartPistol.wav");
			Anim->ChangeAnimation("Idle");
			AStarParticle* Particle = GetWorld()->SpawnActor<AStarParticle>();
			Particle->Init(GetActorLocation());
			Event();
		}
	);
}
