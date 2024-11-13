#include "aepch.h"
#include "IntroBackground.h"

AIntroBackground::AIntroBackground()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize().Half());

	CKLogo = CreateDefaultSubobject<USpriteRendererComponent>("CompileKorea");
	CKLogo->SetSprite("AAA.CNS.BMP", 0);
	CKLogo->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());

	for (int i = 0; i < 2; i++)
	{
		Sr[i] = CreateDefaultSubobject<USpriteRendererComponent>("IntroBackground" + std::to_string(i));
		Sr[i]->SetOrder(-1);
		Sr[i]->SetSprite("OP_LINE.CNS.BMP", 0);
		Sr[i]->SetComponentLocation({ 0.0f, i*-UEngineAPICore::GetEngineWindow().GetWindowSize().Y });
		Sr[i]->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());


		//Sr[1] = CreateDefaultSubobject<USpriteRendererComponent>("IntroBackground2");
		//Sr[1]->SetOrder(-1);
		//Sr[1]->SetSprite("OP_LINE.CNS.BMP", 0);
		//Sr[1]->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	}
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
		Sr[i]->SetComponentLocation(Sr[i]->GetComponentLocation() + FVector2D::DOWN * _DeltaTime * 100.0f);
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
