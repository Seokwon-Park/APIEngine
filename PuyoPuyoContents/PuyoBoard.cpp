#include "aepch.h"
#include "PuyoBoard.h"
#include "PuyoText.h"
#include "OffsetText.h"
#include "PuyoBoomFX.h"
#include "PuyoChainText.h"
#include "GameOverText.h"
#include "PuyoChainFX.h"
#include "ConstData.h"


#include <algorithm>
#include <EnginePlatform/EngineInputSystem.h>
#include <EngineCore/Level.h>
#include <EngineCore/ImageManager.h>

APuyoBoard::APuyoBoard()
	:Difficulty(3), PuyoSize(FVector2D::ZERO), BoardSize(FIntPoint::ZERO),
	MainPuyoCoord(FIntPoint::ZERO), PuyoDropDelay(.5f), PuyoDropTimer(0.0f), PuyoTick(0), BlockDir(0),
	CurStep(EPuyoLogicStep::PuyoIdle), Block(std::vector<APuyo*>(2))
	//,Board(std::vector<std::vector<APuyo*>>(13, std::vector<APuyo*>(6, nullptr)))
{
	PauseText = CreateDefaultSubobject<USpriteRendererComponent>("PauseText");
	PauseText->SetSprite("Pause", static_cast<int>(BoardColor));
	PauseText->SetComponentScale({ 128, 48 });
	PauseText->SetComponentLocation({ 32, 128 });
	PauseText->SetRemoveBackground(true);
	PauseText->SetPivot(EPivotType::TopLeft);
	PauseText->SetOrder(100);
	PauseText->SetActive(false);

	IsDrop.resize(6, false);

}

void APuyoBoard::SmoothRotate(FVector2D _SlavePuyoPos, FVector2D _MainPuyoPos, float _DeltaTime, bool _IsClockwise) {
	// ������ deltaTime�� ����� �����Ͽ� ���������� ���� 

	// 90�� : 1�� = dAngle : _DeltaTime�� dAngle���ϱ�
	float dAngle = 90.0f * _DeltaTime / 0.1f * (_IsClockwise ? 1.0f : -1.0f);
	//���� ȸ������ �̰ɷ� �Ǵ��ؾ� ȸ������ �ȳ�
	NeedToRotate -= abs(dAngle);
	// ȸ�� ��ȯ ��� (�������� ��ȯ �ʿ�)
	float AngleInRadians = FEngineMath::DegreesToRadians(dAngle);
	float CosTheta = std::cos(AngleInRadians);
	float SinTheta = std::sin(AngleInRadians);

	// ���� ���� ȸ�� �� Main Puyo ��ġ�� �̵�
	FVector2D RelativePosition = _SlavePuyoPos - _MainPuyoPos;
	float RotatedX = RelativePosition.X * CosTheta - RelativePosition.Y * SinTheta;
	float RotatedY = RelativePosition.X * SinTheta + RelativePosition.Y * CosTheta;

	FVector2D TargetLocation = Block[0]->GetActorLocation() + FVector2D(Dx[BlockDir] * PuyoSize.iX(), Dy[BlockDir] * PuyoSize.iY());
	// ���ο� Slave Puyo ��ġ
	_SlavePuyoPos = FVector2D(RotatedX, RotatedY) + _MainPuyoPos;
	if (NeedToRotate < .1f || _SlavePuyoPos.Distance(TargetLocation) < 0.2f)
		//if (FVector2D::Distance(slavePuyoPosition, TargetLocation) < 0.1f)
	{
		Block[1]->SetActorLocation(TargetLocation);
		IsRotating = false;
	}
	Block[1]->SetActorLocation(_SlavePuyoPos);
}

void APuyoBoard::SpawnDestroyFX(FVector2D _Loc, EPuyoColor _Color, float _Delay)
{
	APuyoBoomFX* BoomFX = GetWorld()->SpawnActor<APuyoBoomFX>();
	BoomFX->SetupBoomFX(_Color, _Delay);
	BoomFX->SetActorLocation(_Loc);
}

void APuyoBoard::PauseGame()
{
	IsPaused = !IsPaused;
	PauseText->SetActive(IsPaused);
	PauseText->SetRemoveBackground(true);
	for (int i = 0; i < BoardSize.Y; i++)
	{
		for (int j = 0; j < BoardSize.X; j++)
		{
			if (Board[i][j] != nullptr)
			{
				Board[i][j]->SetActive(!IsPaused);
			}
		}
	}

	for (int i = 0; i < Block.size(); i++)
	{
		Block[i]->SetActive(!IsPaused);
		NextBlock[i]->SetActive(!IsPaused);
		NextNextBlock[i]->SetActive(!IsPaused);
	}
}


APuyoBoard::~APuyoBoard()
{
}

void APuyoBoard::BeginPlay()
{
	Super::BeginPlay();
	PuyoDropTimer = PuyoDropDelay;

	// Todo : BeginPlay�� �ӽ���ġ, ���ӽ��� �ִϸ��̼��� ������ ������ �Ǿ�� ��.
	NextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(NextBlockCoord.X, NextBlockCoord.Y + Dy[BlockDir] * i));
	}
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(NextNextBlockCoord.X, NextNextBlockCoord.Y + Dy[BlockDir] * i));
	}

	//APuyoText* Text = GetWorld()->SpawnActor<APuyoText>();
	//Text->SetupText(10, "PUYO_BP.CNS.BMP");
	//Text->SetupText(10, "PUYO_G_.CNS.BMP");
	//Text->SetupText(10, "PUYO_RY.CNS.BMP");
	//Text->SetActorLocation({ 8,16 });
	//Text->SetText("asdfGf");
}

