#pragma once
#include "Star.h"

// 설명 :
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

	// 별 초기화 함수
	void InitStar();

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
	FVector2D StartLocation;
	float Vx, Vy;        // 속도
	float LifeTime;      // 남은 생명시간
	bool isAlive;        // 활성 상태
	UEngineRandom Rnd;
};

