#pragma once
#include "../Player/Player.h"
#include "Object.h"
class Trampoline :
    public Object
{
public:
	//トランポリンが消える時間
	static constexpr float DISAPPEAR_TIME = 3.0f;

	/// <summary>
	/// トランポリンのコンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="scl">大きさ</param>
	/// <param name="rot">角度</param>
	/// <param name="playerType">プレイヤータイプ</param>
	/// <param name="length">長さ</param>
	Trampoline(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot,const Player::PLAYER_TYPE& playerType, const float& length);
	~Trampoline();

	void Init(void);
	void Release(void);
	void Update(float deltaSeconds);
	void Draw(void);

	//プレイヤータイプの取得
	const Player::PLAYER_TYPE& GetPlayerType(void)const { return playerType_; }

	//長さの取得
	const float& GetLength(void)const { return length_; }

	//一定時間経過でトランポリン消滅
	void ExtinctionTrampoline(void);

private:

	virtual void InitCollisionAfter(void) override;

	// 当たり判定後処理
	void HitCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject);

	//生成時間
	float generationTime_;

	//プレイヤータイプ
	Player::PLAYER_TYPE playerType_;

	//雲
	Transform cloudTransform_;

	//長さ
	float length_;

};

