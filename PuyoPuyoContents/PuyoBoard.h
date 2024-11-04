#pragma once
#include "Puyo.h"

#include <EngineCore/Actor.h>

enum class EPuyoLogicStep
{
	PuyoCreate, // �ѿ� �� ����
	PuyoMove, // �ѿ� ������
	PuyoPlace, // �ѿ� ��������
	PuyoConnect, // �ѿ� ���� ����
	PuyoCheck,
	PuyoDestroy,
	PuyoUpdate,
};
// ���� :
class APuyoBoard : public AActor
{
public:
	// constrcuter destructer
	APuyoBoard();
	~APuyoBoard();

	// delete Function
	APuyoBoard(const APuyoBoard& _Other) = delete;
	APuyoBoard(APuyoBoard&& _Other) noexcept = delete;
	APuyoBoard& operator=(const APuyoBoard& _Other) = delete;
	APuyoBoard& operator=(APuyoBoard&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetupPuyoBoard(FVector2D _Offset, FVector2D _PuyoSize, FIntPoint _BoardSize = FIntPoint(6,13));
	std::vector<APuyo*> CreatePuyoBlock();

	//LogicStep
	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoPlaceLogic(float _DeltaTime);
	void PuyoConnectLogic(float _DeltaTime);
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	FVector2D GetLocationByIndex(int _X, int _Y);
	bool CanMoveDown();
	bool CanMoveLR(FVector2D _Dir);

	void MoveLR(FVector2D _Dir);
	void Rotate();
	void PuyoForceDown();
protected:

private:
	//���� ������� �ݽð� �������� -> ���� -> ���� -> �Ʒ��� -> ������
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	FVector2D Offset;
	FVector2D PuyoSize;
	FIntPoint BoardSize;
	// Slave Puyo
	FIntPoint MainPuyoCoord;
	float PuyoDropTimer;
	float PuyoDropDelay;
	int PuyoTick;
	int Dir; // 0,1,2,3 �ð�������� ��,������,�Ʒ�,����
	EPuyoLogicStep CurStep;
	std::vector<APuyo*> Block; // 0�� �ѿ並 �������� ȸ��
	std::vector<APuyo*> NextBlock; // �����ѿ�
	std::vector<APuyo*> NextNextBlock; // ���������ѿ�
	std::vector<FIntPoint> PuyoConnectList;
	std::vector<FIntPoint> PlaceCheckList;
	
	std::vector<std::vector<APuyo*>> Board;
};

