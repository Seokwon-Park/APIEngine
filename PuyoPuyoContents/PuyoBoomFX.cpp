#include "aepch.h"
#include "PuyoBoomFX.h"

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
		Particles[i]->SetSprite("PuyoBoomR");
		Particles[i]->SetComponentLocation({ -12 + 8 * i, 0 });
		Particles[i]->SetComponentScale({ 32,32 });
		Particles[i]->SetRemoveBackground(true);
	}

	Top[0] = { -128, -24 };
	Top[1] = { -16, -32 };
	Top[2] = { 16, -32 };
	Top[3] = { 128, -24 };

	XYStart[0] = { -12,0 };
	XYStart[1] = { -4,0 };
	XYStart[2] = { 4,0 };
	XYStart[3] = { 12,0 };

	for (int i = 0; i < 4; i++)
	{
		float X = (XYStart[i].X - Top[i].X);
		float Y = (XYStart[i].Y - Top[i].Y);
		A[i] = Y / (X * X);
		Dir[i] = { X * X, Y };
	}
}

APuyoBoomFX::~APuyoBoomFX()
{
}

void APuyoBoomFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FXTimer += _DeltaTime;
	if (FXTimer <= 1.0f)
	{
		for (int i = 0; i < 4; i++)
		{
			FVector2D Loc = Particles[i]->GetComponentLocation();
			float X = 0.0f;
			if (i < 2)
			{
				X = Loc.X - _DeltaTime * 50;
			}
			else
			{
				X = Loc.X + _DeltaTime *50;
			}

			FVector2D NextLoc = CalcParabola(A[i], Top[i], X);
			Particles[i]->SetSprite("PuyoBoomR");
			Particles[i]->SetComponentLocation(Loc + Dir[i]*_DeltaTime);
			Particles[i]->SetComponentScale({ 32,32 });
			Particles[i]->SetRemoveBackground(true);
		}
		return;
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	FVector2D Loc = Particles[i]->GetComponentLocation();
	//	Particles[i]->SetSprite("PuyoBoomR");
	//	Particles[i]->SetComponentLocation(Loc + DWDir[i] * _DeltaTime * 30);
	//	Particles[i]->SetComponentScale({ 32,32 });
	//	Particles[i]->SetRemoveBackground(true);
	//}
}

void APuyoBoomFX::BeginPlay()
{
	Super::BeginPlay();
}
