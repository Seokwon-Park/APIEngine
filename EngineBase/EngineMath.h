#pragma once

class FVector
{
public:
	float X = 0.0f;
	float Y = 0.0f;

	static const FVector LEFT;
	static const FVector RIGHT;
	static const FVector UP;
	static const FVector DOWN;

	FVector()
	{

	}

	FVector(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FVector operator+(FVector _Other) const
	{
		FVector Result; 
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector operator/(int _Value) const
	{
		FVector Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FVector _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FVector& operator+=(FVector _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};

class EngineMath
{
};

