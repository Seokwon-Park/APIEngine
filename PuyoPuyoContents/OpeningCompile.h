#pragma once

// 클래스 설명 :
class AOpeningCompile : public AActor
{
public:
	// Constrcuter Destructer
	AOpeningCompile();
	~AOpeningCompile();

	// Delete Function
	AOpeningCompile(const AOpeningCompile& _Other) = delete;
	AOpeningCompile(AOpeningCompile&& _Other) noexcept = delete;
	AOpeningCompile& operator=(const AOpeningCompile& _Other) = delete;
	AOpeningCompile& operator=(AOpeningCompile&& _Other) noexcept = delete;
	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
};
