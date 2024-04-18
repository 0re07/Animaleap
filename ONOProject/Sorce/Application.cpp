#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Common/Vector2.h"
#include "Input/InputManager.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "DeltaTimeManager.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

static constexpr int SCREEN_SIZE_X = 1440;
static constexpr int SCREEN_SIZE_Y = 810;

static constexpr int COLOR_BIT_DEPTH = 32;

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Init(void)
{
	// スクリーン設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT_DEPTH);
	SetMainWindowText(_T("ONOProject"));
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}

	if (!EffekseerInit())
	{
		return false;
	}
	
	// インプット関連初期化
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	// リソースマネージャー初期化
	ResourceManager::CreateInstance();

	// シーンマネージャー初期化
	sceneManager_ = std::make_unique<SceneManager>();
	sceneManager_->Init();

	// デルタタイム初期化
	deltaTimeManager_ = std::make_unique<DeltaTimeManager>();

	std::random_device randomDevice;
	mt_.seed(randomDevice());

	return true;

}

void Application::Run(void)
{

	// メインループ
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		// デルタタイム更新
		deltaTimeManager_->Update();

		// インプット更新
		InputManager::GetInstance().Update();

		// シーン
		sceneManager_->Update(deltaTimeManager_->GetDeltaSconds());
		sceneManager_->Draw();

	}
}

void Application::Destroy(void)
{
	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	sceneManager_.release();

	// Effekseerを終了する。
	Effkseer_End();

	// DxLib終了
	DxLib_End();

	delete instance_;
}

std::mt19937 Application::CreateRandomObject(void)
{
	return std::mt19937(mt_());
}

DeltaTimeManager& Application::GetDeltaTimeManager(void)
{
	return *deltaTimeManager_;
}

const Vector2& Application::GetScreenSize(void) const
{
	return { SCREEN_SIZE_X ,SCREEN_SIZE_Y };
}

bool Application::EffekseerInit(void)
{
	// エフェクシアの初期化
	if (Effekseer_Init(8000) == -1)
	{
		return false;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	return true;
}
