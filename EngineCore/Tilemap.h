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

// 설명 :
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

	// 타일 이미지는 sprite 1개에서 
	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	// 여기에서    이 인덱스에다가    이스프라이트 
	void SetTile(FIntPoint _Index, int _SpriteIndex);
protected:

private:
	std::vector<std::vector<Tile>> AllTiles;
	FIntPoint TileCount;

};

