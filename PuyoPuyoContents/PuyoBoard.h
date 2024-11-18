#pragma once
#include "Puyo.h"
#include "PuyoText.h"
#include "PuyoBoardShake.h"

#include <set>
#include <EngineCore/Actor.h>


//Todo : 
enum class EPuyoLogicStep
{
	PuyoCreate, // 뿌요 블럭 생성
	PuyoMove, // 뿌요 움직임
	PuyoPlace, // 뿌요 위치 조정 로직
	PuyoConnect, // 뿌요 연결 로직
	PuyoCheck, // 뿌요 파괴조건 체크 로직
	PuyoDestroy, // 뿌요 파괴 로직
	PuyoUpdate, // 파괴되고 난다음 낙하해야 되는 뿌요가 있는지 체크-> 있으면 Place로 없으면 Create로
	PuyoGameOver, // 게임오버 로직
	PuyoWin, // 게임 승리 로직
};
// 설명 :
class APuyoBoard : public AActor
{
public:
	struct PuyoBoardSettings
	{
		FVector2D PuyoSize;
		int Difficulty;
		FIntPoint NextBlockCoord;
		FIntPoint NextNextBlockCoord;
		FIntPoint BoardSize;
		UPuyoBoardShake* Shaker;
		APuyoText* Score;
		APuyoBoard* CounterBoard;
		EPuyoBoardColor TextColor;

	};
	// constrcuter destructer
	APuyoBoard();
	~APuyoBoard();

