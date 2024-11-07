#pragma once

// Ό³Έν :
class PuyoChainEffect
{
public:
	// constrcuter destructer
	PuyoChainEffect();
	~PuyoChainEffect();

	// delete Function
	PuyoChainEffect(const PuyoChainEffect& _Other) = delete;
	PuyoChainEffect(PuyoChainEffect&& _Other) noexcept = delete;
	PuyoChainEffect& operator=(const PuyoChainEffect& _Other) = delete;
	PuyoChainEffect& operator=(PuyoChainEffect&& _Other) noexcept = delete;

protected:

private:

};

