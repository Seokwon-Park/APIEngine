#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class ATowerUnit :public AActor
{
public:
	// Constrcuter Destructer
	ATowerUnit();
	~ATowerUnit();

	// Delete Function
	ATowerUnit(const ATowerUnit& _Other) = delete;
	ATowerUnit(ATowerUnit&& _Other) noexcept = delete;
	ATowerUnit& operator=(const ATowerUnit& _Other) = delete;
	ATowerUnit& operator=(ATowerUnit&& _Other) noexcept = delete;

	void SetupPillar(FVector2D _Scale, int _Floor);
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Pillar;
	USpriteRendererComponent* Side[2];
};
