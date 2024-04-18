#include"../Utility/Utility.h"
#include "../Resource/ResourceManager.h"
#include "../Common/Collision/CollisionShape.h"
#include "Trampoline.h"

Trampoline::Trampoline(
	const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType, const float& length):
	Object(pos, scl, rot), playerType_(playerType), length_(length)
{

	auto& res = ResourceManager::GetInstance();
	//モデルの登録
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::TRAMPOLINE_COLLSION_MODEL));

	float rotZ = rot.z;
	const float reverseAngle = 90.0f;
	float absAngle = Utility::Rad2DegF(abs(rotZ));
	//モデルの上方向が下を向いている時、半回転させる
	if (absAngle >= reverseAngle)
	{
		int sign = abs(rotZ) / rotZ;
		float halfTurnAngle = (absAngle - reverseAngle- reverseAngle) * sign;
		rotZ = Utility::Deg2RadF(halfTurnAngle);
	}

	transform_.quaRot_ = Quaternion::Euler({0.0f,0.0f,rotZ});
	cloudTransform_.quaRot_ = transform_.quaRot_;


	cloudTransform_.Update();
	transform_.Update();
}

Trampoline::~Trampoline()
{
}

void Trampoline::Init(void)
{

	// 当たり判定後処理の設定
	InitCollisionAfter();

	// コリジョン生成
	AddCollisions(transform_.pos_, transform_.modelId_,
		COLLISION_OBJECT_TYPE::TRAMPOLINE,
		static_cast<unsigned int>(COLLISION_OBJECT_TYPE::CHARACTER),
		false
	);

	auto& res = ResourceManager::GetInstance();
	//モデルの登録
	cloudTransform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::CLOUD_MODEL));
	cloudTransform_.pos_ = transform_.pos_;
	const float size = 4;
	cloudTransform_.scl_ = { 
		transform_.scl_.x / size,
		0.2, 
		0.2 
	};
	cloudTransform_.Update();

}

void Trampoline::Release(void)
{
}

void Trampoline::Update(float deltaSeconds)
{
	generationTime_ += deltaSeconds;
	//一定時間経過で削除する
	ExtinctionTrampoline();


	//回転
	//float spped = 4;
	//transform_.quaRot_.z += Utility::Deg2RadF(spped);
	//transform_.Update();

}

void Trampoline::Draw(void)
{

	//トランポリン
	MV1DrawModel(cloudTransform_.modelId_);



	//DrawFormatString(20, 300, 0xffffff, "座標：{%0.2f, %0.2f, %0.2f}",
	//	cloudTransform_.pos_.x, cloudTransform_.pos_.y,cloudTransform_.pos_.z);

	//VECTOR test = Quaternion::ToEuler(cloudTransform_.quaRot_);
	//DrawFormatString(20, 300, 0xffffff, "角度：{%0.2f, %0.2f, %0.2f}",
	//	test.x, test.y, test.z);

}

void Trampoline::ExtinctionTrampoline(void)
{
	//一定時間経過でトランポリンの削除
	if (generationTime_ >= DISAPPEAR_TIME)
	{
		SetCollisionActive(COLLISION_OBJECT_TYPE::TRAMPOLINE, false);
		isAlive_ = false;
	}
}

void Trampoline::InitCollisionAfter(void)
{
	collisionCallbacks_[COLLISION_OBJECT_TYPE::CHARACTER] = std::bind(&Trampoline::HitCharacterCollision, this, std::placeholders::_1, std::placeholders::_2);
}

void Trampoline::HitCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	SetCollisionActive(COLLISION_OBJECT_TYPE::TRAMPOLINE, false);

	isAlive_ = false;
}