void APuyoBoard::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//Input->SetActive(false);

	if (true == IsPaused)
	{
		PauseTimer -= _DeltaTime;
		if (PauseTimer <= 0.0f)
		{
			PauseTimer = PauseDelay;
			PauseText->SwitchActive();
		}
		return;
	}

	if (CounterBoardActor->GetCurStep() == EPuyoLogicStep::PuyoGameOver)
	{
		CurStep = EPuyoLogicStep::PuyoGameWin;
	}

	if (true == IsKicking)
	{
		if (BlockDir == 1)
		{
			Block[0]->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 32.0f / 0.1f);
			Block[1]->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 32.0f / 0.1f);
			if (Block[0]->GetActorLocation().X > GetLocationByIndexOnBoard(MainPuyoCoord).X)
			{
				IsKicking = false;
			}
		}
		else if (BlockDir == 3)
		{
			Block[0]->AddActorLocation(FVector2D::LEFT * _DeltaTime * 32.0f / 0.1f);
			Block[1]->AddActorLocation(FVector2D::LEFT * _DeltaTime * 32.0f / 0.1f);
			if (Block[0]->GetActorLocation().X < GetLocationByIndexOnBoard(MainPuyoCoord).X)
			{
				IsKicking = false;
			}
		}
		else
		{
			Block[0]->AddActorLocation(FVector2D::UP * _DeltaTime * 32.0f / 0.1f);
			Block[1]->AddActorLocation(FVector2D::UP * _DeltaTime * 32.0f / 0.1f);
			if (Block[0]->GetActorLocation().Y < GetLocationByIndexOnBoard(MainPuyoCoord).Y)
			{
				IsKicking = false;
			}
		}
	}
	if (true == IsRotating)
	{
		SmoothRotate(Block[1]->GetActorLocation(), Block[0]->GetActorLocation(), UEngineAPICore::GetEngineDeltaTime(), IsRotatedClockWise);
	}

	ForceDownTimer -= _DeltaTime;
	LRMoveTimer -= _DeltaTime;


	// Todo : ���⼭ ���� �ִϸ��̼��� �ȳ������� ��� Return�ϵ��� ����?
	//UEngineDebugHelper::PushString("X = " + std::to_string(MainPuyoCoord.X) + ", Y = " + std::to_string(MainPuyoCoord.Y));
	//UEngineDebugHelper::PushString("Timer = " + std::to_string(PuyoDropTimer));
	//UEngineDebugHelper::PushString("PuyoTick = " + std::to_string(PuyoTick));
	//UEngineDebugHelper::PushString("SlaveCoord = " + FIntPoint(MainPuyoCoord.X + Dx[BlockDir], MainPuyoCoord.Y + Dy[BlockDir]).ToString());
	//UEngineDebugHelper::PushString("CurStep = " + std::to_string(static_cast<int>(CurStep)));
	switch (CurStep)
	{
	case EPuyoLogicStep::PuyoIdle:
		break;
	case EPuyoLogicStep::PuyoCreate:
		PuyoCreateLogic();
		break;
	case EPuyoLogicStep::PuyoMove:
		PuyoMoveLogic();
		break;
	case EPuyoLogicStep::PuyoPlace:
		PuyoPlaceLogic();
		break;
	case EPuyoLogicStep::PuyoConnect:
		PuyoConnectLogic();
		break;
	case EPuyoLogicStep::PuyoCheck:
		PuyoCheckLogic();
		break;
	case EPuyoLogicStep::PuyoDestroy:
		PuyoDestroyLogic();
		break;
	case EPuyoLogicStep::PuyoUpdate:
		PuyoUpdateLogic();
		break;
	case EPuyoLogicStep::PuyoGameOver:
		PuyoGameOverLogic();
		break;
	case EPuyoLogicStep::PuyoGameWin:
		PuyoGameWinLogic();
		break;
	default:
		break;
	}

}

void APuyoBoard::SetupPuyoBoard(const PuyoBoardSettings& _Settings)
{
	Difficulty = _Settings.Difficulty;
	PuyoSize = _Settings.PuyoSize;
	BoardSize = _Settings.BoardSize;
	NextBlockCoord = _Settings.NextBlockCoord;
	NextNextBlockCoord = _Settings.NextNextBlockCoord;
	ScoreActor = _Settings.ScoreActor;
	CounterBoardActor = _Settings.CounterBoardActor;
	ShakePostProcess = _Settings.ShakePostProcess;
	BoardColor = _Settings.BoardColor;
	WarnActor = _Settings.WarnActor;
	BottomFrames = _Settings.BottomFrames;
	Board.clear();
	Board.resize(BoardSize.Y, std::vector<APuyo*>(BoardSize.X, nullptr));
	PauseText->SetSprite("Pause", static_cast<int>(BoardColor));
}

std::vector<APuyo*> APuyoBoard::CreatePuyoBlock()
{
	std::vector<APuyo*> NewBlock(2, nullptr);
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = GetWorld()->SpawnActor<APuyo>();
		Puyo->SetupPuyo(GetLocationByIndexOnBoard((BoardSize.X - 1) / 2 + Dx[BlockDir] * i, 1 + Dy[BlockDir] * i), static_cast<EPuyoColor>(RandomDevice.GetRandomInt(0, Difficulty)));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i), EPuyoColor::Red);
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i), 5);
		NewBlock[i] = Puyo;
	}

	return NewBlock;
}


