#include "aepch.h"
#include "SoloMenuGameMode.h"

#include "SoloMenuBackground.h"
#include "CharacterFrame.h"
#include "SoloText.h"
#include "PuyoText.h"
#include "EnemySelector.h"

ASoloMenuGameMode::ASoloMenuGameMode()
{
}

ASoloMenuGameMode::~ASoloMenuGameMode()
{
}

void ASoloMenuGameMode::BeginPlay()
{
	ASoloMenuBackground* Background = GetWorld()->SpawnActor<ASoloMenuBackground>();

	ACharacterFrame* MyFrame = GetWorld()->SpawnActor<ACharacterFrame>();
	MyFrame->SetActorLocation({ 8,40 });
	MyFrame->SetupFrame(true);

	ACharacterFrame* EnemyFrame = GetWorld()->SpawnActor<ACharacterFrame>();
	//632-8-
	EnemyFrame->SetActorLocation({ 456,40 });

	ASoloText* ChooseText = GetWorld()->SpawnActor<ASoloText>();
	ChooseText->SetActorLocation({ 240,192 });

	APuyoText* Text = GetWorld()->SpawnActor<APuyoText>();
	Text->SetActorLocation({ 256,128 });
	Text->SetText("LEVEL " + std::to_string(GameSettings::GetInstance().CurLevel));

	int EnemySize = LevelEnemies[GameSettings::GetInstance().CurLevel];
	int StartRange = LevelEnemiesPfsum[GameSettings::GetInstance().CurLevel-1];
	AEnemySelector* Selector = GetWorld()->SpawnActor<AEnemySelector>();
	Selector->SetActorLocation({ 320.0f-24.0f*EnemySize , 384.0f});
	Selector->SetupSelector(EnemySize, StartRange, EnemyFrame);

	UAudioManager::ChangeBGM("SelectMenu.MID");
}

void ASoloMenuGameMode::Tick(float _DeltaTime)
{
}
