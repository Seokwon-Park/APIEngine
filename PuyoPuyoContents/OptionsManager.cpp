#include "aepch.h"
#include "OptionsManager.h"

#include "OptionsList.h"


AOptionsManager::AOptionsManager()
{
	OptSelector = CreateDefaultSubobject<USpriteRendererComponent>("");
	OptSelector->SetSprite("PUYO_Y.CNS.BMP");
	OptSelector->SetComponentScale({ 32,32 });
	OptSelector->SetRemoveBackground(true);
	OptSelector->SetPivot(EPivotType::TopRight);

	OptInput = CreateDefaultSubobject<UInputComponent>("");
}

AOptionsManager::~AOptionsManager()
{
}

void AOptionsManager::BeginPlay()
{
	Super::BeginPlay();
	OptInput->BindAction(EKey::Up, KeyEvent::Down, std::bind(&AOptionsList::PrevItem, std::ref(CurList)));
	OptInput->BindAction(EKey::Down, KeyEvent::Down, std::bind(&AOptionsList::NextItem, std::ref(CurList)));
	//OptInput->BindAction(EKey::Left, KeyEvent::Down, std::bind(&AOptionsList::NextItem, std::ref(CurList)));
	//OptInput->BindAction(EKey::Right, KeyEvent::Down, std::bind(&AOptionsList::NextItem, std::ref(CurList)));
	OptInput->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AOptionsList::Execute, std::ref(CurList)));
}

void AOptionsManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (CurList != nullptr)
	{
		SetActorLocation(CurList->GetSelectedItem()->GetActorLocation());
	}
}

