#pragma once

// Ό³Έν :
class UActorComponent : public UObject
{
public:
	friend class AActor;

	using Super = UActorComponent;
	// constrcuter destructer
	UActorComponent();
	virtual ~UActorComponent() = 0;

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	virtual void BeginPlay() {};
	virtual void TickComponent(float _DeltaTime) {};
	
	inline class AActor* GetOwner() { return ParentActor; }
protected:

private:
	class AActor* ParentActor;

};

