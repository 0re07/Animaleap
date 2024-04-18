#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Scene/GameScene.h"
#include "../BoundObject/Obstacle.h"
#include "ObstacleCanon.h"

ObstacleCanon::ObstacleCanon(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot)
	:GenerateObject(gameScene, pos, scl, rot, Player::PLAYER_TYPE::LEFT_PLAYER)
{
	//モデル読み込み
	auto& res = ResourceManager::GetInstance();
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::OBSTACLE_CANON_MODEL));

	transform_.pos_ = pos;
	transform_.scl_ = scl;

	transform_.Update();
}

ObstacleCanon::~ObstacleCanon()
{
}

void ObstacleCanon::Init(void)
{
	count_ = 0;
	delta_ = 0.0f;

}

void ObstacleCanon::Release(void)
{
}

void ObstacleCanon::Update(float deltaSeconds)
{
	if (isFire_) {
		if (count_ < max_) {
			Fire();
		}
		else if (count_ >= max_) {
			count_ = 0;
			isFire_ = false;
			delta_ = 0.0f;
		}
	}
}

void ObstacleCanon::Draw(void)
{
	//DrawFormatString(0, 20, 0xffffff, "deltaTime:%f", delta_);

	MV1DrawModel(transform_.modelId_);
}

/// <summary>
/// おじゃまの作成
/// </summary>
/// <param name="type">プレイヤーの番号（１Ｐか２Ｐか）</param>
/// <param name="level">キャラクターのレベル</param>
void ObstacleCanon::Generate(Player::PLAYER_TYPE type, Character::CHARACTOR_LEVEL level)
{

	//落下量
	fallPow_ = 0.5f;

	obstacleScl_ = { 1.0f,1.0f,1.0f };

	//プレイヤータイプによって発射方向を変更
	Transform transform;

	switch (type)
	{
	case Player::PLAYER_TYPE::LEFT_PLAYER:
		fallPlayerType_ = Player::PLAYER_TYPE::RIGHT_PLAYER;
		transform.quaRot_ = VECTOR{ 0.0f,-90.0f,0.0f };
		moveDir_ = { -1.0f, 1.0f, 0.0f };
		break;
	case Player::PLAYER_TYPE::RIGHT_PLAYER:
		fallPlayerType_ = Player::PLAYER_TYPE::LEFT_PLAYER;
		transform.quaRot_ = VECTOR{ 0.0f,90.0f,0.0f };
		moveDir_ = { 1.0f, 1.0f, 0.0f };
		break;
	default:
		break;
	}

	transform.Update();

	obstacleRot_ = transform.rot_;

	//プレイヤーレベルによっておじゃま個数
	max_ = 0;

	switch (level)
	{
	case Character::CHARACTOR_LEVEL::LEVEL_1:
		max_ = 3;
		break;
	case Character::CHARACTOR_LEVEL::LEVEL_2:
		max_ = 4;
		break;
	case Character::CHARACTOR_LEVEL::LEVEL_3:
		max_ = 5;
		break;
	default:
		break;
	}

	isFire_ = true;
}

void ObstacleCanon::Fire(void)
{
	delta_ += 1.0f;

	//１秒間隔で出現
	if (delta_ >= 60.0f) {
		delta_ -= 60.0f;

		gameScene_.CreateObject<Obstacle>(transform_.pos_, obstacleScl_, obstacleRot_, fallPlayerType_, moveDir_, fallPow_);

		count_++;
	}
}

void ObstacleCanon::InitCollisionAfter(void)
{
}
