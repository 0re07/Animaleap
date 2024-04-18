#include "CollisionShape.h"

CollisionShape::CollisionShape(const VECTOR& pos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate, bool isActive) :
    pos_(pos),
    collisionObjectType_(colObjType),
    hitObjectTypes_(hitObjType),
    isUpdate_(isUpdate),
    isActive_(isActive)
{
    collisionAfterData_ = {};
}

CollisionShape::~CollisionShape()
{
}

void CollisionShape::Draw(void)
{
    if (!isActive_)
    {
        return;
    }

    CollisionDraw();
}

const VECTOR& CollisionShape::GetPos(void) const
{
    return pos_;
}

bool CollisionShape::IsUpdate(void) const
{
    return isUpdate_;
}

void CollisionShape::DisableCollision(void)
{
    //hitObjectTypes_ = 0;
    isActive_ = false;
    collisionAfterData_ = {};
}

COLLISION_OBJECT_TYPE CollisionShape::GetCollisionObjectType(void) const
{
    return collisionObjectType_;
}

unsigned int CollisionShape::GetHitObjectTypes(void) const
{
    return hitObjectTypes_;
}

bool CollisionShape::IsActive(void) const
{
    return isActive_;
}

void CollisionShape::Activate(void) 
{
    isActive_ = true;
}
