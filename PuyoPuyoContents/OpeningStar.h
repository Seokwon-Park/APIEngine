#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ŭ���� ���� :
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

	// �� �ʱ�ȭ �Լ�
	void Init();
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
	FVector2D StartLocation;
	float Vx, Vy;        // �ӵ�
	float LifeTime;      // ���� ����ð�
	bool isAlive;        // Ȱ�� ����
};
