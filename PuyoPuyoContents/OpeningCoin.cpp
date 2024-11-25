#include "aepch.h"
#include "OpeningCoin.h"

AOpeningCoin::AOpeningCoin()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Anim = CreateDefaultSubobject<UAnimatorComponent>("");

	Sr->SetSprite("OPCOIN");
	Sr->SetComponentScale({ 224,224 });
	Sr->SetRemoveBackground(true);
	Sr->SetAnimator(Anim);
	//Anim->CreateAnimation("Idle", 0,0,
	Anim->CreateAnimation("Rotate","OPCOIN",{ 0, 1, 4, 5, 9, 8, 10,2,3,5,6,7}, 0.05f);
	Anim->SetAnimationEvent("Rotate", 0, [this]() {Sr->SetComponentScale({224,224}); });
	Anim->SetAnimationEvent("Rotate", 1, [this]() {Sr->SetComponentScale({160,224}); });
	Anim->SetAnimationEvent("Rotate", 2, [this]() {Sr->SetComponentScale({96,224}); });
	Anim->SetAnimationEvent("Rotate", 3, [this]() {Sr->SetComponentScale({32,224}); });
	Anim->SetAnimationEvent("Rotate", 4, [this]() {Sr->SetComponentScale({96,224}); });
	Anim->SetAnimationEvent("Rotate", 5, [this]() {Sr->SetComponentScale({160,224}); });
	Anim->SetAnimationEvent("Rotate", 6, [this]() {Sr->SetComponentScale({224,224}); });
	Anim->SetAnimationEvent("Rotate", 7, [this]() {Sr->SetComponentScale({160,224}); });
	Anim->SetAnimationEvent("Rotate", 8, [this]() {Sr->SetComponentScale({96,224}); });
	Anim->SetAnimationEvent("Rotate", 9, [this]() {Sr->SetComponentScale({32,224}); });
	Anim->SetAnimationEvent("Rotate", 10, [this]() {Sr->SetComponentScale({96,224}); });
	Anim->ChangeAnimation("Rotate");
	//Anim->CreateAnimation("RotateSlow", {})
}

AOpeningCoin::~AOpeningCoin()
{
}


void AOpeningCoin::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOpeningCoin::BeginPlay()
{
	Super::BeginPlay();
}
