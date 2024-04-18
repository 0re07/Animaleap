#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include <DxLib.h>

#include "../Common/Transform.h"

class CollisionShape;
struct CollisionAfterData;
enum class COLLISION_OBJECT_TYPE;

class Object
{
public:
	Object(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot);
	virtual ~Object();

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(float deltaSeconds) = 0;
	virtual void Draw(void) = 0;

	VECTOR GetPos(void)const;

	bool IsAlive(void) const;
	void SetIsAlive(bool isAlive);

	bool IsEnable(void) const;
	void SetEnable(bool isEnable);

	// AFTER_COL_TYPEごとの当たり判定後処理を呼び出す
	void CollisionAfter(const CollisionAfterData& aftorColData, Object& hitObject, COLLISION_OBJECT_TYPE collisionObjectType);

	const std::vector<std::shared_ptr<CollisionShape>>& GetCollisions(void) const;

	// 各コリジョン追加
	void AddCollisions(const VECTOR& startPos, const VECTOR& endPos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	void AddCollisions(const VECTOR& pos, float radius, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	void AddCollisions(const VECTOR& pos, int modelID, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);

	// コリジョンを検索して有効・無効にする
	void SetCollisionActive(COLLISION_OBJECT_TYPE colObjType, bool active);

protected:
	// 当たり判定後処理（関数）をcollisionCallbacks_にセットする
	virtual void InitCollisionAfter(void) = 0;

	Transform transform_;

	// コリジョン
	std::vector<std::shared_ptr<CollisionShape>> collisions_;

	// 衝突後処理を入れる
	std::unordered_map<COLLISION_OBJECT_TYPE, std::function<void(const CollisionAfterData& colData, Object& hitObject)>> collisionCallbacks_;

	bool isAlive_;	// 生存フラグ
	bool isEnable_;	// 有効フラグ
};

