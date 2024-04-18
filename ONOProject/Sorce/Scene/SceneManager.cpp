#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <assert.h>
#include "../Resource/ResourceManager.h"
#include "../Player/Player.h"
#include "../Camera.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "BaseScene.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// カメラ初期化
	camera_ = std::make_unique<Camera>();
	camera_->Init();

	// 最初のシーン生成（TitleScene）
	//ChangeScene(SCENE_TYPE::TITLE);
	//ChangeScene(std::make_unique<TitleScene>(*this));
	sceneList_.emplace_front(std::make_unique<TitleScene>(*this));
	sceneList_.front()->Init();

	Init3D();
}

void SceneManager::Update(float deltaSeconds)
{
	// シーンの更新
	sceneList_.front()->Update(deltaSeconds);

	// カメラ更新
	camera_->Update();

}

void SceneManager::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	camera_->CameraSetUp();

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

	// シーンの描画
	for (auto rIt = sceneList_.rbegin(); rIt != sceneList_.rend(); rIt++)
	{
		(*rIt)->Draw();
	}

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();

	ScreenFlip();
}

void SceneManager::ChangeScene(std::unique_ptr<BaseScene>&& scene)
{
	if (!sceneList_.empty())
	{
		int sceneNum = sceneList_.size() - 1;
		if (sceneNum > 0)
		{
			// すべて消す
			for (int n = 0; n < sceneNum; n++)
			{
				sceneList_.front()->Release();
				sceneList_.pop_front();
			}
		}
		else
		{
			sceneList_.front()->Release();
			
		}

		ResourceManager::GetInstance().Release();

		scene->Init();
		sceneList_.front() = std::move(scene);
	}
}

void SceneManager::PushScene(std::unique_ptr<BaseScene>&& scene)
{
	scene->Init();
	sceneList_.push_front(std::move(scene));
}

void SceneManager::PopScene(void)
{
	if (sceneList_.size() > 1)
	{
		sceneList_.front()->Release();
		sceneList_.pop_front();
	}
}

Camera& SceneManager::GetCamera(void) const
{
	return *camera_;
}

Player::PLAYER_TYPE SceneManager::GetWinnerPlayerType(void) const
{
	return winnerPlayerType_;
}

void SceneManager::SetWinnerPlayerType(Player::PLAYER_TYPE winnerPlayerType)
{
	winnerPlayerType_ = winnerPlayerType;
}

void SceneManager::Init3D(void)
{
	// 背景色設定
	SetBackgroundColor(0, 139, 139);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// ライトの設定
	ChangeLightTypeDir({ 0.0f, -0.7f, 0.8f });


	//// フォグ設定
	//SetFogEnable(true);
	//SetFogColor(5, 5, 5);
	//SetFogStartEnd(10000.0f, 20000.0f);
}
