#include "aepch.h"
#include "PuyoBoard.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>

APuyoBoard::APuyoBoard()
	:Offset(FVector2D::ZERO), PuyoDropDelay(.1f), PuyoDropTimer(0.0f), PuyoTick(0), BlockX(0), BlockY(0),
	Dir(0), CurStep(PuyoCreate), Block(std::vector<APuyo*>(2)),
	Board(std::vector<std::vector<APuyo*>>(12, std::vector<APuyo*>(6, nullptr)))
{
}

APuyoBoard::~APuyoBoard()
{
}

void APuyoBoard::BeginPlay()
{
	Super::BeginPlay();
	PuyoDropTimer = PuyoDropDelay;

	Offset = { 48, 48 };
	UEngineInput::GetInstance().BindAction(Key::Down, KeyEvent::Down, std::bind(&APuyoBoard::PuyoForceDown, this));
	UEngineInput::GetInstance().BindAction(Key::Left, KeyEvent::Down, std::bind(&APuyoBoard::Move, this, FVector2D::LEFT));
	UEngineInput::GetInstance().BindAction(Key::Right, KeyEvent::Down, std::bind(&APuyoBoard::Move, this, FVector2D::RIGHT));

}

void APuyoBoard::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UEngineDebugHelper::PushString("X = " + std::to_string(BlockX) + ", Y = " + std::to_string(BlockY));
	UEngineDebugHelper::PushString("Timer = " + std::to_string(PuyoDropTimer));
	UEngineDebugHelper::PushString("CurStep = " + std::to_string(CurStep));
	switch (CurStep)
	{
	case PuyoCreate:
		PuyoCreateLogic();
		break;
	case PuyoMove:
		PuyoMoveLogic();
		break;
	case PuyoCheck:
		PuyoCheckLogic();
		break;
	case PuyoDestroy:
		PuyoDestroyLogic();
		break;
	case PuyoUpdate:
		PuyoUpdateLogic();
		break;
	default:
		break;
	}
}

void APuyoBoard::PuyoCreateLogic()
{
	BlockX = 2;
	BlockY = 1;
	Dir = 0;
	APuyo* Puyo1 = GetWorld()->SpawnActor<APuyo>();
	//임시 
	//추후 SetupPuyo(Location, Color);
	Puyo1->SetActorLocation(GetPosByIndex(BlockX, BlockY));
	APuyo * Puyo2 = GetWorld()->SpawnActor<APuyo>();
	Puyo2->SetActorLocation(GetPosByIndex(BlockX, BlockY - 1));
	Block[0] = Puyo1;
	Block[1] = Puyo2;

	CurStep = PuyoMove;
}

void APuyoBoard::PuyoMoveLogic()
{
	PuyoDropTimer -= UEngineAPICore::GetEngineDeltaTime();
	if (PuyoDropTimer >= 0.0f)return;
	if (PuyoTick % 2 == 0)
	{
		if (!CanMoveDown())
		{
			Board[BlockY][BlockX] = Block[0];
			Board[BlockY - 1][BlockX] = Block[1];
			CurStep = PuyoCheck;
			return;
		}
		BlockY++;
	}
	PuyoTick++;
	PuyoTick %= 2;
	for (auto Puyo : Block)
	{
		Puyo->AddActorLocation(FVector2D(0, 16));
		//Puyo->SetActorLocation(FVector2D::Lerp(Puyo->GetActorLocation(), Puyo->GetActorLocation() + FVector2D(0,32),UEngineAPICore::GetCore()->GetDeltaTime()));
	}

	PuyoDropTimer = PuyoDropDelay;
}

void APuyoBoard::PuyoCheckLogic()
{
	CurStep = PuyoDestroy;
}

void APuyoBoard::PuyoDestroyLogic()
{
	CurStep = PuyoUpdate;
}

void APuyoBoard::PuyoUpdateLogic()
{
	CurStep = PuyoCreate;
}

FVector2D APuyoBoard::GetPosByIndex(int _X, int _Y)
{

	return FVector2D(Offset.iX() + _X * 32, Offset.iY() + _Y * 32);
}

bool APuyoBoard::CanMoveDown()
{
	if (BlockY + 1 >= 12)
		return false;
	if (Board[BlockY + 1][BlockX] != nullptr)
		return false;
	return true;
}

void APuyoBoard::Move(FVector2D _Dir)
{
	BlockX += _Dir.iX();
	Block[0]->AddActorLocation(_Dir * 16);
	Block[1]->AddActorLocation(_Dir * 16);
}

void APuyoBoard::PuyoForceDown()
{
	if (CurStep != PuyoMove)return;
	PuyoDropTimer -= 0.5f;

}