void APuyoBoard::PuyoCreateLogic()
{
	//���ӿ���,,,
	if (Board[1][2] != nullptr)
	{
		AGameOverText* Test = GetWorld()->SpawnActor<AGameOverText>();
		Test->SetActorLocation(GetActorLocation());
		CurStep = EPuyoLogicStep::PuyoGameOver;
		return;
	}

	//���ؾߵ� ������ ������ ����
	ScoreActor->Add(ScoreToAdd);
	ScoreToAdd = 0;

	Rensa = 0; // ����� ���ԵǸ� ����� 0

	//ó�� ��Ϲ����� ����, ó�� ��� ��ġ�� ��Ʈ����(=0����)
	BlockDir = 0;
	MainPuyoCoord.X = (BoardSize.X - 1) / 2;
	MainPuyoCoord.Y = 0;
	// ���� �����غ� ����

	Block = NextBlock;
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = Block[i];
		Puyo->SetActorLocation(GetLocationByIndexOnBoard(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[Dir] * i, MainPuyoCoord.Y + Dy[Dir] * i), 0);
	}

	// �� �������� NextNextBlock�� NextBlockĭ���� �ε巴�� �̵��ؾ� �ȴ�.
	NextBlock = NextNextBlock;
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(NextBlockCoord.X, NextBlockCoord.Y + Dy[BlockDir] * i));
	}

	//���� ������ NextNextBlock�� ������ �����̼����� �̵��ؾ� �Ѵ�.
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(NextNextBlockCoord.X, NextNextBlockCoord.Y + Dy[BlockDir] * i));
	}

	//0�� ����� MainPuyo�� �ȴ�.
	Block[0]->PlayAnimation("AxisPuyoIdle");
	/*APuyo* Puyo1 = GetWorld()->SpawnActor<APuyo>();
	Puyo1->SetupPuyo(GetPosByIndex(MainPuyoCoord.X, MainPuyoCoord.Y), UEngineRandom::GetRandomInt(0, 4));
	APuyo* Puyo2 = GetWorld()->SpawnActor<APuyo>();
	Puyo2->SetupPuyo(GetPosByIndex(MainPuyoCoord.X + Dx[Dir], MainPuyoCoord.Y + Dy[Dir]), UEngineRandom::GetRandomInt(0, 4));*/
	if (PuyoCreateDelegate.IsBind() == true)
	{
		PuyoCreateDelegate();
	}
	CurStep = EPuyoLogicStep::PuyoMove;
}

void APuyoBoard::PuyoMoveLogic()
{
	PuyoDropTimer -= UEngineAPICore::GetEngineDeltaTime();
	// ������ �ð��� ������ �ѿ並 ������.
	if (PuyoDropTimer >= 0.0f)
	{
		return;
	}
	PuyoTick++;
	// ��ġ������ ���� �� �ִ��� Ȯ���Ѵ�.
	if (true == CanMoveLocation())
	{
		for (auto Puyo : Block)
		{
			Puyo->AddActorLocation(FVector2D(0.0f, PuyoSize.Half().Y));
			//Puyo->SetActorLocation(FVector2D::Lerp(Puyo->GetActorLocation(), Puyo->GetActorLocation() + FVector2D(0,32),UEngineAPICore::GetCore()->GetDeltaTime()));
		}
	}
	MainPuyoCoord.Y += (PuyoTick % 2 == 0);

	//Todo: �ؿ� �����͵� �����̰� �־�� �Ǵµ� ���� ��ġ��
	if (false == CanMoveDown())
	{
		for (int i = 0; i < 2; i++)
		{
			int X = MainPuyoCoord.X + Dx[BlockDir] * i;
			int Y = MainPuyoCoord.Y + Dy[BlockDir] * i;
			IsRotating = false;
			Block[i]->SetActorLocation(GetLocationByIndexOnBoard(X, Y));
			PlaceCheckList.push_back(Block[i]);
			Block[i]->SetCurXY({ X,Y });
			Block[i]->SetTargetXY({ X,Y });
			if (BlockDir % 2 == 1) // ���η� ���� ���� ���
			{
				int PlaceY = Y;
				while (PlaceY + 1 < BoardSize.Y && Board[PlaceY + 1][X] == nullptr) { PlaceY++; }
				Block[i]->SetTargetXY({ X,PlaceY });
			}
			if (Block[i]->GetTargetXY().Y < 0)
			{
				PlaceCheckList.pop_back();
				Block[i]->Destroy();
				continue;
			}
			SetPuyoOnBoard(Block[i]->GetTargetXY(), Block[i]);
			PuyoTick = 0;
		}

		//���� �ѿ並 ������ ��, ��밡 �������� �ƴ�(���� ��), ���� ����ѿ䰡 ���� ������, ���üũ�� �����Ѵ�.
		// ���ʿ� �̰� �ʿ���µ�.
		//if (WarnActor->HasWarn() && !CounterBoardActor->IsChaining)
		//{
		//	CheckOffset = true;
		//	//SpawnNuisancePuyo();
		//}
		CurStep = EPuyoLogicStep::PuyoPlace;
		return;
	}

	PuyoDropTimer = PuyoDropDelay;
}



