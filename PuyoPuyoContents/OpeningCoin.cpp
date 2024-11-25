#include "aepch.h"
#include "OpeningCoin.h"

AOpeningCoin::AOpeningCoin()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Anim = CreateDefaultSubobject<UAnimatorComponent>("");

	Sr->SetSprite("OPCOIN");
	Sr->SetAnimator(Anim);
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
