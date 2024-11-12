#pragma once
#include <EngineBase/EngineMath.h>
#include "ActorComponent.h"

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
	virtual void Tick(float _DeltaTime) {}

	inline class ULevel* GetWorld() const { return World; }
	inline FTransform GetTransform() const { return Transform; }
	inline FVector2D GetActorLocation() const { return Transform.Location; }
	inline std::list<class UActorComponent*> GetComponents() const { return Components; }

	inline void AddActorLocation(FVector2D _Direction) { Transform.Location += _Direction; }
	inline void SetActorLocation(FVector2D _Location) { Transform.Location = _Location; }
	inline void SetActorScale(FVector2D _Scale){Transform.Scale = _Scale;}

	inline virtual void SetActive(bool _Value) override
	{
		UObject::SetActive(_Value);
		for (auto Component : Components)
		{
			Component->SetActive(_Value);
		}
	}

	// �� �Լ��� �����ڿ����� ȣ���ؾ� �մϴ�.
	template<typename UComponentType>
	UComponentType* CreateDefaultSubobject(std::string_view _Name)
	{
		UComponentType* NewComponent = new UComponentType();

		UActorComponent* UComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);

		UComponentPtr->SetName(_Name);
		UComponentPtr->ParentActor = this;

		// Actor�� �����ڰ� �� ������ ���� World�� �����˴ϴ�.
		//NewComponent->BeginPlay();
		Components.push_back(NewComponent);
		return NewComponent;
	}
protected:
	virtual void BeginPlay();
private:
	class ULevel* World;
	FTransform Transform;
	std::list<class UActorComponent*> Components;
};

