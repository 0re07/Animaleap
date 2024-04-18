#pragma once
#include <DxLib.h>
#include <utility>

enum class COLLISION_OBJECT_TYPE
{
	CHARACTER = 1,
	TRAMPOLINE = 2,
	GOAL = 4,
	WALL = 8
};

struct CollisionAfterData
{
	VECTOR pos;		// 当たった場所
	VECTOR normal;		// 法線ベクトル
	bool hitFlag = false;	// 当たったフラグ
};

class CollisionCircle;
class CollisionLine;
class CollisionPolygon;

class CollisionShape
{
public:
	CollisionShape(const VECTOR& pos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	virtual ~CollisionShape();

	// ダブルディスパッチに使う
	virtual const CollisionAfterData& Dispatch(CollisionShape& other) = 0;

	// それぞれのコリジョンに対する当たり判定処理
	virtual const CollisionAfterData& Collision(const CollisionCircle& circle) = 0;
	virtual const CollisionAfterData& Collision(const CollisionLine& line) = 0;
	virtual const CollisionAfterData& Collision(const CollisionPolygon& polygon) = 0;

	// 更新処理
	virtual void UpdateCollisionInfo(const VECTOR& pos) = 0;

	// 描画（デバッグ用）
	void Draw(void);

	const VECTOR& GetPos(void) const;
	COLLISION_OBJECT_TYPE GetCollisionObjectType(void) const;
	unsigned int GetHitObjectTypes(void) const;

	bool IsUpdate(void) const;
	bool IsActive(void) const;
	void Activate(void);

	// 当たり判定を無効にする
	void DisableCollision(void);

protected:

	// コリジョンの描画（フレーム）
	virtual void CollisionDraw(void) = 0;

	// 当たり判定するかどうか
	bool isActive_;

	// 更新処理をするかどうか
	bool isUpdate_;

	VECTOR pos_;

	CollisionAfterData collisionAfterData_;

	// CollisionObjectTypeと衝突判定するかがまとまってる
	// ビット演算を用いて判定する
	unsigned int hitObjectTypes_;

	COLLISION_OBJECT_TYPE collisionObjectType_;

};


