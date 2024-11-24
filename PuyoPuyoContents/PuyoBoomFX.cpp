#include "aepch.h"
#include "PuyoBoomFX.h"
#include <EngineCore/ImageManager.h>

APuyoBoomFX::APuyoBoomFX()
{
	ColorSprites.push_back("PUYOBOOMR");
	ColorSprites.push_back("PUYOBOOMG");
	ColorSprites.push_back("PUYOBOOMB");
	ColorSprites.push_back("PUYOBOOMP");
	ColorSprites.push_back("PUYOBOOMY");
	Particles.resize(4, nullptr);
	A.resize(4);
	Dir.resize(4);
	Top.resize(4);
	XYStart.resize(4);
	for (int i = 0; i < 4; i++)
	{
		Particles[i] = CreateDefaultSubobject<USpriteRendererComponent>("BoomParticles" + std::to_string(i));
		Particles[i]->SetSprite("PuyoBoomR", 1);
		Particles[i]->SetComponentLocation({ -12 + 8 * i, 0 });
		Particles[i]->SetComponentScale({ 16,16 });
		Particles[i]->SetRemoveBackground(true);
		Particles[i]->SetActive(false);
	}

	Dir[0] = { -32, -144 };
	Dir[1] = { -16, -144 };
	Dir[2] = { 16, -144 };
	Dir[3] = { 32, -144 };

	XYStart[0] = { -12,0 };
	XYStart[1] = { -4,0 };
	XYStart[2] = { 4,0 };
	XYStart[3] = { 12,0 };
}

APuyoBoomFX::~APuyoBoomFX()
{
}

void APuyoBoomFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FXDelay -= _DeltaTime;
	if (FXDelay > 0.0f) return;
	FXTimer += _DeltaTime;
	for (int i = 0; i < 4; i++)
	{
		FVector2D Loc = Particles[i]->GetComponentLocation();

		Dir[i].Y += 0.1f;

		Particles[i]->SetSprite(SpriteName, 1);
		Particles[i]->SetActive(true);
		Particles[i]->SetRemoveColor(FIntPoint::ZERO);
		Particles[i]->SetComponentLocation(Loc + Dir[i] * _DeltaTime);
	}

	if (FXTimer >= 0.25f)
	{
		UEngineSprite::USpriteData CurData = UImageManager::GetInstance().FindSprite(SpriteName)->GetSpriteData(0);
		for (int i = 0; i < 4; i++)
		{
			Particles[i]->SetSprite(SpriteName, 0);
			Particles[i]->SetComponentScale(CurData.Transform.Scale);
		}
	}

	if (FXTimer >= 0.5f)
	{
		UEngineSprite::USpriteData CurData = UImageManager::GetInstance().FindSprite(SpriteName)->GetSpriteData(1);
		for (int i = 0; i < 4; i++)
		{
			Particles[i]->SetSprite(SpriteName, 1);
			Particles[i]->SetComponentScale(CurData.Transform.Scale);
		}
	}
	if (FXTimer >= 0.75f)
	{
		UEngineSprite::USpriteData CurData = UImageManager::GetInstance().FindSprite(SpriteName)->GetSpriteData(2);

		for (int i = 0; i < 4; i++)
		{
			Particles[i]->SetSprite(SpriteName, 2);
			Particles[i]->SetComponentScale(CurData.Transform.Scale);
		}
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	FVector2D Loc = Particles[i]->GetComponentLocation();
	//	Particles[i]->SetSprite("PuyoBoomR");
	//	Particles[i]->SetComponentLocation(Loc + DWDir[i] * _DeltaTime * 30);
	//	Particles[i]->SetComponentScale({ 32,32 });
	//	Particles[i]->SetRemoveBackground(true);
	//}
	if (FXTimer >= 1.5f)
	{
		this->Destroy();
	}
}

void APuyoBoomFX::SetupBoomFX(EPuyoColor _Color, float _Delay)
{
	SpriteName = ColorSprites[static_cast<int>(_Color)];
	FXDelay = _Delay;

}

void APuyoBoomFX::BeginPlay()
{
	Super::BeginPlay();
}
