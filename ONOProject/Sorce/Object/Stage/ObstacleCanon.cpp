#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Scene/GameScene.h"
#include "../BoundObject/Obstacle.h"
#include "ObstacleCanon.h"

ObstacleCanon::ObstacleCanon(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot)
	:GenerateObject(gameScene, pos, scl, rot, Player::PLAYER_TYPE::LEFT_PLAYER)
{
	//���f���ǂݍ���
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
/// ������܂̍쐬
/// </summary>
/// <param name="type">�v���C���[�̔ԍ��i�P�o���Q�o���j</param>
/// <param name="level">�L�����N�^�[�̃��x��</param>
void ObstacleCanon::Generate(Player::PLAYER_TYPE type, Character::CHARACTOR_LEVEL level)
{

	//������
	fallPow_ = 0.5f;

	obstacleScl_ = { 1.0f,1.0f,1.0f };

	//�v���C���[�^�C�v�ɂ���Ĕ��˕�����ύX
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

	//�v���C���[���x���ɂ���Ă�����܌�
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

	//�P�b�Ԋu�ŏo��
	if (delta_ >= 60.0f) {
		delta_ -= 60.0f;

		gameScene_.CreateObject<Obstacle>(transform_.pos_, obstacleScl_, obstacleRot_, fallPlayerType_, moveDir_, fallPow_);

		count_++;
	}
}

void ObstacleCanon::InitCollisionAfter(void)
{
}
