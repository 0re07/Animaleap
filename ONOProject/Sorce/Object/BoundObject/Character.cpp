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

	//���x���ʃ��f��
	dogModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_DOG_MODEL);
	fishModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_FISH_MODEL);
	chickenModelHandle_= res.LoadModelDuplicate(ResourceManager::SRC::CHARACTER_CHICKEN_MODEL);

	//���f���̓o�^
	transform_.SetModel(dogModelHandle_);

	//���[�J�����W
	localPos = {0.0f,-30.0f,0.0f};

	//�傫��
	const float baseSize = 80;
	float scale = HIT_SIZE_RADIOUS / baseSize;
	transform_.scl_ = { scale,scale,scale };
	
	//3D��{���̍X�V
	transform_.Update();

	//��������
	SetIsAlive(true);

	//�ړ��X�s�[�h
	speed_ = 2;
	//�o�E���h��
	boundCount_ = 0;
	//�L�����N�^�[���x��
	level_ = CHARACTOR_LEVEL::LEVEL_1;

	// �����蔻��㏈���̐ݒ�
	InitCollisionAfter();

	// �R���W��������
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
	//��������
	FallProcess();
	//���S����
	DeathProcess();
	//��]����
	RotateProcess();

	//���]�e�X�g
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

void Character::Draw(void)
{
	//�L�����N�^�[���f��
	MV1DrawModel(transform_.modelId_);

	//testRenderer_->Draw();

#ifdef DEBUG
	//�o�E���h��
	DrawFormatString(10, 160, 0xffffff, "�o�E���h�񐔁F%d", boundCount_);
	//�L�������x��
	std::string charLevel = "�L�������x��:���x���P";
	if (level_ == CHARACTOR_LEVEL::LEVEL_2)charLevel = "�L�������x��:���x���Q";
	else if (level_ == CHARACTOR_LEVEL::LEVEL_3)charLevel = "�L�������x��:���x���R";
	DrawFormatString(10, 180, 0xffffff, charLevel.c_str(), boundCount_);

	//�L�����N�^�[���W
	DrawFormatString(10, 50, 0xffffff, "�L�������W�F{%0.2f,%0.2f,%0.2f}",
		transform_.pos_.x, transform_.pos_.y, transform_.pos_.z);

	//�L�����N�^�[�ړ�����
	DrawFormatString(10, 70, 0xffffff, "�ړ������@�F{%0.2f,%0.2f,%0.2f}",
		moveDir_.x, moveDir_.y, moveDir_.z);
	DrawLine3D(transform_.pos_, VNorm(moveDir_), 0x00ffff);

	//������
	DrawFormatString(10, 90, 0xffffff, "�����ʁF{%0.2f,%0.2f,%0.2f}",
		fallingPow_.x, fallingPow_.y, fallingPow_.z);


#endif // _DEBUG

}

void Character::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//�W�����v����
	BoundObject::JumpProcess(jumpDir, jumpRate);

	//�L�������x���̃`�F�b�N
	CheckLevelUp();
}

void Character::CheckLevelUp(void)
{
	//�o�E���h�񐔂̉��Z
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

