#pragma once

// Ό³Έν :
class AAController : public AActor
{
public:
	// constrcuter destructer
	AAController();
	~AAController();

	// delete Function
	AAController(const AAController& _Other) = delete;
	AAController(AAController&& _Other) noexcept = delete;
	AAController& operator=(const AAController& _Other) = delete;
	AAController& operator=(AAController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

