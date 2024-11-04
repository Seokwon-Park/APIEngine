#include "aepch.h"
#include "PuyoBoard.h"

#include <algorithm>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>

APuyoBoard::APuyoBoard()
	:Difficulty(3), Offset(FVector2D::ZERO), PuyoSize(FVector2D::ZERO), BoardSize(FIntPoint::ZERO),
	MainPuyoCoord(FIntPoint::ZERO),	PuyoDropDelay(.1f), PuyoDropTimer(0.0f), PuyoTick(0), BlockDir(0),
	CurStep(EPuyoLogicStep::PuyoCreate), Block(std::vector<APuyo*>(2))
	//,Board(std::vector<std::vector<APuyo*>>(13, std::vector<APuyo*>(6, nullptr)))
{
}

APuyoBoard::~APuyoBoard()
{
}

void APuyoBoard::BeginPlay()
{
	Super::BeginPlay();
	PuyoDropTimer = PuyoDropDelay;

	// ȸ��
	// Todo : ���� �޾Ƽ� ȸ������ �ð����, �ݽð���� �����ϰ� Ű ���� �α�?
	UEngineInput::GetInstance().BindAction(Key::Up, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, this));
	// ���� ����
	UEngineInput::GetInstance().BindAction(Key::Down, KeyEvent::Down, std::bind(&APuyoBoard::PuyoForceDown, this));
	// �¿� �̵�
	UEngineInput::GetInstance().BindAction(Key::Left, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::LEFT));
	UEngineInput::GetInstance().BindAction(Key::Right, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::RIGHT));

	// Todo : BeginPlay�� �ӽ���ġ, ���ӽ��� �ִϸ��̼��� ������ ������ �Ǿ�� ��.
	NextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(7, 4 + Dy[BlockDir] * i));
	}
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(8, 5 + Dy[BlockDir] * i));
	}


}

void APuyoBoard::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// Todo : ���⼭ ���� �ִϸ��̼��� �ȳ������� ��� Return�ϵ��� ����?
	UEngineDebugHelper::PushString("X = " + std::to_string(MainPuyoCoord.X) + ", Y = " + std::to_string(MainPuyoCoord.Y));
	UEngineDebugHelper::PushString("Timer = " + std::to_string(PuyoDropTimer));
	UEngineDebugHelper::PushString("CurStep = " + std::to_string(static_cast<int>(CurStep)));
	switch (CurStep)
	{
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
	default:
		break;
	}
}

void APuyoBoard::SetupPuyoBoard(FVector2D _Offset, FVector2D _PuyoSize, int _Difficulty, FIntPoint _BoardSize )
{
	Difficulty = _Difficulty;
	Offset = _Offset;
	PuyoSize = _PuyoSize;
	BoardSize = _BoardSize;
	Board.clear();
	Board.resize(BoardSize.Y, std::vector<APuyo*>(BoardSize.X, nullptr));
}

std::vector<APuyo*> APuyoBoard::CreatePuyoBlock()
{
	std::vector<APuyo*> NewBlock(2, nullptr);
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = GetWorld()->SpawnActor<APuyo>();
		Puyo->SetupPuyo(GetLocationByIndex((BoardSize.X - 1) / 2 + Dx[BlockDir] * i, 1 + Dy[BlockDir] * i), RandomDevice.GetRandomInt(0, Difficulty));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i), 0);
		NewBlock[i] = Puyo;
	}

	return NewBlock;
}


void APuyoBoard::PuyoCreateLogic()
{
	BlockDir = 0;
	MainPuyoCoord.X = (BoardSize.X - 1) / 2;
	MainPuyoCoord.Y = 1;
	// ���� �����غ� ����

	Block = NextBlock;
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = Block[i];
		Puyo->SetActorLocation(GetLocationByIndex(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[Dir] * i, MainPuyoCoord.Y + Dy[Dir] * i), 0);
	}


	// �� �������� NextNextBlock�� NextBlockĭ���� �ε巴�� �̵��ؾ� �ȴ�.
	NextBlock = NextNextBlock;
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(7, 4 + Dy[BlockDir] * i));
	}
	//���� ������ NextNextBlock�� ������ �����̼����� �̵��ؾ� �Ѵ�.
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(8, 5 + Dy[BlockDir] * i));
	}

	//0�� ����� MainPuyo�� �ȴ�.
	Block[0]->PlayAnimation("AxisPuyoIdle");
	/*APuyo* Puyo1 = GetWorld()->SpawnActor<APuyo>();
	Puyo1->SetupPuyo(GetPosByIndex(MainPuyoCoord.X, MainPuyoCoord.Y), UEngineRandom::GetRandomInt(0, 4));
	APuyo* Puyo2 = GetWorld()->SpawnActor<APuyo>();
	Puyo2->SetupPuyo(GetPosByIndex(MainPuyoCoord.X + Dx[Dir], MainPuyoCoord.Y + Dy[Dir]), UEngineRandom::GetRandomInt(0, 4));*/

	CurStep = EPuyoLogicStep::PuyoMove;
}

