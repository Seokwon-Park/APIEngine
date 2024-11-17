#include "aepch.h"
#include "PuyoBoard.h"
#include "PuyoText.h"
#include "PuyoBoomFX.h"
#include "PuyoChainText.h"
#include "PuyoChainFX.h"
#include "ScoringTable.h"


#include <algorithm>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>
#include <EngineCore/ImageManager.h>

APuyoBoard::APuyoBoard()
	:Difficulty(3), PuyoSize(FVector2D::ZERO), BoardSize(FIntPoint::ZERO),
	MainPuyoCoord(FIntPoint::ZERO), PuyoDropDelay(.5f), PuyoDropTimer(0.0f), PuyoTick(0), BlockDir(0),
	CurStep(EPuyoLogicStep::PuyoCreate), Block(std::vector<APuyo*>(2))
	//,Board(std::vector<std::vector<APuyo*>>(13, std::vector<APuyo*>(6, nullptr)))
{
	// 예고 뿌요
	Warnings.resize(6, nullptr);
	for (int i = 0; i < 6; i++)
	{
		Warnings[i] = CreateDefaultSubobject<USpriteRendererComponent>("Warn" + std::to_string(i));
		Warnings[i]->SetRemoveBackground(true);
		Warnings[i]->SetOrder(100);
		Warnings[i]->SetActive(false);
	}
}

void APuyoBoard::SmoothRotate(FVector2D _SlavePuyoPos, FVector2D _MainPuyoPos, float _DeltaTime, bool _IsClockwise) {
	// 각도를 deltaTime에 비례해 보간하여 점진적으로 증가 

	// 90도 : 1초 = dAngle : _DeltaTime로 dAngle구하기
	float dAngle = 90.0f * _DeltaTime / 0.1f * (_IsClockwise ? 1.0f : -1.0f);
	//남은 회전각도 이걸로 판단해야 회전오류 안남
	NeedToRotate -= abs(dAngle);
	// 회전 변환 계산 (라디안으로 변환 필요)
	float AngleInRadians = FEngineMath::DegreesToRadians(dAngle);
	float CosTheta = std::cos(AngleInRadians);
	float SinTheta = std::sin(AngleInRadians);


	// 원점 기준 회전 후 Main Puyo 위치로 이동
	FVector2D RelativePosition = _SlavePuyoPos - _MainPuyoPos;
	float RotatedX = RelativePosition.X * CosTheta - RelativePosition.Y * SinTheta;
	float RotatedY = RelativePosition.X * SinTheta + RelativePosition.Y * CosTheta;

	FVector2D TargetLocation = Block[0]->GetActorLocation() + FVector2D(Dx[BlockDir] * PuyoSize.iX(), Dy[BlockDir] * PuyoSize.iY());
	// 새로운 Slave Puyo 위치
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

APuyoBoard::~APuyoBoard()
{
}

void APuyoBoard::BeginPlay()
{
	Super::BeginPlay();
	PuyoDropTimer = PuyoDropDelay;

	// 회전
	// Todo : 인자 받아서 회전방향 시계방향, 반시계방향 결정하기, 추가키설정 허용?
	GetWorld()->GetInputSystem().BindAction(CWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, this, true));
	GetWorld()->GetInputSystem().BindAction(CCWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, this, false));

	// 빠른 낙하
	GetWorld()->GetInputSystem().BindAction(DownKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoForceDown, this));

	// 좌우 이동
	GetWorld()->GetInputSystem().BindAction(LeftKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, this, FVector2D::LEFT));
	GetWorld()->GetInputSystem().BindAction(RightKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, this, FVector2D::RIGHT));

	// Todo : BeginPlay는 임시위치, 게임시작 애니메이션이 끝나고 렌더링 되어야 함.
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

	if (IsKicking)
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
	if (IsRotating)
	{
		SmoothRotate(Block[1]->GetActorLocation(), Block[0]->GetActorLocation(), UEngineAPICore::GetEngineDeltaTime(), IsRotatedClockWise);
	}


	// Todo : 여기서 시작 애니메이션이 안끝났으면 계속 Return하도록 설정?
	//UEngineDebugHelper::PushString("X = " + std::to_string(MainPuyoCoord.X) + ", Y = " + std::to_string(MainPuyoCoord.Y));
	//UEngineDebugHelper::PushString("Timer = " + std::to_string(PuyoDropTimer));
	//UEngineDebugHelper::PushString("PuyoTick = " + std::to_string(PuyoTick));
	//UEngineDebugHelper::PushString("SlaveCoord = " + FIntPoint(MainPuyoCoord.X + Dx[BlockDir], MainPuyoCoord.Y + Dy[BlockDir]).ToString());
	//UEngineDebugHelper::PushString("CurStep = " + std::to_string(static_cast<int>(CurStep)));
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

