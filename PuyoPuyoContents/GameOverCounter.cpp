#include "aepch.h"
#include "GameOverCounter.h"

#include "Puyo.h"

AGameOverCounter::AGameOverCounter()
{
	Board.resize(7, std::vector<APuyo*>(5, nullptr));
}

AGameOverCounter::~AGameOverCounter()
{
}


//�׳� �������� ���̴� ȿ�� ����������? ���ڸ� �����ָ� �ɵ�??
void AGameOverCounter::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{

		}
	}
}

void AGameOverCounter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
