#pragma once
#include "Puyo.h"
#include "PuyoText.h"
#include "PuyoBoardShake.h"

#include <set>
#include <EngineCore/Actor.h>


//Todo : 
enum class EPuyoLogicStep
{
	PuyoCreate, // �ѿ� �� ����
	PuyoMove, // �ѿ� ������
	PuyoPlace, // �ѿ� ��ġ ���� ����
	PuyoConnect, // �ѿ� ���� ����
	PuyoCheck, // �ѿ� �ı����� üũ ����
	PuyoDestroy, // �ѿ� �ı� ����
	PuyoUpdate, // �ı��ǰ� ������ �����ؾ� �Ǵ� �ѿ䰡 �ִ��� üũ-> ������ Place�� ������ Create��
	PuyoGameOver, // ���ӿ��� ����
};
// ���� :
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
	//������ �� �ִ��� �˻��ϴ� �Լ�
	// �Ʒ� ������
	// �� 2���� ���������� �ƹ�ư �ʿ��ؼ� ����
	bool CanMoveDown();
	bool CanMoveLocation();
	//�¿� ������
	bool CanMoveLR(FVector2D _Dir);

	void PuyoMoveLR(FVector2D _Dir);
	void Rotate(bool _IsClockwise);
	void PuyoForceDown();

	void SpawnChainText();
	void SpawnAttack(int _Amount, FVector2D _StartPos);
	void UpdateWarning();
	bool CalcWarn(const int _SpriteIndex, FVector2D& _Offset, int& _CurIndex, int& _Left);

	void SmoothRotate(FVector2D _SlavePuyoPosition, FVector2D _MainPuyoPosition, float _DeltaTime, bool _IsClockwise);

	//Todo: Effect��� Ŭ������ �߻�ȭ�ʼ���
	void SpawnDestroyFX(FVector2D _Loc, EPuyoColor _Color, float _Delay);
protected:
	void BeginPlay() override;
private:
	//���� ������� �ݽð� �������� -> ���� -> ���� -> �Ʒ��� -> ������
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	//���� �ѿ� ����
	const int WarnUnit[6] = { 1,6,30, 200, 300, 420 };

	// ���� ������
	UEngineRandom RandomDevice;

	//Setup�Լ����� ���ڷ� �޴� �κ�.
	int Difficulty;
	FVector2D PuyoSize; // �ѿ� 1���� �ȼ� ũ��
	FIntPoint BoardSize; // �������� ĭ��
	FIntPoint NextBlockCoord; // �������� ĭ��
	FIntPoint NextNextBlockCoord; // �������� ĭ��

	//Key�ڵ� �� ������ �޴� ����
	int CWRotateKey = 0;
	int CCWRotateKey = 0;
	int DownKey = 0;
	int LeftKey = 0;
	int RightKey = 0;

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

	// MainPuyo�� �������� SlavePuyo�� ��� ������ ���ϰ� �ִ����� ���Ѵ�.
	int BlockDir; // 0,1,2,3 �ݽð�������� ���� -> ���� -> �Ʒ��� -> ������

	// ���� ������ �ܰ�
	EPuyoLogicStep CurStep;

	// �ѿ� ����
	std::vector<APuyo*> Block; // 0�� �ѿ並 �������� ȸ��
	std::vector<APuyo*> NextBlock; // �����ѿ�
	std::vector<APuyo*> NextNextBlock; // ���������ѿ�

	// �������� üũ�ؾ��� ��ǥ�� ������ ��� �迭
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
	// �ѿ�ѿ� ������ - 2���� �迭
	std::vector<std::vector<APuyo*>> Board;

	//���ػѿ�?
	std::vector<USpriteRendererComponent*> Warnings;
	int WarnNums = 0;
	// ���� ���ػѿ䰡 ������ ��Ⱑ �����Ҷ����� �̷�� �뵵(?) �ƿ� ����
	bool CheckOffset = false;

	//���� ���Ҿ ��� ���Ⱑ �������̸� ���ػѿ並 ���� �ʴ´�.
	bool IsChaining = false;

	//���� ī��Ʈ
	int Rensa = 0;
	int ScoreToAdd = 0;


	APuyoText* Score;
	UPuyoBoardShake* Shaker;
	// ��� ������ ��ü ������
	APuyoBoard* CounterBoard;




	//���� �����δ� ����� ����
};

