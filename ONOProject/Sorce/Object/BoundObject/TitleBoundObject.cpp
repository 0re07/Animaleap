#include <random>
#include <cstdlib>
#include "../../Application.h"
#include "../../Resource/ResourceManager.h"
#include "../../Common/Vector2.h"
#include "TitleBoundObject.h"

TitleBoundObject::TitleBoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const VECTOR& moveDir, const float& fallingPow):
	Object(pos, scl, rot),
	moveDir_(moveDir),
	fallingPow_(fallingPow)
{
}


TitleBoundObject::~TitleBoundObject()
{
}

void TitleBoundObject::Init(void)
{
	//srand(static_cast<unsigned int>(time(nullptr)));

	//�����_���l
	auto gen = Application::GetInstance().CreateRandomObject();
	std::uniform_real_distribution<float>dis(-1.0, 1.0);
	//�����_����]����
	rotateDir_ = VNorm(VECTOR({ dis(gen),dis(gen),dis(gen) }));
	//��]�X�s�[�h�̃����_���l
	float randomValue = dis(gen);
	rotateSpeed_ = randomValue / 10;

	auto& res = ResourceManager::GetInstance();
	//�����_���Ƀ��f����I������
	int modelNum = rand() % 4; 

	ResourceManager::SRC model;
	model = ResourceManager::SRC::CHARACTER_DOG_MODEL;

	if (modelNum == 0)
	{
		model = ResourceManager::SRC::CHARACTER_DOG_MODEL;
	}
	else if (modelNum == 1)
	{
		model = ResourceManager::SRC::CHARACTER_FISH_MODEL;
	}
	else if (modelNum == 2)
	{
		model = ResourceManager::SRC::CHARACTER_CHICKEN_MODEL;
	}
	else
	{
		model = ResourceManager::SRC::CHARACTER_DOG_MODEL;
	}


	//���f���̓o�^
	transform_.SetModel(res.LoadModelDuplicate(model));

	//�傫��
	const float baseSize = 80;
	float scale = 20.0f / baseSize;
	transform_.scl_ = { scale,scale,scale };

	//3D��{���̍X�V
	transform_.Update();

	//�ړ��X�s�[�h
	speed_ = 2;

}

void TitleBoundObject::Release(void)
{
}

void TitleBoundObject::Update(float deltaSeconds)
{
	//��������
	FallProcess();
	//��]����
	RotateProcess();
	//�W�����v����
	JumpProcess();

	//���]�e�X�g
	bool rightWallHit = false, leftWallHit = false;
	Vector2 screenSize = Application::GetInstance().GetScreenSize();
	rightWallHit = transform_.pos_.x >= 300.0f && moveDir_.x > 0.0f;
	leftWallHit = transform_.pos_.x <= -300.0f && moveDir_.x < 0.0f;
	if (rightWallHit || leftWallHit)
	{
		//�ړ������A���]
		ReverseMoveDirX();
	}

	//3D��{���̍X�V
	transform_.Update();

}

void TitleBoundObject::Draw(void)
{
	//�L�����N�^�[���f��
	MV1DrawModel(transform_.modelId_);
}

void TitleBoundObject::GravityProcess(void)
{
	// �d�͕���
	const VECTOR dirGravity = { 0.0f,-1.0f,0.0f };

	// �����ʂ̉��Z
	fallingPow_ += VScale(dirGravity, 0.05f).y;

	//�ړ�������ύX
	moveDir_.y = fallingPow_;
}

void TitleBoundObject::FallProcess(void)
{
	movePow_ = { 0,0,0 };	//�ړ��ʂ��O�ɂ���

	movePow_ = VScale(moveDir_, speed_);		//�ړ��ʂ̌v�Z
	GravityProcess();							//�d�͂ɂ��ړ��ʂ����Z
	movedPos_ = VAdd(transform_.pos_, movePow_);//�ړ�����W
	transform_.pos_ = movedPos_;				//�ړ�����W�𔽉f
}

void TitleBoundObject::RotateProcess(void)
{
	VECTOR  rotatePos = VScale(rotateDir_, rotateSpeed_);
	transform_.quaRot_ = transform_.quaRot_.Mult(Quaternion::Euler(rotatePos));
}

void TitleBoundObject::JumpProcess()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
	std::uniform_real_distribution<float> disFall(0.0f, 3.0f);

	float randomFloat = dis(gen); // -1.0f����1.0f�͈̗̔͂������擾

	//
	if (transform_.pos_.y >= -250.0f)return;

	//�g�����|�����ƏՓ˂����ꍇ�̏���
	if (fallingPow_ <= 0.0f)
	{
		//�W�����v�����i�^��j
		//-1�`1�̃����_��
		moveDir_ = VECTOR{ dis(gen),1.0f,0.0f};

		//�W�����v�������ɁA�����ʂ��v�Z		
		fallingPow_ = disFall(gen)+2.5f;
	}
}

void TitleBoundObject::ReverseMoveDirX(void)
{
	moveDir_.x *= -1;
}

void TitleBoundObject::InitCollisionAfter(void)
{
}
