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

	//ランダム値
	auto gen = Application::GetInstance().CreateRandomObject();
	std::uniform_real_distribution<float>dis(-1.0, 1.0);
	//ランダム回転方向
	rotateDir_ = VNorm(VECTOR({ dis(gen),dis(gen),dis(gen) }));
	//回転スピードのランダム値
	float randomValue = dis(gen);
	rotateSpeed_ = randomValue / 10;

	auto& res = ResourceManager::GetInstance();
	//ランダムにモデルを選択する
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


	//モデルの登録
	transform_.SetModel(res.LoadModelDuplicate(model));

	//大きさ
	const float baseSize = 80;
	float scale = 20.0f / baseSize;
	transform_.scl_ = { scale,scale,scale };

	//3D基本情報の更新
	transform_.Update();

	//移動スピード
	speed_ = 2;

}

void TitleBoundObject::Release(void)
{
}

void TitleBoundObject::Update(float deltaSeconds)
{
	//落下処理
	FallProcess();
	//回転処理
	RotateProcess();
	//ジャンプ処理
	JumpProcess();

	//反転テスト
	bool rightWallHit = false, leftWallHit = false;
	Vector2 screenSize = Application::GetInstance().GetScreenSize();
	rightWallHit = transform_.pos_.x >= 300.0f && moveDir_.x > 0.0f;
	leftWallHit = transform_.pos_.x <= -300.0f && moveDir_.x < 0.0f;
	if (rightWallHit || leftWallHit)
	{
		//移動方向、反転
		ReverseMoveDirX();
	}

	//3D基本情報の更新
	transform_.Update();

}

void TitleBoundObject::Draw(void)
{
	//キャラクターモデル
	MV1DrawModel(transform_.modelId_);
}

void TitleBoundObject::GravityProcess(void)
{
	// 重力方向
	const VECTOR dirGravity = { 0.0f,-1.0f,0.0f };

	// 落下量の加算
	fallingPow_ += VScale(dirGravity, 0.05f).y;

	//移動方向を変更
	moveDir_.y = fallingPow_;
}

void TitleBoundObject::FallProcess(void)
{
	movePow_ = { 0,0,0 };	//移動量を０にする

	movePow_ = VScale(moveDir_, speed_);		//移動量の計算
	GravityProcess();							//重力により移動量を加算
	movedPos_ = VAdd(transform_.pos_, movePow_);//移動後座標
	transform_.pos_ = movedPos_;				//移動後座標を反映
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

	float randomFloat = dis(gen); // -1.0fから1.0fの範囲の乱数を取得

	//
	if (transform_.pos_.y >= -250.0f)return;

	//トランポリンと衝突した場合の処理
	if (fallingPow_ <= 0.0f)
	{
		//ジャンプ方向（真上）
		//-1～1のランダム
		moveDir_ = VECTOR{ dis(gen),1.0f,0.0f};

		//ジャンプ率を元に、落下量を計算		
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
