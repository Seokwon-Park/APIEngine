#pragma once

#include <numbers>

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

	float Dot(const FVector2D& _Other) const
	{
		return X * _Other.X + Y * _Other.Y;
	}

	float Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	FVector2D Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			Y = Y / Len;
		}
		return *this;
	}

	float Distance(const FVector2D _Other)
	{
		return FVector2D::Distance(*this, _Other);
	}

	bool operator==(FVector2D _Other) const
	{
		return abs(X - _Other.X) < 1e-6f && abs(Y - _Other.Y) < 1e-6f;
	}

	bool operator!=(FVector2D _Other) const
	{
		return !(*this == _Other);
	}

	FVector2D operator*(int _Value) const
	{
		return operator*(static_cast<float>(_Value));
	}

	FVector2D operator*(float _Value) const
	{
		return FVector2D(X * _Value, Y * _Value);
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

	FVector2D operator-() const
	{
		FVector2D Result;
		Result.X = -X;
		Result.Y = -Y;
		return Result;
	}

	FVector2D operator/(int _Value) const
	{
		return operator/(static_cast<float>(_Value));
	}

	FVector2D operator/(float _Value) const
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
		return Result;
	}

	static FVector2D Lerp(FVector2D _A, FVector2D _B, float _T)
	{
		// (1-T)*A + T*B
		return _A + (_B - _A) * _T;
	}


	static FVector2D BezierLerp(FVector2D _Start, FVector2D _Middle, FVector2D _Target, float _T)
	{
		// (1-T)*A + T*B
		float U = 1 - _T;
		FVector2D Result;
		Result.X = U * U * _Start.X + 2 * U * _T * _Middle.X + _T * _T * _Target.X;
		Result.Y = U * U * _Start.Y + 2 * U * _T * _Middle.Y + _T * _T * _Target.Y;
		return Result;
	}

	static float Distance(const FVector2D& _A, const FVector2D& _B)
	{
		float X = _A.X - _B.X;
		float Y = _A.Y - _B.Y;
		return std::sqrt(X * X + Y * Y);
	}


	static FVector2D MoveTowards(FVector2D _Current, FVector2D _Target, float _MoveStep)
	{
		FVector2D Direction = _Target - _Current;     // 목표 지점으로 가는 방향 벡터
		float Distance = Direction.Distance(_Target); // 현재와 목표 사이의 거리

		// 목표 지점에 이미 도달했거나 maxDistanceDelta가 더 크다면 목표 위치 반환
		if (Distance <= _MoveStep || Distance == 0.0f) {
			return _Target;
		}

		return _Current + Direction * (_MoveStep / Distance);
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

	FTransform(FVector2D _Location, FVector2D _Scale)
		:Location(_Location), Scale(_Scale)
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
	static const FIntPoint ZERO;

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

	std::string ToString()
	{
		std::string Result = "";
		Result = "X : [" + std::to_string(X) + "] Y : [" + std::to_string(Y) + "]";
		return Result;
	}
};

class UColor
{
public:
	union
	{
		unsigned int Color = 0;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

	};

	UColor()
		:Color(0)
	{

	}

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
	operator DWORD()
	{
		return (A << 24) | (R << 16) | (G << 8) | B;
	}
};

class FEngineMath
{
public:
	static const double PI_D;
	static const float PI;
	FEngineMath() {};

	inline static float Sqrt(float _Value)
	{
		return ::sqrtf(_Value);
	}
	inline static float DegreesToRadians(float _Degrees)
	{
		return _Degrees * (PI / 180.0f);
	}

	inline static float Lerp(float _Start, float _End, float _T)
	{
		return _Start + (_End - _Start) * _T;
	}

	template <typename T>
	static T Max(T A, T B)
	{
		return (A >= B ? A : B);
	}

	template <typename T>
	static T Min(T A, T B)
	{
		return (A <= B ? A : B);
	}


};

