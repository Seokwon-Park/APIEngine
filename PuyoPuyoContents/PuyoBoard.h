#pragma once
#include "Puyo.h"
#include "PuyoWarn.h"
#include "PuyoText.h"
#include "PuyoBoardShakePostProcess.h"
#include "BottomFrame.h"

#include <set>
#include <EngineCore/Actor.h>
#include <EngineCore/InputComponent.h>



//Todo : 
enum class EPuyoLogicStep
{
	PuyoIdle, // 대기상태
	PuyoCreate, // 뿌요 블럭 생성
	PuyoMove, // 뿌요 움직임
	PuyoPlace, // 뿌요 위치 조정 로직
	PuyoConnect, // 뿌요 연결 로직
	PuyoCheck, // 뿌요 파괴조건 체크 로직
	PuyoDestroy, // 뿌요 파괴 로직
	PuyoUpdate, // 파괴되고 난다음 낙하해야 되는 뿌요가 있는지 체크-> 있으면 Place로 없으면 Create로
	PuyoGameOver, // 게임오버 로직
	PuyoGameWin, // 게임 승리 로직
};
// 설명 :
class APuyoBoard : public AActor
{
public:
	struct PuyoBoardSettings
	{
		int Difficulty;
		FVector2D PuyoSize;
		EPuyoBoardColor BoardColor;

		FIntPoint BoardSize;
		FIntPoint NextBlockCoord;
		FIntPoint NextNextBlockCoord;

		APuyoWarn* WarnActor;
		APuyoText* ScoreActor;
		APuyoBoard* CounterBoardActor;
		UPuyoBoardShakePostProcess* ShakePostProcess;
		std::vector<ABottomFrame*> BottomFrames;
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


	//보드 설정 세팅
	void SetupPuyoBoard(const PuyoBoardSettings& _Settings);
	
	//LogicStep
	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoPlaceLogic();
	void PuyoConnectLogic();
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();
	void PuyoGameOverLogic();
	void PuyoGameWinLogic();

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
	inline FIntPoint GetPuyoBoardSize()
	{
		return BoardSize;
	}

	inline std::vector<int> GetBlockInfo()
	{
		// Todo: 솔직히 스태틱 캐스트 적기가 귀찮음.
		return { (int)Block[0]->GetColor(), (int)Block[1]->GetColor()};
	}

	inline std::pair<FIntPoint, int> GetMainPuyoInfo() 
	{
		return std::make_pair(MainPuyoCoord, BlockDir);
	}
	inline void SetPuyoOnBoard(int _X, int _Y, APuyo* _Puyo)
	{
		Board[_Y][_X] = _Puyo;
	}
	inline void SetPuyoOnBoard(FIntPoint _XY, APuyo* _Puyo)
	{
		SetPuyoOnBoard(_XY.X, _XY.Y, _Puyo);
	}
	inline EPuyoLogicStep GetCurStep() const
	{
		return CurStep;
	}
	inline APuyoBoard* GetCounterBoard()
	{
		return CounterBoardActor;
	}

	//AI용 함수
	std::vector<std::vector<int>> GetBoardState();

	bool IsInBoard(int TargetX, int TargetY); 
	//Create 로직 관련 함수
	std::vector<APuyo*> CreatePuyoBlock();
	UEngineDelegate PuyoCreateDelegate;
	
	// Move 로직 관련 함수
	// 
	// 조건 검사
	// 아래 움직임
	bool CanMoveDown();
	bool CanMoveLocation();
	//좌우 움직임
	bool CanMoveLR(FVector2D _Dir);
	
	//실제 움직임
	void PuyoMoveLR(FVector2D _Dir);
	void Rotate(bool _IsClockwise);
	void PuyoForceDown();
	void SmoothRotate(FVector2D _SlavePuyoPosition, FVector2D _MainPuyoPosition, float _DeltaTime, bool _IsClockwise);


	//Spawn Actor
	void SpawnChainText();
	void SpawnAttack(int _Amount, FVector2D _StartPos, bool _IsOffset);
	void SpawnNuisancePuyo();
	//Todo: Effect라는 클래스로 추상화필수적
	void SpawnDestroyFX(FVector2D _StartPos, EPuyoColor _Color, float _Delay);

	//일시정지
	void PauseGame();

	inline void StartGame() { CurStep = EPuyoLogicStep::PuyoCreate; }
	

	
protected:
	void BeginPlay() override;
private:
	//위쪽 방향부터 반시계 방향으로 -> 위쪽 -> 왼쪽 -> 아래쪽 -> 오른쪽
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	const int DropOrder[6] = { 2,3,1,4,0,5 };
	int DropIndex = 0;

	// 난수 생성기
	UEngineRandom RandomDevice;

	//Setup함수에서 인자로 받는 부분.
	int Difficulty;
	FVector2D PuyoSize; // 뿌요 1개의 픽셀 크기
	FIntPoint BoardSize; // 게임판의 칸수
	FIntPoint NextBlockCoord; // 게임판의 칸수
	FIntPoint NextNextBlockCoord; // 게임판의 칸수
	EPuyoBoardColor BoardColor;

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

	// 키 조작 딜레이(꾹 누를 때 딜레이)
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

	// MainPuyo를 기준으로 SlavePuyo가 어느 방향을 향하고 있는지 저장
	int BlockDir; // 0,1,2,3 반시계방향으로 위쪽 -> 왼쪽 -> 아래쪽 -> 오른쪽

	// 현재 로직의 단계를 저장
	EPuyoLogicStep CurStep;

	// 뿌요 관련
	std::vector<APuyo*> Block; // 0번 뿌요를 기준으로 회전
	std::vector<APuyo*> NextBlock; // 다음뿌요
	std::vector<APuyo*> NextNextBlock; // 다음다음뿌요

	// 로직에서 체크해야할 정보를 담는 배열
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
	std::set<int> PuyoUpdateColumns;

	// 뿌요뿌요 게임판 - 2차원 배열
	std::vector<std::vector<APuyo*>> Board;

	//내가 연쇄중이거나 상대 연쇄가 진행중이면 방해뿌요를 놓지 않는다.
	bool IsChaining = false;
	//방해뿌요 한번 뿌리고 나면 예고뿌요가 남아있어도
	// 이 플래그를 통해 다음 블럭 생성 후에 뿌리도록 한다.
	bool IsNuiSpawned = false;

	//연쇄 카운트
	int Rensa = 0;

	//파괴에서 계산된 더해질 점수
	int ScoreToAdd = 0;

	//방해뿌요 계산용 변수들
	float SC = 0;
	float TP = 70.0f;
	float NL = 0.0f;

	// 예고 뿌요
	APuyoWarn* WarnActor;
	int DropBonus;

	//점수
	APuyoText* ScoreActor;
	// 상대 게임판 객체 포인터
	APuyoBoard* CounterBoardActor;
	//화면 흔들림 포스트프로세스
	UPuyoBoardShakePostProcess* ShakePostProcess;

	//게임 일시정지 관련 
	USpriteRendererComponent* PauseText;
	bool IsPaused = false;
	float PauseTimer = 0.5f;
	float PauseDelay = 0.5f;

	USpriteRendererComponent* GameOverBG;

	std::vector<ABottomFrame*> BottomFrames;
	std::vector<bool> IsDrop;
	float Delay = 0.15f;
	float Timer = 0.0f;

	//여기 밑으로는 실험실 변수
};

