#include "aepch.h"
#include "SoloMenuGameMode.h"

#include "SoloMenuBackground.h"
#include "CharacterFrame.h"

ASoloMenuGameMode::ASoloMenuGameMode()
{
}

ASoloMenuGameMode::~ASoloMenuGameMode()
{
}

void ASoloMenuGameMode::BeginPlay()
{
	ASoloMenuBackground* Background = GetWorld()->SpawnActor<ASoloMenuBackground>();

	ACharacterFrame* Test = GetWorld()->SpawnActor<ACharacterFrame>();
	Test->SetActorLocation({ 8,32 });

	ACharacterFrame* Test2 = GetWorld()->SpawnActor<ACharacterFrame>();
	//632-8-
	Test2->SetActorLocation({ 456,32 });
}

void ASoloMenuGameMode::Tick(float _DeltaTime)
{
}
