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

	// AFTER_COL_TYPE���Ƃ̓����蔻��㏈�����Ăяo��
	void CollisionAfter(const CollisionAfterData& aftorColData, Object& hitObject, COLLISION_OBJECT_TYPE collisionObjectType);

	const std::vector<std::shared_ptr<CollisionShape>>& GetCollisions(void) const;

	// �e�R���W�����ǉ�
	void AddCollisions(const VECTOR& startPos, const VECTOR& endPos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	void AddCollisions(const VECTOR& pos, float radius, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	void AddCollisions(const VECTOR& pos, int modelID, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);

	// �R���W�������������ėL���E�����ɂ���
	void SetCollisionActive(COLLISION_OBJECT_TYPE colObjType, bool active);

protected:
	// �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
	virtual void InitCollisionAfter(void) = 0;

	Transform transform_;

	// �R���W����
	std::vector<std::shared_ptr<CollisionShape>> collisions_;

	// �Փˌ㏈��������
	std::unordered_map<COLLISION_OBJECT_TYPE, std::function<void(const CollisionAfterData& colData, Object& hitObject)>> collisionCallbacks_;

	bool isAlive_;	// �����t���O
	bool isEnable_;	// �L���t���O
};