void APuyoBoard::PuyoPlaceLogic()
{

	if (!PlaceCheckList.empty())
	{
		// �̺κ��� set���� ��ü�Ǿ���.
		//sort(PlaceCheckList.begin(), PlaceCheckList.end(), [](auto _A, auto _B)
		//	{
		//		if (_A.Y == _B.Y)
		//		{
		//			return _A.X < _B.X;
		//		}
		//		return _A.Y > _B.Y;
		//	}
		//);

		// ���忡�� �������� �� �ѿ䰡 �ִ��� üũ�ؼ� ������Ʈ �ϴ� �κ�.
		// üũ�ؾ��� ��� �ѿ信 ���� ������.
		// ��ӻ��¿����� ��ĭ�� �������ٸ� ���⼭�� ���� �ε巴�� ����������
		for (APuyo* CurPuyo : PlaceCheckList)
		{
			if (false == CurPuyo->GetIsDropComplete())
			{
				if (CurPuyo->GetTargetXY().Y == CurPuyo->GetCurXY().Y)
				{
					Board[CurPuyo->GetTargetXY().Y][CurPuyo->GetTargetXY().X] = CurPuyo;
					CurPuyo->PlayAnimation("PlaceComplete");
					CurPuyo->SetIsDropComplete(true);
				}
				else
				{
					CurPuyo->AddActorLocation(FVector2D::DOWN * UEngineAPICore::GetEngineDeltaTime() * 32.0f / 0.1f);
					if (CurPuyo->GetActorLocation().Y >= GetLocationByIndexOnBoard(CurPuyo->GetTargetXY()).Y)// || CurPuyo->GetActorLocation().Distance(GetLocationByIndexOnBoard(CurPuyo->GetTargetXY())) < 0.1f)
					{
						//Board[Point.Y][Point.X] = nullptr;
						//Point = FIntPoint(Point.X, PlaceY);
						Board[CurPuyo->GetTargetXY().Y][CurPuyo->GetTargetXY().X] = CurPuyo;
						CurPuyo->SetCurXY(CurPuyo->GetTargetXY());
						CurPuyo->SetActorLocation(GetLocationByIndexOnBoard(CurPuyo->GetTargetXY()));
						if (CurPuyo->GetColor() != EPuyoColor::Garbage)
						{
							CurPuyo->PlayAnimation("PlaceComplete");
						}
						else
						{
							CurPuyo->SetIsAnimationEnd(true);
						}
						CurPuyo->SetIsDropComplete(true);
					}
				}
			}
		}
		// ��� ���� ���� ��ġ �Ϸ� �ִϸ��̼��� ������ �Ѿ��.
		bool CheckAllFinished = true;
		for (APuyo* CurPuyo : PlaceCheckList)
		{
			if (false == CurPuyo->GetIsAnimationEnd())
			{
				CheckAllFinished = false;
				break;
			}
		}
		if (!CheckAllFinished)
			return;
	}
	for (APuyo* CurPuyo : PlaceCheckList)
	{
		CurPuyo->SetIsDropComplete(false);
		CurPuyo->SetIsAnimationEnd(false);
		if (CurPuyo->GetColor() != EPuyoColor::Garbage)
		{
			PuyoConnectList.push_back(CurPuyo);
		}
	}

	PlaceCheckList.clear();

	CurStep = EPuyoLogicStep::PuyoConnect;
}

void APuyoBoard::PuyoConnectLogic()
{
	//SetConnection
	for (APuyo* CurPuyo : PuyoConnectList)
	{
		int X = CurPuyo->GetCurXY().X;
		int Y = CurPuyo->GetCurXY().Y;
		int SpriteIndex = 0;
		for (int i = 0; i < 4; i++)
		{
			int Dir = i;
			int TargetX = X + Dx[Dir];
			int TargetY = Y + Dy[Dir];
			// ������ ���� ���̸� �ȵȴ�.
			if (!IsInBoard(TargetX, TargetY))
			{
				continue;
			}
			APuyo* NearPuyo = Board[TargetY][TargetX];
			// �̿� �ѿ䰡 null�̾ �����ϸ� �ȵȴ�.
			if (NearPuyo == nullptr)
			{
				continue;
			}
			// �̿� �ѿ�� ���� �ѿ��� ������ ���� ���
			if (NearPuyo->GetColor() == CurPuyo->GetColor())
			{
				// �̿��ѿ��� ��������Ʈ�� ���� �ѿ�� �̾����� �ϱ� ������ ������Ʈ ���ش�.
				// Todo: ���� �����ϰ� �� ����� �ֳ�?
				int NearSpriteIndex = 0;
				for (int j = 0; j < 4; j++)
				{
					int NearDir = j % 4;
					int NearTargetX = X + Dx[Dir] + Dx[NearDir];
					int NearTargetY = Y + Dy[Dir] + Dy[NearDir];
					if (NearTargetX < 0 || NearTargetY < 0 || NearTargetX >= BoardSize.X || NearTargetY >= BoardSize.Y)
					{
						continue;
					}
					APuyo* NearNearPuyo = Board[NearTargetY][NearTargetX];
					if (NearNearPuyo == nullptr)
					{
						continue;
					}
					if (NearPuyo->GetColor() == NearNearPuyo->GetColor())
					{
						NearSpriteIndex |= 1 << j;
					}
				}
				NearPuyo->SetSprite(NearSpriteIndex);
				SpriteIndex |= 1 << i;
			}
		}
		CurPuyo->SetSprite(SpriteIndex);
	}
	for (APuyo* CurPuyo : PuyoConnectList)
	{
		if (CurPuyo->GetColor() != EPuyoColor::Garbage)
		{
			PuyoCheckList.push_back(CurPuyo->GetCurXY());
		}
	}
	PuyoConnectList.clear();

	CurStep = EPuyoLogicStep::PuyoCheck;
}


