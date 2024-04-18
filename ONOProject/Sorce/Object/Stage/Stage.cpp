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
	//３つの壁をモデルで作成
	gameScene_.CreateObject<Wall>(VECTOR{ 0.0f,-290.0f,500.0f }, VECTOR{ 0.5f,1.0f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });		//真ん中
	gameScene_.CreateObject<Wall>(VECTOR{ -480.0f,-80.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//左：上
	gameScene_.CreateObject<Wall>(VECTOR{ -480.0f,-307.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//左：下
	gameScene_.CreateObject<Wall>(VECTOR{ 480.0f,-80.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });		//右：上
	gameScene_.CreateObject<Wall>(VECTOR{ 480.0f,-307.0f,500.0f }, VECTOR{ 0.5f,1.2f ,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });	//右：下


	//ゴールを３つ作成
	CreateGoals();

	//キャノンを作成
	CreateCanonObjects();

}

void Stage::Release(void)
{
}

void Stage::Update(float deltaSeconds)
{
	delta_ += deltaSeconds;
	deltaSec_ += deltaSeconds;

	//１０秒ごとにゴールを変更
	ChengeGoalObjects(10.0f);

	//キャラクターと開いているゴールが衝突
	if (goal_[goalOpenNow_]->GetIsGoal()) {

		//ゴール
		goal_[goalOpenNow_]->SetIsGoalFalse();

		for (auto& object : gameScene_.GetObjectList())
		{
			//キャラクターではなかった場合
			if (typeid(*object) != typeid(Character))continue;

			//ダウンキャスト
			Character* character = dynamic_cast<Character*>(object.get());

			//お邪魔を作成※
			obstacleCanon_->Generate(goal_[goalOpenNow_]->GetPlayerType(), character->GetCharaLevel());
			break;
		}
	}

}

void Stage::Draw(void)
{

#ifdef _DEBUG

	//開いているゴール表示
	DrawFormatString(0, 50, 0xffffff, "開いているゴール:%d番目", goalOpenNow_);

	//ゴール変更確認
	DrawString(0, 160, "開いているゴールは黄色表示", 0xffffff);
	for (int i = 0; i < GOAL_NUM; i++) {
		if (!goal_[i]->GetIsOpen()) {
			DrawFormatString(0, 180 + 20 * i, 0x0000ff, "ゴール %d番目", i+1);
		}
		else {
			DrawFormatString(0, 180 + 20 * i, 0xffff00, "ゴール %d番目", i+1);
		}
	}

	//経過秒数表示
	DrawFormatString(0, 260, 0xffffff, "経過秒数:%f", deltaSec_);

#endif //_DEBUG

}

void Stage::CreateGoals(void)
{
	//現在開いているゴール
	goalOpenNow_ = 0;

	auto& screenSize = Application::GetInstance().GetScreenSize();
	//VECTOR goalPos = { screenSize.x / 2,screenSize.y / 2,500.0f };
	VECTOR goalPos = { 0.0f,100.0f,500.0f };

	for (int i = 0; i < GOAL_NUM; i++) {
		goal_[i] = gameScene_.CreateObjectTest<Goal>(
			VECTOR{ goalPos.x,goalPos.y - 90 * i,goalPos.z },
			VECTOR{ 1.0f,0.7f,1.0f }, VECTOR{ 0.0f,0.0f,0.0f });
		goal_[i]->Init();

		//ゴールを１つ開いている設定にする
		goal_[goalOpenNow_]->OpenSign();

		gameScene_.AddObjectList(std::move(goal_[i]));
	}
}

void Stage::ChengeGoalObjects(float changeSec)
{
	if (delta_ >= changeSec) {
		delta_ -= changeSec;

		//開いていたゴールを閉める
		goal_[goalOpenNow_]->CloseSign();

		//開いていたゴールの次を開ける
		goalOpenNow_ += 1;
		if (goalOpenNow_ >= GOAL_NUM) {
			goalOpenNow_ = 0;
		}
		goal_[goalOpenNow_]->OpenSign();
	}
}

void Stage::CreateCanonObjects(void)
{
	//キャラクターキャノンを作成
	gameScene_.CreateObject<CharacterCanon>(gameScene_,
		VECTOR{ -600.0f,170.0f,600.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{ 0.0f,-90.0f,0.0f },
		Player::PLAYER_TYPE::LEFT_PLAYER);
	gameScene_.CreateObject<CharacterCanon>(gameScene_,
		VECTOR{ 600.0f, 170.0f, 600.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{ 0.0f,90.0f,0.0f },
		Player::PLAYER_TYPE::RIGHT_PLAYER);

	//お邪魔キャノンを作成
	obstacleCanon_ = gameScene_.CreateObjectTest<ObstacleCanon>(gameScene_, VECTOR{ 0.0f,180.0f,500.0f }, VECTOR{ 0.8f,0.8f,0.8f }, VECTOR{});
	obstacleCanon_->Init();
	gameScene_.AddObjectList(std::move(obstacleCanon_));
}
