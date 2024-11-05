#include "aepch.h"
#include "Tilemap.h"

ATilemap::ATilemap()
{
}

ATilemap::~ATilemap()
{
}

void ATilemap::Create(std::string_view _Sprite, FIntPoint _XYCount, FVector2D _TileSize)
{
	TileCount = _XYCount;

	AllTiles.resize(_XYCount.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_XYCount.X);
	}
}

void ATilemap::SetTile(FIntPoint _Index, int _SpriteIndex)
{
	if (0 > _Index.X) { return; }
	if (0 > _Index.Y) { return; }
	if (TileCount.X - 1 < _Index.X) { return; }
	if (TileCount.Y - 1 < _Index.Y) { return; }
	
	if (nullptr == AllTiles[TileCount.Y][TileCount.X].SpriteRenderer)
	{
		//USpriteR* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		AllTiles[TileCount.Y][TileCount.X].SpriteRenderer;
	}

}