void APuyoBoard::PuyoCheckLogic()
{
	// Place�� �� ���� ���ؼ� BFS ���Ž���� ������ 4�� �̻��� ��츦 ã�� �ı��� ����Ʈ�� �����.
	// ���� �ִ� ������ ������ �ʿ䰡 ����.
	int PC = 0;
	std::vector<std::vector<bool>> Checked(BoardSize.Y, std::vector<bool>(BoardSize.X, false));

	for (FIntPoint Point : PuyoCheckList)
	{
		std::vector<std::vector<bool>> Visited(BoardSize.Y, std::vector<bool>(BoardSize.X, false));
		if (Checked[Point.Y][Point.X] == true) continue;
		// ���� BFS �Լ��� ����
		std::queue<FIntPoint> Queue;

		// Todo : �꿡���� 4��� �ٸ����� ���� �� �ְ� �� ����
		// ���� ��ġ�� �ѿ�� ������ ���� �ѿ��� ��ǥ���� ����Ǵ� 
		// �ӽ� ���� ����� 4���� ũ�� ���Ÿ�Ͽ� ����
		std::vector<FIntPoint> Temp;
		// ��ó�� ���ػѿ䵵 ���� �����س��� �ӽ� ���� ����� 4���� ũ�� ���� �����.
		std::vector<FIntPoint> Garbages;


		Queue.push(Point);
		Temp.push_back(Point);
		Visited[Point.Y][Point.X] = true;
		while (!Queue.empty())
		{
			auto [CurX, CurY] = Queue.front();
			APuyo* CurPuyo = Board[CurY][CurX];
			Queue.pop();
			for (int Dir = 0; Dir < 4; Dir++)
			{
				int TargetX = CurX + Dx[Dir];
				int TargetY = CurY + Dy[Dir];
				if (!IsInBoard(TargetX, TargetY) || true == Visited[TargetY][TargetX])
				{
					continue;
				}
				APuyo* TargetPuyo = Board[TargetY][TargetX];
				if (nullptr == TargetPuyo)
				{
					continue;
				}
				if (TargetPuyo->GetColor() == CurPuyo->GetColor())
				{
					Queue.push(FIntPoint(TargetX, TargetY));
					Temp.push_back(FIntPoint(TargetX, TargetY));
					Visited[TargetY][TargetX] = true;
				}
				if (TargetPuyo->GetColor() == EPuyoColor::Garbage)
				{
					Garbages.push_back(FIntPoint(TargetX, TargetY));
					Visited[TargetY][TargetX] = true;
				}
			}
		}
		if (Temp.size() >= GameSettings::GetInstance().DestroyRule)
		{
			PC += static_cast<int>(Temp.size());
			for (FIntPoint Point : Temp)
			{
				Checked[Point.Y][Point.X] = true;
				PuyoDestroyList.insert(Point);
				//PuyoDestroyList.push_back(Point);
			}
			for (FIntPoint Point : Garbages)
			{
				PuyoDestroyList.insert(Point);
				//PuyoDestroyList.push_back(Point);
			}
		}
	}

	// ���⼭ ������ ���ⷮ�� ����Ѵ�.
	if (!PuyoDestroyList.empty())
	{
		Rensa++;
		int CP = SingleCPTable[Rensa];
		//TODO : �÷����ʽ� ����ؾ���
		int CB = ColorBonusTable[1];
		int GB = GroupBonusTable[PC];
		std::string PCText = std::to_string(PC * 10);
		std::string BonusText = std::to_string(CP + CB + GB);
		std::string Display = std::string(4 - PCText.size(), ' ') + PCText + '*' + std::string(3 - BonusText.size(), ' ') + BonusText;
		ScoreActor->SetText(Display);
		ScoreToAdd += PC * 10 * (CP + CB + GB);
		SC = static_cast<float>(PC * 10 * (SingleCPTable[Rensa] + CB + GB));
	}
	PuyoCheckList.clear();

	CurStep = EPuyoLogicStep::PuyoDestroy;
}



