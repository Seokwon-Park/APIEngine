#include "aepch.h"
#include "PuyoBoard.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>

APuyoBoard::APuyoBoard()
	:Offset(FVector2D::ZERO), PuyoSize(FVector2D::ZERO), BoardSize(FVector2D::ZERO), PuyoDropDelay(.1f),
	PuyoDropTimer(0.0f), PuyoTick(0), BlockX(0), BlockY(0), Dir(0),
	CurStep(EPuyoLogicStep::PuyoCreate), Block(std::vector<APuyo*>(2)),
	Board(std::vector<std::vector<APuyo*>>(13, std::vector<APuyo*>(6, nullptr)))
{
}

APuyoBoard::~APuyoBoard()
{
}

void APuyoBoard::BeginPlay()
{
	Super::BeginPlay();
	PuyoDropTimer = PuyoDropDelay;

	UEngineInput::GetInstance().BindAction(Key::Up, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, this));
	UEngineInput::GetInstance().BindAction(Key::Down, KeyEvent::Down, std::bind(&APuyoBoard::PuyoForceDown, this));
	UEngineInput::GetInstance().BindAction(Key::Left, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::LEFT));
	UEngineInput::GetInstance().BindAction(Key::Right, KeyEvent::Down, std::bind(&APuyoBoard::MoveLR, this, FVector2D::RIGHT));

}

void APuyoBoard::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UEngineDebugHelper::PushString("X = " + std::to_string(BlockX) + ", Y = " + std::to_string(BlockY));
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
	case EPuyoLogicStep::PuyoBlockUpdate:
		PuyoBlockUpdateLogic(_DeltaTime);
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

void APuyoBoard::SetupPuyoBoard(FVector2D _Offset, FVector2D _PuyoSize, FVector2D _BoardSize)
{
	Offset = _Offset;
	PuyoSize = _PuyoSize;
	BoardSize = _BoardSize;
	Board.clear();
	Board.resize(BoardSize.iY(), std::vector<APuyo*>(BoardSize.iX(), nullptr));
}

void APuyoBoard::PuyoCreateLogic()
{
	// 대충 생각해본 로직
	// if(첫 뿌요)
	//    그냥 만들어서 떨군다.
	// else
	//    다음 내려올 뿌요를 가져와서 떨군다.
	// 
	// 다시 다음 내려올 뿌요를 만든다.
	// 
	//임시
	BlockX = (BoardSize.iX() - 1) / 2;
	BlockY = 1;
	Dir = 0;
	//0번 블록이 회전축(=기준)이 된다.
	for (int i = 0; i < 2; i++)
	{
		APuyo* Puyo = GetWorld()->SpawnActor<APuyo>();
		Puyo->SetupPuyo(GetPosByIndex(BlockX + Dx[Dir] * i, BlockY + Dy[Dir] * i), UEngineRandom::GetRandomInt(0, 4));
		Block[i] = Puyo;
	}
	Block[0]->PlayAnimation("AxisPuyoIdle");
	/*APuyo* Puyo1 = GetWorld()->SpawnActor<APuyo>();
	Puyo1->SetupPuyo(GetPosByIndex(BlockX, BlockY), UEngineRandom::GetRandomInt(0, 4));
	APuyo* Puyo2 = GetWorld()->SpawnActor<APuyo>();
	Puyo2->SetupPuyo(GetPosByIndex(BlockX + Dx[Dir], BlockY + Dy[Dir]), UEngineRandom::GetRandomInt(0, 4));*/

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
		Puyo->AddActorLocation(FVector2D(0, PuyoSize.Half().iY()));
		//Puyo->SetActorLocation(FVector2D::Lerp(Puyo->GetActorLocation(), Puyo->GetActorLocation() + FVector2D(0,32),UEngineAPICore::GetCore()->GetDeltaTime()));
	}
	if (PuyoTick == 0)
	{
		BlockY++;
		// 더 이상 내려갈 수 없으면
		if (false == CanMoveDown())
		{
			CurStep = EPuyoLogicStep::PuyoBlockUpdate;
			return;
		}
	}

	PuyoDropTimer = PuyoDropDelay;
}

