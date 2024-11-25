#pragma once
#include "Star.h"

// ���� :
class AStar : public AActor
{
public:
	// constrcuter destructer
	AStar();
	~AStar();

	// delete Function
	AStar(const AStar& _Other) = delete;
	AStar(AStar&& _Other) noexcept = delete;
	AStar& operator=(const AStar& _Other) = delete;
	AStar& operator=(AStar&& _Other) noexcept = delete;

	// �� �ʱ�ȭ �Լ�
	void InitStar();

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
	FVector2D StartLocation;
	float Vx, Vy;        // �ӵ�
	float LifeTime;      // ���� ����ð�
	bool isAlive;        // Ȱ�� ����
	UEngineRandom Rnd;
};