void APuyoBoard::PuyoMoveLogic()
{
	PuyoDropTimer -= UEngineAPICore::GetEngineDeltaTime();
	if (PuyoDropTimer >= 0.0f)return;
	PuyoTick++;
	PuyoTick %= 2;
	for (auto Puyo : Block)
	{
		Puyo->AddActorLocation(FVector2D(0.0f, PuyoSize.Half().Y));
		//Puyo->SetActorLocation(FVector2D::Lerp(Puyo->GetActorLocation(), Puyo->GetActorLocation() + FVector2D(0,32),UEngineAPICore::GetCore()->GetDeltaTime()));
	}
	if (PuyoTick == 0)
	{
		MainPuyoCoord.Y++;

		// �� �̻� ������ �� ������
		if (false == CanMoveDown())
		{
			for (int i = 0; i < 2; i++)
			{
				int X = MainPuyoCoord.X + Dx[BlockDir] * i;
				int Y = MainPuyoCoord.Y + Dy[BlockDir] * i;
				Block[i]->SetActorLocation(GetLocationByIndex(X, Y));
				PlaceCheckList.push_back({ X, Y });
				Board[Y][X] = Block[i];
			}

			CurStep = EPuyoLogicStep::PuyoPlace;
			return;
		}
	}

	PuyoDropTimer = PuyoDropDelay;
}

void APuyoBoard::PuyoPlaceLogic()
{
	if (!PlaceCheckList.empty())
	{
		sort(PlaceCheckList.begin(), PlaceCheckList.end(), [](auto _A, auto _B)
			{
				if (_A.Y == _B.Y)
				{
					return _A.X < _B.X;
				}
				return _A.Y > _B.Y;
			}
		);

		// ���忡�� �������� �� ���� �ִ��� üũ�ؼ� ������Ʈ �ϴ� �κ�.
		// üũ�ؾ��� ��� ���� ���� ������.
		// ����� ��ĭ�� �������ٸ� ���⼭�� �ε巴�� �������� ������.(Lerp? MoveTowards?)
		for (FIntPoint& Point : PlaceCheckList)
		{
			APuyo* CurPuyo = Board[Point.Y][Point.X];
			int PlaceY = Point.Y;
			while (PlaceY + 1 < BoardSize.Y && Board[PlaceY + 1][Point.X] == nullptr) { PlaceY++; }
			if (false == CurPuyo->IsDropComplete)
			{
				if (PlaceY == Point.Y)
				{
					CurPuyo->PlayAnimation("PlaceComplete");
					CurPuyo->IsDropComplete = true;
				}
				else
				{
					CurPuyo->SetActorLocation(FVector2D::MoveTowards(CurPuyo->GetActorLocation(), GetLocationByIndex(Point.X, PlaceY), 2.0f));
					if (CurPuyo->GetActorLocation().Distance(GetLocationByIndex(Point.X, PlaceY)) < 0.1f)
					{
						Board[Point.Y][Point.X] = nullptr;
						Point = FIntPoint(Point.X, PlaceY);
						Board[PlaceY][Point.X] = CurPuyo;
						CurPuyo->PlayAnimation("PlaceComplete");
						CurPuyo->IsDropComplete = true;
					}
				}
			}
		}
		// ��� ���� ���� ��ġ �Ϸ� �ִϸ��̼��� ������ �Ѿ��.
		bool CheckAllFinished = true;
		for (FIntPoint Point : PlaceCheckList)
		{
			APuyo* CurPuyo = Board[Point.Y][Point.X];
			if (CurPuyo->IsAnimationEnd == false)
			{
				CheckAllFinished = false;
				break;
			}
		}
		if (!CheckAllFinished)
			return;
	}
	for (FIntPoint Point : PlaceCheckList)
	{
		Board[Point.Y][Point.X]->IsAnimationEnd = false;
	}

	PuyoConnectList = PlaceCheckList;
	PlaceCheckList.clear();

	CurStep = EPuyoLogicStep::PuyoConnect;
}

