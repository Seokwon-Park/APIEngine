#include "aepch.h"
#include "PuyoPlayerController.h"

APuyoPlayerController::APuyoPlayerController()
{
}

APuyoPlayerController::~APuyoPlayerController()
{
}


void APuyoPlayerController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void APuyoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Board = GetActor<APuyoBoard>();
	// 회전
	// Todo : 인자 받아서 회전방향 시계방향, 반시계방향 결정하기, 추가키설정 허용?
	InputComponent->BindAction(CWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, Board, true));
	InputComponent->BindAction(CCWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, Board, false));

	// 빠른 낙하
	InputComponent->BindAction(DownKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoForceDown, Board));

	// 좌우 이동
	InputComponent->BindAction(LeftKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, Board, FVector2D::LEFT));
	InputComponent->BindAction(RightKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, Board, FVector2D::RIGHT));

	// 일시 정지
	InputComponent->BindAction(EKey::Esc, KeyEvent::Down, std::bind(&APuyoBoard::PauseGame, Board));

	if (GameSettings::GetInstance().GameMode == EPuyoGameMode::Solo)
	{
		InputComponent->BindAction(EKey::Esc, KeyEvent::Down, std::bind(&APuyoBoard::PauseGame, Board->GetCounterBoard()));
	}
	//InputComponent->BindAction();
}

void APuyoPlayerController::SetKey(int _CWRotate, int _CCWRotate, int _Down, int _Left, int _Right)
{
	CWRotateKey = _CWRotate;
	CCWRotateKey = _CCWRotate;
	DownKey = _Down;
	LeftKey = _Left;
	RightKey = _Right;
}