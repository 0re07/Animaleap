#include <EffekseerForDXLib.h>
#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Utility/Utility.h"
#include "../../Common/Collision/CollisionShape.h"
#include "../../Sound/SoundController.h"
#include "../Trampoline.h"
#include "../Stage/Goal.h"
#include "BoundObject.h"

BoundObject::BoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
	const VECTOR& moveDir, const float& fallingPow) :
	Object(pos, scl, rot),
	playerType_(playerType),
	moveDir_(moveDir),
	fallingPow_(fallingPow)
{
}

BoundObject::~BoundObject()
{
}

void BoundObject::Init(void)
{
	//�����_���l
	auto gen = Application::GetInstance().CreateRandomObject();
	std::uniform_real_distribution<float>dis(-1.0, 1.0);
	//�����_����]����
	rotateDir_ = VNorm(VECTOR({ dis(gen),dis(gen),dis(gen) }));
	//��]�X�s�[�h�̃����_���l
	float randomValue = dis(gen);
	rotateSpeed_ = randomValue / 10;


	auto& res = ResourceManager::GetInstance();
	//�G�t�F�N�g�̃��[�h
	hitEffect_ = res.Load(ResourceManager::SRC::HIT_EFFECT).handleId_;

	//SE
	boundSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::BOUND_SE).handleId_);
	//�S�[����
	goalSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::GOAL_SE).handleId_);


}

void BoundObject::DeathProcess(void)
{
	//Y���W�����l�ȉ��ɂȂ������A���S��Ԃɂ���
	if (transform_.pos_.y <= DEATH_HIGHT)
	{
		SetIsAlive(false);
	}
}

void BoundObject::GravityProcess(void)
{
	// �d�͕���
	const VECTOR dirGravity = {0.0f,-1.0f,0.0f};

	// �����ʂ̉��Z
	fallingPow_ += VScale(dirGravity, GRAVITY_POWER).y;

	//�ړ�������ύX
	moveDir_.y = fallingPow_;

	//�ړ��ʂ̉��Z
	//movePow_ = VAdd(fallingPow_, movePow_);

}

void BoundObject::FallProcess(void)
{
	movePow_ = { 0,0,0 };	//�ړ��ʂ��O�ɂ���

	movePow_ = VScale(moveDir_, speed_);		//�ړ��ʂ̌v�Z
	GravityProcess();							//�d�͂ɂ��ړ��ʂ����Z
	movedPos_ = VAdd(transform_.pos_, movePow_);//�ړ�����W
	transform_.pos_ = movedPos_;				//�ړ�����W�𔽉f
}

void BoundObject::RotateProcess(void)
{
	VECTOR  rotatePos = VScale(rotateDir_, rotateSpeed_);
	transform_.quaRot_=transform_.quaRot_.Mult(Quaternion::Euler(rotatePos));
}

void BoundObject::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//�g�����|�����ƏՓ˂����ꍇ�̏���
	if (fallingPow_ <= 0.0f)	
	{
		//SE�Đ�
		boundSE_->Play();

		//�W�����v�����i�^��j
		VECTOR dirJump = jumpDir;
		moveDir_ = CalcReflection(moveDir_, dirJump);

		//�W�����v�������ɁA�����ʂ��v�Z
		const float minJumpPow = JUMP_POW * 0.5;		//�Œ�W�����v��
		fallingPow_ = (std::max)(minJumpPow, JUMP_POW * jumpRate);

	}
}

void BoundObject::ReverseMoveDirX(void)
{
	moveDir_.x *= -1;
}

VECTOR BoundObject::CalcReflection(const VECTOR& moveDIr, const VECTOR& trampolineVec)
{
	//����
	float dot = VDot(moveDIr, trampolineVec);

	//���˃x�N�g��
	VECTOR reflect = VSub(moveDIr, VScale(trampolineVec, 2.0f * dot));

	return reflect;
}

void BoundObject::InitCollisionAfter(void)
{
	collisionCallbacks_[COLLISION_OBJECT_TYPE::TRAMPOLINE] = std::bind(&BoundObject::JumpAfterTrampolineCollision, this, std::placeholders::_1, std::placeholders::_2);
	collisionCallbacks_[COLLISION_OBJECT_TYPE::GOAL] = std::bind(&BoundObject::GoalAfterGoalCollision, this, std::placeholders::_1, std::placeholders::_2);
	collisionCallbacks_[COLLISION_OBJECT_TYPE::WALL] = std::bind(&BoundObject::GoalAfterWallCollision, this, std::placeholders::_1, std::placeholders::_2);
}

void BoundObject::JumpAfterTrampolineCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	Trampoline& trampoline = dynamic_cast<Trampoline&>(hitObject);

	//�g�����|�����̔����̒���
	float halfTramLength = trampoline.GetLength() / 2;

	//�g�����|�������S�ʒu�ƏՓˍ��W�̋���
	float dis = Utility::Distance(hitObject.GetPos(), collisionData.pos);

	//��������
	float ratio = std::clamp(dis / halfTramLength, 0.0f,1.0f);

	//�W�����v�̍����{���i1.0f�ɋ߂��قǁA�����W�����v����j
	float jumpHeightRaito = 1.0f - ratio;

	JumpProcess(collisionData.normal, jumpHeightRaito);

	//�Փˈʒu�������ɋ߂�������
	//�q�b�g�G�t�F�N�g�̍Đ�
	float nearDis = 0.6f;
	if (jumpHeightRaito <= nearDis)return;

	float size = 10.0f;
	int playHandle = PlayEffekseer3DEffect(hitEffect_);
	SetScalePlayingEffekseer3DEffect(playHandle, size, size, size);
	SetPosPlayingEffekseer3DEffect(playHandle, 
		collisionData.pos.x, collisionData.pos.y, collisionData.pos.z);

}

void BoundObject::GoalAfterGoalCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	Goal& goal = dynamic_cast<Goal&>(hitObject);

	//�S�[�����J���Ă��Ȃ��ꍇ�A���������Ȃ�
	if (!goal.GetIsOpen())return;

	//���Ŏ��̉��o���l����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�S�[����
	if (IsAlive() && IsEnable())
	{
		goalSE_->Play();
	}

	//���S����
	SetIsAlive(false);
	SetEnable(false);
}

void BoundObject::GoalAfterWallCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	//�ړ������A���]
	ReverseMoveDirX();

	//�ǂƉ��x���Փ˔�����N�����Ȃ��悤�ɁA�ړ������� �����o��
	// float pushPow=5.0f;
	//transform_.pos_.x += moveDir_.x * pushPow;
}