void APuyoBoard::SetupPuyoBoard(const PuyoBoardSettings& _Settings)
{
	Difficulty = _Settings.Difficulty;
	PuyoSize = _Settings.PuyoSize;
	BoardSize = _Settings.BoardSize;
	NextBlockCoord = _Settings.NextBlockCoord;
	NextNextBlockCoord = _Settings.NextNextBlockCoord;
	Score = _Settings.Score;
	CounterBoard = _Settings.CounterBoard;
	Shaker = _Settings.Shaker;
	Board.clear();
	Board.resize(BoardSize.Y, std::vector<APuyo*>(BoardSize.X, nullptr));
}

void APuyoBoard::SetKey(int _CWRotate, int _CCWRotate, int _Down, int _Left, int _Right)
{
	CWRotateKey = _CWRotate;
	CCWRotateKey = _CCWRotate;
	DownKey = _Down;
	LeftKey = _Left;
	RightKey = _Right;
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
	//게임오벌,,,
	if (Board[1][2] != nullptr)
	{
		return;
	}

	//더해야될 점수가 있으면 더해
	Score->Add(ScoreToAdd);
	ScoreToAdd = 0;


	Rensa = 0; // 여기로 오게되면 연쇄는 0

	//처음 블록방향은 위쪽, 처음 블록 위치는 고스트라인(=0번줄)
	BlockDir = 0;
	MainPuyoCoord.X = (BoardSize.X - 1) / 2;
	MainPuyoCoord.Y = 0;
	// 대충 생각해본 로직

	Block = NextBlock;
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = Block[i];
		Puyo->SetActorLocation(GetLocationByIndexOnBoard(MainPuyoCoord.X + Dx[BlockDir] * i, MainPuyoCoord.Y + Dy[BlockDir] * i));
		//Puyo->SetupPuyo(GetLocationByIndex(MainPuyoCoord.X + Dx[Dir] * i, MainPuyoCoord.Y + Dy[Dir] * i), 0);
	}

	// 이 과정에서 NextNextBlock이 NextBlock칸으로 부드럽게 이동해야 된다.
	NextBlock = NextNextBlock;
	for (int i = 0; i < 2; i++)
	{
		NextBlock[i]->SetActorLocation(GetLocationByIndex(NextBlockCoord.X, NextBlockCoord.Y + Dy[BlockDir] * i));
	}

	//새로 생성된 NextNextBlock은 설정된 로케이션으로 이동해야 한다.
	NextNextBlock = CreatePuyoBlock();
	for (int i = 0; i < 2; i++)
	{
		NextNextBlock[i]->SetActorLocation(GetLocationByIndex(NextNextBlockCoord.X, NextNextBlockCoord.Y + Dy[BlockDir] * i));
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
	// 정해진 시간이 지나면 뿌요를 내린다.
	if (PuyoDropTimer >= 0.0f)
	{
		return;
	}
	PuyoTick++;
	// 위치상으로 내릴 수 있는지 확인한다.
	if (true == CanMoveLocation())
	{
		for (auto Puyo : Block)
		{
			Puyo->AddActorLocation(FVector2D(0.0f, PuyoSize.Half().Y));
			//Puyo->SetActorLocation(FVector2D::Lerp(Puyo->GetActorLocation(), Puyo->GetActorLocation() + FVector2D(0,32),UEngineAPICore::GetCore()->GetDeltaTime()));
		}
	}
	MainPuyoCoord.Y += (PuyoTick % 2 == 0);

	//Todo: 밑에 내려와도 딜레이가 있어야 되는데 어케 고치지
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
			if (BlockDir % 2 == 1) // 가로로 누운 블럭인 경우
			{
				int PlaceY = Y;
				while (PlaceY + 1 < BoardSize.Y && Board[PlaceY + 1][X] == nullptr) { PlaceY++; }
				Block[i]->SetTargetXY({ X,PlaceY });
			}
			SetPuyoOnBoard(Block[i]->GetTargetXY(), Block[i]);
			PuyoTick = 0;
		}

		//Todo : 방해뿌요 떨구는 로직 (상대방의 연쇄가 진행중이 아닐때) 상쇄랑 관련해서 이 코드의 위치를 아직 모르겠음...
		//일단 방해뿌요가 내보드에 존재하면 파괴 로직 단계에서 상쇄검사를 하십쇼.
		if (WarnNums > 0 && !CounterBoard->IsChaining)
		{
			CheckOffset = true;
			//SpawnNuisancePuyo();
		}
		CurStep = EPuyoLogicStep::PuyoPlace;
		return;
	}

	PuyoDropTimer = PuyoDropDelay;
}



