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
	float Angle = (rand() % 360) * (3.14159f / 180.0f); // ������ ���� (���� ����)
	float Speed = 100.0f + rand() % 50;                 // ������ �ӵ�
	Vx = cos(Angle) * Speed;
	Vy = sin(Angle) * Speed;
	LifeTime = 2.0f;                               // ���� �ð� 2��
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
