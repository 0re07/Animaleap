#pragma once
class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2(void);
	Vector2(int vX, int vY);
	
	~Vector2() {};

	Vector2 operator + (Vector2 vec)
	{
		return { x += vec.x, y += vec.y };
	}

	Vector2 operator - (Vector2 vec)
	{
		return { x -= vec.x, y -= vec.y };
	}
	Vector2 operator * (Vector2 vec)
	{
		return { x *= vec.x, y *= vec.y };
	}

	//Vector2 Normlize (Vector2 vec)
	//{
	//	int size = vec.x * vec.x + vec.y * vec.y;

	//	if (size == 0)
	//	{
	//		return vec;
	//	}

	//	return { x /= size, y /= size };
	//}

	
};

