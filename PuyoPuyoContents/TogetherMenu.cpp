#include "aepch.h"
#include "TogetherMenu.h"

#include "TogetherMenuGameMode.h"
#include "TogetherPlayGameMode.h"

ATogetherMenu::ATogetherMenu()
{
	MapRenderer.resize(5, nullptr);
	for (int i = 0; i < 5; i++)
	{
		MapRenderer[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		MapRenderer[i]->SetSprite("VSBG",i);
		MapRenderer[i]->SetComponentLocation(Locations[i]);
		MapRenderer[i]->SetComponentScale({ 304, 224 });
	}

	TextRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	TextRenderer->SetSprite("VSMenuText");
	TextRenderer->SetComponentLocation({ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X, 416.0f });
	TextRenderer->SetComponentScale({ 512, 32 });
	TextRenderer->SetRemoveBackground(true);

	MenuInput = CreateDefaultSubobject<UInputComponent>("");
}

ATogetherMenu::~ATogetherMenu()
{
}

void ATogetherMenu::StartPlay()
{
	GameSettings::GetInstance().GameMode = EPuyoGameMode::Versus;
	GameSettings::GetInstance().MapIndex = CurIndex;
	GameSettings::GetInstance().DestroyRule = DestroyRule[CurIndex];

	UEngineAPICore::GetCore()->ResetLevel<ATogetherPlayGameMode, ADummyPawn>("TogetherPlay");
	UEngineAPICore::GetCore()->OpenLevel("TogetherPlay");//
}

void ATogetherMenu::MoveMenu(int _Dir)
{
	CurIndex += _Dir;
	if (CurIndex < 0)
	{
		CurIndex += 5;
	}
	CurIndex %= 5;

	TextRenderer->SetSprite("VSMenuText", CurIndex);

	for (int i = 0; i < 5; i++)
	{
		MapRenderer[i]->SetComponentLocation(MapRenderer[i]->GetComponentLocation() + FVector2D(-400.0f * _Dir, 0.0f));
	}
	if (_Dir == 1)
	{
		MapRenderer[(CurIndex + 2) % 5]->SetComponentLocation(Locations[2]);
	}
	else
	{
		MapRenderer[(CurIndex + 3) % 5]->SetComponentLocation(Locations[3]);
	}
	
}

void ATogetherMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ATogetherMenu::BeginPlay()
{
	Super::BeginPlay();
	MenuInput->BindAction(EKey::Right, KeyEvent::Down, std::bind(&ATogetherMenu::MoveMenu, this, 1));
	MenuInput->BindAction(EKey::Left, KeyEvent::Down, std::bind(&ATogetherMenu::MoveMenu, this, -1));
	MenuInput->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&ATogetherMenu::StartPlay, this));
	
}
