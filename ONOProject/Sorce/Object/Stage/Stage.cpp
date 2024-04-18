#include "../../Application.h"
#include "../../Scene/GameScene.h"
#include "../BoundObject/Character.h"
#include "CharacterCanon.h"
#include "ObstacleCanon.h"
#include "Goal.h"
#include "Wall.h"
#include "Stage.h"

Stage::Stage(GameScene& gameScene) :gameScene_(gameScene)
{
	delta_ = 0.0f;
	deltaSec_ = 0.0f;

	goalOpenNow_ = 0;
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
	//�R�̕ǂ����f���ō쐬
	gameScene_.CreateObject<Wall>(VECTOR{ 0.0f,-290.0f,500.0f }, VECTOR{ 0.5f,1.0f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });		//�^��
	gameScene_.CreateObject<Wall>(VECTOR{ -480.0f,-80.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//���F��
	gameScene_.CreateObject<Wall>(VECTOR{ -480.0f,-307.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//���F��
	gameScene_.CreateObject<Wall>(VECTOR{ 480.0f,-80.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });		//�E�F��
	gameScene_.CreateObject<Wall>(VECTOR{ 480.0f,-307.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//�E�F��


	//�S�[�����R�쐬
	CreateGoals();

	//�L���m�����쐬
	CreateCanonObjects();

}

void Stage::Release(void)
{
}

void Stage::Update(float deltaSeconds)
{
	delta_ += deltaSeconds;
	deltaSec_ += deltaSeconds;

	//�P�O�b���ƂɃS�[����ύX
	ChengeGoalObjects(10.0f);

	//�L�����N�^�[�ƊJ���Ă���S�[�����Փ�
	if (goal_[goalOpenNow_]->GetIsGoal()) {

		//�S�[��
		goal_[goalOpenNow_]->SetIsGoalFalse();

		for (auto& object : gameScene_.GetObjectList())
		{
			//�L�����N�^�[�ł͂Ȃ������ꍇ
			if (typeid(*object) != typeid(Character))continue;

			//�_�E���L���X�g
			Character* character = dynamic_cast<Character*>(object.get());

			//���ז����쐬��
			obstacleCanon_->Generate(goal_[goalOpenNow_]->GetPlayerType(), character->GetCharaLevel());
			break;
		}
	}

}

void Stage::Draw(void)
{

#ifdef _DEBUG

	//�J���Ă���S�[���\��
	DrawFormatString(0, 50, 0xffffff, "�J���Ă���S�[��:%d�Ԗ�", goalOpenNow_);

	//�S�[���ύX�m�F
	DrawString(0, 160, "�J���Ă���S�[���͉��F�\��", 0xffffff);
	for (int i = 0; i < GOAL_NUM; i++) {
		if (!goal_[i]->GetIsOpen()) {
			DrawFormatString(0, 180 + 20 * i, 0x0000ff, "�S�[�� %d�Ԗ�", i+1);
		}
		else {
			DrawFormatString(0, 180 + 20 * i, 0xffff00, "�S�[�� %d�Ԗ�", i+1);
		}
	}

	//�o�ߕb���\��
	DrawFormatString(0, 260, 0xffffff, "�o�ߕb��:%f", deltaSec_);

#endif //_DEBUG

}

void Stage::CreateGoals(void)
{
	//���݊J���Ă���S�[��
	goalOpenNow_ = 0;

	auto& screenSize = Application::GetInstance().GetScreenSize();
	//VECTOR goalPos = { screenSize.x / 2,screenSize.y / 2,500.0f };
	VECTOR goalPos = { 0.0f,100.0f,500.0f };

	for (int i = 0; i < GOAL_NUM; i++) {
		goal_[i] = gameScene_.CreateObjectTest<Goal>(
			VECTOR{ goalPos.x,goalPos.y - 90 * i,goalPos.z },
			VECTOR{ 1.0f,0.7f,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });
		goal_[i]->Init();

		//�S�[�����P�J���Ă���ݒ�ɂ���
		goal_[goalOpenNow_]->OpenSign();

		gameScene_.AddObjectList(std::move(goal_[i]));
	}
}

void Stage::ChengeGoalObjects(float changeSec)
{
	if (delta_ >= changeSec) {
		delta_ -= changeSec;

		//�J���Ă����S�[����߂�
		goal_[goalOpenNow_]->CloseSign();

		//�J���Ă����S�[���̎����J����
		goalOpenNow_ += 1;
		if (goalOpenNow_ >= GOAL_NUM) {
			goalOpenNow_ = 0;
		}
		goal_[goalOpenNow_]->OpenSign();
	}
}

void Stage::CreateCanonObjects(void)
{
	//�L�����N�^�[�L���m�����쐬
	gameScene_.CreateObject<CharacterCanon>(gameScene_,
		VECTOR{ -600.0f,170.0f,600.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{ 0.0f,-90.0f,0.0f },
		Player::PLAYER_TYPE::LEFT_PLAYER);
	gameScene_.CreateObject<CharacterCanon>(gameScene_,
		VECTOR{ 600.0f, 170.0f, 600.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{ 0.0f,90.0f,0.0f },
		Player::PLAYER_TYPE::RIGHT_PLAYER);

	//���ז��L���m�����쐬
	obstacleCanon_ = gameScene_.CreateObjectTest<ObstacleCanon>(gameScene_, VECTOR{ 0.0f,180.0f,500.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{});
	obstacleCanon_->Init();
	gameScene_.AddObjectList(std::move(obstacleCanon_));
}
