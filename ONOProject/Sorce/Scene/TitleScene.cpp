#include <cassert>
#include "../Application.h"
#include "../Input/InputManager.h"
#include "../Resource/ResourceManager.h"
#include "../Utility/Utility.h"
#include "../Sound/SoundController.h"
#include "../Object/BoundObject/TitleBoundObject.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& sceneManager) :
	BaseScene(sceneManager)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//タイトルロゴ
	titleImg_ = LoadGraph("Data/Image/Title.png");
	startPos_ = Vector2{};

	//操作方法フォント
	std::string path = "Data/Font/GenEiPOPle-Bk.ttf";
	int fontHandle = AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
	assert(fontHandle >= 1);
	fontHandle_ = CreateFontToHandle(
		"源暎ぽっぷる Black", 44, -1, DX_FONTTYPE_ANTIALIASING_4X4);

	//BGM
	bgm_ = std::make_unique<SoundController>(res.Load(ResourceManager::SRC::TITLE_BGM).handleId_);
	bgm_->SetVolume(250);
	//BGM再生
	bgm_->PlayLoop();

	//バウンドオブジェクト
	float fallPow = 1.0f;
	//VECTOR pos = { -300.0f,200.0f,300.0f };
	//VECTOR moveDir = { 1.0f, 1.0f, 0.0f };

	VECTOR scl = VECTOR{};
	VECTOR rot = VECTOR{};

	auto createBoundObj = [&](VECTOR pos, VECTOR moveDir)
	{
		boundObjcts_.push_back(std::make_unique<TitleBoundObject>(pos, scl, rot, moveDir, fallPow));
	};

	createBoundObj({ -300.0f,200.0f,300.0f }, { 1.0f, 1.0f, 0.0f });
	createBoundObj({ 300.0f,200.0f,300.0f }, { 0.8f, 1.0f, 0.0f });
	createBoundObj({ -200.0f,200.0f,300.0f }, { 0.3f, 1.0f, 0.0f });
	createBoundObj({ 200.0f,200.0f,300.0f }, { -0.3f, 1.0f, 0.0f });
	createBoundObj({ 100.0f,200.0f,300.0f }, { -0.6f, 1.0f, 0.0f });
	createBoundObj({ -100.0f,200.0f,300.0f }, { -0.7f, 1.0f, 0.0f });

	for (const auto& obj : boundObjcts_)
	{
		obj->Init();
	}
}

void TitleScene::Release(void)
{
}

void TitleScene::Update(float deltaSeconds)
{
	deltaTime_ += deltaSeconds;

	for (const auto& obj : boundObjcts_)
	{
		obj->Update(deltaSeconds);
	}

	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_SPACE))
	{
		//BGM停止
		bgm_->Stop();

		sceneManager_.ChangeScene(std::move(std::make_unique<GameScene>(sceneManager_)));
	}

}

void TitleScene::Draw(void)
{
	for (const auto& obj : boundObjcts_)
	{
		obj->Draw();
	}


	Vector2 screenSize = Application::GetInstance().GetScreenSize();

	//タイトル画像
	Vector2 titleSize;
	GetGraphSize(titleImg_, &titleSize.x, &titleSize.y);
	Vector2 titlePos;
	titlePos.x = screenSize.x / 2 - titleSize.x / 2;
	titlePos.y = 130;
	DrawGraph(titlePos.x, titlePos.y, titleImg_, true);

	//スタート
	std::string str = "Spaceでスタート！";
	int halfLn = Utility::GetStringLength(str, fontHandle_);
	startPos_ = Vector2{ screenSize.x / 2 - halfLn / 2,700};

	int  s = static_cast<int>(deltaTime_) ;
	if (s % 2 != 0)
	{
		DrawFormatStringToHandle(startPos_.x, startPos_.y, 0xffffff, fontHandle_, str.c_str());
	}

}
