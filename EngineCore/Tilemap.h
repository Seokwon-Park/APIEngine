#pragma once
#include "Actor.h"
#include "SpriteRendererComponent.h"

class Tile
{
public:
	USpriteRendererComponent* SpriteRenderer;
	bool IsMove = true;
	FVector2D Scale;
	FVector2D Pivot;
};

// ���� :
class ATilemap : public AActor
{
public:
	// constrcuter destructer
	ATilemap();
	~ATilemap();

	// delete Function
	ATilemap(const ATilemap& _Other) = delete;
	ATilemap(ATilemap&& _Other) noexcept = delete;
	ATilemap& operator=(const ATilemap& _Other) = delete;
	ATilemap& operator=(ATilemap&& _Other) noexcept = delete;

	// Ÿ�� �̹����� sprite 1������ 
	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	// ���⿡��    �� �ε������ٰ�    �̽�������Ʈ 
	void SetTile(FIntPoint _Index, int _SpriteIndex);
protected:

private:
	std::vector<std::vector<Tile>> AllTiles;
	FIntPoint TileCount;

};

