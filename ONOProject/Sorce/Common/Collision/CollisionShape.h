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
	VECTOR pos;		// ���������ꏊ
	VECTOR normal;		// �@���x�N�g��
	bool hitFlag = false;	// ���������t���O
};

class CollisionCircle;
class CollisionLine;
class CollisionPolygon;

class CollisionShape
{
public:
	CollisionShape(const VECTOR& pos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
	virtual ~CollisionShape();

	// �_�u���f�B�X�p�b�`�Ɏg��
	virtual const CollisionAfterData& Dispatch(CollisionShape& other) = 0;

	// ���ꂼ��̃R���W�����ɑ΂��铖���蔻�菈��
	virtual const CollisionAfterData& Collision(const CollisionCircle& circle) = 0;
	virtual const CollisionAfterData& Collision(const CollisionLine& line) = 0;
	virtual const CollisionAfterData& Collision(const CollisionPolygon& polygon) = 0;

	// �X�V����
	virtual void UpdateCollisionInfo(const VECTOR& pos) = 0;

	// �`��i�f�o�b�O�p�j
	void Draw(void);

	const VECTOR& GetPos(void) const;
	COLLISION_OBJECT_TYPE GetCollisionObjectType(void) const;
	unsigned int GetHitObjectTypes(void) const;

	bool IsUpdate(void) const;
	bool IsActive(void) const;
	void Activate(void);

	// �����蔻��𖳌��ɂ���
	void DisableCollision(void);

protected:

	// �R���W�����̕`��i�t���[���j
	virtual void CollisionDraw(void) = 0;

	// �����蔻�肷�邩�ǂ���
	bool isActive_;

	// �X�V���������邩�ǂ���
	bool isUpdate_;

	VECTOR pos_;

	CollisionAfterData collisionAfterData_;

	// CollisionObjectType�ƏՓ˔��肷�邩���܂Ƃ܂��Ă�
	// �r�b�g���Z��p���Ĕ��肷��
	unsigned int hitObjectTypes_;

	COLLISION_OBJECT_TYPE collisionObjectType_;

};


