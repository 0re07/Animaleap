#include <EffekseerForDXLib.h>
#include "../../Resource/ResourceManager.h"
#include "../../Common/Collision/CollisionShape.h"
#include "../BoundObject/Character.h"
#include "Goal.h"

Goal::Goal(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot) :Object(pos, scl, rot)
{
	//���f���ǂݍ���
	auto& res = ResourceManager::GetInstance();
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::GOAL_MODEL));

	transform_.pos_ = pos;
	transform_.scl_ = scl;

	//3D��{���̍X�V
	transform_.Update();

	Init();
}

Goal::~Goal()
{
}

void Goal::Init(void)
{
	//�G�t�F�N�g�ǂݍ���
	auto& res = ResourceManager::GetInstance();
	goalLeftEffect_ = res.Load(ResourceManager::SRC::GOAL_LEFT_EFFECT).handleId_;
	goalRightEffect_ = res.Load(ResourceManager::SRC::GOAL_RIGHT_EFFECT).handleId_;
	goalOpenEffect_ = res.Load(ResourceManager::SRC::GOAL_OPEN_EFFECT).handleId_;

	isGoal_ = false;

	//�S�[���̐F���������i���j
	SetGoalColor(1.0f, 1.0f, 1.0f, 1.0f);

	//���Ă�����
	isOpen_ = false;

	// �����蔻��㏈���̐ݒ�
	InitCollisionAfter();

	// �R���W��������
	AddCollisions(transform_.pos_, transform_.modelId_,
		COLLISION_OBJECT_TYPE::GOAL,
		static_cast<unsigned int>(COLLISION_OBJECT_TYPE::CHARACTER)
	);

	countLeft_ = 0;
	countRight_ = 0;
}

void Goal::Release(void)
{
}

void Goal::Update(float deltaSeconds)
{
}

void Goal::Draw(void)
{
	//�g�����|�������W
	MV1DrawModel(transform_.modelId_);

	//�G�t�F�N�g�`��
	//�J���Ă���S�[��
	if (isOpen_) {
		PlayOpenEffect();
	}
	else {
		StopEffekseer2DEffect(goalOpenEffect_);
	}

	//�S�[�������Ƃ�
	if (isOpen_) {
		if (isGoal_) {
			if (playerType_ == Player::PLAYER_TYPE::LEFT_PLAYER) {
				PlayLeftEffect();
			}
			else if (playerType_ == Player::PLAYER_TYPE::RIGHT_PLAYER) {
				PlayRightEffect();
			}
		}
	}
	else {
		StopEffekseer2DEffect(goalLeftEffect_);
		StopEffekseer2DEffect(goalRightEffect_);
	}
}

/// <summary>
/// �S�[�����J���鏈��
/// </summary>
/// <param name=""></param>
void Goal::OpenSign(void)
{
	//�J����
	isOpen_ = true;

	//�S�[���̐F�ύX�i���F�j
	SetGoalColor(1.0f, 1.0f, 0.0f, 1.0f);
}

/// <summary>
/// �S�[������鏈��
/// </summary>
/// <param name=""></param>
void Goal::CloseSign(void)
{
	//�߂�
	isOpen_ = false;

	//�S�[���𖳂��ɂ���
	isGoal_ = false;

	//�S�[���̐F���������i���j
	SetGoalColor(1.0f, 1.0f, 1.0f, 1.0f);
}

bool Goal::GetIsOpen(void)
{
	return isOpen_;
}

bool Goal::GetIsGoal(void)
{
	return isGoal_;
}

void Goal::SetIsGoalFalse(void)
{
	isGoal_ = false;
}

Player::PLAYER_TYPE Goal::GetPlayerType(void)
{
	return playerType_;
}

void Goal::SetGoalColor(float red, float green, float blue, float alpha)
{
	MV1SetDifColorScale(transform_.modelId_, GetColorF(red, green, blue, alpha));
}

void Goal::PlayOpenEffect(void)
{
	float size = 15.0f;

	int playHandle = PlayEffekseer3DEffect(goalOpenEffect_);
	SetScalePlayingEffekseer3DEffect(playHandle, size, size, size);
	SetPosPlayingEffekseer3DEffect(playHandle,
		transform_.pos_.x, transform_.pos_.y, transform_.pos_.z);

}

void Goal::PlayLeftEffect(void)
{
	float size = 15.0f;

	int playHandle = PlayEffekseer3DEffect(goalLeftEffect_);
	SetScalePlayingEffekseer3DEffect(playHandle, size, size, size);
	SetPosPlayingEffekseer3DEffect(playHandle,
		transform_.pos_.x -20.0f, transform_.pos_.y, transform_.pos_.z);
}

void Goal::PlayRightEffect(void)
{
	float size = 15.0f;

	int playHandle = PlayEffekseer3DEffect(goalRightEffect_);
	SetScalePlayingEffekseer3DEffect(playHandle, size, size, size);
	SetPosPlayingEffekseer3DEffect(playHandle,
		transform_.pos_.x +20.0f, transform_.pos_.y, transform_.pos_.z);
}

void Goal::InitCollisionAfter(void)
{
	collisionCallbacks_[COLLISION_OBJECT_TYPE::CHARACTER] = std::bind(&Goal::GoalAfterCharacterCollision, this, std::placeholders::_1, std::placeholders::_2);
}

void Goal::GoalAfterCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	//�L�����N�^�[�ł͂Ȃ������ꍇ
	if (typeid(hitObject) != typeid(Character))return;

	//�_�E���L���X�g
	Character& character = dynamic_cast<Character&>(hitObject);

	if (hitObject.IsAlive()) {
		isGoal_ = true;
	}

	playerType_ = character.GetPlayerType();
}
