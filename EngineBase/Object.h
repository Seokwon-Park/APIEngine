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

	inline virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

	inline virtual std::string GetName()
	{
		return Name;
	}
protected:

private:
	std::string Name;

};