void APuyoBoard::PuyoPlaceLogic()
{

	if (!PlaceCheckList.empty())
	{
		// 이부분은 set으로 대체되었다.
		//sort(PlaceCheckList.begin(), PlaceCheckList.end(), [](auto _A, auto _B)
		//	{
		//		if (_A.Y == _B.Y)
		//		{
		//			return _A.X < _B.X;
		//		}
		//		return _A.Y > _B.Y;
		//	}
		//);

		// 보드에서 떨어져야 할 블럭이 있는지 체크해서 업데이트 하는 부분.
		// 체크해야할 모든 블럭에 대해 돌리자.
		// 블록은 반칸씩 떨어졌다면 여기서는 좀더 스무스하게 떨어지는 느낌임.
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
						CurPuyo->PlayAnimation("PlaceComplete");
						CurPuyo->SetIsDropComplete(true);
					}
				}
			}
		}
		// 모든 블럭에 대해 위치 완료 애니메이션이 끝나야 넘어간다.
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
		PuyoConnectList.push_back(CurPuyo);
	}

	PlaceCheckList.clear();

	CurStep = EPuyoLogicStep::PuyoConnect;
}

void APuyoBoard::PuyoConnectLogic()
{
	//SetConnection
	for (APuyo* CurPuyo : PuyoConnectList)
	{
		if (CurPuyo->GetColor() == EPuyoColor::Garbage) continue;
		int X = CurPuyo->GetCurXY().X;
		int Y = CurPuyo->GetCurXY().Y;
		int SpriteIndex = 0;
		for (int i = 0; i < 4; i++)
		{
			int Dir = i;
			int TargetX = X + Dx[Dir];
			int TargetY = Y + Dy[Dir];
			// 범위가 보드 밖이면 조사하면 안된다.
			if (!IsInBoard(TargetX, TargetY))
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
	// Place한 각 점에 대해서 BFS 기반탐색을 돌려서 4개 이상인 경우를 찾고 파괴할 리스트를 만든다.
	// 원래 있던 점들은 조사할 필요가 없다.
	for (FIntPoint Point : PuyoCheckList)
	{
		// 추후 BFS 함수로 추출
		std::vector<std::vector<bool>> Visited(BoardSize.Y, std::vector<bool>(BoardSize.X, false));
		std::queue<FIntPoint> Queue;

		// Todo : 룰에따라 4대신 다른값도 쓰일 수 있게 할 예정
		// 현재 위치의 뿌요와 색상이 같은 뿌요의 좌표들이 저장되는 
		// 임시 벡터 사이즈가 4보다 크면 제거목록에 넣음
		std::vector<FIntPoint> Temp;
		// 근처의 방해뿌요도 같이 저장해놓고 4보다 크면 지우자
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
		// Todo: 4대신 다른값 넣으세우
		if (Temp.size() >= 4)
		{
			for (FIntPoint Point : Temp)
			{
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

	if (!PuyoDestroyList.empty())
	{
		Rensa++;
		int PC = static_cast<int>(PuyoDestroyList.size());
		int CP = ChainPowerTable[Rensa];
		//TODO : 컬러보너스 계산해야함
		int CB = ColorBonusTable[1];
		int GB = GroupBonusTable[PC];
		std::string PCText = std::to_string(PC * 10);
		std::string BonusText = std::to_string(CP + CB + GB);
		std::string Display = std::string(4 - PCText.size(), ' ') + PCText + '*' + std::string(3 - BonusText.size(), ' ') + BonusText;
		Score->SetText(Display);
		ScoreToAdd += PC * 10 * (CP + CB + GB);
	}
	PuyoCheckList.clear();

	CurStep = EPuyoLogicStep::PuyoDestroy;
}



void APuyoBoard::PuyoDestroyLogic()
{
	//파괴할게 없어
	if (PuyoDestroyList.empty())
	{
		CurStep = EPuyoLogicStep::PuyoUpdate;
		return;
	}

	IsChaining = true;
	//파괴할게 있어
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

	if (!IsDestroying)
	{
		SpawnChainText();
		//Todo : 방해뿌요량계산공식 추가하십쇼 두번하십쇼 이것도 코드위치 여기 맞는지 확신X
		//NP : 계산된 방해 뿌요 (=AttackAmount)
		int AttackAmount = RandomDevice.GetRandomInt(6, 12);
		//상쇄 검사가 필요하다면
		if (CheckOffset)
		{
			CheckOffset = false;
			// Todo: WarnNums에 따른 순서때문에 따로 적어야함 나중에 고칠것.
			// +추가 지금 로직에도 문제가 좀 있음,
			//내가 상쇄하는 양이 더 적으면
			if (AttackAmount < WarnNums)
			{
				//Todo: 이경우에는 
				WarnNums -= AttackAmount;
				AttackAmount = 0;
				SpawnAttack(AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()));
			}
			//내가 상쇄하는 양이 더 많으면
			else
			{
				AttackAmount -= WarnNums;
				SpawnAttack(AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()));
				WarnNums = 0;
			}
			UpdateWarning();
		}
		else
		{
			SpawnAttack(AttackAmount, GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()));
		}
		int ix = 0;
		for (auto [X, Y] : PuyoDestroyList)
		{
			APuyo* CurPuyo = Board[Y][X];
			if (CurPuyo->GetColor() != EPuyoColor::Garbage)
			{
				CurPuyo->PlayAnimation("Boom");
				SpawnDestroyFX(CurPuyo->GetActorLocation(), CurPuyo->GetColor(), 0.05f + ix * 0.1f);
				ix++;
			}
		}
		//여기서 공격한다.
		IsDestroying = true;
	}

	// 모든 블럭에 대해 파괴 완료 애니메이션이 끝나야 넘어간다.
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
		PuyoUpdateColumns.push_back(X);
	}

	FlickCount = 0;
	IsDestroying = false;
	PuyoDestroyList.clear();

	CurStep = EPuyoLogicStep::PuyoUpdate;
}


void APuyoBoard::PuyoUpdateLogic()
{
	if (WarnNums > 0 && CounterBoard->IsChaining == false)
	{
		// Todo: 현재 직관성이 좀 떨어지는거 같음.
		SpawnNuisancePuyo();
		Shaker->SetEnable();
		CurStep = EPuyoLogicStep::PuyoPlace;
		return;
	}
	if (PuyoUpdateColumns.empty())
	{
		IsChaining = false;
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

bool APuyoBoard::IsInBoard(int TargetX, int TargetY)
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

	// 반칸 겹쳐도 옆으로 못가게 해야함.
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

	//좌우 움직임 꾹 눌렀을때 딜레이
	LRMoveTimer -= UEngineAPICore::GetEngineDeltaTime();
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
	//Todo : 버그 ㅈㄴ생김 지속적 관찰 요망
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
	ForceDownTimer -= UEngineAPICore::GetEngineDeltaTime();
	if (ForceDownTimer < 0.0f)
	{
		PuyoDropTimer = 0.0f;
		ForceDownTimer = 0.05f;
		if (PuyoTick % 2 == 0)
		{
			Score->Add(1);
		}
	}
}

void APuyoBoard::SpawnChainText()
{
	APuyoChainText* Text = GetWorld()->SpawnActor<APuyoChainText>();
	Text->SetActorLocation(GetLocationByIndexOnBoard(*PuyoDestroyList.rbegin()));
	Text->SetupChainText(Rensa, EPuyoTextColor::Red);
}


void APuyoBoard::SpawnAttack(int _Amount, FVector2D _StartPos) // 방해뿌요 몇개 보낼껀지
{
	// Todo: 대충 머 구슬같은거 날라가는 모션 추가해
	APuyoChainFX* ChainFX = GetWorld()->SpawnActor<APuyoChainFX>();
	ChainFX->SetActorLocation(_StartPos);
	FVector2D TargetLocation = CounterBoard->GetActorLocation() + FVector2D(PuyoSize.X * 3.0f, 32.0f);
	if (WarnNums > 0)
	{
		TargetLocation = GetActorLocation() + FVector2D(PuyoSize.X * 3.0f, 32.0f);
	}
	CounterBoard->AddWarnNums(_Amount);
	ChainFX->SetupChainFX(CounterBoard, _StartPos, TargetLocation, _Amount);
}

void APuyoBoard::SpawnNuisancePuyo()
{
	int DropAmount = FEngineMath::Min(WarnNums, 30); // 최대 5줄씩떨어뜨릴 수 있다.
	WarnNums -= DropAmount;
	std::vector<APuyo*> DropList;
	//떨어뜨려야 하는 개수만큼 생성한다.
	for (int i = 0; i < DropAmount; i++)
	{
		APuyo* GarbagePuyo = GetWorld()->SpawnActor<APuyo>();
		DropList.push_back(GarbagePuyo);
	}

	// 일단 게임판의 폭(=6)보다 크면 Height줄 만큼 채우고 시작한다.
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

	//남은 횟수는 그냥 랜덤 인덱스를 뽑아보자.
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

	UpdateWarning();
}

void APuyoBoard::UpdateWarning()
{
	int CurIndex = 0;
	int Temp = WarnNums;
	FVector2D CurLocation = FVector2D(0.0f, PuyoSize.Y);
	for (int i = 0; i < 6; i++)
	{
		Warnings[i]->SetActive(false);
	}
	// i = WarUnitIndex ?머라할지 모르겠다 코드 복잡해짐.
	for (int i = 5; i >= 0; i--)
	{
		if (CalcWarn(i, CurLocation, CurIndex, Temp))
		{
			break;
		}
	}
}

// 만약 6자리가 다찼으면 true를 리턴한다.
bool APuyoBoard::CalcWarn(const int _SpriteIndex, FVector2D& _Offset, int& _CurIndex, int& _Left)
{
	while (_Left >= WarnUnit[_SpriteIndex])
	{
		UEngineSprite::USpriteData CurData = UImageManager::GetInstance().FindSprite("Warning")->GetSpriteData(_SpriteIndex);
		Warnings[_CurIndex]->SetSprite("Warning", _SpriteIndex);
		Warnings[_CurIndex]->SetPivot(EPivotType::BottomLeft);
		Warnings[_CurIndex]->SetComponentLocation(_Offset);
		Warnings[_CurIndex]->SetComponentScale(CurData.Transform.Scale);
		Warnings[_CurIndex]->SetActive(true);
		_Left -= WarnUnit[_SpriteIndex];
		_CurIndex++;
		_Offset += FVector2D(CurData.Transform.Scale.X, 0.0f);
		if (_CurIndex == 6)
		{
			return true;
			break;
		}
	}
	return false;

}
