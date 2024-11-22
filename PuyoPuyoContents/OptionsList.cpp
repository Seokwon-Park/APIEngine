#include "aepch.h"
#include "OptionsList.h"


AOptionsList::AOptionsList()
{
}

AOptionsList::~AOptionsList()
{
}

void AOptionsList::SetupList(float _ItemHeight, FVector2D _Offset)
{
	ItemHeight = _ItemHeight;
	Offset = _Offset;
}

void AOptionsList::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOptionsList::BeginPlay()
{
	Super::BeginPlay();

	Title->SetActorLocation(TitlePos);
	FVector2D StartPos = { Offset.X,TitlePos.Y + ItemHeight + Offset.Y };
	for (int i = 0; i < ItemList.size(); i++)
	{
		ItemList[i]->SetActorLocation(StartPos);
		StartPos.Y += ItemHeight + Offset.Y;
	}
}
