#include <DxLib.h>
#include <algorithm>
#include <DirectXMath.h>
#include <cassert>
#include "../Application.h"
#include "../Scene/GameScene.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"
#include "../Resource/ResourceManager.h"
#include "../Sound/SoundController.h"

#include "../Object/Trampoline.h"
#include "../Object/BoundObject/Character.h"
#include "../Object/BoundObject/Obstacle.h"

#include "../Graphics/Drawable/2DImage/ImageMaterial.h"
#include "../Graphics/Drawable/2DImage/ImageRenderer.h"

#include "Player.h"


Player::Player(GameScene& gameScene, PLAYER_TYPE playerType) :
	gameScene_(gameScene),
	playerType_(playerType)
{
}

Player::~Player()
{
}

void Player::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	testStartPos_ = {};
	testEndPos_ = {};
	createTrampolineStartPos_ = {};
	createTrampolineEndPos_ = {};

	//���C�t
	playerLife_ = PLAYER_LIFE;
	//�J�[�\���X�s�[�h
	cursolSpeed_ = 20;

	//�g�����|�����������C��
	createLineImg_= LoadGraph("./Data/Image/CreateCloudLine.png");

	const int creviceY = 10;
	const int wallLength = 40;
	const int createablePosMin_Y = 150;
	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//�����v���C���[
		//�J�[�\�����W
		cursolPos_ = { 300,300 };

		//�J�[�\���摜
		cursolImageHandle_ = LoadGraph("./Data/Image/cursol_player1.png");
		//���C�t�摜
		lifeImage_ = LoadGraph("./Data/Image/life_player1.png");

		//�g�����|���������\�Ȕ͈�
		createablePosMin_ = { wallLength,creviceY + createablePosMin_Y };
		createablePosMax_ = {
			Application::GetInstance().GetScreenSize().x / 2 - wallLength,
			Application::GetInstance().GetScreenSize().y - creviceY };
	}
	else
	{
		//�E���v���C���[
		//�J�[�\�����W
		cursolPos_ = { 900,300 };

		//�J�[�\���摜
		cursolImageHandle_ = LoadGraph("./Data/Image/cursol_player2.png");
		//���C�t�摜
		lifeImage_ = LoadGraph("./Data/Image/life_player2.png");

		//�g�����|���������\�Ȕ͈�
		createablePosMin_ = { 
			Application::GetInstance().GetScreenSize().x / 2 + wallLength,
			creviceY + createablePosMin_Y };
		createablePosMax_ = { 
			Application::GetInstance().GetScreenSize().x - wallLength,
			Application::GetInstance().GetScreenSize().y - creviceY };
	}

	//�g�����|���������\���t�H���g
	std::string path = "Data/Font/Digital.TTF";
	int fontHandle=AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
	assert(fontHandle >= 1);
	creatableNumFontHandle_ = CreateFontToHandle("DS-Digital", 40, -1);

	//������@�t�H���g
	path = "Data/Font/GenEiPOPle-Bk.ttf";
	fontHandle=AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
	assert(fontHandle >= 1);
	operationFontHandle_ = CreateFontToHandle(
		"����ۂ��Ղ� Black", 22, -1, DX_FONTTYPE_ANTIALIASING_4X4);

	//������
	fallSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::FALL_SE).handleId_);

}

void Player::Update(void)
{
	//�J�[�\������
	OperationCursol();

	//�g�����|�����̐�������
	OperationCreateTrampoline();


#ifdef _DEBUG
	//���͕��@�̕ύX
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_Z))
	{
		if (inputType == INPUT_TYPE::PAD)
		{
			inputType = INPUT_TYPE::MOUSE;
		}
		else
		{
			inputType = INPUT_TYPE::PAD;
		}
	}
#endif // DEBUG

}

