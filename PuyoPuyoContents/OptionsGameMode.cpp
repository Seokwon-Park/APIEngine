#include "aepch.h"
#include "OptionsGameMode.h"

#include "OptionsItem.h"
#include "OptionsList.h"
#include "OptionsManager.h"
#include "OptionsBackground.h"

AOptionsGameMode::AOptionsGameMode()
{
}

AOptionsGameMode::~AOptionsGameMode()
{
}

void AOptionsGameMode::BeginPlay()
{
	Super::BeginPlay();

	AOptionsItem* OptionsTitle = GetWorld()->SpawnActor<AOptionsItem>();

	AOptionsItem* SoundTitle = GetWorld()->SpawnActor<AOptionsItem>();
	SoundTitle->SetupItem("OPTMENU", 5);

	AOptionsList* OptionsList = GetWorld()->SpawnActor<AOptionsList>();
	OptionsList->SetItemTitle(OptionsTitle, {176, 16});
	OptionsList->SetupList(32, { 32,24 });
	
	AOptionsList* SoundOptionsList = GetWorld()->SpawnActor<AOptionsList>();
	SoundOptionsList->SetItemTitle(SoundTitle, { 176, 16 });
	SoundOptionsList->SetupList(32, { 32,32 });

	for (int i = 0; i < 7; i++)
	{
		AOptionsItem* Options = GetWorld()->SpawnActor<AOptionsItem>();
		Options->SetupItem("OPTMENU", i + 1);
		*OptionsList += Options;
	}

	for (int i = 0; i < 6; i++)
	{
		AOptionsItem* Options = GetWorld()->SpawnActor<AOptionsItem>();
		Options->SetupItem("SOUNDMENU",i );
		*SoundOptionsList += Options;
	}

	SoundOptionsList->SetActive(false);

	AOptionsManager* tt = GetWorld()->SpawnActor<AOptionsManager>();
	tt->SetList(OptionsList);
	


	GetWorld()->SpawnActor<AOptionsBackground>();
}

void AOptionsGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
