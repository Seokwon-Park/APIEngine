#pragma once
#include <EngineBase/EngineMath.h>

// Ό³Έν :
class AActor
{
public:
	using Super = AActor;

	friend class ULevel;
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	virtual void Tick(float _DeltaTime) {}
	virtual void Render();

	class ULevel* GetWorld()
	{
		return World;
	}

	FVector2D GetActorLocation()
	{
		return Transform.Location;
	}
	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

protected:

private:
	class ULevel* World;

	FTransform Transform;

};

