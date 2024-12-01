#include "aepch.h"
#include "GameOverCounter.h"
#include "GameOverGameMode.h"

#include "Puyo.h"

AGameOverCounter::AGameOverCounter()
{
	Board.resize(7, std::vector<APuyo*>(7, nullptr));
}

AGameOverCounter::~AGameOverCounter()
{
}


void AGameOverCounter::SkipTime()
{
	Timer = 2.5f;
}

//�׳� �������� ���̴� ȿ�� ����������? ���ڸ� �����ָ� �ɵ�??
void AGameOverCounter::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Board[i][j] = GetWorld()->SpawnActor<APuyo>();
			Board[i][j]->SetActorLocation(GetActorLocation()+FVector2D(32 * j, 32 * i ));
			//Board[i][j]->PlayAnimation("PlaceComplete");
		}
	}
	UpdateNumber();
}

void AGameOverCounter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsGameOver == true)
	{
		if (Text->GetActorLocation().Y < 416.0f)
		{
			Text->AddActorLocation(FVector2D::DOWN * _DeltaTime * 150.0f);
		}
		else
		{
			IsGameOverEnd1 = true;
		}
		if (GameOverPuyo->GetActorLocation().Y < 272.0f)
		{
			GameOverPuyo->AddActorLocation(FVector2D::DOWN * _DeltaTime * 200.0f);
		}
		else
		{
			IsGameOverEnd2 = true;
		}
		return;
	}

	Timer += _DeltaTime;
	if (Timer > 2.0f) {
		Timer = 0.0f; // Ÿ�̸� �ʱ�ȭ
		Count--;

		if (Count >= 0) {
			UpdateNumber(); // ���ο� ���� Ȱ��ȭ
		}
		else
		{
			IsGameOver = true;
			Text->StopWave();
			GameOverPuyo = GetWorld()->SpawnActor<AGameOverPuyo>();
			GameOverPuyo->SetActorLocation({ 208, -200 });
			BG->RemoveText();
		}
	}

}

void AGameOverCounter::UpdateNumber()
{
	if (Count < 0 || Count >= NumberPatterns.size()) return; // �߸��� ���� Ȯ��

	const auto& CurrentPattern = NumberPatterns[Count];

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (CurrentPattern[i][j] == 1) {
				Board[i][j]->SetActive(true);  // Ȱ��ȭ
				Board[i][j]->SetupPuyo(Board[i][j]->GetActorLocation(), Colors[Count%5]);
				Board[i][j]->PlayAnimation("CountDown");
			}
			else {
				Board[i][j]->SetActive(false); // ��Ȱ��ȭ
			}
		}
	}
}
