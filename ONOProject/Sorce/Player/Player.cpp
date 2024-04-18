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

	//ライフ
	playerLife_ = PLAYER_LIFE;
	//カーソルスピード
	cursolSpeed_ = 20;

	//トランポリン生成ライン
	createLineImg_= LoadGraph("./Data/Image/CreateCloudLine.png");

	const int creviceY = 10;
	const int wallLength = 40;
	const int createablePosMin_Y = 150;
	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//左側プレイヤー
		//カーソル座標
		cursolPos_ = { 300,300 };

		//カーソル画像
		cursolImageHandle_ = LoadGraph("./Data/Image/cursol_player1.png");
		//ライフ画像
		lifeImage_ = LoadGraph("./Data/Image/life_player1.png");

		//トランポリン生成可能な範囲
		createablePosMin_ = { wallLength,creviceY + createablePosMin_Y };
		createablePosMax_ = {
			Application::GetInstance().GetScreenSize().x / 2 - wallLength,
			Application::GetInstance().GetScreenSize().y - creviceY };
	}
	else
	{
		//右側プレイヤー
		//カーソル座標
		cursolPos_ = { 900,300 };

		//カーソル画像
		cursolImageHandle_ = LoadGraph("./Data/Image/cursol_player2.png");
		//ライフ画像
		lifeImage_ = LoadGraph("./Data/Image/life_player2.png");

		//トランポリン生成可能な範囲
		createablePosMin_ = { 
			Application::GetInstance().GetScreenSize().x / 2 + wallLength,
			creviceY + createablePosMin_Y };
		createablePosMax_ = { 
			Application::GetInstance().GetScreenSize().x - wallLength,
			Application::GetInstance().GetScreenSize().y - creviceY };
	}

	//トランポリン生成可能数フォント
	std::string path = "Data/Font/Digital.TTF";
	int fontHandle=AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
	assert(fontHandle >= 1);
	creatableNumFontHandle_ = CreateFontToHandle("DS-Digital", 40, -1);

	//操作方法フォント
	path = "Data/Font/GenEiPOPle-Bk.ttf";
	fontHandle=AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
	assert(fontHandle >= 1);
	operationFontHandle_ = CreateFontToHandle(
		"源暎ぽっぷる Black", 22, -1, DX_FONTTYPE_ANTIALIASING_4X4);

	//落下音
	fallSE_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::FALL_SE).handleId_);

}

void Player::Update(void)
{
	//カーソル操作
	OperationCursol();

	//トランポリンの生成処理
	OperationCreateTrampoline();


#ifdef _DEBUG
	//入力方法の変更
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
	//ライフ画像位置
	Vector2 lifeImgPos = { 0,0 };

#ifdef _DEBUG
	//ワールド座標
	//for (int i = 0; i <= 100; i++)
	//{
		//const float start = -1000.0f;
		//const float end = 1000.0f;
		//const float high = -250.0f;
	//	//X軸（赤）
	//	float zPos = start;
	//	zPos += i * 20.0f;
	//	DrawLine3D({ start,high,zPos }, { end,high,zPos }, 0xff0000);
	//	//Y軸（緑）
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
	//	//Z軸（青）
	//	float xPos = start;
	//	xPos += i * 20.0f;
	//	DrawLine3D({ xPos,high,start }, { xPos,high,end }, 0x0000ff);
	//}

	//トランポリン生成範囲
	auto& app = Application::GetInstance();
	DrawBox(createablePosMin_.x, createablePosMin_.y,
		createablePosMax_.x, createablePosMax_.y, 0xffaa00, false);

	//UI情報座標
	int posX = 0;

	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//入力方法
		//DrawString(20, 180, "入力切替：Zキー", 0xffffff);
		//std::string inputTypeStr = "現在の入力方法：PAD";
		//if(inputType==INPUT_TYPE::MOUSE)inputTypeStr = "現在の入力方法：MOUSE";
		//DrawString(20, 200, inputTypeStr.c_str(), 0xffffff);

		//UI情報座標
		posX = 20;
		lifeImgPos = { app.GetScreenSize().x / 4,20 };

		//操作方法
		int strColor = 0xdddddd;
		//DrawFormatStringToHandle(10, 722, strColor, operationFontHandle_, "[A]：雲の生成");
		//DrawFormatStringToHandle(10, 746, strColor, operationFontHandle_, "[L][R]：スピード変化");
		DrawFormatStringToHandle(40, 770, strColor, operationFontHandle_, "スピード：%d", cursolSpeed_);

	}
	else
	{
		posX = 1150;
		lifeImgPos = { app.GetScreenSize().x / 4 * 3,20 };

		//操作方法
		const int maxX = app.GetScreenSize().x;
		const int strColor = 0xeeeeee;
		auto drawOpeString = [&](std::string operationStr,int posY)
		{
			int len = Utility::GetStringLength(operationStr, operationFontHandle_);
			DrawFormatStringToHandle(maxX - len -40, posY, strColor, operationFontHandle_, 
				operationStr.c_str());
		};

		//drawOpeString("[A]：雲の生成", 722);
		//drawOpeString("[L][R]：スピード変化", 746);
		drawOpeString("スピード：" + std::to_string(cursolSpeed_), 770);
	}

