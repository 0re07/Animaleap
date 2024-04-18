#include <DxLib.h>
#include "Image.h"

Image::Image(int handle, const Vector2& pos) :
	handle_(handle),
	pos_(pos)
{
}

Image::~Image()
{
}

void Image::Init(void)
{
}

void Image::Update(void)
{
}

void Image::Draw(void)
{
	DrawGraph(pos_.x, pos_.y, handle_,true);
}

void Image::SetPos(const Vector2& pos)
{
	pos_ = pos;
}
