#include "aepch.h"
#include "OptionsGameMode.h"

#include "IntroGameMode.h"

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



	OptionsList = GetWorld()->SpawnActor<AOptionsList>();
	OptionsList->SetItemTitle(OptionsTitle, { 176, 16 });
	OptionsList->SetupList(32, { 32,24 });

	SoundOptionsList = GetWorld()->SpawnActor<AOptionsList>();
	SoundOptionsList->SetItemTitle(SoundTitle, { 176, 16 });
	SoundOptionsList->SetupList(32, { 32,32 });

	AOptionsManager* tt = GetWorld()->SpawnActor<AOptionsManager>();
	tt->SetList(OptionsList);

	for (int i = 0; i < 7; i++)
	{
		AOptionsItem* Options = GetWorld()->SpawnActor<AOptionsItem>();
		Options->SetupItem("OPTMENU", i + 1);
		if (i == 0)
		{
			Options->AddSelectAction(std::bind(&UEngineAPICore::ResetLevel<AIntroGameMode,ADummyPawn>, UEngineAPICore::GetCore(), "Intro"));
			Options->AddSelectAction(std::bind(&UEngineAPICore::OpenLevel, UEngineAPICore::GetCore(), "Intro"));
		}
		if (i == 4)
		{
			Options->AddSelectAction(std::bind(&AOptionsList::SetActive, OptionsList, false));
			Options->AddSelectAction(std::bind(&AOptionsList::SetActive, SoundOptionsList, true));
			Options->AddSelectAction(std::bind(&AOptionsList::InitList, SoundOptionsList));
			Options->AddSelectAction(std::bind(&AOptionsManager::SetList, tt, SoundOptionsList));
		}
		if (i == 6)
		{
			Options->AddSelectAction(std::bind(&DestroyWindow, UEngineAPICore::GetEngineWindow().GetHandle()));

		}
		OptionsList->AddItem(Options);
	}


	for (int i = 0; i < 6; i++)
	{
		AOptionsItem* Options = GetWorld()->SpawnActor<AOptionsItem>();
		Options->SetupItem("SOUNDMENU", i);
		if (i == 5)
		{
			Options->AddSelectAction(std::bind(&AOptionsList::SetActive, OptionsList, true));
			Options->AddSelectAction(std::bind(&AOptionsList::SetActive, SoundOptionsList, false));
			Options->AddSelectAction(std::bind(&AOptionsList::InitList, OptionsList));
			Options->AddSelectAction(std::bind(&AOptionsManager::SetList, tt, OptionsList));
		}
		SoundOptionsList->AddItem(Options);
	}

	SoundOptionsList->SetActive(false);

	GetWorld()->SpawnActor<AOptionsBackground>();
}

void AOptionsGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
