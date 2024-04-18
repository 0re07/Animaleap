#pragma once
#include <DxLib.h>
#include "CollisionShape.h"


class CollisionLine :
    public CollisionShape
{
public:
    CollisionLine(const VECTOR& startPos, const VECTOR& endPos, const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
    ~CollisionLine();

    virtual const CollisionAfterData& Dispatch(CollisionShape& other) override;

    virtual void UpdateCollisionInfo(const VECTOR& pos) override;

    const VECTOR& GetStartPos(void) const;
    const VECTOR& GetEndPos(void) const;

private:

    virtual const CollisionAfterData& Collision(const CollisionCircle& circle) override;
    virtual const CollisionAfterData& Collision(const CollisionLine& line) override;
    virtual const CollisionAfterData& Collision(const CollisionPolygon& polygon) override;

    virtual void CollisionDraw(void) override;

    float Cross(const VECTOR& x, const VECTOR& y);

    VECTOR startPos_;
    VECTOR endPos_;
};

