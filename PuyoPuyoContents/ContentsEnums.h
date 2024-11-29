#pragma once

enum class EPuyoGameMode
{
	Solo,
	Versus,
	Training
};

enum class ERenderLayer
{
	Background = -1000,
	BottomBackground = -150,
	BottomCover = -100,
	Play = 0,
	TitleSepia = 5,
	Frame = 100,
	Text = 105,
	Warn = 110,
	TitlePuyo = 115,
};

//»Ñ¿ä»Ñ¿ä »ö
enum class EPuyoColor
{
	Red,
	Green,
	Blue,
	Purple,
	Yellow,
	Garbage,
};

//»Ñ¿ä»Ñ¿ä ÅØ½ºÆ® »ö
enum class EPuyoBoardColor
{
	Red,
	Blue,
	Green,
	Black
};