void APuyoBoard::PuyoConnectLogic()
{
	//SetConnection
	for (FIntPoint Point : PuyoConnectList)
	{
		auto [X, Y] = Point;
		int SpriteIndex = 0;
		// ������ CurPuyo�� nullptr�� �� ���µ� üũ�ؾ��ϳ�?
		APuyo* CurPuyo = Board[Y][X];
		for (int i = 0; i < 4; i++)
		{
			int Dir = i;
			int TargetX = X + Dx[Dir];
			int TargetY = Y + Dy[Dir];
			// ������ ���� ���̸� �����ϸ� �ȵȴ�.
			if (TargetX < 0 || TargetY < 0 || TargetX >= BoardSize.X || TargetY >= BoardSize.Y)
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
	PuyoCheckList = PuyoConnectList;
	PuyoConnectList.clear();

	CurStep = EPuyoLogicStep::PuyoCheck;
}


void APuyoBoard::PuyoCheckLogic()
{
	// Place�� �� ���� ���ؼ� BFS ���Ž���� ������ 4�� �̻��� ��츦 ã�� �ı��� ����Ʈ�� �����.
	// ���� �ִ� ������ ������ �ʿ䰡 ����.
	for (FIntPoint Point : PuyoCheckList)
	{
		// ���� BFS �Լ��� ����
		std::vector<std::vector<bool>> Visited(BoardSize.Y, std::vector<bool>(BoardSize.X ,false));
		std::queue<FIntPoint> Queue;
		std::vector<FIntPoint> Temp;

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
				if (TargetX < 0 || TargetY < 0 || TargetX >= BoardSize.X || TargetY >= BoardSize.Y || true == Visited[TargetY][TargetX])
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
					Queue.push(FIntPoint(TargetX,TargetY));
					Temp.push_back(FIntPoint(TargetX, TargetY));
					Visited[TargetY][TargetX] = true;
				}
			}
		}

		if (Temp.size() >= 4)
		{
			for (FIntPoint Point : Temp)
			{
				PuyoDestroyList.insert(std::make_pair(Point.X, Point.Y));
			}
		}
	}
	PuyoCheckList.clear();
	
	CurStep = EPuyoLogicStep::PuyoDestroy;
}

void APuyoBoard::PuyoDestroyLogic()
{
	for (auto [X, Y] : PuyoDestroyList)
	{
		APuyo* Puyo = Board[Y][X];
		Puyo->Destroy();
		Board[Y][X] = nullptr;
		PuyoUpdateColumns.push_back(X);
	}

	PuyoDestroyList.clear();

	CurStep = EPuyoLogicStep::PuyoUpdate;
}

void APuyoBoard::PuyoUpdateLogic()
{
	if(PuyoUpdateColumns.empty())
	{
		CurStep = EPuyoLogicStep::PuyoCreate;
	}
	else
	{
		for (int X : PuyoUpdateColumns)
		{
			int Start = BoardSize.Y - 1;
			for (int i = BoardSize.Y - 1; i >= 0; i--)
			{
				if (Board[i][X] == nullptr)
				{
					Start = i;
					break;
				}				
			}

			for (int i = Start; i >= 0; i--)
			{
				if (Board[i][X] != nullptr)
				{
					Board[i][X]->IsDropComplete = false;
					Board[i][X]->SetSprite(0);
					PlaceCheckList.push_back(FIntPoint(X, i));
				}
			}
		}
		PuyoUpdateColumns.clear();
		CurStep = EPuyoLogicStep::PuyoPlace;
	}

}

FVector2D APuyoBoard::GetLocationByIndex(int _X, int _Y)
{
	return FVector2D(Offset.iX() + _X * PuyoSize.iX(), Offset.iY() + _Y * PuyoSize.iY());
}

