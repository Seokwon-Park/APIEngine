#pragma once

// 클래스 설명 :
class ANameText : public AActor
{
public:
	// Constrcuter Destructer
	ANameText();
	~ANameText();

	// Delete Function
	ANameText(const ANameText& _Other) = delete;
	ANameText(ANameText&& _Other) noexcept = delete;
	ANameText& operator=(const ANameText& _Other) = delete;
	ANameText& operator=(ANameText&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;
private:

};
