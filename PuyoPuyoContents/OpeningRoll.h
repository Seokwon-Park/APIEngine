#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOpeningRoll : public AActor
{
public:
	// constrcuter destructer
	AOpeningRoll();
	~AOpeningRoll();

	// delete Function
	AOpeningRoll(const AOpeningRoll& _Other) = delete;
	AOpeningRoll(AOpeningRoll&& _Other) noexcept = delete;
	AOpeningRoll& operator=(const AOpeningRoll& _Other) = delete;
	AOpeningRoll& operator=(AOpeningRoll&& _Other) noexcept = delete;

	void Init() { 
		//Timer = 0.0f;
		//Sr->SetComponentLocation({ 0,-160 }); 
	}
	void SetupRoll(FVector2D _Start, float _TargetY, float _Speed);
	void ToSepia() {
		SepiaFilter->SetAlphaRate(0.4f);
		Anim->ChangeAnimation("ToSepia"); 
	}
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	int Dir = 0;
	float Amount = 0.0f;
	float TargetY = 0.0f;
	float Speed = 1.0f;
	USpriteRendererComponent* SepiaFilter;
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Anim;
};

