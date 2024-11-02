#pragma once
#include "Puyo.h"

#include <EngineCore/Actor.h>

enum EPuyoLogicStep
{
	PuyoCreate, // �ѿ� �� ����
	PuyoMove, // �ѿ� ������
	PuyoBlockUpdate, // �ѿ䰡 ����� ��? ���� ģ���� �������� �Ҽ��� �ִ�.
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

	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoBlockUpdateLogic();
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	FVector2D GetPosByIndex(int _X, int _Y);
	bool CanMoveDown();

	void Move(FVector2D _Dir);
	void Rotate();
	void PuyoForceDown();
protected:

private:
	FVector2D Offset;
	float PuyoDropTimer;
	float PuyoDropDelay;
	int PuyoTick;
	int BlockX;
	int BlockY;
	int Dir; // 0,1,2,3 �ð�������� ��,������,�Ʒ�,����
	EPuyoLogicStep CurStep;
	std::vector<APuyo*> Block; // 0�� �ѿ並 �������� ȸ��
	std::vector<std::vector<APuyo*>> Board;
};

