#include "aepch.h"
#include "OpeningStar.h"

AOpeningStar::AOpeningStar()
{
}

AOpeningStar::~AOpeningStar()
{
}

void AOpeningStar::Init()
{
	float Angle = (rand() % 360) * (3.14159f / 180.0f); // 무작위 각도 (라디안 단위)
	float Speed = 100.0f + rand() % 50;                 // 무작위 속도
	Vx = cos(Angle) * Speed;
	Vy = sin(Angle) * Speed;
	LifeTime = 2.0f;                               // 생명 시간 2초
	isAlive = true;
}

void AOpeningStar::BeginPlay()
{
	Super::BeginPlay();
}

void AOpeningStar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