void APuyoBoard::PuyoDestroyLogic()
{
	//�ı��Ұ� ����
	if (PuyoDestroyList.empty())
	{
		CurStep = EPuyoLogicStep::PuyoUpdate;
		return;
	}

	//�ı��Ұ� �ִ� ���
	//�ϴ� ���� ����
	if (FlickCount < 10)
	{
		FlickDelay -= UEngineAPICore::GetEngineDeltaTime();
		if (FlickDelay > 0.0f) return;
		for (auto [X, Y] : PuyoDestroyList)
		{
			APuyo* Puyo = Board[Y][X];
			if (FlickCount % 2 == 0)
			{
				Puyo->SetActive(false);
			}
			else
			{
				Puyo->SetActive(true);
			}
		}
		FlickDelay = 0.05f;
		FlickCount++;
		return;
	}

	//�ı����� ��������
	if (!IsDestroying)
	{
		IsChaining = true;
		//���⼭���� �ı�����
		//���� �ؽ�Ʈ�� ǥ���Ѵ�.
		SpawnChainText();
		// SC = ���� ���� (�̰� �̱� ��Ƽ ���о��� �Ȱ��� ��Ƽ�÷��� CP���̺��� ���µ�

		//NP = SC / TP + NL
		//NP : ���� ���� �ѿ� (=AttackAmount)
		//NC = NP ����
		//NL = NP-NC

		float CheckNL = FEngineMath::Floor(NL);
		NL -= CheckNL;
		float NP = (SC / TP + CheckNL);
		float NC = FEngineMath::Floor(NP);
		NL += NP - static_cast<float>(NC);

		//������ ��
		int AttackAmount = static_cast<int>(NP);
		//int AttackAmount = rand() % 10 + 6;

		// Todo: ������ ������ ���̴µ� ���� �𸣰���
		// ���� ���� ���� �ѿ䰡 ������
		if (WarnActor->HasWarn())
		{
			AOffsetText* OffText = GetWorld()->SpawnActor<AOffsetText>();
			OffText->SetActorLocation(GetActorLocation() + FVector2D(96.0f, 0.0f));

			if (WarnActor->GetWarnNum() < AttackAmount)
			{
				SpawnAttack(WarnActor->GetWarnNum() - AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()), true);
				CounterBoardActor->WarnActor->SubWarnNum(WarnActor->GetWarnNum() - AttackAmount);
				WarnActor->SetWarnNum(0);

			}
			else
			{
				//�ڱ����� ������ ������ ����Ų��.
				SpawnAttack(AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()), true);
				//���� �縸ŭ ���δ�.
				WarnActor->SubWarnNum(AttackAmount);
			}

		}
		else
		{
			//��ġ���� ��� ���忡 ������ ������ ����Ʈ�� �����Ѵ�.
			SpawnAttack(AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()), false);
			CounterBoardActor->WarnActor->AddWarnNum(AttackAmount);
		}

		int ix = 0;
		for (auto [X, Y] : PuyoDestroyList)
		{
			APuyo* CurPuyo = Board[Y][X];
			CurPuyo->PlayAnimation("Boom");
			if (CurPuyo->GetColor() != EPuyoColor::Garbage)
			{
				SpawnDestroyFX(CurPuyo->GetActorLocation(), CurPuyo->GetColor(), 0.05f + ix * 0.1f);
				ix++;
			}
		}
		//���⼭ �����Ѵ�.
		IsDestroying = true;
	}

	// ��� ���� ���� �ı� �Ϸ� �ִϸ��̼��� ������ �Ѿ��.
	bool CheckAllFinished = true;
	for (auto [X, Y] : PuyoDestroyList)
	{
		APuyo* CurPuyo = Board[Y][X];
		if (false == CurPuyo->GetIsAnimationEnd())
		{
			CheckAllFinished = false;
			break;
		}
	}

	if (!CheckAllFinished)
		return;

	for (auto [X, Y] : PuyoDestroyList)
	{
		APuyo* Puyo = Board[Y][X];
		Puyo->Destroy();
		Board[Y][X] = nullptr;
		if (X - 1 >= 0) PuyoUpdateColumns.insert(X - 1);
		PuyoUpdateColumns.insert(X);
		if (X + 1 < BoardSize.X) PuyoUpdateColumns.insert(X + 1);
	}

	FlickCount = 0;
	IsDestroying = false;
	PuyoDestroyList.clear();

	CurStep = EPuyoLogicStep::PuyoUpdate;
}


void APuyoBoard::PuyoUpdateLogic()
{
	if (PuyoUpdateColumns.empty())
	{
		IsChaining = false;
		if (WarnActor->HasWarn() && CounterBoardActor->IsChaining == false && IsChaining == false && IsNuiSpawned == false)
		{
			IsNuiSpawned = true;
			SpawnNuisancePuyo();
			WarnActor->UpdateWarning();
			ShakePostProcess->SetEnable();
			CurStep = EPuyoLogicStep::PuyoPlace;
			return;
		}
		IsNuiSpawned = false;
		CurStep = EPuyoLogicStep::PuyoCreate;
		return;
	}
	for (int X : PuyoUpdateColumns)
	{
		for (int Y = BoardSize.Y - 1; Y >= 0; Y--)
		{
			for (int Dir = 0; Dir < 4; Dir++)
			{
				int TargetX = X + Dx[Dir];
				int TargetY = Y + Dy[Dir];
				if (!IsInBoard(TargetX, TargetY)) continue;
				if (Board[TargetY][TargetX] != nullptr)
				{
					PuyoConnectList.push_back(Board[TargetY][TargetX]);
				}
			}
			if (Board[Y][X] == nullptr)
			{
				for (int FindY = Y - 1; FindY >= 0; FindY--)
				{
					if (Board[FindY][X] != nullptr)
					{
						Board[Y][X] = Board[FindY][X];
						Board[FindY][X] = nullptr;
						Board[Y][X]->SetTargetXY({ X, Y });
						PlaceCheckList.push_back(Board[Y][X]);
						break;
					}
				}
			}
		}
	}
	PuyoUpdateColumns.clear();
	CurStep = EPuyoLogicStep::PuyoPlace;
}

void APuyoBoard::PuyoGameOverLogic()
{
	Timer += UEngineAPICore::GetEngineDeltaTime();
	if (Timer > Delay)
	{
		Timer = 0.0f;
		if (DropIndex < 6)
		{
			IsDrop[DropOrder[DropIndex++]] = true;
		}
	}
	for (int j = 0; j < BottomFrames.size(); j++)
	{
		if (!IsDrop[j]) continue;
		BottomFrames[j]->SetActorLocation(BottomFrames[j]->GetActorLocation() + FVector2D(0, 1) * UEngineAPICore::GetEngineDeltaTime() * 200.0f);
		for (int i = 0; i < BoardSize.Y; i++)
		{
			if (Board[i][j] != nullptr)
			{
				Board[i][j]->AddActorLocation(FVector2D::DOWN* UEngineAPICore::GetEngineDeltaTime()*200.0f);

			}
		}
	}
}

