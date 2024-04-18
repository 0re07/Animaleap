#include "PlayerUI.h"
#include "GameSceneUI.h"

GameSceneUI::GameSceneUI()
{
}

GameSceneUI::~GameSceneUI()
{
}

void GameSceneUI::Init(void)
{
	for (int n = 0; n < 2; n++)
	{
		playerUIs_[n] = std::make_unique<PlayerUI>();
	}
}

void GameSceneUI::Draw(void)
{
	for (const auto& playerUI : playerUIs_)
	{
		playerUI->Draw();
	}
}

void GameSceneUI::CreatePlayerUI(void)
{
	for (int n = 0; n < 2; n++)
	{
		playerUIs_[n] = std::make_unique<PlayerUI>();
	}
}
