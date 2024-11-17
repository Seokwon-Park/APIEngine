#pragma once

// 클래스 설명 :
class UContentsCore : public UObject
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};