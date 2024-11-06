#include "aepch.h"
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
			BgRenderers[i][j]->SetComponentLocation(FVector2D((j-1) * 128, i * 128));
			BgRenderers[i][j]->SetComponentScale({ 128,128 });
			BgRenderers[i][j]->SetAnimator(BgAnimators[i]);
			//BgRenderers[i][j]->SetRemoveBackground(true);
			BgAnimators[i]->ChangeAnimation("Loop" + std::to_string(Selected[i]));
			BgRenderers[i][j]->SetPivot(PivotType::TopLeft);
		
		}
	}
}


AMenuBackground::~AMenuBackground()
{
}

void AMenuBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (int i = 0; i < 4; i++)
	{
		std::string LineSpriteName = "SD" + std::to_string(Selected[i]) + (i % 2 == 0 ? "R" : "L") + ".CNS.BMP";
		for (int j = 0; j < 6; j++)
		{
			if (i % 2 == 0)
			{
				BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D::RIGHT *.3f);
				if (BgRenderers[i][j]->GetComponentLocation().X > UEngineAPICore::GetEngineWindow().GetWindowSize().X)
				{
					BgRenderers[i][j]->SetComponentLocation({ BgRenderers[i][(j+1)%6]->GetComponentLocation().X -127,
						BgRenderers[i][j]->GetComponentLocation().Y});
				}
			}
			else
			{
				BgRenderers[i][j]->SetComponentLocation(BgRenderers[i][j]->GetComponentLocation() + FVector2D::LEFT * .3f);
				if (BgRenderers[i][j]->GetComponentLocation().X < -128.0f)
				{
					BgRenderers[i][j]->SetComponentLocation({ BgRenderers[i][(j + 5) % 6]->GetComponentLocation().X +127,
						BgRenderers[i][j]->GetComponentLocation().Y });
				}
			}


		}
	}
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

