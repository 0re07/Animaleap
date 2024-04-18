#pragma once
#include <array>
#include <memory>
#include "../SceneUI.h"

class PlayerUI;

class GameSceneUI :
	public SceneUI
{
public:
	GameSceneUI();
	~GameSceneUI();

	void Init(void) override;
	void Draw(void) override;

	void CreatePlayerUI(void);

private:
	std::array<std::unique_ptr<PlayerUI>, 2> playerUIs_;
};