void APuyoBoard::PuyoGameWinLogic()
{
	for (int i = 0; i < BoardSize.Y; i++)
	{
		for (int j = 0; j < BoardSize.X; j++)
		{
			if (Board[i][j] != nullptr)
			{
				Board[i][j]->SetActive(false);
			}
		}
	}
}

std::vector<std::vector<int>> APuyoBoard::GetBoardState()
{
	std::vector<std::vector<int>> Return(BoardSize.Y, std::vector<int>(BoardSize.X, 0));

	for (int i = 0; i < BoardSize.Y; i++)
	{
		for (int j = 0; j < BoardSize.X; j++)
		{
			if (Board[i][j] == nullptr)
			{
				Return[i][j] = -1;
			}
			else
			{
				Return[i][j] = static_cast<int>(Board[i][j]->GetColor());
			}
		}
	}
	return Return;
}

bool APuyoBoard::IsInBoard(const int TargetX, const int TargetY)
{
	return false == (TargetX < 0 || TargetY < 0 || TargetX >= BoardSize.X || TargetY >= BoardSize.Y);
}

bool APuyoBoard::CanMoveDown()
{
	if (MainPuyoCoord.Y + Dy[BlockDir] + 1 >= BoardSize.Y ||
		MainPuyoCoord.Y + 1 >= BoardSize.Y ||
		Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X] != nullptr ||
		Board[MainPuyoCoord.Y + Dy[BlockDir] + 1][MainPuyoCoord.X + Dx[BlockDir]] != nullptr)
	{
		return false;
	}
	return true;
}

bool APuyoBoard::CanMoveLocation()
{
	int Y = BoardSize.Y - 1;
	//if (PuyoTick >= (Y - 1 - Dy[BlockDir]) * 2)
	if (PuyoTick % 2 == 0 && MainPuyoCoord.Y == BoardSize.Y - 1)
	{
		return false;
	}
	return true;
}

bool APuyoBoard::CanMoveLR(FVector2D _Dir)
{
	if (MainPuyoCoord.X + _Dir.iX() < 0 || MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX() < 0 ||
		MainPuyoCoord.X + _Dir.iX() >= BoardSize.X || MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX() >= BoardSize.X ||
		Board[MainPuyoCoord.Y][MainPuyoCoord.X + _Dir.iX()] != nullptr ||
		(MainPuyoCoord.Y - 1 >= 0 && Board[MainPuyoCoord.Y + Dy[BlockDir]][MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX()] != nullptr))
	{
		return false;
	}

	// ��ĭ ���ĵ� ������ ������ �ؾ���.
	if (PuyoTick % 2 == 1)
	{
		if (MainPuyoCoord.Y + Dy[BlockDir] < BoardSize.Y && (Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X + _Dir.iX()] != nullptr ||
			Board[MainPuyoCoord.Y + Dy[BlockDir] + 1][MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX()] != nullptr))
			return false;
	}
	return true;

}

void APuyoBoard::PuyoMoveLR(FVector2D _Dir)
{
	if (CurStep != EPuyoLogicStep::PuyoMove)
	{
		return;
	}

	//�¿� ������ �� �������� ������
	if (LRMoveTimer > 0.0f)
	{
		return;
	}
	LRMoveTimer = 0.08f;

	if (false == CanMoveLR(_Dir))
	{
		return;
	}

	MainPuyoCoord.X += _Dir.iX();
	for (int i = 0; i < 2; i++)
	{
		Block[i]->AddActorLocation(_Dir * PuyoSize.X);
	}
	/*Block[0]->AddActorLocation(_Dir * PuyoSize.iX());
	Block[1]->AddActorLocation(_Dir * PuyoSize.iX());*/
}


void APuyoBoard::Rotate(bool _IsClockwise)
{
	if (CurStep != EPuyoLogicStep::PuyoMove || IsRotating || IsKicking)
	{
		return;
	}

	int PrevDir = BlockDir;
	if (true == _IsClockwise)
	{
		BlockDir = (BlockDir + 3) % 4;
	}
	else
	{
		BlockDir = (BlockDir + 1) % 4;
	}
	//Todo : ���� �������� ������ ���� ���
	//Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[BlockDir] * PuyoSize.iX(), Dy[BlockDir] * PuyoSize.iY()));
	if (MainPuyoCoord.X == 0 || Board[MainPuyoCoord.Y][MainPuyoCoord.X - 1] != nullptr || (PuyoTick % 2 == 1 && Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X - 1] != nullptr))
	{
		if (BlockDir == 1)
		{
			if (MainPuyoCoord.X + 1 >= BoardSize.X || Board[MainPuyoCoord.Y][MainPuyoCoord.X + 1] != nullptr || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X + 1] != nullptr)
			{
				BlockDir = PrevDir;
				return;
			}
			MainPuyoCoord.X += 1;
			IsKicking = true;
			Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[PrevDir] * PuyoSize.iX(), Dy[PrevDir] * PuyoSize.iY()));
		}
	}
	if (MainPuyoCoord.X == BoardSize.X - 1 || Board[MainPuyoCoord.Y][MainPuyoCoord.X + 1] != nullptr || (PuyoTick % 2 == 1 && Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X + 1] != nullptr))
	{
		if (BlockDir == 3)
		{
			if (MainPuyoCoord.X - 1 < 0 || Board[MainPuyoCoord.Y][MainPuyoCoord.X - 1] != nullptr || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X - 1] != nullptr)
			{
				BlockDir = PrevDir;
				return;
			}
			MainPuyoCoord.X -= 1;
			IsKicking = true;
			Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[PrevDir] * PuyoSize.iX(), Dy[PrevDir] * PuyoSize.iY()));
		}
	}
	if (PuyoTick % 2 == 1)
	{
		if (MainPuyoCoord.Y + 1 == BoardSize.Y - 1 || Board[MainPuyoCoord.Y + 2][MainPuyoCoord.X] != nullptr)
		{
			if (BlockDir == 2)
			{
				if (MainPuyoCoord.Y + 1 == BoardSize.Y - 1 || Board[MainPuyoCoord.Y + 2][MainPuyoCoord.X] != nullptr)
				{
					PuyoTick--;
					IsKicking = true;
				}
			}
		}
	}
	IsRotatedClockWise = _IsClockwise;
	NeedToRotate = 90;
	IsRotating = true;
}