void Player::Draw(void)
{
	//���C�t�摜�ʒu
	Vector2 lifeImgPos = { 0,0 };

#ifdef _DEBUG
	//���[���h���W
	//for (int i = 0; i <= 100; i++)
	//{
		//const float start = -1000.0f;
		//const float end = 1000.0f;
		//const float high = -250.0f;
	//	//X���i�ԁj
	//	float zPos = start;
	//	zPos += i * 20.0f;
	//	DrawLine3D({ start,high,zPos }, { end,high,zPos }, 0xff0000);
	//	//Y���i�΁j
	//	Vector2 screenSize = Application::GetInstance().GetScreenSize();
	//	//DrawLine3D({ 0,start,500.0f }, { 0,end,500.0f }, 0x00ff00);
	//	DrawLine3D(
	//		{ screenSize.x / 2.0f - 220.0f,start,500.0f },
	//		{ screenSize.x / 2.0f - 220.0f,end,500.0f }, 0x00ff00);
	//	DrawLine3D(
	//		{ -(screenSize.x / 2.0f - 220.0f),start,500.0f },
	//		{ -(screenSize.x / 2.0f - 220.0f),end,500.0f }, 0x00ff00);
	//	DrawLine3D(
	//		{ -20.0f,start,500.0f },
	//		{ -20.0f,end,500.0f }, 0x00ff00);
	//	DrawLine3D(
	//		{ 20.0f,start,500.0f },
	//		{ 20.0f,end,500.0f }, 0x00ff00);
	//	//Z���i�j
	//	float xPos = start;
	//	xPos += i * 20.0f;
	//	DrawLine3D({ xPos,high,start }, { xPos,high,end }, 0x0000ff);
	//}

	//�g�����|���������͈�
	auto& app = Application::GetInstance();
	DrawBox(createablePosMin_.x, createablePosMin_.y,
		createablePosMax_.x, createablePosMax_.y, 0xffaa00, false);

	//UI�����W
	int posX = 0;

	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//���͕��@
		//DrawString(20, 180, "���͐ؑցFZ�L�[", 0xffffff);
		//std::string inputTypeStr = "���݂̓��͕��@�FPAD";
		//if(inputType==INPUT_TYPE::MOUSE)inputTypeStr = "���݂̓��͕��@�FMOUSE";
		//DrawString(20, 200, inputTypeStr.c_str(), 0xffffff);

		//UI�����W
		posX = 20;
		lifeImgPos = { app.GetScreenSize().x / 4,20 };

		//������@
		int strColor = 0xdddddd;
		//DrawFormatStringToHandle(10, 722, strColor, operationFontHandle_, "[A]�F�_�̐���");
		//DrawFormatStringToHandle(10, 746, strColor, operationFontHandle_, "[L][R]�F�X�s�[�h�ω�");
		DrawFormatStringToHandle(40, 770, strColor, operationFontHandle_, "�X�s�[�h�F%d", cursolSpeed_);

	}
	else
	{
		posX = 1150;
		lifeImgPos = { app.GetScreenSize().x / 4 * 3,20 };

		//������@
		const int maxX = app.GetScreenSize().x;
		const int strColor = 0xeeeeee;
		auto drawOpeString = [&](std::string operationStr,int posY)
		{
			int len = Utility::GetStringLength(operationStr, operationFontHandle_);
			DrawFormatStringToHandle(maxX - len -40, posY, strColor, operationFontHandle_, 
				operationStr.c_str());
		};

		//drawOpeString("[A]�F�_�̐���", 722);
		//drawOpeString("[L][R]�F�X�s�[�h�ω�", 746);
		drawOpeString("�X�s�[�h�F" + std::to_string(cursolSpeed_), 770);
	}

