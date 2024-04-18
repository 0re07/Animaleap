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
	//���f���̓o�^
	transform_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::OBSTACLE_MODEL));

	//�傫��
	const float baseSize = 55;
	float size = HIT_SIZE_RADIOUS / baseSize;
	transform_.scl_ = { size,size,size };


	//3D��{���̍X�V
	transform_.Update();

	//��������
	SetIsAlive(true);

	//�ړ��X�s�[�h
	speed_ = 2.5f;

	// �����蔻��㏈���̐ݒ�
	InitCollisionAfter();

	// �R���W��������
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
	//��������
	FallProcess();
	//���S����
	DeathProcess();
	//��]����
	RotateProcess();


	//���]�e�X�g
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
		//�ړ������A���]
		ReverseMoveDirX();
	}

	// �R���W�����X�V����
	for (const auto& col : collisions_)
	{
		if (col->IsUpdate())
		{
			col->UpdateCollisionInfo(transform_.pos_);
		}
	}


	//3D��{���̍X�V
	transform_.Update();

}

void Obstacle::Draw(void)
{
	//���ז���
	MV1DrawModel(transform_.modelId_);
}

void Obstacle::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//�W�����v����
	BoundObject::JumpProcess(jumpDir,jumpRate);
}

//void Obstacle::InitCollisionAfter(void)
//{
//}
