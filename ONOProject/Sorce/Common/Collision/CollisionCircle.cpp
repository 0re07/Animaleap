#include "CollisionPolygon.h"
#include "CollisionLine.h"
#include "CollisionCircle.h"

CollisionCircle::CollisionCircle(const VECTOR& pos, const float& radius, const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate, bool isActive) :
	CollisionShape(pos, colObjType, hitObjType, isUpdate, isActive),
	radius_(radius)
{
}

CollisionCircle::~CollisionCircle()
{
}

const CollisionAfterData& CollisionCircle::Dispatch(CollisionShape& other)
{
	return other.Collision(*this);
}

const float& CollisionCircle::GetRadius(void) const
{
	return radius_;
}

void CollisionCircle::UpdateCollisionInfo(const VECTOR& pos)
{
	pos_ = pos;
}

const CollisionAfterData& CollisionCircle::Collision(const CollisionCircle& circle)
{
	collisionAfterData_.hitFlag = false;
	auto test = circle.GetPos();
	// ‰~‚Æ‰~‚Ì“–‚½‚è”»’è
	if (VSquareSize(VSub(pos_, circle.GetPos())) <
		(circle.GetRadius() + radius_) * (circle.GetRadius() + radius_))
	{
		collisionAfterData_.hitFlag = true;

		auto hitPos = VAdd(pos_,VScale(VNorm(VSub(pos_, circle.GetPos())),radius_));
		collisionAfterData_.pos = hitPos;

		return collisionAfterData_;
	}

	return collisionAfterData_;
}

const CollisionAfterData& CollisionCircle::Collision(const CollisionLine& line)
{

	return collisionAfterData_;
}

const CollisionAfterData& CollisionCircle::Collision(const CollisionPolygon& polygon)
{
	collisionAfterData_.hitFlag = false;

	auto hitPolygon = MV1CollCheck_Sphere(polygon.GetModelID(), -1, pos_, radius_);

	if (hitPolygon.HitNum >= 1)
	{
		collisionAfterData_.hitFlag = true;
		collisionAfterData_.normal = hitPolygon.Dim[0].Normal;
		collisionAfterData_.pos = hitPolygon.Dim[0].Position[0];
	}

	return collisionAfterData_;
}

void CollisionCircle::CollisionDraw(void)
{
	DrawSphere3D(pos_, radius_, 10, 0x00ff00, 0x000000, false);
}



