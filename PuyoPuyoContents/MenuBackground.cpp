#include "aepch.h"
#include "CarbuncleMenu.h"
#include "MenuBackground.h"

AMenuBackground::AMenuBackground()
{
	//  Make Background Combination;
	std::vector<bool> Select(10, 0);
	std::fill(Select.end() - 4, Select.end(), 1);
	do
	{
		std::vector<int> Temp;
		Temp.reserve(4);
		for (int i = 0; i < 10; i++)
		{
			if (true == Select[i])
			{
				Temp.push_back(i);
			}
		}
		Combinations.push_back(Temp);

	} while (std::next_permutation(Select.begin(), Select.end()));

	BgAnimators.resize(4, nullptr);
	for (int i = 0; i < 4; i++)
	{
		BgAnimators[i] = CreateDefaultSubobject<UAnimatorComponent>("BgAnimator" + std::to_string(i));
		for (int j = 0; j < 10; j++)
		{
			std::string LineSpriteName = "SD" + std::to_string(j) + (i % 2 == 0 ? "R" : "L") + ".CNS.BMP";
			BgAnimators[i]->CreateAnimation("Loop" + std::to_string(j), LineSpriteName, 0, 3, .5f);
		}

	}
	BgRenderers.resize(4, std::vector<USpriteRendererComponent*>(6, nullptr));
	Selected = Combinations[Random.GetRandomInt(0, static_cast<int>(Combinations.size()))];
	for (int i = 0; i < 4; i++)
	{
		std::string LineSpriteName = "SD" + std::to_string(Selected[i]) + (i % 2 == 0 ? "R" : "L") + ".CNS.BMP";
		for (int j = 0; j < 6; j++)
		{
			BgRenderers[i][j] = CreateDefaultSubobject<USpriteRendererComponent>("BgRenderer" + std::to_string(i * 6 + j));
			BgRenderers[i][j]->SetSprite(LineSpriteName, 0);
			BgRenderers[i][j]->SetComponentLocation(FVector2D((j - 1) * 128, i * 128));
			BgRenderers[i][j]->SetComponentScale({ 128,128 });
			BgRenderers[i][j]->SetAnimator(BgAnimators[i]);
			BgRenderers[i][j]->SetPivot(EPivotType::TopLeft);
			//BgRenderers[i][j]->SetRemoveBackground(true);
			BgAnimators[i]->ChangeAnimation("Loop" + std::to_string(Selected[i]));

		}
	}

	FVector2D Size = UEngineAPICore::GetEngineWindow().GetWindowSize();
	TextRenderer = CreateDefaultSubobject<USpriteRendererComponent>("MenuBgText");
	TextRenderer->SetSprite("MENU_RO.CNS.BMP");
	TextRenderer->SetComponentScale({ 528, 48 });
	TextRenderer->SetComponentLocation(FVector2D(Size.Half().X, 48.0f));
	TextRenderer->SetRemoveBackground(true);
	TextRenderer->SetPivot(EPivotType::TopCenter);
}


AMenuBackground::~AMenuBackground()
{
}

void AMenuBackground::BeginPlay()
{
	Super::BeginPlay();


	//std::vector<int> Selected = Combinations[Random.GetRandomInt(0, static_cast<int>(Combinations.size()))];
	//for (int i = 0; i < 4; i++)
	//{
	//	std::string LineSpriteName = "SD" + std::to_string(Selected[i]) + (i % 2 == 0 ? "R" : "L") + ".CNS.BMP";
	//	for (int j = 0; j < 6; j++)
	//	{
	//		BgRenderers[i][j]->SetSprite(LineSpriteName, 0);
	//		BgRenderers[i][j]->SetComponentLocation(FVector2D(j * 128, i * 128));
	//		BgRenderers[i][j]->SetComponentScale({ 128,128 });
	//		BgRenderers[i][j]->SetPivot(PivotType::TopLeft);
	//	}
	//}
}



void AMenuBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D Size = UEngineAPICore::GetEngineWindow().GetWindowSize();
	for (int i = 0; i < 4; i++)
	{
		std::string LineSpriteName = "SD" + std::to_string(Selected[i]) + (i % 2 == 0 ? "R" : "L") + ".CNS.BMP";
		for (int j = 0; j < 6; j++)
		{
			if (i % 2 == 0)
			{
				BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D::RIGHT * _DeltaTime * 100.0f);
				if (BgRenderers[i][j]->GetComponentLocation().X >= UEngineAPICore::GetEngineWindow().GetWindowSize().X)
				{
					BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() - FVector2D(128, 0) * 6);
				}
			}
			else
			{
				BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D::LEFT * _DeltaTime * 100.0f);
				if (BgRenderers[i][j]->GetComponentLocation().X <= -128.0f)
				{
					BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D(128, 0) * 6);

				}
			}


		}
	}
}

