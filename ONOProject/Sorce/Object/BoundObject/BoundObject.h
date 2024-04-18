#pragma once
#include "../../Common/Vector2.h"
#include "../../Player/Player.h"
#include "../Object.h"

//バウンドオブジェクトが死亡する高さ
constexpr float DEATH_HIGHT = -300.0f;
//オブジェクトが落下する重力加速度
constexpr float GRAVITY_POWER = 0.05f;
//オブジェクトのジャンプ量
constexpr float JUMP_POW = 5.0f;

class SoundController;

class BoundObject :
    public Object
{
public:

	BoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~BoundObject();

	virtual void Init(void);
	virtual void Release(void) = 0;
	virtual void Update(float deltaSeconds) = 0;
	virtual void Draw(void) = 0;

	//プレイヤータイプ
	const void SetPlayerType(Player::PLAYER_TYPE type) { playerType_ = type; }
	Player::PLAYER_TYPE GetPlayerType(void) const { return playerType_; }

	//死亡処理
	void DeathProcess(void);
	//重力処理
	void GravityProcess(void);
	//落下処理
	void FallProcess(void);
	//回転処理
	void RotateProcess(void);
	//ジャンプ処理
	virtual void JumpProcess(const VECTOR& jumpDir, const float& jumpRate);

	//X座標の移動方向を反転
	void ReverseMoveDirX(void);
	//トランポリンとの反射ベクトルを求める
	VECTOR CalcReflection(const VECTOR& moveDIr,const VECTOR& trampolineVec);

protected:

	virtual void InitCollisionAfter(void) override;

	// 当たり判定後処理
	void JumpAfterTrampolineCollision(const CollisionAfterData& collisionData, Object& hitObject);
	void GoalAfterGoalCollision(const CollisionAfterData& collisionData, Object& hitObject);
	void GoalAfterWallCollision(const CollisionAfterData& collisionData, Object& hitObject);

	float speed_;		//移動速度
	VECTOR moveDir_;    //移動方向
	VECTOR movePow_;    //移動量
	VECTOR movedPos_;   //移動後の座標
	float fallingPow_;	//落下量

	VECTOR rotateDir_;	//回転方向
	float rotateSpeed_;	//回転スピード

	//プレイヤータイプ
	//Player::PLAYER_TYPE playerType_ = Player::PLAYER_TYPE::LEFT_PLAYER;
	Player::PLAYER_TYPE playerType_;

private:
	//生死判定
	bool isAlive_;


	//ヒットエフェクト
	int hitEffect_;

	//跳躍音
	std::unique_ptr< SoundController>boundSE_;
	//ゴールSE
	std::unique_ptr<SoundController> goalSE_;

};

