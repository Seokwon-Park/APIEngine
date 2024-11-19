#pragma once

//점수계산에 들어가는 상수모음

// Single Player Chain Power Table
const int SingleCPTable[25] = { 0,4,20,24,32,48,96,160,240,320,480,600,700,800,900,999,999,999,999,999,999,999,999,999,999 };
// 멀티플레이어 체인 파워 테이블
const int MultiCPTable[25] = { 0, 1, 8 ,16, 32, 64 ,96 ,128 ,160 ,192 ,224 ,256 ,288, 320 ,352 ,384 ,416 ,448 ,480 ,512 ,544 ,576 ,608 ,640 ,672 };
const int ColorBonusTable[6] = { 0,0,3,6,12,24 };
const int GroupBonusTable[12] = { 0,0,0,0,0,2,3,4,5,6,7,10 };