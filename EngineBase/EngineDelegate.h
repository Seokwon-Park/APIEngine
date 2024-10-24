#pragma once

// Ό³Έν :
class EngineDelegate
{
public:
	// constrcuter destructer
	EngineDelegate();

	EngineDelegate(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	~EngineDelegate();

	// delete Function
	//EngineDelegate(const EngineDelegate& _Other) = delete;
	//EngineDelegate(EngineDelegate&& _Other) noexcept = delete;
	//EngineDelegate& operator=(const EngineDelegate& _Other) = delete;
	//EngineDelegate& operator=(EngineDelegate&& _Other) noexcept = delete;

	bool IsBind()
	{
		return false == Functions.empty();
	}

	//push_back
	void operator+=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	void operator()()
	{
		for (auto func : Functions)
		{
			func();
		}
	}

	void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

