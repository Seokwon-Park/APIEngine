#pragma once
#include <EngineBase/EngineMath.h>
#include "ActorComponent.h"

#include "EngineSprite.h"

// 설명 :
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

	virtual void Tick(float _DeltaTime);

	inline class ULevel* GetWorld() const { return World; }
	inline FTransform GetTransform() const { return Transform; }
	inline FVector2D GetActorLocation() const { return Transform.Location; }
	inline std::list<class UActorComponent*> GetComponents() const { return Components; }

	inline void AddActorLocation(FVector2D _Direction) { Transform.Location += _Direction; }
	inline void SetActorLocation(FVector2D _Location) { Transform.Location = _Location; }
	inline void SetActorDebug(bool _Value) { IsDebug = _Value; }

	inline virtual void SetActive(bool _Value) override
	{
		UObject::SetActive(_Value);
		for (auto Component : Components)
		{
			Component->SetActive(_Value);
		}
	}

	// 이 함수는 생성자에서만 호출해야 합니다.
	template<typename UComponentType>
	UComponentType* CreateDefaultSubobject(std::string_view _Name)
	{
		UComponentType* NewComponent = new UComponentType();

		UActorComponent* UComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);

		UComponentPtr->SetName(_Name);
		UComponentPtr->ParentActor = this;

		// Actor의 생성자가 다 끝나고 나서 World가 결정되므로
		// Actor의 BeginPlay를 미룬다. -> Actor의 BeginPlay에서 컴포넌트 리스트들의 BeginPlay를 실행해준다.
		//NewComponent->BeginPlay();
		Components.push_back(NewComponent);
		return NewComponent;
	}
protected:
	// 이 객체가 처음 Tick을 돌리기 직전에 실행
	virtual void BeginPlay();
private:
	bool IsDebug = false;
	class ULevel* World;
	FTransform Transform;
	std::list<class UActorComponent*> Components;
};

