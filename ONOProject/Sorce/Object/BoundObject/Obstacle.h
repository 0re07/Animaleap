#pragma once
#include "BoundObject.h"
class Obstacle :
    public BoundObject
{
public:
	//当たり判定の半径
	static constexpr float HIT_SIZE_RADIOUS = 10;

	/// <summary>
	/// お邪魔玉のコンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="scl">大きさ</param>
	/// <param name="rot">角度</param>
	/// <param name="playerType">プレイヤータイプ</param>
	/// <param name="moveDir">移動方向</param>
	/// <param name="fallingPow">落下量</param>
	Obstacle(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType, const VECTOR& moveDir, const float& fallingPow);
	virtual ~Obstacle();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

	//ジャンプ処理
	void JumpProcess(const VECTOR& jumpDir, const float& jumpRate)override;


private:

	//virtual void InitCollisionAfter(void) override;


};

