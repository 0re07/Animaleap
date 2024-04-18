#include "CollisionCircle.h"
#include "CollisionLine.h"
#include "CollisionPolygon.h"

CollisionPolygon::CollisionPolygon(const VECTOR& pos, int modelID, const COLLISION_OBJECT_TYPE& colObjType, unsigned int hitObjType, bool isUpdate, bool isActive) :
	CollisionShape(pos, colObjType, hitObjType, isUpdate, isActive),
	modelID_(modelID)
{
}

CollisionPolygon::~CollisionPolygon()
{
}

const CollisionAfterData& CollisionPolygon::Dispatch(CollisionShape& other)
{
	return other.Collision(*this);
}

int CollisionPolygon::GetModelID(void) const
{
	return modelID_;
}

void CollisionPolygon::UpdateCollisionInfo(const VECTOR& pos)
{
}

const CollisionAfterData& CollisionPolygon::Collision(const CollisionCircle& circle)
{
	collisionAfterData_.hitFlag = false;

	auto hitPolygon = MV1CollCheck_Sphere(modelID_, -1, circle.GetPos(), circle.GetRadius());

	if (hitPolygon.HitNum >= 1)
	{
		collisionAfterData_.hitFlag = true;
		collisionAfterData_.normal = hitPolygon.Dim[0].Normal;
		collisionAfterData_.pos = hitPolygon.Dim[0].Position[0];
	}

	return collisionAfterData_;
}

const CollisionAfterData& CollisionPolygon::Collision(const CollisionLine& line)
{
	/*auto CheckLine = [](int modelID, const VECTOR& startPos, const VECTOR& endPos) {
		auto hitPolygon = MV1CollCheck_Line(modelID, -1, startPos, endPos);
		if (hitPolygon.HitFlag == 1)
		{
			return true;
		}

		return false;
	};*/

	collisionAfterData_.hitFlag = false;
	
	auto hitPolygon = MV1CollCheck_Line(modelID_, -1, line.GetStartPos(), line.GetEndPos());
	if (hitPolygon.HitFlag)
	{
		collisionAfterData_.hitFlag = true;
		collisionAfterData_.pos = hitPolygon.HitPosition;
		collisionAfterData_.normal = hitPolygon.Normal;

		return collisionAfterData_;
	}

	return collisionAfterData_;
}

const CollisionAfterData& CollisionPolygon::Collision(const CollisionPolygon& polygon)
{
	return collisionAfterData_;
}

void CollisionPolygon::CollisionDraw(void)
{
	// モデル全体の参照用メッシュを構築
	MV1SetupReferenceMesh(modelID_, -1, TRUE);

	// 参照用メッシュ情報の取得
	auto RefPoly = MV1GetReferenceMesh(modelID_, -1, TRUE);

	// ポリゴンの数だけ繰り返し
	for (int i = 0; i < RefPoly.PolygonNum; i++)
	{
		// ポリゴンを形成する三頂点を使用してワイヤーフレームを描画する
		DrawLine3D(
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[0]].Position,
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[1]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[1]].Position,
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[2]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[2]].Position,
			RefPoly.Vertexs[RefPoly.Polygons[i].VIndex[0]].Position,
			GetColor(255, 255, 0));
	}
}


