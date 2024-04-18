#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Scene/GameScene.h"
#include "../BoundObject/Character.h"
#include "CharacterCanon.h"

CharacterCanon::CharacterCanon(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, Player::PLAYER_TYPE playerType)
	:GenerateObject(gameScene, pos, scl, rot, playerType)
{
	//モデル読み込み
	auto& res = ResourceManager::GetInstance();

	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_CANON_MODEL));

	transform_.pos_ = pos;
	transform_.scl_ = scl;

	transform_.quaRot_ = rot;

	//3D基本情報の更新
	transform_.Update();

	delta_ = 0.0f;
	playerType_ = playerType;
}

CharacterCanon::~CharacterCanon()
{
}

void CharacterCanon::Init(void)
{
}

void CharacterCanon::Release(void)
{
}

void CharacterCanon::Update(float deltaSeconds)
{
	delta_ += deltaSeconds;

	CreateCharacter();
}

void CharacterCanon::Draw(void)
{
	MV1DrawModel(transform_.modelId_);
}

void CharacterCanon::CreateCharacter(void)
{
	//落下量
	float fallPow = 1.0f;

	VECTOR pos;

	VECTOR scl = transform_.scl_;

	VECTOR rot = transform_.rot_;


	//プレイヤータイプによって向きを変更
	VECTOR moveDir;

	switch (playerType_)
	{
	case Player::PLAYER_TYPE::LEFT_PLAYER:
		pos = { -450.0f,200.0f,500.0f };
		moveDir = { 1.0f, 1.0f, 0.0f };
		break;
	case Player::PLAYER_TYPE::RIGHT_PLAYER:
		pos = { 450.0f,200.0f,500.0f };
		moveDir = { -1.0f, 1.0f, 0.0f };
		break;
	default:
		break;
	}

	//５秒間隔で出現
	if (delta_ >= 5.0f) {
		delta_ -= 5.0f;

		gameScene_.CreateObject<Character>(pos, scl, rot, playerType_, moveDir, fallPow);
	}
}

void CharacterCanon::InitCollisionAfter(void)
{
}
