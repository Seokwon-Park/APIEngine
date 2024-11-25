#include "aepch.h"
#include "StarParticle.h"

AStarParticle::AStarParticle()
{
}

AStarParticle::~AStarParticle()
{
}


void AStarParticle::Init(FVector2D _Location)
{
	for (int i = 0; i < 50; i++)
	{
		AStar* S = GetWorld()->SpawnActor<AStar>();
		S->InitStar();
		S->SetActorLocation(_Location+ FVector2D(-16,16));
	}
}

void AStarParticle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AStarParticle::BeginPlay()
{
	Super::BeginPlay();


}
