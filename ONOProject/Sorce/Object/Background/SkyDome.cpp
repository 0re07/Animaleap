#include "SkyDome.h"

SkyDome::SkyDome(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot) :
	Object(pos, scl, rot)
{
	int model = MV1LoadModel("Data/Model/Background/SkyDome/SkyDome_Night_a.mv1");
	transform_.SetModel(model);

	transform_.pos_ = pos;
	transform_.scl_ = scl;

	transform_.quaRot_ = Quaternion::Euler(rot);

	transform_.Update();
}

SkyDome::~SkyDome()
{
}

void SkyDome::Init(void)
{
	InitCollisionAfter();
}

void SkyDome::Release(void)
{
}

void SkyDome::Update(float deltaSeconds)
{
	transform_.Update();
}

void SkyDome::Draw(void)
{
	MV1DrawModel(transform_.modelId_);
}

void SkyDome::InitCollisionAfter(void)
{
}
