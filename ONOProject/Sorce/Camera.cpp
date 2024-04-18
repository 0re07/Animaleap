#include <EffekseerForDXLib.h>
#include "Camera.h"

Camera::Camera() :
	pos_({ 0.0f,0.0f,0.0f }),
	rot_({ 0.0f,0.0f,0.0f }),
	targetPos_({0.0f,0.0f,0.0f})
{
}

Camera::~Camera()
{
}

void Camera::Init(void)
{	
}

void Camera::Release(void)
{
}

void Camera::Update(void)
{
}

void Camera::Draw(void)
{
}

void Camera::CameraSetUp(void)
{
	// �N���b�v�����̐ݒ�
	SetCameraNearFar(10.0f, 10000.0f);

	// �J�����̐ݒ�
	SetCameraPositionAndAngle(pos_, rot_.x, rot_.y, rot_.z);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

void Camera::SetPos(const VECTOR& pos)
{
	pos_ = pos;
}

void Camera::SetRot(const VECTOR& rot)
{
	rot_ = rot;
}

