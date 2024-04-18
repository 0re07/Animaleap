#pragma once
#include "../Common/Vector2.h"

class Image
{
public:
	Image(int handle, const Vector2& pos);
	~Image();

	void Init(void);
	void Update(void);
	void Draw(void);

	void SetPos(const Vector2& pos);
	
private:
	int handle_;
	Vector2 pos_;
};

