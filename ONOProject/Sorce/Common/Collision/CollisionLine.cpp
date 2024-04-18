#include "CollisionPolygon.h"
#include "CollisionLine.h"

CollisionLine::CollisionLine(const VECTOR& startPos, const VECTOR& endPos, const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate, bool isActive) :
	CollisionShape(VECTOR(), colObjType, hitObjType, isUpdate, isActive),
	startPos_(startPos),
	endPos_(endPos)
{
	// íÜêSç¿ïW
	pos_ = VScale(VAdd(startPos_, endPos_), 0.5f);
}

CollisionLine::~CollisionLine()
{
}

const CollisionAfterData& CollisionLine::Dispatch(CollisionShape& other)
{
	return other.Collision(*this);
}

void CollisionLine::UpdateCollisionInfo(const VECTOR& pos)
{
	pos_ = pos;
}

const VECTOR& CollisionLine::GetStartPos(void) const
{
	return startPos_;
}

const VECTOR& CollisionLine::GetEndPos(void) const
{
	return endPos_;
}

const CollisionAfterData& CollisionLine::Collision(const CollisionCircle& circle)
{
	
	return collisionAfterData_;
}

const CollisionAfterData& CollisionLine::Collision(const CollisionLine& line)
{

	return collisionAfterData_;
}

const CollisionAfterData& CollisionLine::Collision(const CollisionPolygon& polygon)
{
	collisionAfterData_.hitFlag = false;
	auto modelID = polygon.GetModelID();
	auto hitPolygon = MV1CollCheck_Line(modelID, -1, startPos_, endPos_);
	if (hitPolygon.HitFlag == 1)
	{
		collisionAfterData_.hitFlag = true;
		collisionAfterData_.pos = hitPolygon.HitPosition;
		collisionAfterData_.normal = hitPolygon.Normal;

		return collisionAfterData_;
	}

	return collisionAfterData_;
}

void CollisionLine::CollisionDraw(void)
{
	DrawLine3D(startPos_, endPos_, 0x00ff00);
}

float CollisionLine::Cross(const VECTOR& x, const VECTOR& y)
{
	return x.x * y.y - x.y * y.x;
}