	// delete Function
	APuyoBoard(const APuyoBoard& _Other) = delete;
	APuyoBoard(APuyoBoard&& _Other) noexcept = delete;
	APuyoBoard& operator=(const APuyoBoard& _Other) = delete;
	APuyoBoard& operator=(APuyoBoard&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

	void SetupPuyoBoard(const PuyoBoardSettings& _Settings);
	void SetKey(int _CWRotate, int _CCWRotate, int _Down, int _Left, int _Right);
	std::vector<APuyo*> CreatePuyoBlock();

	//LogicStep
	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void SpawnNuisancePuyo();
	void PuyoPlaceLogic();
	void PuyoConnectLogic();
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();
	void PuyoGameOverLogic();

	bool IsInBoard(int TargetX, int TargetY);
	inline FVector2D GetLocationByIndex(int _X, int _Y) const
	{
		return FVector2D(_X * PuyoSize.iX(), _Y * PuyoSize.iY());
	}
	inline FVector2D GetLocationByIndex(FIntPoint _XY) const
	{
		return GetLocationByIndex(_XY.X, _XY.Y);
	}

	inline FVector2D GetLocationByIndexOnBoard(int _X, int _Y)const
	{
		return FVector2D(GetActorLocation().iX() + _X * PuyoSize.iX(), GetActorLocation().iY() + _Y * PuyoSize.iY());
	}
	inline FVector2D GetLocationByIndexOnBoard(FIntPoint _XY)const
	{
		return GetLocationByIndexOnBoard(_XY.X, _XY.Y);
	}
	inline void SetPuyoOnBoard(int _X, int _Y, APuyo* _Puyo)
	{
		Board[_Y][_X] = _Puyo;
	}
	inline void SetPuyoOnBoard(FIntPoint _XY, APuyo* _Puyo)
	{
		SetPuyoOnBoard(_XY.X, _XY.Y, _Puyo);
	}

	inline void AddWarnNums(int _Amount)
	{
		WarnNums += _Amount;
	}
	//움직일 수 있는지 검사하는 함수
	// 아래 움직임
	// 왜 2개로 나눴는지는 아무튼 필요해서 나눔
	bool CanMoveDown();
	bool CanMoveLocation();
	//좌우 움직임
	bool CanMoveLR(FVector2D _Dir);

	void PuyoMoveLR(FVector2D _Dir);
	void Rotate(bool _IsClockwise);
	void PuyoForceDown();

	void SpawnChainText();
	void SpawnAttack(int _Amount, FVector2D _StartPos);
	void UpdateWarning();
	bool CalcWarn(const int _SpriteIndex, FVector2D& _Offset, int& _CurIndex, int& _Left);

	void SmoothRotate(FVector2D _SlavePuyoPosition, FVector2D _MainPuyoPosition, float _DeltaTime, bool _IsClockwise);

	//Todo: Effect라는 클래스로 추상화필수적
	void SpawnDestroyFX(FVector2D _Loc, EPuyoColor _Color, float _Delay);

	//일시정지
	void PauseGame();

	
protected:
	void BeginPlay() override;
private:
	//위쪽 방향부터 반시계 방향으로 -> 위쪽 -> 왼쪽 -> 아래쪽 -> 오른쪽
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	//예고 뿌요 단위
	const int WarnUnit[6] = { 1,6,30, 200, 300, 420 };

	// 난수 생성기
	UEngineRandom RandomDevice;

	//Setup함수에서 인자로 받는 부분.
	int Difficulty;
	FVector2D PuyoSize; // 뿌요 1개의 픽셀 크기
	FIntPoint BoardSize; // 게임판의 칸수
	FIntPoint NextBlockCoord; // 게임판의 칸수
	FIntPoint NextNextBlockCoord; // 게임판의 칸수

	//Key코드 값 정보를 받는 변수
	int CWRotateKey = 0;
	int CCWRotateKey = 0;
	int DownKey = 0;
	int LeftKey = 0;
	int RightKey = 0;

	//부드러운 움직임을 위한 회전 관련 처리 변수
	bool IsRotating = false;
	bool IsKicking = false;
	bool IsRotatedClockWise = false;
	float NeedToRotate = 0.0f;

	// Slave Puyo의 좌표는 MainCoord와 Dir을 통해서 얻을 수 있다.
	FIntPoint MainPuyoCoord;

	// 뿌요를 몇초마다 떨어뜨릴 것인가?
	float PuyoDropDelay;
	float PuyoDropTimer;
	float ForceDownDelay;
	float ForceDownTimer;
	float LRMoveDelay;
	float LRMoveTimer;

	//파괴애니메이션 재생중
	bool IsDestroying = false;
	float FlickDelay = 0.05f;
	int FlickCount = 0;

	// 2틱 마다 보드 좌표상으로 Y가 1 증가한다.
	int PuyoTick;
	//float DropCompleteDelay = 0.5f;
	//float DropCompleteTimer = 0.0f;

	// MainPuyo를 기준으로 SlavePuyo가 어느 방향을 향하고 있는지를 말한다.
	int BlockDir; // 0,1,2,3 반시계방향으로 위쪽 -> 왼쪽 -> 아래쪽 -> 오른쪽

	// 현재 로직의 단계
	EPuyoLogicStep CurStep;

	// 뿌요 관련
	std::vector<APuyo*> Block; // 0번 뿌요를 기준으로 회전
	std::vector<APuyo*> NextBlock; // 다음뿌요
	std::vector<APuyo*> NextNextBlock; // 다음다음뿌요

	// 로직에서 체크해야할 좌표의 정보를 담는 배열
	std::vector<APuyo*> PlaceCheckList;
	std::vector<APuyo*> PuyoConnectList;
	std::vector<FIntPoint> PuyoCheckList;
	//std::set<std::pair<int, int>> PuyoDestroyList;
	std::set < FIntPoint, decltype([](const auto a, const auto b) {
		if (a.Y == b.Y)
		{
			return a.X < b.X;
		}
		return a.Y < b.Y;
		}) > PuyoDestroyList;
	std::vector<int> PuyoUpdateColumns;
	// 뿌요뿌요 게임판 - 2차원 배열
	std::vector<std::vector<APuyo*>> Board;

	//방해뿌요?
	std::vector<USpriteRendererComponent*> Warnings;
	int WarnNums = 0;
	// 만약 방해뿌요가 있으면 상쇄가 가능할때까지 미루는 용도(?) 아오 복잡
	bool CheckOffset = false;

	//내가 놓았어도 상대 연쇄가 진행중이면 방해뿌요를 놓지 않는다.
	bool IsChaining = false;

	//연쇄 카운트
	int Rensa = 0;
	int ScoreToAdd = 0;


	APuyoText* Score;
	UPuyoBoardShake* Shaker;
	// 상대 게임판 객체 포인터
	APuyoBoard* CounterBoard;
	EPuyoBoardColor TextColor;

	//게임 일시정지
	USpriteRendererComponent* PauseText;
	bool IsPaused = false;







	//여기 밑으로는 실험실 변수
};

