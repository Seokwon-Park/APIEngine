#pragma once

// 설명 :
class UObject
{
public:
	// constrcuter destructer
	UObject();
	virtual ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	inline virtual std::string GetName() const { return Name; }
	inline virtual std::string_view GetNameView() const { return Name.c_str(); }
	inline virtual void SetName(std::string_view _Name) { Name = _Name.data(); }

	inline bool IsTickable() const { return Tickable; }
	inline bool IsActivated() const { return true == IsActive; }
	inline bool CheckDestroy() const { return IsDestroyed; }
	inline void Destroy(float _Delay= 0.0f) 
	{ 
		DestroyDelay = _Delay;
		IsDestroyed = true;
	}
	inline virtual void SetActive(bool _Value) { IsActive = _Value; }
	//inline void SetActorTickEnabled(bool _IsActive) { Tickable = _IsActive; }
	// 현재 객체의 타입과 비교
	inline virtual bool IsA(const std::type_info& type) const { return typeid(*this) == type; }

protected:

private:
	std::string Name;
	bool IsActive;
	bool Tickable;
	bool IsDestroyed;
	float DestroyDelay;
};

