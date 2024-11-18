#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class AOpeningCar : public AActor
{
public:
	// Constrcuter Destructer
	AOpeningCar();
	~AOpeningCar();

	// Delete Function
	AOpeningCar(const AOpeningCar& _Other) = delete;
	AOpeningCar(AOpeningCar&& _Other) noexcept = delete;
	AOpeningCar& operator=(const AOpeningCar& _Other) = delete;
	AOpeningCar& operator=(AOpeningCar&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay()override;

private:
	USpriteRendererComponent* OPCar;
	USpriteRendererComponent* OPCarJewel;
};
