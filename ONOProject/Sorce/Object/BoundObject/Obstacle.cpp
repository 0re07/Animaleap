#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Common/Collision/CollisionShape.h"
#include "Obstacle.h"

Obstacle::Obstacle(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
	const VECTOR& moveDir, const float& fallingPow) :
	BoundObject(pos, scl, rot, playerType, moveDir, fallingPow)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init(void)
{
	BoundObject::Init();

	auto& res = ResourceManager::GetInstance();
	//モデルの登録
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::OBSTACLE_MODEL));

	//大きさ
	const float baseSize = 55;
	float size = HIT_SIZE_RADIOUS / baseSize;
	transform_.scl_ = { size,size,size };


	//3D基本情報の更新
	transform_.Update();

	//生死判定
	SetIsAlive(true);

	//移動スピード
	speed_ = 2.5f;

	// 当たり判定後処理の設定
	InitCollisionAfter();

	// コリジョン生成
	AddCollisions(transform_.pos_, HIT_SIZE_RADIOUS,
		COLLISION_OBJECT_TYPE::CHARACTER,
		static_cast<unsigned int>(COLLISION_OBJECT_TYPE::TRAMPOLINE)
	);
}

void Obstacle::Release(void)
{
}

void Obstacle::Update(float deltaSeconds)
{
	//落下処理
	FallProcess();
	//死亡処理
	DeathProcess();
	//回転処理
	RotateProcess();


	//反転テスト
	bool lightWallHit = false, leftWallHit = false;
	Vector2 screenSize = Application::GetInstance().GetScreenSize();
	if (playerType_ == Player::PLAYER_TYPE::LEFT_PLAYER)
	{
		lightWallHit = transform_.pos_.x >= -40.0f && moveDir_.x > 0.0f;
		leftWallHit = transform_.pos_.x <= -(screenSize.x / 2.0f - 280.0f) && moveDir_.x < 0.0f;
	}
	else
	{
		lightWallHit = transform_.pos_.x >= screenSize.x / 2.0f - 280.0f && moveDir_.x > 0.0f;
		leftWallHit = transform_.pos_.x <= 40.0f && moveDir_.x < 0.0f;
	}
	if (lightWallHit || leftWallHit)
	{
		//移動方向、反転
		ReverseMoveDirX();
	}

	// コリジョン更新処理
	for (const auto& col : collisions_)
	{
		if (col->IsUpdate())
		{
			col->UpdateCollisionInfo(transform_.pos_);
		}
	}


	//3D基本情報の更新
	transform_.Update();

}

void Obstacle::Draw(void)
{
	//お邪魔玉
	MV1DrawModel(transform_.modelId_);
}

void Obstacle::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//ジャンプ処理
	BoundObject::JumpProcess(jumpDir,jumpRate);
}

//void Obstacle::InitCollisionAfter(void)
//{
//}
