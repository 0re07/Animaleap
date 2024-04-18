#include "../../Resource/ResourceManager.h"
#include "Wall.h"

Wall::Wall(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot) :Object(pos, scl, rot)
{
	//モデル読み込み
	auto& res = ResourceManager::GetInstance();
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::WALL_MODEL));

	transform_.pos_ = pos;
	transform_.scl_ = scl;

	transform_.quaRot_ = Quaternion::Euler(rot);

	//3D基本情報の更新
	transform_.Update();
}

Wall::~Wall()
{
}

void Wall::Init(void)
{
}

void Wall::Release(void)
{
}

void Wall::Update(float deltaSeconds)
{
}

void Wall::Draw(void)
{	
	//トランポリン座標
	MV1DrawModel(transform_.modelId_);
}

void Wall::InitCollisionAfter(void)
{
}