#endif // DEBUG

	//UI
	//�g�����|�����������i�{�^�����͒��̂݁A�\���j
	auto& ins = InputManager::GetInstance();
	//�p�b�h�ԍ����f
	InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
		InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
	if (ins.IsClickMouseLeft() ||
		ins.IsPadBtnNew(joypadNo, InputManager::JOYPAD_BTN::DOWN))
	{
		//�g�����|�����̐�����������ɒB���Ă���ꍇ�A�����������s��Ȃ�
		if (TRAMPOLINE_CREATE_MAX_NUM > GetAliveTrampolineNum())
		{

			Vector2 disY = { 0,15 };
			Vector2 pos1 = testStartPos_ + disY;
			Vector2 pos2 = testStartPos_ - disY;
			Vector2 pos3 = cursolPos_ - disY;
			Vector2 pos4 = cursolPos_ + disY;


			DrawModiGraph(
				pos1.x, pos1.y,
				pos2.x, pos2.y,
				pos3.x, pos3.y,
				pos4.x, pos4.y,
				createLineImg_,true);

		}
	}


	//�g�����|����������
	int x = 0, y = 0;
	GetGraphSize(cursolImageHandle_, &x, &y);
	int createNum = TRAMPOLINE_CREATE_MAX_NUM - GetAliveTrampolineNum();
	x = cursolPos_.x + x;		//�E�ɂ��炷
	y = cursolPos_.y - 16;		//��ɂ��炷
	int color = (createNum >= 1) ? 0xffffff : 0xff0000;		//���������O�Ȃ�A�F��Ԃɂ���
	DrawFormatStringToHandle(x, y, color, creatableNumFontHandle_, "%d", createNum);


	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//���C�t�摜
	int size = 60;
	lifeImgPos.x -= size ;
	for (int i = 0; i < playerLife_; i++)
	{
		DrawExtendGraph(
			lifeImgPos.x, lifeImgPos.y, 
			lifeImgPos.x + size,lifeImgPos.y + size,
			lifeImage_, true);
		lifeImgPos.x += size;
	} 
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//�J�[�\���̕`��
	DrawGraph(cursolPos_.x, cursolPos_.y, cursolImageHandle_, true);
}

void Player::SetPlayerType(PLAYER_TYPE type)
{
	playerType_ = type;
}

void Player::OperationCursol(void)
{
	auto& ins = InputManager::GetInstance();

	//�p�b�h�ԍ����f
	InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
		InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
	//�X�e�B�b�N���͏��
	VECTOR stickVec = ins.GetPadLStickVec(joypadNo);

	//�����͏�Ԃł́A���������Ȃ�
	if (stickVec.y < 0.0f)return;
	

	//�ړ����x�ω�
	if (ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::L_TRIGGER))cursolSpeed_ -= 5;
	if (ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::R_TRIGGER))cursolSpeed_ += 5;
	cursolSpeed_ = std::clamp(cursolSpeed_, 5, 50);


	//�J�[�\���ړ�
	cursolPos_.x += round(stickVec.x * static_cast<float>(cursolSpeed_));
	cursolPos_.y += round ( - stickVec.z * static_cast<float>(cursolSpeed_));		//Z�����͔��]������

	//�ړ�����
	cursolPos_.x = std::clamp(cursolPos_.x, createablePosMin_.x, createablePosMax_.x);
	cursolPos_.y = std::clamp(cursolPos_.y, createablePosMin_.y, createablePosMax_.y);
}

void Player::OperationCreateTrampoline(void)
{
	//�g�����|�����̐�����������ɒB���Ă���ꍇ�A�����������s��Ȃ�
	if (TRAMPOLINE_CREATE_MAX_NUM <= GetAliveTrampolineNum())return;

	//Z���W//SetCameraNearFar ��Far�ɑ΂��Ă̋���					//���C��
	const float posZ = 0.9809811f;
	//const float posZ = 0.9809f;

	auto& ins = InputManager::GetInstance();

	//�g�����|���������{�^����
	//�{�^���������A�{�^��������A�{�^�����͒�
	bool btnTrgDown, btnTrgUp, btnNew;
	btnTrgDown = btnTrgUp = btnNew = false;

	//���͕��@�ɉ����āA�{�^�����͂𔻒f����
	if (inputType == INPUT_TYPE::PAD)
	{
		//�g�����|�����̐������W�̌���i�p�b�h�p�j
		//�p�b�h�ԍ����f
		InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
			InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
		//�g�����|�����̎n�_���W�̌���
		btnTrgDown = ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::DOWN);
		//�g�����|�����̏I�_���W�̌���
		btnTrgUp = ins.IsPadBtnTrgUp(joypadNo, InputManager::JOYPAD_BTN::DOWN);
		//�{�^�����͒��A�g�����|���������\�z���̍��W���w�肷��
		btnNew = ins.IsPadBtnNew(joypadNo, InputManager::JOYPAD_BTN::DOWN);
	}
	else
	{
		//�g�����|�����̐������W�̌���i�}�E�X�F�e�X�g�p�j
		//�}�E�X���W�̎擾
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		//�����\�͈͂łȂ���΁A���������Ȃ�
		if (mouseX <= createablePosMin_.x || createablePosMax_.x <= mouseX)return;
		if (mouseY <= createablePosMin_.y || createablePosMax_.y <= mouseY)return;

		//�g�����|�����̎n�_���W�̌���
		btnTrgDown = ins.IsTrgDownMouseLeft();
		//�g�����|�����̏I�_���W�̌���
		btnTrgUp = ins.IsTrgUpMouseLeft();
		//�{�^�����͒��A�g�����|���������\�z���̍��W���w�肷��
		btnNew = ins.IsClickMouseLeft();

		//�}�E�X���W���J�[�\�����W�ɃZ�b�g
		cursolPos_ = { mouseX, mouseY };
	}
	

	//�{�^��������
	if (btnTrgDown)
	{
		testStartPos_ = testEndPos_ = cursolPos_;
		//�n�_�̃��[���h���W�����߂�
		createTrampolineStartPos_ =
			ConvScreenPosToWorldPos({ (float)cursolPos_.x ,(float)cursolPos_.y ,posZ });
	}
	//�{�^�������
	if (btnTrgUp)
	{
		//�I�_�̃��[���h���W�����߂�
		createTrampolineEndPos_ =
			ConvScreenPosToWorldPos({ (float)cursolPos_.x ,(float)cursolPos_.y ,posZ });

		//�g�����|�����̐���
		CreateTrampoline();
	}
	//�{�^�����͒�
	if (btnNew)
	{
		testEndPos_ = { cursolPos_.x ,cursolPos_.y };
	}

}

