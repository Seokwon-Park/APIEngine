#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineMath.h>

#include "EngineSprite.h"

// ���� :
class AActor : public UObject
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

	// �� ��ü�� ó�� Tick�� ������ ������ ����
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime) {}

	inline class ULevel* GetWorld() const { return World; }
	inline FTransform GetTransform() const { return Transform; }
	inline FVector2D GetActorLocation() const { return Transform.Location; }

	inline void AddActorLocation(FVector2D _Direction) { Transform.Location += _Direction; }
	inline void SetActorLocation(FVector2D _Location) { Transform.Location = _Location; }
	inline void SetActorScale(FVector2D _Scale){Transform.Scale = _Scale;}

	// �� �Լ��� �����ڿ����� ȣ���ؾ� �մϴ�.
	template<typename UComponentType>
	UComponentType* CreateDefaultSubObject()
	{
		UComponentType* NewComponent = new UComponentType();

		UActorComponent* UComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);

		UComponentPtr->ParentActor = this;

		// Actor�� �����ڰ� �� ������ ���� World�� �����˴ϴ�.
		//NewComponent->BeginPlay();
		Components.push_back(NewComponent);
		return NewComponent;
	}
protected:

private:
	class ULevel* World;
	FTransform Transform;
	std::list<class UActorComponent*> Components;

};

