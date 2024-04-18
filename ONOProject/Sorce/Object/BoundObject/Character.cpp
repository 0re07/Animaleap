#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Common/Collision/CollisionShape.h"
#include "Character.h"

#include "../../Graphics/Drawable/3DModel/ModelMaterial.h"
#include "../../Graphics/Drawable/3DModel/ModelRenderer.h"

Character::Character(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
	const VECTOR& moveDir, const float& fallingPow) :
	BoundObject(pos, scl, rot, playerType, moveDir, fallingPow)
{
}

Character::~Character()
{
}

void Character::Init(void)
{
	BoundObject::Init();

	auto& res = ResourceManager::GetInstance();

	//レベル別モデル
	dogModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_DOG_MODEL);
	fishModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_FISH_MODEL);
	chickenModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_CHICKEN_MODEL);

	//モデルの登録
	transform_.SetModel(dogModelHandle_);

	//ローカル座標
	localPos = {0.0f,-30.0f,0.0f};

	//大きさ
	const float baseSize = 80;
	float scale = HIT_SIZE_RADIOUS / baseSize;
	transform_.scl_ = { scale,scale,scale };
	
	//3D基本情報の更新
	transform_.Update();

	//生死判定
	SetIsAlive(true);

	//移動スピード
	speed_ = 2;
	//バウンド回数
	boundCount_ = 0;
	//キャラクターレベル
	level_ = CHARACTOR_LEVEL::LEVEL_1;

	// 当たり判定後処理の設定
	InitCollisionAfter();

	// コリジョン生成
	AddCollisions(transform_.pos_, HIT_SIZE_RADIOUS,
		COLLISION_OBJECT_TYPE::CHARACTER,
		static_cast<unsigned int>(COLLISION_OBJECT_TYPE::TRAMPOLINE)+
		static_cast<unsigned int>(COLLISION_OBJECT_TYPE::GOAL)
	);
}

void Character::Release(void)
{
}

void Character::Update(float deltaSeconds)
{
	//落下処理
	FallProcess();
	//死亡処理
	DeathProcess();
	//回転処理
	RotateProcess();

	//反転テスト
	bool rightWallHit = false, leftWallHit = false;
	Vector2 screenSize = Application::GetInstance().GetScreenSize();
	if (playerType_ == Player::PLAYER_TYPE::LEFT_PLAYER)
	{
		rightWallHit = transform_.pos_.x >=  -40.0f && moveDir_.x > 0.0f;
		leftWallHit = transform_.pos_.x <= -(screenSize.x / 2.0f - 280.0f) && moveDir_.x < 0.0f;
	}
	else
	{
		rightWallHit = transform_.pos_.x >= screenSize.x / 2.0f - 280.0f && moveDir_.x > 0.0f;
		leftWallHit = transform_.pos_.x <= 40.0f && moveDir_.x < 0.0f;
	}
	if (rightWallHit || leftWallHit)
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

void Character::Draw(void)
{
	//キャラクターモデル
	MV1DrawModel(transform_.modelId_);

	//testRenderer_->Draw();

#ifdef DEBUG
	//バウンド回数
	DrawFormatString(10, 160, 0xffffff, "バウンド回数：%d", boundCount_);
	//キャラレベル
	std::string charLevel = "キャラレベル:レベル１";
	if (level_ == CHARACTOR_LEVEL::LEVEL_2)charLevel = "キャラレベル:レベル２";
	else if (level_ == CHARACTOR_LEVEL::LEVEL_3)charLevel = "キャラレベル:レベル３";
	DrawFormatString(10, 180, 0xffffff, charLevel.c_str(), boundCount_);

	//キャラクター座標
	DrawFormatString(10, 50, 0xffffff, "キャラ座標：{%0.2f,%0.2f,%0.2f}",
		transform_.pos_.x, transform_.pos_.y, transform_.pos_.z);

	//キャラクター移動方向
	DrawFormatString(10, 70, 0xffffff, "移動方向　：{%0.2f,%0.2f,%0.2f}",
		moveDir_.x, moveDir_.y, moveDir_.z);
	DrawLine3D(transform_.pos_, VNorm(moveDir_), 0x00ffff);

	//落下量
	DrawFormatString(10, 90, 0xffffff, "落下量：{%0.2f,%0.2f,%0.2f}",
		fallingPow_.x, fallingPow_.y, fallingPow_.z);


#endif // _DEBUG

}

void Character::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//ジャンプ処理
	BoundObject::JumpProcess(jumpDir, jumpRate);

	//キャラレベルのチェック
	CheckLevelUp();
}

void Character::CheckLevelUp(void)
{
	//バウンド回数の加算
	boundCount_++;

	if (boundCount_ >= 3 && boundCount_ < 6)
	{
		level_ = CHARACTOR_LEVEL::LEVEL_2;
		transform_.SetModel(chickenModelHandle_);

	}
	else if (boundCount_ >= 6)
	{
		level_ = CHARACTOR_LEVEL::LEVEL_3;	
		transform_.SetModel(fishModelHandle_);

	}

}

