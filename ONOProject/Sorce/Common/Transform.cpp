#include "Transform.h"

Transform::Transform(void)
{
	modelId_ = -1;

	scl_ = { 0.0f,0.0f,0.0f };
	rot_ = { 1.0f,1.0f,1.0f };
	pos_ = { 0.0f,0.0f,0.0f };

	scaling_ = { 1.0f,1.0f,1.0f };

	matScl_ = MGetIdent();
	matRot_ = MGetIdent();
	matPos_ = MGetIdent();
	quaRot_ = Quaternion();
	quaRotLocal_ = Quaternion();

}

Transform::Transform(int model)
{
	modelId_ = model;

	scl_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };
	pos_ = { 1.0f,1.0f,1.0f };

	scaling_ = { 1.0f,1.0f,1.0f };

	matScl_ = MGetIdent();
	matRot_ = MGetIdent();
	matPos_ = MGetIdent();
	quaRot_ = Quaternion();
	quaRotLocal_ = Quaternion();
}

Transform::Transform(VECTOR pos, VECTOR scl, VECTOR rot)
{
	modelId_ = -1;

	scl_ = scl;
	rot_ = rot;
	pos_ = pos;

	scaling_ = { 1.0f,1.0f,1.0f };

	matScl_ = MGetScale(scl);

	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(rot.x));
	matRot = MMult(matRot, MGetRotY(rot.y));
	matRot = MMult(matRot, MGetRotZ(rot.z));
	matRot_ = matRot;

	matPos_ = MGetTranslate(pos);

	quaRot_ = Quaternion::Euler(rot);

	quaRotLocal_ = Quaternion();
}

Transform::Transform(int model, VECTOR pos, VECTOR scl, VECTOR rot)
{

	modelId_ = model;

	scl_ = scl;
	rot_ = rot;
	pos_ = pos;

	scaling_ = { 1.0f,1.0f,1.0f };

	matScl_ = MGetScale(scl);

	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(rot.x));
	matRot = MMult(matRot, MGetRotY(rot.y));
	matRot = MMult(matRot, MGetRotZ(rot.z));
	matRot_ = matRot;

	matPos_ = MGetTranslate(pos);

	quaRot_ = Quaternion::Euler(rot);

	quaRotLocal_ = Quaternion();
}

Transform::~Transform(void)
{
}

void Transform::Update(void)
{

	// 大きさ
	matScl_ = MGetScale(scl_);

	if (matScl_.m[0][0] != 10.0f || matScl_.m[1][1] != 10.0f || matScl_.m[2][2] != 10.0f)
	{
		int n = 0;
	}

	// 回転
	rot_ = quaRot_.ToEuler();
	matRot_ = quaRot_.ToMatrix();

	// 位置
	matPos_ = MGetTranslate(pos_);

	// 行列の合成
	MATRIX mat = MGetIdent();

	mat = MMult(mat, MMult(matScl_, MGetScale(scaling_)));

	Quaternion q = quaRot_.Mult(quaRotLocal_);
	auto qMat = q.ToMatrix();
	mat = MMult(mat, q.ToMatrix());
	mat = MMult(mat, matPos_);

	// 行列をモデルに判定
	if (modelId_ != -1)
	{
		MV1SetMatrix(modelId_, mat);
	}

}

void Transform::SetModel(int model)
{
	modelId_ = model;
}

VECTOR Transform::GetForward(void)const
{
	return GetDir({ 0.0f, 0.0f, 1.0f });
}

VECTOR Transform::GetBack(void)const
{
	return GetDir({ 0.0f, 0.0f, -1.0f });
}

VECTOR Transform::GetRight(void)const
{
	return GetDir({ 1.0f, 0.0f, 0.0f });
}

VECTOR Transform::GetLeft(void)const
{
	return GetDir({ -1.0f, 0.0f, 0.0f });
}

VECTOR Transform::GetUp(void)const
{
	return GetDir({ 0.0f, 1.0f, 0.0f });
}

VECTOR Transform::GetDown(void)const
{
	return GetDir({ 0.0f, -1.0f, 0.0f });
}

VECTOR Transform::GetDir(VECTOR vec) const
{
	return VNorm(VTransform(vec, quaRot_.ToMatrix()));
}
