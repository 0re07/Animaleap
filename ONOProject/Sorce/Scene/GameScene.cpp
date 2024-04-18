#include <DxLib.h>
#include "../Common/Collision/CollisionShape.h"
#include "../Object/Background/Background.h"
#include "../Object/Background/SkyDome.h"
#include "../Object/BoundObject/Character.h"
#include "../Object/BoundObject/Obstacle.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Trampoline.h"
#include "../Resource/ResourceManager.h"
#include "../Sound/SoundController.h"
#include "../Player/Player.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager& sceneManager) :
	BaseScene(sceneManager)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{

	//// CreateObjectTest�̎g�����@AddObjectList��objectList��obj��ǉ����Ă���
	//auto obj = CreateObjectTest<Character>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 1.0f,1.0f,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });
	//obj->Init();
	//AddObjectList(std::move(obj));

	// �w�i�I�u�W�F�N�g
	CreateObject<SkyDome>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 12.0f,12.0f,12.0f }, VECTOR{ 0.0f,0.0f,0.0f });
	CreateObject<Background>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 12.0f,12.0f,12.0f }, VECTOR{ 0.0f,0.0f,0.0f });

	// �v���C���[������
	leftPlayer_ = std::make_unique<Player>(*this, Player::PLAYER_TYPE::LEFT_PLAYER);
	leftPlayer_->Init();
	rightPlayer_ = std::make_unique<Player>(*this, Player::PLAYER_TYPE::RIGHT_PLAYER);
	rightPlayer_->Init();

	stage_ = std::make_unique<Stage>(*this);
	stage_->Init();

	auto& res = ResourceManager::GetInstance();

	//BGM
	bgm_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::GAME_BGM).handleId_);
	bgm_->SetVolume(200);
	//BGM�Đ�
	bgm_->PlayLoop();
	//������
	settlementSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::SETTLEMENT_SE).handleId_);

}

void GameScene::Release(void)
{
}

void GameScene::Update(float deltaSeconds)
{
	leftPlayer_->Update();
	rightPlayer_->Update();

	stage_->Update(deltaSeconds);

	ObjectUpdate(deltaSeconds);

	// �L�����N�^�[������������v���C���[�̎c�@�����炷
	for (auto& object : objectList_)
	{
		//continue;
		if (typeid(*object) == typeid(Character))
		{
			if (!object->IsAlive() && object->IsEnable())
			{
				object->SetEnable(false);

				Character* character = dynamic_cast<Character*>(object.get());
				if (character->GetPlayerType() == Player::PLAYER_TYPE::LEFT_PLAYER)
				{
					leftPlayer_->DecreaseLife();
					if (leftPlayer_->GetPlayerLife() <= 0)
					{		
						//BGM��~
						bgm_->Stop();
						//������
						settlementSE_->Play();

						// �Q�[���N���A
						sceneManager_.SetWinnerPlayerType(Player::PLAYER_TYPE::RIGHT_PLAYER);
						//sceneManager_.ChangeScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						sceneManager_.PushScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						return;
					}
				}
				else
				{
					rightPlayer_->DecreaseLife();
					if (rightPlayer_->GetPlayerLife() <= 0)
					{
						//BGM��~
						bgm_->Stop();
						//������
						settlementSE_->Play();

						// �Q�[���N���A
						sceneManager_.SetWinnerPlayerType(Player::PLAYER_TYPE::LEFT_PLAYER);
						//sceneManager_.ChangeScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						sceneManager_.PushScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						return;
					}
				}
			}
		}
	}

	// �I�u�W�F�N�g���m�̓����蔻�菈��
	ObjectCollision();

	// �s�v�ȃI�u�W�F�N�g�̍폜
	DeleteObject();
}

void GameScene::Draw(void)
{

	stage_->Draw();

	ObjectDraw();
	//ObjectCollisionDraw();

	//DrawString(0, 0, "GameScene��Draw", 0xffffff);

	leftPlayer_->Draw();
	rightPlayer_->Draw();

}

void GameScene::GameOver(void)
{
}

void GameScene::AddObjectList(Object* object)
{
	objectList_.emplace_back(std::move(object));
}

const std::list<std::unique_ptr<Object>>& GameScene::GetObjectList(void) const
{
	return objectList_;
}

void GameScene::ObjectUpdate(float deltaSeconds)
{
	// �I�u�W�F�N�g�̍X�V
	for (const auto& object : objectList_)
	{
		if (object->IsAlive())
		{
			object->Update(deltaSeconds);
		}
	}
	
}

void GameScene::ObjectDraw(void)
{
	// �I�u�W�F�N�g�̕`��
	for (const auto& object : objectList_)
	{
		if (object->IsAlive())
		{
			object->Draw();
		}
	}
}

void GameScene::ObjectCollisionDraw(void)
{
	// �I�u�W�F�N�g�̃R���W�����̕`��
	for (const auto& object : objectList_)
	{
		for (const auto& col : object->GetCollisions())
		{
			col->Draw();
		}
	}
}

void GameScene::ObjectCollision(void)
{
	// �Q�[���I�u�W�F�N�g�����蔻�菈��
	for (const auto& object1 : objectList_)
	{
		for (const auto& object2 : objectList_)
		{
			// �����I�u�W�F�N�g�͔r��
			if (object1 == object2)
			{
				continue;
			}

			CheckCollision(*object1, *object2);
		}
	}
}

void GameScene::DeleteObject(void)
{
	objectList_.remove_if([](const std::unique_ptr<Object>& object) { return object->IsAlive() == false && object->IsEnable() == false; });
}

void GameScene::CheckCollision(Object& obj1, Object& obj2)
{
	// �I�u�W�F�N�g�̃R���W�����z�񓯎m�����[�v
	for (auto& col1 : obj1.GetCollisions())
	{
		for (auto& col2 : obj2.GetCollisions())
		{
			// �����蔻�������R���W�����^�C�v�𔻕�
			if (col1->GetHitObjectTypes() & static_cast<unsigned int>(col2->GetCollisionObjectType()) &&
				(col1->IsActive() && col2->IsActive())
				)
			{
				auto collisionData = col1->Dispatch(*col2);
				if (collisionData.hitFlag)
				{
					// �����蔻��㏈��
					obj1.CollisionAfter(collisionData, obj2, col2->GetCollisionObjectType());
					obj2.CollisionAfter(collisionData, obj1, col1->GetCollisionObjectType());

				}
			}
		}
	}
}
