#pragma once

// Ό³Έν :
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
	inline bool CheckDestroy() const { return IsDestroyed; }
	inline void Destroy(float _Delay= 0.0f) 
	{ 
		DestroyDelay = _Delay;
		IsDestroyed = true;
	}
	inline void SetActorTickEnabled(bool _IsActive) { Tickable = _IsActive; }

protected:

private:
	std::string Name;
	bool Tickable;
	bool IsDestroyed;
	float DestroyDelay;
};

