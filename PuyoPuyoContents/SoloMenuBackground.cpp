#include "aepch.h"
#include "SoloMenuBackground.h"

ASoloMenuBackground::ASoloMenuBackground()
{
	BgRenderers.resize(3, std::vector<USpriteRendererComponent*>(3, nullptr));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BgRenderers[i][j] = CreateDefaultSubobject<USpriteRendererComponent>("BgRenderer" + std::to_string(i * 6 + j));
			BgRenderers[i][j]->SetSprite("SELECT_B.CNS.BMP", 0);
			BgRenderers[i][j]->SetComponentLocation(FVector2D((j - 1) * 320, (i-1) * 240));
			BgRenderers[i][j]->SetComponentScale({ 320,240 });
			BgRenderers[i][j]->SetPivot(EPivotType::TopLeft);

		}
	}
}

ASoloMenuBackground::~ASoloMenuBackground()
{
}


void ASoloMenuBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D Size = UEngineAPICore::GetEngineWindow().GetWindowSize();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D(.8f, .6f) * _DeltaTime * 100.f);
			float Jump = static_cast<float>(3 - abs(i - j));
			if (BgRenderers[i][j]->GetComponentLocation().X > Size.X || BgRenderers[i][j]->GetComponentLocation().Y > Size.Y)
			{
				BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() - BgRenderers[i][j]->GetComponentScale() * Jump);
			}

		}
	}
}

void ASoloMenuBackground::BeginPlay()
{
	Super::BeginPlay();


}