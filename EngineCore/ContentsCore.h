#pragma once

// Ŭ���� ���� :
class UContentsCore : public UObject
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};