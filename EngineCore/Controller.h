#pragma once

// Ό³Έν :
class AController : public AActor
{
public:
	// constrcuter destructer
	AController();
	~AController();

	// delete Function
	AController(const AController& _Other) = delete;
	AController(AController&& _Other) noexcept = delete;
	AController& operator=(const AController& _Other) = delete;
	AController& operator=(AController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	virtual void Possess(AActor* InActor);
	inline void SetActor(AActor* InActor) { Actor = InActor; }

	template <class ActorType>
	inline ActorType* GetActor()
	{
		return dynamic_cast<ActorType*>(Actor);
	}
protected:
	virtual void BeginPlay() override;

private:
	AActor* Actor = nullptr;
};