bool APuyoBoard::CanMoveDown()
{
	if (MainPuyoCoord.Y + Dy[BlockDir] + 1 >= Board.size() ||
		MainPuyoCoord.Y + 1 >= Board.size() ||
		Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X] != nullptr ||
		Board[MainPuyoCoord.Y + Dy[BlockDir] + 1][MainPuyoCoord.X + Dx[BlockDir]] != nullptr)
	{
		return false;
	}
	/*switch(Dir)
	{
	case 0:
		if (MainPuyoCoord.Y + 1 >= Board.size() || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X] != nullptr)
			return false;
		break;
	case 1:
		if (MainPuyoCoord.Y + 1 >= Board.size() || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X] != nullptr || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X+1] != nullptr)
			return false;
		break;
	case 2:
		if (MainPuyoCoord.Y + 2 >= Board.size() || Board[MainPuyoCoord.Y + 2][MainPuyoCoord.X] != nullptr)
			return false;
		break;
	case 3:
		if (MainPuyoCoord.Y + 1 >= Board.size() || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X] != nullptr || Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X - 1] != nullptr)
			return false;
		break;
	}*/

	return true;
}

bool APuyoBoard::CanMoveLR(FVector2D _Dir)
{
	if (MainPuyoCoord.X + _Dir.iX() < 0 || MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX() < 0 ||
		MainPuyoCoord.X + _Dir.iX() >= BoardSize.X || MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX() >= BoardSize.X ||
		Board[MainPuyoCoord.Y][MainPuyoCoord.X + _Dir.iX()] != nullptr ||
		Board[MainPuyoCoord.Y + Dy[BlockDir]][MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX()] != nullptr ||
		Board[MainPuyoCoord.Y + 1][MainPuyoCoord.X + _Dir.iX()] != nullptr ||
		Board[MainPuyoCoord.Y + Dy[BlockDir] + 1][MainPuyoCoord.X + Dx[BlockDir] + _Dir.iX()] != nullptr)
	{
		return false;
	}
	return true;

}

void APuyoBoard::MoveLR(FVector2D _Dir)
{
	if (CurStep != EPuyoLogicStep::PuyoMove)
	{
		return;
	}
	if (false == CanMoveLR(_Dir))
	{
		return;
	}

	/*switch (Dir)
	{
	case 0:
		if (MainPuyoCoord.X + _Dir.iX() < 0 || MainPuyoCoord.X + _Dir.iX() >= Board[0].size())return;
		break;
	case 1:
		if (MainPuyoCoord.X + _Dir.iX() < 0 || MainPuyoCoord.X + 1 + _Dir.iX() >= Board[0].size())return;
		break;
	case 2:
		if (MainPuyoCoord.X + _Dir.iX() < 0 || MainPuyoCoord.X + _Dir.iX() >= Board[0].size())return;
		break;
	case 3:
		if (MainPuyoCoord.X - 1 + _Dir.iX() < 0 || MainPuyoCoord.X + _Dir.iX() >= Board[0].size())return;
		break;
	}*/
	MainPuyoCoord.X += _Dir.iX();
	for (int i = 0; i < 2; i++)
	{
		Block[i]->AddActorLocation(_Dir * PuyoSize.X);
	}
	/*Block[0]->AddActorLocation(_Dir * PuyoSize.iX());
	Block[1]->AddActorLocation(_Dir * PuyoSize.iX());*/
}

void APuyoBoard::Rotate()
{
	if (CurStep != EPuyoLogicStep::PuyoMove)
	{
		return;
	}
	BlockDir = (BlockDir + 3) % 4;
	//Todo : �̰͵� �ٷ� Set�� ���ϰ� �ε巴�� �����̰� �ؾ���.
	Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[BlockDir] * PuyoSize.iX(), Dy[BlockDir] * PuyoSize.iY()));
	//Todo : ȸ���� ���ܿ� ���� ó��. ���� ��� �ؾ����� �𸣰ڴ�.
	/*switch (Dir)
	{
	case 0:
		Block[1]->SetActorLocation(Block[0]->GetActorLocation() - FVector2D(0, 32));
		break;
	case 1:
		Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(32, 0));
		break;
	case 2:
		Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(0, 32));
		break;
	case 3:
		Block[1]->SetActorLocation(Block[0]->GetActorLocation() - FVector2D(32, 0));
		break;
	}*/

}

void APuyoBoard::PuyoForceDown()
{
	if (CurStep != EPuyoLogicStep::PuyoMove)
	{
		return;
	}
	PuyoDropTimer -= 0.5f;
}