#endif // DEBUG

	//UI
	//トランポリン生成線（ボタン入力中のみ、表示）
	auto& ins = InputManager::GetInstance();
	//パッド番号判断
	InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
		InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
	if (ins.IsClickMouseLeft() ||
		ins.IsPadBtnNew(joypadNo, InputManager::JOYPAD_BTN::DOWN))
	{
		//トランポリンの生成数が上限に達している場合、生成処理を行わない
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


	//トランポリン生成数
	int x = 0, y = 0;
	GetGraphSize(cursolImageHandle_, &x, &y);
	int createNum = TRAMPOLINE_CREATE_MAX_NUM - GetAliveTrampolineNum();
	x = cursolPos_.x + x;		//右にずらす
	y = cursolPos_.y - 16;		//上にずらす
	int color = (createNum >= 1) ? 0xffffff : 0xff0000;		//生成数が０なら、色を赤にする
	DrawFormatStringToHandle(x, y, color, creatableNumFontHandle_, "%d", createNum);


	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//ライフ画像
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

	//カーソルの描画
	DrawGraph(cursolPos_.x, cursolPos_.y, cursolImageHandle_, true);
}

void Player::SetPlayerType(PLAYER_TYPE type)
{
	playerType_ = type;
}

void Player::OperationCursol(void)
{
	auto& ins = InputManager::GetInstance();

	//パッド番号判断
	InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
		InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
	//スティック入力情報
	VECTOR stickVec = ins.GetPadLStickVec(joypadNo);

	//無入力状態では、処理をしない
	if (stickVec.y < 0.0f)return;
	

	//移動速度変化
	if (ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::L_TRIGGER))cursolSpeed_ -= 5;
	if (ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::R_TRIGGER))cursolSpeed_ += 5;
	cursolSpeed_ = std::clamp(cursolSpeed_, 5, 50);


	//カーソル移動
	cursolPos_.x += round(stickVec.x * static_cast<float>(cursolSpeed_));
	cursolPos_.y += round ( - stickVec.z * static_cast<float>(cursolSpeed_));		//Z方向は反転させる

	//移動制限
	cursolPos_.x = std::clamp(cursolPos_.x, createablePosMin_.x, createablePosMax_.x);
	cursolPos_.y = std::clamp(cursolPos_.y, createablePosMin_.y, createablePosMax_.y);
}

