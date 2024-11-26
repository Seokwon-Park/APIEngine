#pragma once

//������꿡 ���� �������

// Single Player Chain Power Table
const int SingleCPTable[25] = { 0,4,20,24,32,48,96,160,240,320,480,600,700,800,900,999,999,999,999,999,999,999,999,999,999 };
// ��Ƽ�÷��̾� ü�� �Ŀ� ���̺�
const int MultiCPTable[25] = { 0, 1, 8 ,16, 32, 64 ,96 ,128 ,160 ,192 ,224 ,256 ,288, 320 ,352 ,384 ,416 ,448 ,480 ,512 ,544 ,576 ,608 ,640 ,672 };
const int ColorBonusTable[6] = { 0,0,3,6,12,24 };
const int GroupBonusTable[12] = { 0,0,0,0,0,2,3,4,5,6,7,10 };

const int LevelEnemies[7] = { 0,8,6,5,4,2,1 };
const int LevelEnemiesPfsum[7] = { 0,8,14,19,23,25,26 };

const int DestroyRule[5] = { 4,2,6,4,4 };

const int ScoreToNextLevel[9] = { 0, 15000,45000,80000,120000,150000 };

const FIntPoint EnemyRemoveColor[28] = 
{
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
};

const std::vector<std::vector<std::string>> EnemyNameData = {
{"Skeleton", "   -T", ""},
{"  Will","   o","  Wisp"},
{" Sukiya"," Podes", ""},
{" Trio"," the"," Banshee"},
{"  Nomi", "", ""},
{" Momomo", "", ""},
{"Baromett", "", ""},
{"  Mini"," Zombie", ""},
{"Panotty", "", ""},
{"Mermaid", "", ""},
{" Nohoho", "", ""},
{"  Cait","  Sith", ""},
{" Fufufu","", ""},
{" Mummy","", ""},
{"Scorpion","Man",""},
{"Samurai","  Mole",""},
{" Harpy","",""},
{" Parara", "", ""},
{" Gazi"," Grave",""},
{"Suketou","  Dara", ""},
{" Monster", "",""},
{" Witch","",""},
{"Pakista","",""},
{"Drago","Centaur","",""},
{"Minotaur","",""},
{" Schezo"," Wegey",""},
{" Rulue","",""},
{" Satan","",""},
};

const std::vector<std::string> EnemyNameShort = {
"Skel",
"Wisp",
"Pode",
"Bans",
"Nomi",
"Momo",
"Baro",
"MZon",
"Pano",
"Merm",
"Noho",
"Cait",
"Fufu",
"Mumy",
"Scop",
"Mole",
"Hapy",
"Para",
"Gazi",
"Tara",
"Mons",
"Paki",
"Drag",
"Mino",
"Shez",
"Rulu",
"Sata",
};