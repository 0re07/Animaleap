#include "../Application.h"
#include "../Input/InputManager.h"
#include "../Resource/ResourceManager.h"
#include "../Player/Player.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "ResultScene.h"

ResultScene::ResultScene(SceneManager& sceneManager) :
	BaseScene(sceneManager)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init(void)
{
	winImage1_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::WIN_IMAGE_1).handleId_;
	winImage2_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::WIN_IMAGE_2).handleId_;
}

void ResultScene::Release(void)
{
}

void ResultScene::Update(float deltaSeconds)
{
	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_SPACE))
	{
		sceneManager_.ChangeScene(std::move(std::make_unique<TitleScene>(sceneManager_)));
	}
}

void ResultScene::Draw(void)
{
	auto winnerPlayerType = sceneManager_.GetWinnerPlayerType();

	auto screenSize = Application::GetInstance().GetScreenSize();

	Vector2 si = Application::GetInstance().GetScreenSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �����x�𔼕��ɐݒ�i0�����S�����A255�����S�s�����j
	DrawBox(0, 0, screenSize.x, screenSize.y, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �`�惂�[�h��ʏ�ɖ߂�

	if (winnerPlayerType == Player::PLAYER_TYPE::LEFT_PLAYER)
	{
		//DrawFormatString(screenSize.x / 2, screenSize.y / 2, 0xffffff, "1P�̏���");
		DrawGraph(screenSize.x / 2 - 260, screenSize.y / 2, winImage1_, true);
		//DrawGraph(0,0, winImage1_, true);
	}
	else
	{
		//DrawFormatString(screenSize.x / 2, screenSize.y / 2, 0xffffff, "2P�̏���");
		DrawGraph(screenSize.x / 2 - 260, screenSize.y / 2, winImage2_, true);
		//DrawGraph(0,0, winImage2_, true);
	}
}
