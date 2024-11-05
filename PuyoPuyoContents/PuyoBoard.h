#pragma once
#include "Puyo.h"

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
};
// ���� :
class APuyoBoard : public AActor
{
public:
	struct PuyoBoardSettings
	{
		FVector2D Offset;
		FVector2D PuyoSize;
		int Difficulty;
		FIntPoint NextBlockCoord;
		FIntPoint NextNextBlockCoord;
		FIntPoint BoardSize;
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
	void SetKey(int _Up, int _Down, int _Left, int _Right);
	std::vector<APuyo*> CreatePuyoBlock();

	//LogicStep
	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoPlaceLogic();
	void PuyoConnectLogic();
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	inline FVector2D GetLocationByIndex(int _X, int _Y) const
	{
		return FVector2D(_X * PuyoSize.iX(), _Y * PuyoSize.iY()) + PuyoSize.Half();
	}
	inline FVector2D GetLocationByIndex(FIntPoint _XY) const
	{
		return GetLocationByIndex(_XY.X, _XY.Y);
	}

	inline FVector2D GetLocationByIndexWithOffset(int _X, int _Y)const
	{
		return FVector2D(Offset.iX() + _X * PuyoSize.iX(), Offset.iY() + _Y * PuyoSize.iY());
	}
	inline FVector2D GetLocationByIndexWithOffset(FIntPoint _XY)const
	{
		return GetLocationByIndexWithOffset(_XY.X, _XY.Y);
	}
	inline void SetPuyoOnBoard(int _X, int _Y, APuyo* _Puyo)
	{
		Board[_Y][_X] = _Puyo;
	}
	inline void SetPuyoOnBoard(FIntPoint _XY, APuyo* _Puyo)
	{
		SetPuyoOnBoard(_XY.X, _XY.Y, _Puyo);
	}
	bool CanMoveDown();
	bool CanMoveLR(FVector2D _Dir);

	void MoveLR(FVector2D _Dir);
	void Rotate();
	void PuyoForceDown();
protected:
	void BeginPlay() override;
private:
	//���� ������� �ݽð� �������� -> ���� -> ���� -> �Ʒ��� -> ������
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };

	// ���� ������
	UEngineRandom RandomDevice;

	//Setup�Լ����� ���ڷ� �޴� �κ�.
	int Difficulty;
	FVector2D Offset; // �����츦 �������� XY�� ���ȼ� ����������?
	FVector2D PuyoSize; // �ѿ� 1���� �ȼ� ũ��
	FIntPoint BoardSize; // �������� ĭ��
	FIntPoint NextBlockCoord; // �������� ĭ��
	FIntPoint NextNextBlockCoord; // �������� ĭ��

	//Key����
	int UpKey = 0;
	int DownKey = 0;
	int LeftKey = 0;
	int RightKey = 0;

	// Slave Puyo�� ��ǥ�� MainCoord�� Dir�� ���ؼ� ���� �� �ִ�.
	FIntPoint MainPuyoCoord;

	// �ѿ並 ���ʸ��� ����߸� ���ΰ�?
	float PuyoDropDelay;
	float PuyoDropTimer;

	// 2ƽ ���� ���� ��ǥ������ Y�� 1 �����Ѵ�.
	int PuyoTick;

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
	std::set<std::pair<int, int>> PuyoDestroyList;
	std::vector<int> PuyoUpdateColumns;
	// �ѿ�ѿ� ������ - 2���� �迭
	std::vector<std::vector<APuyo*>> Board;
};

