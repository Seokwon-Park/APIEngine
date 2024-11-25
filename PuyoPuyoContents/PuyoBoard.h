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
	PuyoIdle, // ������
	PuyoCreate, // �ѿ� �� ����
	PuyoMove, // �ѿ� ������
	PuyoPlace, // �ѿ� ��ġ ���� ����
	PuyoConnect, // �ѿ� ���� ����
	PuyoCheck, // �ѿ� �ı����� üũ ����
	PuyoDestroy, // �ѿ� �ı� ����
	PuyoUpdate, // �ı��ǰ� ������ �����ؾ� �Ǵ� �ѿ䰡 �ִ��� üũ-> ������ Place�� ������ Create��
	PuyoGameOver, // ���ӿ��� ����
	PuyoGameWin, // ���� �¸� ����
};
// ���� :
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


	//���� ���� ����
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
		// Todo: ������ ����ƽ ĳ��Ʈ ���Ⱑ ������.
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

	//AI�� �Լ�
	std::vector<std::vector<int>> GetBoardState();

	bool IsInBoard(int TargetX, int TargetY); 
	//Create ���� ���� �Լ�
	std::vector<APuyo*> CreatePuyoBlock();
	UEngineDelegate PuyoCreateDelegate;
	
	// Move ���� ���� �Լ�
	// 
	// ���� �˻�
	// �Ʒ� ������
	bool CanMoveDown();
	bool CanMoveLocation();
	//�¿� ������
	bool CanMoveLR(FVector2D _Dir);
	
	//���� ������
	void PuyoMoveLR(FVector2D _Dir);
	void Rotate(bool _IsClockwise);
	void PuyoForceDown();
	void SmoothRotate(FVector2D _SlavePuyoPosition, FVector2D _MainPuyoPosition, float _DeltaTime, bool _IsClockwise);


	//Spawn Actor
	void SpawnChainText();
	void SpawnAttack(int _Amount, FVector2D _StartPos, bool _IsOffset);
	void SpawnNuisancePuyo();
	//Todo: Effect��� Ŭ������ �߻�ȭ�ʼ���
	void SpawnDestroyFX(FVector2D _StartPos, EPuyoColor _Color, float _Delay);

	//�Ͻ�����
	void PauseGame();

	inline void StartGame() { CurStep = EPuyoLogicStep::PuyoCreate; }
	

	
protected:
	void BeginPlay() override;
private:
	//���� ������� �ݽð� �������� -> ���� -> ���� -> �Ʒ��� -> ������
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	const int DropOrder[6] = { 2,3,1,4,0,5 };
	int DropIndex = 0;

	// ���� ������
	UEngineRandom RandomDevice;

	//Setup�Լ����� ���ڷ� �޴� �κ�.
	int Difficulty;
	FVector2D PuyoSize; // �ѿ� 1���� �ȼ� ũ��
	FIntPoint BoardSize; // �������� ĭ��
	FIntPoint NextBlockCoord; // �������� ĭ��
	FIntPoint NextNextBlockCoord; // �������� ĭ��
	EPuyoBoardColor BoardColor;

	//�ε巯�� �������� ���� ȸ�� ���� ó�� ����
	bool IsRotating = false;
	bool IsKicking = false;
	bool IsRotatedClockWise = false;
	float NeedToRotate = 0.0f;

	// Slave Puyo�� ��ǥ�� MainCoord�� Dir�� ���ؼ� ���� �� �ִ�.
	FIntPoint MainPuyoCoord;

	// �ѿ並 ���ʸ��� ����߸� ���ΰ�?
	float PuyoDropDelay;
	float PuyoDropTimer;

	// Ű ���� ������(�� ���� �� ������)
	float ForceDownDelay;
	float ForceDownTimer;
	float LRMoveDelay;
	float LRMoveTimer;

	//�ı��ִϸ��̼� �����
	bool IsDestroying = false;
	float FlickDelay = 0.05f;
	int FlickCount = 0;

	// 2ƽ ���� ���� ��ǥ������ Y�� 1 �����Ѵ�.
	int PuyoTick;
	//float DropCompleteDelay = 0.5f;
	//float DropCompleteTimer = 0.0f;

	// MainPuyo�� �������� SlavePuyo�� ��� ������ ���ϰ� �ִ��� ����
	int BlockDir; // 0,1,2,3 �ݽð�������� ���� -> ���� -> �Ʒ��� -> ������

	// ���� ������ �ܰ踦 ����
	EPuyoLogicStep CurStep;

	// �ѿ� ����
	std::vector<APuyo*> Block; // 0�� �ѿ並 �������� ȸ��
	std::vector<APuyo*> NextBlock; // �����ѿ�
	std::vector<APuyo*> NextNextBlock; // ���������ѿ�

	// �������� üũ�ؾ��� ������ ��� �迭
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

	// �ѿ�ѿ� ������ - 2���� �迭
	std::vector<std::vector<APuyo*>> Board;

	//���� �������̰ų� ��� ���Ⱑ �������̸� ���ػѿ並 ���� �ʴ´�.
	bool IsChaining = false;
	//���ػѿ� �ѹ� �Ѹ��� ���� ����ѿ䰡 �����־
	// �� �÷��׸� ���� ���� �� ���� �Ŀ� �Ѹ����� �Ѵ�.
	bool IsNuiSpawned = false;

	//���� ī��Ʈ
	int Rensa = 0;

	//�ı����� ���� ������ ����
	int ScoreToAdd = 0;

	//���ػѿ� ���� ������
	float SC = 0;
	float TP = 70.0f;
	float NL = 0.0f;

	// ���� �ѿ�
	APuyoWarn* WarnActor;
	int DropBonus;

	//����
	APuyoText* ScoreActor;
	// ��� ������ ��ü ������
	APuyoBoard* CounterBoardActor;
	//ȭ�� ��鸲 ����Ʈ���μ���
	UPuyoBoardShakePostProcess* ShakePostProcess;

	//���� �Ͻ����� ���� 
	USpriteRendererComponent* PauseText;
	bool IsPaused = false;
	float PauseTimer = 0.5f;
	float PauseDelay = 0.5f;

	USpriteRendererComponent* GameOverBG;

	std::vector<ABottomFrame*> BottomFrames;
	std::vector<bool> IsDrop;
	float Delay = 0.15f;
	float Timer = 0.0f;

	//���� �����δ� ����� ����
};

