#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class AOpeningStar : public AActor
{
public:
	// Constrcuter Destructer
	AOpeningStar();
	~AOpeningStar();

	// Delete Function
	AOpeningStar(const AOpeningStar& _Other) = delete;
	AOpeningStar(AOpeningStar&& _Other) noexcept = delete;
	AOpeningStar& operator=(const AOpeningStar& _Other) = delete;
	AOpeningStar& operator=(AOpeningStar&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;

	// 별 초기화 함수
	void Init();
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
	FVector2D StartLocation;
	float Vx, Vy;        // 속도
	float LifeTime;      // 남은 생명시간
	bool isAlive;        // 활성 상태
};
