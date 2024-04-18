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
	// クリップ距離の設定
	SetCameraNearFar(10.0f, 10000.0f);

	// カメラの設定
	SetCameraPositionAndAngle(pos_, rot_.x, rot_.y, rot_.z);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
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

