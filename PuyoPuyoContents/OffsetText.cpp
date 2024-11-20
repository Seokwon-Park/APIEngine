#include "aepch.h"
#include "OffsetText.h"

AOffsetText::AOffsetText()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");

}

AOffsetText::~AOffsetText()
{
}


void AOffsetText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOffsetText::BeginPlay()
{
	Super::BeginPlay();
}
