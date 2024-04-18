#pragma once
#include "../Object.h"
class TitleBoundObject :
    public Object
{
public:
	TitleBoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~TitleBoundObject();

	void Init(void)override;
	void Release(void)override;
	void Update(float deltaSeconds)override;
	void Draw(void)override;


	//重力処理
	void GravityProcess(void);
	//落下処理
	void FallProcess(void);
	//回転処理
	void RotateProcess(void);
	//ジャンプ処理
	void JumpProcess();

	//X座標の移動方向を反転
	void ReverseMoveDirX(void);


protected:
	// 当たり判定後処理（関数）をcollisionCallbacks_にセットする
	void InitCollisionAfter(void)override;

	float speed_;		//移動速度
	VECTOR moveDir_;    //移動方向
	VECTOR movePow_;    //移動量
	VECTOR movedPos_;   //移動後の座標
	float fallingPow_;	//落下量

	VECTOR rotateDir_;	//回転方向
	float rotateSpeed_;	//回転スピード

private:


};