void APuyoBoard::PuyoForceDown()
{
	if (CurStep != EPuyoLogicStep::PuyoMove)
	{
		return;
	}
	if (ForceDownTimer < 0.0f)
	{
		PuyoDropTimer = 0.0f;
		ForceDownTimer = 0.03f;
		if (PuyoTick % 2 == 0)
		{
			DropBonus++;
			ScoreActor->Add(1);
		}
	}
}

void APuyoBoard::SpawnChainText()
{
	APuyoChainText* Text = GetWorld()->SpawnActor<APuyoChainText>();
	Text->SetActorLocation(GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()));
	Text->SetupChainText(Rensa, BoardColor);
}


void APuyoBoard::SpawnAttack(int _Amount, FVector2D _StartPos, bool _IsOffset) // ���ػѿ� � ��������
{
	APuyoChainFX* ChainFX = GetWorld()->SpawnActor<APuyoChainFX>();
	ChainFX->SetActorLocation(_StartPos);
	APuyoWarn* Target = nullptr;
	FVector2D MyLocation = GetActorLocation() + FVector2D(PuyoSize.X * 3.0f, 32.0f);
	FVector2D OpLocation = CounterBoardActor->GetActorLocation() + FVector2D(PuyoSize.X * 3.0f, 32.0f);
	bool IsCounter = _Amount < 0;

	if (_IsOffset)
	{
		Target = this->WarnActor;
		ChainFX->SetupChainFX(Target, _StartPos, MyLocation, BoardColor, IsCounter, 0.5f, CounterBoardActor->WarnActor, OpLocation);
	}
	else
	{
		Target = CounterBoardActor->WarnActor;
		ChainFX->SetupChainFX(Target, _StartPos, OpLocation, BoardColor, IsCounter, 0.5f);

	}
}

void APuyoBoard::SpawnNuisancePuyo()
{

	int DropAmount = FEngineMath::Min(30, WarnActor->GetWarnNum()); // �ִ� 5�پ�����߸� �� �ִ�.
	WarnActor->SubWarnNum(DropAmount);
	std::vector<APuyo*> DropList;
	//����߷��� �ϴ� ������ŭ �����Ѵ�.
	for (int i = 0; i < DropAmount; i++)
	{
		APuyo* GarbagePuyo = GetWorld()->SpawnActor<APuyo>();
		DropList.push_back(GarbagePuyo);
	}

	// �ϴ� �������� ��(=6)���� ũ�� Height�� ��ŭ ä��� �����Ѵ�.
	int Height = DropAmount / BoardSize.X;
	for (int Y = 0; Y < Height; Y++)
	{
		for (int X = 0; X < BoardSize.X; X++)
		{
			int Index = BoardSize.X * Y + X;
			DropList[Index]->SetupPuyo(GetActorLocation() + FVector2D(PuyoSize.X * X, -PuyoSize.Y * Y), EPuyoColor::Garbage);
			for (int Y = BoardSize.Y - 1; Y >= 0; Y--)
			{
				if (Board[Y][X] == nullptr)
				{
					Board[Y][X] = DropList[Index];
					Board[Y][X]->SetTargetXY({ X, Y });
					PlaceCheckList.push_back(Board[Y][X]);
					break;
				}
			}
		}
	}

	int Index = Height * BoardSize.X;
	std::vector<int> XLines(BoardSize.X);
	for (int i = 0; i < BoardSize.X; i++)
	{
		XLines[i] = i;
	}

	//���� Ƚ���� �׳� ���� �ε����� �̾ƺ���.
	int Range = BoardSize.X - 1;
	for (int i = 0; i < DropAmount % BoardSize.X; i++)
	{
		int Pick = RandomDevice.GetRandomInt(0, static_cast<int>(XLines.size() - 1));
		int X = XLines[Pick];
		std::swap(XLines[Pick], XLines[XLines.size() - 1]);
		XLines.pop_back();
		DropList[Index]->SetupPuyo(GetActorLocation() + FVector2D(PuyoSize.X * X, -PuyoSize.Y * Height), EPuyoColor::Garbage);
		for (int Y = BoardSize.Y - 1; Y >= 0; Y--)
		{
			if (Board[Y][X] == nullptr)
			{
				Board[Y][X] = DropList[Index];
				Board[Y][X]->SetTargetXY({ X, Y });
				PlaceCheckList.push_back(Board[Y][X]);
				break;
			}
		}
		Index++;
	}

}


