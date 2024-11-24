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
	// ȸ��
	// Todo : ���� �޾Ƽ� ȸ������ �ð����, �ݽð���� �����ϱ�, �߰�Ű���� ���?
	InputComponent->BindAction(CWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, Board, true));
	InputComponent->BindAction(CCWRotateKey, KeyEvent::Down, std::bind(&APuyoBoard::Rotate, Board, false));

	// ���� ����
	InputComponent->BindAction(DownKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoForceDown, Board));

	// �¿� �̵�
	InputComponent->BindAction(LeftKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, Board, FVector2D::LEFT));
	InputComponent->BindAction(RightKey, KeyEvent::Press, std::bind(&APuyoBoard::PuyoMoveLR, Board, FVector2D::RIGHT));

	// �Ͻ� ����
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