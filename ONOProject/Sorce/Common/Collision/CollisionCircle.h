#pragma once
#include <DxLib.h>
#include "CollisionShape.h"

class CollisionCircle :
    public CollisionShape
{
public:
    CollisionCircle(const VECTOR& pos, const float& radius ,const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
    ~CollisionCircle();

    virtual const CollisionAfterData& Dispatch(CollisionShape& other) override;

    const float& GetRadius(void) const;

    virtual void UpdateCollisionInfo(const VECTOR& pos) override;

private:

    virtual const CollisionAfterData& Collision(const CollisionCircle& circle) override;
    virtual const CollisionAfterData& Collision(const CollisionLine& line) override;
    virtual const CollisionAfterData& Collision(const CollisionPolygon& polygon) override;

    virtual void CollisionDraw(void) override;

    float radius_;

};

