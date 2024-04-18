#include "../Common/Collision/CollisionCircle.h"
#include "../Common/Collision/CollisionLine.h"
#include "../Common/Collision/CollisionPolygon.h"
#include "Object.h"

Object::Object(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot) :
	transform_(pos, scl, rot),
	isAlive_(true),
	isEnable_(true)
{
}

Object::~Object()
{
}

VECTOR Object::GetPos(void) const
{
	return transform_.pos_; 
}

bool Object::IsAlive(void) const
{
	return isAlive_;
}

void Object::SetIsAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

bool Object::IsEnable(void) const
{
	return isEnable_;
}

void Object::SetEnable(bool isEnable)
{
	isEnable_ = isEnable;
}

void Object::CollisionAfter(const CollisionAfterData& aftorColData, Object& hitObject, COLLISION_OBJECT_TYPE collisionObjectType)
{
	// AFTER_COL_TYPEÇ≤Ç∆ÇÃìñÇΩÇËîªíËå„èàóù
	if (collisionCallbacks_.size() > 0)
	{
		collisionCallbacks_[collisionObjectType](aftorColData, hitObject);
	}
	
}

const std::vector<std::shared_ptr<CollisionShape>>& Object::GetCollisions(void) const
{
	return collisions_;
}

void Object::AddCollisions(const VECTOR& startPos, const VECTOR& endPos, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate, bool isActive)
{
	collisions_.emplace_back(std::make_shared<CollisionLine>(startPos, endPos, colObjType, hitObjType, isUpdate, isActive));
}

void Object::AddCollisions(const VECTOR& pos, float radius, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate, bool isActive)
{
	auto it = std::find_if(collisions_.begin(), collisions_.end(),
		[colObjType](const std::shared_ptr<CollisionShape>& collision)
		{
			return collision->GetCollisionObjectType() == colObjType;
		}
	);
	// ÉRÉäÉWÉáÉìÇ™Ç»Ç©Ç¡ÇΩÇÁçÏê¨
	// Ç†Ç¡ÇΩÇÁçÌèúÇµÇƒêVÇµÇ≠çÏê¨
	if (it == collisions_.end())
	{
		collisions_.emplace_back(std::make_shared<CollisionCircle>(pos, radius, colObjType, hitObjType, isUpdate, isActive));
	}
	else
	{
		collisions_.erase(it);
		collisions_.emplace_back(std::make_shared<CollisionCircle>(pos, radius, colObjType, hitObjType, isUpdate, isActive));
	}

	//collisions_.emplace_back(std::make_shared<CollisionCircle>(pos, radius, colObjType, hitObjType, isUpdate, isActive));
}

void Object::AddCollisions(const VECTOR& pos, int modelID, COLLISION_OBJECT_TYPE colObjType, unsigned int hitObjType, bool isUpdate, bool isActive)
{
	collisions_.emplace_back(std::make_shared<CollisionPolygon>(pos, modelID, colObjType, hitObjType, isUpdate, isActive));
}

void Object::SetCollisionActive(COLLISION_OBJECT_TYPE colObjType, bool active)
{
	auto it = std::find_if(collisions_.begin(), collisions_.end(),
		[colObjType](const std::shared_ptr<CollisionShape>& collision)
		{
			return collision->GetCollisionObjectType() == colObjType;
		}
	);

	//assert(it != collisions_.end());
	if (it == collisions_.end())
	{
		return;
	}

	(*it)->DisableCollision();
}