void APuyoBoard::PuyoBlockUpdateLogic(float _DeltaTime)
{
	// 2개의 블럭중 떨어져야 할 블럭이 있는지 체크해서 업데이트 하는 부분.
	// 이 부분은 블럭이 가로로 놓인 경우에만 체크해주면 된다.
	// 블록은 반칸씩 떨어졌다면 여기서는 Lerp로 떨어지는 느낌임.
	// 여기서 이어줘야 할 녀석이 있다면 이어주기로 하자.
	if (Dir == 1 || Dir == 3)
	{
		// Block[0]
		int AxisPuyoX = BlockX;
		int AxisPuyoY = BlockY;
		// Block[1]
		int RotatePuyoX = BlockX + Dx[Dir];
		int RotatePuyoY = BlockY;

		while (AxisPuyoY + 1 < BoardSize.iY() && Board[AxisPuyoY + 1][AxisPuyoX] == nullptr)
		{
			AxisPuyoY++;
		}

		while (RotatePuyoY + 1 < BoardSize.iY() && Board[RotatePuyoY + 1][RotatePuyoX] == nullptr)
		{
			RotatePuyoY++;
		}

		if (AxisPuyoY == BlockY)
		{
			if (false == Block[0]->IsDropComplete)
			{
				Block[0]->PlayAnimation("DropComplete");
				Block[0]->IsDropComplete = true;
				Board[AxisPuyoY][AxisPuyoX] = Block[0];
			}
		}

		if (RotatePuyoY == BlockY)
		{
			if (false == Block[1]->IsDropComplete)
			{
				Block[1]->PlayAnimation("DropComplete");
				Block[1]->IsDropComplete = true;
				Board[RotatePuyoY][RotatePuyoX] = Block[1];
			}
		}

		if (false == Block[0]->IsDropComplete)
		{
			Block[0]->SetActorLocation(FVector2D::MoveTowards(Block[0]->GetActorLocation(), GetPosByIndex(AxisPuyoX, AxisPuyoY), 2.0f));
			if (Block[0]->GetActorLocation().Distance(GetPosByIndex(AxisPuyoX, AxisPuyoY)) > 0.1f)
			{
				return;
			}
			Block[0]->PlayAnimation("DropComplete");
			Block[0]->IsDropComplete = true;
			Board[AxisPuyoY][AxisPuyoX] = Block[0];
		}
		if (false == Block[1]->IsDropComplete)
		{
			Block[1]->SetActorLocation(FVector2D::MoveTowards(Block[1]->GetActorLocation(), GetPosByIndex(RotatePuyoX, RotatePuyoY), 2.0f));
			if (Block[1]->GetActorLocation().Distance(GetPosByIndex(RotatePuyoX, RotatePuyoY)) > 0.1f)
			{
				return;
			}
			Block[1]->PlayAnimation("DropComplete");
			Block[1]->IsDropComplete = true;
			Board[RotatePuyoY][RotatePuyoX] = Block[1];
		}

	}
	else
	{
		if (false == Block[0]->IsDropComplete)
		{
			Block[0]->PlayAnimation("DropComplete");
			Block[0]->IsDropComplete = true;
		}
		if (false == Block[1]->IsDropComplete)
		{
			Block[1]->PlayAnimation("DropComplete");
			Block[1]->IsDropComplete = true;
		}
		Board[BlockY][BlockX] = Block[0];
		Board[BlockY + Dy[Dir]][BlockX + Dx[Dir]] = Block[1];
	}

	if (false == Block[0]->IsAnimationEnd || false == Block[1]->IsAnimationEnd)
	{
		return;
	}
	//Check Connection
	int SpriteIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		int Dir = (i * 3) % 4;
		if (BlockY + Dy[Dir] < 0 || BlockX + Dx[Dir] < 0 ||
			BlockY + Dy[Dir] >= BoardSize.iY() || BlockX + Dx[Dir] >= BoardSize.iX())
		{
			continue;
		}
		APuyo* NearPuyo = Board[BlockY + Dy[Dir]][BlockX + Dx[Dir]];
		if (NearPuyo == nullptr)
		{
			continue;
		}
		if (NearPuyo->GetColor() == Block[0]->GetColor())
		{
			int NearSpriteIndex = 0;
			for (int j = 0; j < 4; j++)
			{
				int NearDir = (j * 3) % 4;
				if (BlockY + Dy[Dir] + Dy[NearDir] < 0 || BlockX + Dx[Dir] + Dx[NearDir] < 0 ||
					BlockY + Dy[Dir] + Dy[NearDir] >= BoardSize.iY() || BlockX + Dx[Dir] + Dx[NearDir] >= BoardSize.iX())
				{
					continue;
				}
				APuyo* NearNearPuyo = Board[BlockY + Dy[Dir] + Dy[NearDir]][BlockX + Dx[Dir]+ Dx[NearDir]];
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
	Block[0]->SetSprite(SpriteIndex);

	CurStep = EPuyoLogicStep::PuyoCheck;
}

void APuyoBoard::PuyoCheckLogic()
{

	CurStep = EPuyoLogicStep::PuyoDestroy;
}

void APuyoBoard::PuyoDestroyLogic()
{
	CurStep = EPuyoLogicStep::PuyoUpdate;
}

void APuyoBoard::PuyoUpdateLogic()
{
	CurStep = EPuyoLogicStep::PuyoCreate;
}

FVector2D APuyoBoard::GetPosByIndex(int _X, int _Y)
{
	return FVector2D(Offset.iX() + _X * 32, Offset.iY() + _Y * 32);
}

bool APuyoBoard::CanMoveDown()
{
	if (BlockY + Dy[Dir] + 1 >= Board.size() ||
		BlockY + 1 >= Board.size() ||
		Board[BlockY + 1][BlockX] != nullptr ||
		Board[BlockY + Dy[Dir] + 1][BlockX + Dx[Dir]] != nullptr)
	{
		return false;
	}
	/*switch(Dir)
	{
	case 0:
		if (BlockY + 1 >= Board.size() || Board[BlockY + 1][BlockX] != nullptr)
			return false;
		break;
	case 1:
		if (BlockY + 1 >= Board.size() || Board[BlockY + 1][BlockX] != nullptr || Board[BlockY + 1][BlockX+1] != nullptr)
			return false;
		break;
	case 2:
		if (BlockY + 2 >= Board.size() || Board[BlockY + 2][BlockX] != nullptr)
			return false;
		break;
	case 3:
		if (BlockY + 1 >= Board.size() || Board[BlockY + 1][BlockX] != nullptr || Board[BlockY + 1][BlockX - 1] != nullptr)
			return false;
		break;
	}*/

	return true;
}

bool APuyoBoard::CanMoveLR(FVector2D _Dir)
{
	if (BlockX + _Dir.iX() < 0 || BlockX + Dx[Dir] + _Dir.iX() < 0 ||
		BlockX + _Dir.iX() >= BoardSize.iX() || BlockX + Dx[Dir] + _Dir.iX() >= BoardSize.iX() ||
		Board[BlockY][BlockX + _Dir.iX()] != nullptr ||
		Board[BlockY + Dy[Dir]][BlockX + Dx[Dir] + _Dir.iX()] != nullptr ||
		Board[BlockY + 1][BlockX + _Dir.iX()] != nullptr ||
		Board[BlockY + Dy[Dir] + 1][BlockX + Dx[Dir] + _Dir.iX()] != nullptr)
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
		if (BlockX + _Dir.iX() < 0 || BlockX + _Dir.iX() >= Board[0].size())return;
		break;
	case 1:
		if (BlockX + _Dir.iX() < 0 || BlockX + 1 + _Dir.iX() >= Board[0].size())return;
		break;
	case 2:
		if (BlockX + _Dir.iX() < 0 || BlockX + _Dir.iX() >= Board[0].size())return;
		break;
	case 3:
		if (BlockX - 1 + _Dir.iX() < 0 || BlockX + _Dir.iX() >= Board[0].size())return;
		break;
	}*/
	BlockX += _Dir.iX();
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
	Dir = (Dir + 1) % 4;
	//Todo : 이것도 바로 Set을 안하고 부드럽게 움직이게 해야함.
	Block[1]->SetActorLocation(Block[0]->GetActorLocation() + FVector2D(Dx[Dir] * PuyoSize.iX(), Dy[Dir] * PuyoSize.iY()));
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
