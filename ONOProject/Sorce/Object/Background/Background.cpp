#include "Background.h"

Background::Background(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot) :
	Object(pos, scl, rot)
{
}

Background::~Background()
{
}

void Background::Init(void)
{
	int model = MV1LoadModel("Data/Model/Background/SkyDome/SkyDome_Night_a.mv1");
	transform_.SetModel(model);

	transform_.Update();

	InitCollisionAfter();
}

void Background::Release(void)
{
}

void Background::Update(float deltaSeconds)
{
	transform_.Update();
}

void Background::Draw(void)
{
	MV1DrawModel(transform_.modelId_);
}

void Background::InitCollisionAfter(void)
{
}
