#include "aepch.h"
#include "IntroBackground.h"

AIntroBackground::AIntroBackground()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize() / 2);
	SetActorScale({ 100,100 });

	Sr[0] = CreateDefaultSubobject<USpriteRendererComponent>("IntroBackground");
	Sr[0]->SetOrder(-1);
	Sr[0]->SetSprite("OP_LINE.CNS.BMP", 0);
	Sr[0]->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());

	Sr[1] = CreateDefaultSubobject<USpriteRendererComponent>("IntroBackground2");
	Sr[1]->SetOrder(-1);
	Sr[1]->SetSprite("OP_LINE.CNS.BMP", 0);
	Sr[1]->SetComponentLocation({ Sr[1]->GetComponentLocation().X, -UEngineAPICore::GetEngineWindow().GetWindowSize().Y });
	Sr[1]->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	//Animator->CreateAnimation("BgAnim1", "OP_LINE.CNS.BMP", )

}

AIntroBackground::~AIntroBackground()
{
}

void AIntroBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (int i = 0; i < 2; i++)
	{
		Sr[i]->SetComponentLocation(Sr[i]->GetComponentLocation() + FVector2D::DOWN);
		if (Sr[i]->GetComponentLocation().Y > UEngineAPICore::GetEngineWindow().GetWindowSize().Y)
		{
			Sr[i]->SetComponentLocation({ Sr[i]->GetComponentLocation().X, Sr[i]->GetComponentLocation().Y - UEngineAPICore::GetEngineWindow().GetWindowSize().Y*2});
		}
	}


}

void AIntroBackground::BeginPlay()
{
	Super::BeginPlay();
}
