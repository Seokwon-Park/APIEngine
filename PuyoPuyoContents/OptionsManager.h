#pragma once
#include <EngineCore/SpriteRendererComponent.h>
#include <EngineCore/InputComponent.h>



// Ό³Έν :
class AOptionsManager : public AActor
{
public:
	// constrcuter destructer
	AOptionsManager();
	~AOptionsManager();

	// delete Function
	AOptionsManager(const AOptionsManager& _Other) = delete;
	AOptionsManager(AOptionsManager&& _Other) noexcept = delete;
	AOptionsManager& operator=(const AOptionsManager& _Other) = delete;
	AOptionsManager& operator=(AOptionsManager&& _Other) noexcept = delete;

	inline void SetList(class AOptionsList* _List) { CurList = _List; }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* OptSelector;

	AOptionsList* CurList = nullptr;

	UInputComponent* OptInput;
};

