#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ACarbuncleMenu : public AActor
{
public:
	// constrcuter destructer
	ACarbuncleMenu();
	~ACarbuncleMenu();

	// delete Function
	ACarbuncleMenu(const ACarbuncleMenu& _Other) = delete;
	ACarbuncleMenu(ACarbuncleMenu&& _Other) noexcept = delete;
	ACarbuncleMenu& operator=(const ACarbuncleMenu& _Other) = delete;
	ACarbuncleMenu& operator=(ACarbuncleMenu&& _Other) noexcept = delete;

protected:

private:
	USpriteRendererComponent* HeadRenderer;
	USpriteRendererComponent* BodyRenderer;
	USpriteRendererComponent* TailRenderer;

};