void Player::OperationCreateTrampoline(void)
{
	//トランポリンの生成数が上限に達している場合、生成処理を行わない
	if (TRAMPOLINE_CREATE_MAX_NUM <= GetAliveTrampolineNum())return;

	//Z座標//SetCameraNearFar のFarに対しての距離					//※修正
	const float posZ = 0.9809811f;
	//const float posZ = 0.9809f;

	auto& ins = InputManager::GetInstance();

	//トランポリン生成ボタンの
	//ボタン押下時、ボタン解放時、ボタン入力中
	bool btnTrgDown, btnTrgUp, btnNew;
	btnTrgDown = btnTrgUp = btnNew = false;

	//入力方法に応じて、ボタン入力を判断する
	if (inputType == INPUT_TYPE::PAD)
	{
		//トランポリンの生成座標の決定（パッド用）
		//パッド番号判断
		InputManager::JOYPAD_NO joypadNo = ChackLeftPlayer() ?
			InputManager::JOYPAD_NO::PAD1 : InputManager::JOYPAD_NO::PAD2;
		//トランポリンの始点座標の決定
		btnTrgDown = ins.IsPadBtnTrgDown(joypadNo, InputManager::JOYPAD_BTN::DOWN);
		//トランポリンの終点座標の決定
		btnTrgUp = ins.IsPadBtnTrgUp(joypadNo, InputManager::JOYPAD_BTN::DOWN);
		//ボタン入力中、トランポリン生成予想線の座標を指定する
		btnNew = ins.IsPadBtnNew(joypadNo, InputManager::JOYPAD_BTN::DOWN);
	}
	else
	{
		//トランポリンの生成座標の決定（マウス：テスト用）
		//マウス座標の取得
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		//生成可能範囲でなければ、処理をしない
		if (mouseX <= createablePosMin_.x || createablePosMax_.x <= mouseX)return;
		if (mouseY <= createablePosMin_.y || createablePosMax_.y <= mouseY)return;

		//トランポリンの始点座標の決定
		btnTrgDown = ins.IsTrgDownMouseLeft();
		//トランポリンの終点座標の決定
		btnTrgUp = ins.IsTrgUpMouseLeft();
		//ボタン入力中、トランポリン生成予想線の座標を指定する
		btnNew = ins.IsClickMouseLeft();

		//マウス座標をカーソル座標にセット
		cursolPos_ = { mouseX, mouseY };
	}
	

	//ボタン押下時
	if (btnTrgDown)
	{
		testStartPos_ = testEndPos_ = cursolPos_;
		//始点のワールド座標を求める
		createTrampolineStartPos_ =
			ConvScreenPosToWorldPos({ (float)cursolPos_.x ,(float)cursolPos_.y ,posZ });
	}
	//ボタン解放時
	if (btnTrgUp)
	{
		//終点のワールド座標を求める
		createTrampolineEndPos_ =
			ConvScreenPosToWorldPos({ (float)cursolPos_.x ,(float)cursolPos_.y ,posZ });

		//トランポリンの生成
		CreateTrampoline();
	}
	//ボタン入力中
	if (btnNew)
	{
		testEndPos_ = { cursolPos_.x ,cursolPos_.y };
	}

}

void Player::CreateTrampoline(void)
{
	//座標
	VECTOR pos = CalcCenterPos(createTrampolineStartPos_, createTrampolineEndPos_);

	//大きさ
	const float baseSizeX = 100;			
	float length = Utility::Distance(createTrampolineStartPos_, createTrampolineEndPos_);
	//X方向の大きさの決定
	float sizeX = length / baseSizeX;
	//最小値を下回った場合
	if (length / baseSizeX <= TRAMPOLINE_MIN_LENGTH)
	{
		sizeX = TRAMPOLINE_MIN_LENGTH;
		length = TRAMPOLINE_MIN_LENGTH * baseSizeX;
	}
	VECTOR scl = VECTOR{ sizeX,0.001f,0.1f };

	//角度
	Vector2 vec = {
		static_cast<int>(createTrampolineStartPos_.x - createTrampolineEndPos_.x),
		static_cast<int>(createTrampolineStartPos_.y - createTrampolineEndPos_.y)
	};
	float angleRad = atan2(vec.y, vec.x);
	VECTOR rot = VECTOR{ 0.0f,0.0f,angleRad };


	//トランポリンの生成
	gameScene_.CreateObject<Trampoline>(pos, scl, rot,playerType_, length);
}

void Player::DecreaseLife(void)
{
	//落下音
	fallSE_->Play();

	playerLife_--;
}

bool Player::ChackLeftPlayer(void)
{
	bool ret;

	auto& ins = InputManager::GetInstance();
	if (playerType_ == PLAYER_TYPE::LEFT_PLAYER)
	{
		//1Pコントローラー
		ret = true;
	}
	else
	{
		//2Pコントローラー
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
		//トランポリンではなかった場合
		if (typeid(*object) != typeid(Trampoline))continue;

		//トランポリンが生存状態ではない場合
		if (!object->IsAlive())continue;

		//ダウンキャスト
		Trampoline* trampoline = dynamic_cast<Trampoline*>(object.get());
		//自プレイヤーのトランポリンの数
		if (trampoline->GetPlayerType() == playerType_)
		{
			trampolineNum++;
		}
	}

	return trampolineNum;
}
