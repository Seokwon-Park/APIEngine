#pragma once

// Ό³Έν :
class USoundManager : public UObject
{
public:
	// constrcuter destructer
	USoundManager();
	~USoundManager();

	// delete Function
	USoundManager(const USoundManager& _Other) = delete;
	USoundManager(USoundManager&& _Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& _Other) = delete;
	USoundManager& operator=(USoundManager&& _Other) noexcept = delete;

	static USoundManager& GetInstance()
	{
		static USoundManager Instance;
		return Instance;
	}

protected:

private:

}; 

