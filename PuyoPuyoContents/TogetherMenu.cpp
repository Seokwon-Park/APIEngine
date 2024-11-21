#include "aepch.h"
#include "TogetherMenu.h"

#include "TogetherMenuGameMode.h"
#include "TogetherPlayGameMode.h"

ATogetherMenu::ATogetherMenu()
{
	MapRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	MapRenderer->SetSprite("VSBG");
	MapRenderer->SetComponentLocation({ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X, 224.0f });
	MapRenderer->SetComponentScale({ 304, 224 });

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
	MapRenderer->SetSprite("VSBG", CurIndex);
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
