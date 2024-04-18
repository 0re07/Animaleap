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
	//ランダム値
	auto gen = Application::GetInstance().CreateRandomObject();
	std::uniform_real_distribution<float>dis(-1.0, 1.0);
	//ランダム回転方向
	rotateDir_ = VNorm(VECTOR({ dis(gen),dis(gen),dis(gen) }));
	//回転スピードのランダム値
	float randomValue = dis(gen);
	rotateSpeed_ = randomValue / 10;


	auto& res = ResourceManager::GetInstance();
	//エフェクトのロード
	hitEffect_ = res.Load(ResourceManager::SRC::HIT_EFFECT).handleId_;

	//SE
	boundSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::BOUND_SE).handleId_);
	//ゴール音
	goalSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::GOAL_SE).handleId_);


}

void BoundObject::DeathProcess(void)
{
	//Y座標が一定値以下になった時、死亡状態にする
	if (transform_.pos_.y <= DEATH_HIGHT)
	{
		SetIsAlive(false);
	}
}

void BoundObject::GravityProcess(void)
{
	// 重力方向
	const VECTOR dirGravity = {0.0f,-1.0f,0.0f};

	// 落下量の加算
	fallingPow_ += VScale(dirGravity, GRAVITY_POWER).y;

	//移動方向を変更
	moveDir_.y = fallingPow_;

	//移動量の加算
	//movePow_ = VAdd(fallingPow_, movePow_);

}

void BoundObject::FallProcess(void)
{
	movePow_ = { 0,0,0 };	//移動量を０にする

	movePow_ = VScale(moveDir_, speed_);		//移動量の計算
	GravityProcess();							//重力により移動量を加算
	movedPos_ = VAdd(transform_.pos_, movePow_);//移動後座標
	transform_.pos_ = movedPos_;				//移動後座標を反映
}

void BoundObject::RotateProcess(void)
{
	VECTOR  rotatePos = VScale(rotateDir_, rotateSpeed_);
	transform_.quaRot_=transform_.quaRot_.Mult(Quaternion::Euler(rotatePos));
}

void BoundObject::JumpProcess(const VECTOR& jumpDir, const float& jumpRate)
{
	//トランポリンと衝突した場合の処理
	if (fallingPow_ <= 0.0f)	
	{
		//SE再生
		boundSE_->Play();

		//ジャンプ方向（真上）
		VECTOR dirJump = jumpDir;
		moveDir_ = CalcReflection(moveDir_, dirJump);

		//ジャンプ率を元に、落下量を計算
		const float minJumpPow = JUMP_POW * 0.5;		//最低ジャンプ量
		fallingPow_ = (std::max)(minJumpPow, JUMP_POW * jumpRate);

	}
}

void BoundObject::ReverseMoveDirX(void)
{
	moveDir_.x *= -1;
}

VECTOR BoundObject::CalcReflection(const VECTOR& moveDIr, const VECTOR& trampolineVec)
{
	//内積
	float dot = VDot(moveDIr, trampolineVec);

	//反射ベクトル
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

	//トランポリンの半分の長さ
	float halfTramLength = trampoline.GetLength() / 2;

	//トランポリン中心位置と衝突座標の距離
	float dis = Utility::Distance(hitObject.GetPos(), collisionData.pos);

	//距離割合
	float ratio = std::clamp(dis / halfTramLength, 0.0f,1.0f);

	//ジャンプの高さ倍率（1.0fに近いほど、高くジャンプする）
	float jumpHeightRaito = 1.0f - ratio;

	JumpProcess(collisionData.normal, jumpHeightRaito);

	//衝突位置が中央に近かったら
	//ヒットエフェクトの再生
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

	//ゴールが開いていない場合、処理をしない
	if (!goal.GetIsOpen())return;

	//消滅時の演出を考えるーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	//ゴール音
	if (IsAlive() && IsEnable())
	{
		goalSE_->Play();
	}

	//死亡処理
	SetIsAlive(false);
	SetEnable(false);
}

void BoundObject::GoalAfterWallCollision(const CollisionAfterData& collisionData, Object& hitObject)
{
	//移動方向、反転
	ReverseMoveDirX();

	//壁と何度も衝突判定を起こさないように、移動方向に 押し出し
	// float pushPow=5.0f;
	//transform_.pos_.x += moveDir_.x * pushPow;
}

