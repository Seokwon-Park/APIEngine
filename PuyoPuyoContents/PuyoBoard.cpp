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

	// 회전
	// Todo : 인자 받아서 회전방향 시계방향, 반시계방향 결정하고 키 따로 두기?
	UEngineInput::GetInstance().BindAction(Key::Up, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, this));
	// 빠른 낙하
	UEngineInput::GetInstance().BindAction(Key::Down, KeyEvent::Down, std::bind(&APuyoBoard::PuyoForceDown, this));
	// 좌우 이동
	UEngineInput::GetInstance().BindAction(Key::Left, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::LEFT));
	UEngineInput::GetInstance().BindAction(Key::Right, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::RIGHT));

	// Todo : BeginPlay는 임시위치, 게임시작 애니메이션이 끝나고 렌더링 되어야 함.
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

	// Todo : 여기서 시작 애니메이션이 안끝났으면 계속 Return하도록 설정?
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
	// 대충 생각해본 로직

	Block = NextBlock;
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = Block[i];
		Puyo->SetActorLocation(GetLocationByIndex(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[Dir] * i, MainPuyoCoord.Y + Dy[Dir] * i), 0);
	}


	// 이 과정에서 NextNextBlock이 NextBlock칸으로 부드럽게 이동해야 된다.
	NextBlock = NextNextBlock;
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(7, 4 + Dy[BlockDir] * i));
	}
	//새로 생성된 NextNextBlock은 설정된 로케이션으로 이동해야 한다.
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(8, 5 + Dy[BlockDir] * i));
	}

	//0번 블록이 MainPuyo가 된다.
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

		// 더 이상 내려갈 수 없으면
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

		// 보드에서 떨어져야 할 블럭이 있는지 체크해서 업데이트 하는 부분.
		// 체크해야할 모든 블럭에 대해 돌리자.
		// 블록은 반칸씩 떨어졌다면 여기서는 부드럽게 떨어지는 느낌임.(Lerp? MoveTowards?)
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
		// 모든 블럭에 대해 위치 완료 애니메이션이 끝나야 넘어간다.
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
		// 로직상 CurPuyo는 nullptr일 수 없는데 체크해야하나?
		APuyo* CurPuyo = Board[Y][X];
		for (int i = 0; i < 4; i++)
		{
			int Dir = i;
			int TargetX = X + Dx[Dir];
			int TargetY = Y + Dy[Dir];
			// 범위가 보드 밖이면 조사하면 안된다.
			if (TargetX < 0 || TargetY < 0 || TargetX >= BoardSize.X || TargetY >= BoardSize.Y)
			{
				continue;
			}
			APuyo* NearPuyo = Board[TargetY][TargetX];
			// 이웃 뿌요가 null이어도 조사하면 안된다.
			if (NearPuyo == nullptr)
			{
				continue;
			}
			// 이웃 뿌요와 현재 뿌요의 색깔이 같은 경우
			if (NearPuyo->GetColor() == CurPuyo->GetColor())
			{
				// 이웃뿌요의 스프라이트도 현재 뿌요와 이어져야 하기 때문에 업데이트 해준다.
				// Todo: 좀더 간단하게 할 방법이 있나?
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
	// Place한 각 점에 대해서 BFS 기반탐색을 돌려서 4개 이상인 경우를 찾고 파괴할 리스트를 만든다.
	// 원래 있던 점들은 조사할 필요가 없다.
	for (FIntPoint Point : PuyoCheckList)
	{
		// 추후 BFS 함수로 추출
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
	}

	PuyoDestroyList.clear();

	CurStep = EPuyoLogicStep::PuyoUpdate;
}

void APuyoBoard::PuyoUpdateLogic()
{
	CurStep = EPuyoLogicStep::PuyoCreate;
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
	//Todo : 이것도 바로 Set을 안하고 부드럽게 움직이게 해야함.
	Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[BlockDir] * PuyoSize.iX(), Dy[BlockDir] * PuyoSize.iY()));
	//Todo : 회전시 예외에 대한 처리. 아직 어떻게 해야할지 모르겠다.
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
