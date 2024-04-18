#pragma once
#include "CollisionShape.h"
class CollisionPolygon :
    public CollisionShape
{
public:
    CollisionPolygon(const VECTOR& pos, int modelID, const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate = true, bool isActive = true);
    ~CollisionPolygon();

    virtual const CollisionAfterData& Dispatch(CollisionShape& other) override;

    //const VECTOR& GetPos(void) const;
    int GetModelID(void) const;

    virtual void UpdateCollisionInfo(const VECTOR& pos) override;

private:
   
    virtual const CollisionAfterData& Collision(const CollisionCircle& circle) override;
    virtual const CollisionAfterData& Collision(const CollisionLine& line) override;
    virtual const CollisionAfterData& Collision(const CollisionPolygon& polygon) override;

    virtual void CollisionDraw(void) override;

    int modelID_;
};

