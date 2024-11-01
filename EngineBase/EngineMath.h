#pragma once

// FVector로 통일하겠습니다.
// FVector2D xy
// FVector3D xyz
// FVector4D xyzw
// FVector4D == FVector;

class FVector2D
{
public:
	float X;
	float Y;

	static const FVector2D ZERO;
	static const FVector2D LEFT;
	static const FVector2D RIGHT;
	static const FVector2D UP;
	static const FVector2D DOWN;

	FVector2D() :X(0.0f), Y(0.0f)
	{

	}

	FVector2D(float _X, float _Y) : X(_X), Y(_Y)
	{

	}

	FVector2D(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	FVector2D(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	bool isZero() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	FVector2D Half()const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	float Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	void Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			X = Y / Len;
		}
	}

	bool operator==(FVector2D _Other) const
	{
		return abs(X - _Other.X) < 1e-6f && abs(Y - _Other.Y) < 1e-6f;
	}

	bool operator!=(FVector2D _Other) const
	{
		return !(*this == _Other);
	}



	FVector2D operator*(float _Value) const
	{
		FVector2D Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		return Result;
	}

	FVector2D operator+(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector2D operator-(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}


	FVector2D operator/(int _Value) const
	{
		FVector2D Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	FVector2D& operator+=(FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	FVector2D& operator-=(FVector2D _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}

	FVector2D& operator-=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		return *this;
	}

	std::string ToString()
	{
		std::string Result = "";
		Result = "X : [" + std::to_string(X) + "] Y : [" + std::to_string(Y) + "]";
	}
};

class FTransform
{

public:
	FVector2D Location;
	FVector2D Scale;

	FTransform()
		:Location(FVector2D()), Scale(FVector2D())
	{

	}

	FVector2D CenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	FVector2D CenterRightBottom() const
	{
		return Location + Scale.Half();
	}
};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}
};

class UColor
{
public:
	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};

class EngineMath
{
};