void Player::CreateTrampoline(void)
{
	//���W
	VECTOR pos = CalcCenterPos(createTrampolineStartPos_, createTrampolineEndPos_);

	//�傫��
	const float baseSizeX = 100;			
	float length = Utility::Distance(createTrampolineStartPos_, createTrampolineEndPos_);
	//X�����̑傫���̌���
	float sizeX = length / baseSizeX;
	//�ŏ��l����������ꍇ
	if (length / baseSizeX <= TRAMPOLINE_MIN_LENGTH)
	{
		sizeX = TRAMPOLINE_MIN_LENGTH;
		length = TRAMPOLINE_MIN_LENGTH * baseSizeX;
	}
	VECTOR scl = VECTOR{ sizeX,0.001f,0.1f };

	//�p�x
	Vector2 vec = {
		static_cast<int>(createTrampolineStartPos_.x - createTrampolineEndPos_.x),
		static_cast<int>(createTrampolineStartPos_.y - createTrampolineEndPos_.y)
	};
	float angleRad = atan2(vec.y, vec.x);
	VECTOR rot = VECTOR{ 0.0f,0.0f,angleRad };


	//�g�����|�����̐���
	gameScene_.CreateObject<Trampoline>(pos, scl, rot,playerType_, length);
}

void Player::DecreaseLife(void)
{
	//������
	fallSE_->Play();

	playerLife_--;
}

bool Player::ChackLeftPlayer(void)
{
	bool ret;

	auto& ins = InputManager::GetInstance();
	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//1P�R���g���[���[
		ret = true;
	}
	else
	{
		//2P�R���g���[���[
		ret = false;
	}

	return ret;
}

VECTOR Player::CalcCenterPos(VECTOR start, VECTOR end)
{
	VECTOR centerPos = {
		(start.x + end.x) / 2,
		(start.y + end.y) / 2,
		(start.z + end.z) / 2,
	};

	return centerPos;
}

const int& Player::GetAliveTrampolineNum(void) const
{
	int trampolineNum = 0;
	for (auto& object : gameScene_.GetObjectList())
	{
		//�g�����|�����ł͂Ȃ������ꍇ
		if (typeid(*object) != typeid(Trampoline))continue;

		//�g�����|������������Ԃł͂Ȃ��ꍇ
		if (!object->IsAlive())continue;

		//�_�E���L���X�g
		Trampoline* trampoline = dynamic_cast<Trampoline*>(object.get());
		//���v���C���[�̃g�����|�����̐�
		if (trampoline->GetPlayerType() == playerType_)
		{
			trampolineNum++;
		}
	}

	return trampolineNum;
}
