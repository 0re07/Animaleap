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

	//// CreateObjectTestの使い方　AddObjectListはobjectListにobjを追加している
	//auto obj = CreateObjectTest<Character>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 1.0f,1.0f,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });
	//obj->Init();
	//AddObjectList(std::move(obj));

	// 背景オブジェクト
	CreateObject<SkyDome>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 12.0f,12.0f,12.0f }, VECTOR{ 0.0f,0.0f,0.0f });
	CreateObject<Background>(VECTOR{ 0.0f,0.0f,0.0f }, VECTOR{ 12.0f,12.0f,12.0f }, VECTOR{ 0.0f,0.0f,0.0f });

	// プレイヤー初期化
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
	//BGM再生
	bgm_->PlayLoop();
	//決着音
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

	// キャラクターが落下したらプレイヤーの残機を減らす
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
						//BGM停止
						bgm_->Stop();
						//決着音
						settlementSE_->Play();

						// ゲームクリア
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
						//BGM停止
						bgm_->Stop();
						//決着音
						settlementSE_->Play();

						// ゲームクリア
						sceneManager_.SetWinnerPlayerType(Player::PLAYER_TYPE::LEFT_PLAYER);
						//sceneManager_.ChangeScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						sceneManager_.PushScene(std::move(std::make_unique<ResultScene>(sceneManager_)));
						return;
					}
				}
			}
		}
	}

	// オブジェクト同士の当たり判定処理
	ObjectCollision();

	// 不要なオブジェクトの削除
	DeleteObject();
}

void GameScene::Draw(void)
{

	stage_->Draw();

	ObjectDraw();
	//ObjectCollisionDraw();

	//DrawString(0, 0, "GameSceneのDraw", 0xffffff);

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
	// オブジェクトの更新
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
	// オブジェクトの描画
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
	// オブジェクトのコリジョンの描画
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
	// ゲームオブジェクト当たり判定処理
	for (const auto& object1 : objectList_)
	{
		for (const auto& object2 : objectList_)
		{
			// 同じオブジェクトは排除
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
	// オブジェクトのコリジョン配列同士をループ
	for (auto& col1 : obj1.GetCollisions())
	{
		for (auto& col2 : obj2.GetCollisions())
		{
			// 当たり判定をするコリジョンタイプを判別
			if (col1->GetHitObjectTypes() & static_cast<unsigned int>(col2->GetCollisionObjectType()) &&
				(col1->IsActive() && col2->IsActive())
				)
			{
				auto collisionData = col1->Dispatch(*col2);
				if (collisionData.hitFlag)
				{
					// 当たり判定後処理
					obj1.CollisionAfter(collisionData, obj2, col2->GetCollisionObjectType());
					obj2.CollisionAfter(collisionData, obj1, col1->GetCollisionObjectType());

				}
			}
		}
	}
}
