#include "../Application.h"
#include "../Common/Vector2.h"
#include "SceneUI.h"
#include "GameSceneUI/GameSceneUI.h"
#include "ViewManager.h"

ViewManager* ViewManager::instance_ = nullptr;

void ViewManager::Init(void)
{	
}

void ViewManager::Draw(void)
{
	for (const auto& sceneUI : sceneUIs_)
	{
		sceneUI->Draw();
	}
}

void ViewManager::CreateGameSceneUI(void)
{
	sceneUIs_.emplace_back(std::make_unique<GameSceneUI>());
}

void ViewManager::Destroy(void)
{
	sceneUIs_.clear();
}


//void ViewManager::CreateTitleUI(void)
//{
//	//titleUI_ = std::make_unique<TitleUI>();
//	titleUI_->Init();
//}
//
//void ViewManager::CreatePlayerUIManager(void)
//{
//	playerUIManager_ = std::make_unique<PlayerUIManager>();
//}
//
//void ViewManager::CreateCountDownUI(const std::vector<int>& imageHandles)
//{
//	auto screenSize = Application::GetInstance().GetScreenSize();
//	countDownUI_ = std::make_unique<CountDownUI>(imageHandles,Vector2{ screenSize.x / 2,screenSize.y / 2 });
//	countDownUI_->Init();
//}
//
//void ViewManager::CreateMenuUI(void)
//{
//	//menuUI_ = std::make_unique<MenuUI>();
//	menuUI_->Init();
//}
//
//TitleUI& ViewManager::GetTitleUI(void) const
//{
//	return *titleUI_;
//}
//
//PlayerUIManager& ViewManager::GetPlayerUIManager(void) const
//{
//	return *playerUIManager_;
//}
//
//CountDownUI& ViewManager::GetCountDownUI(void) const
//{
//	return *countDownUI_;
//}
//
//MenuUI& ViewManager::GetMenuUI(void) const
//{
//	return *menuUI_;
//}
//
//void ViewManager::DeleteTitleUI(void)
//{
//	titleUI_->Release();
//}
//
//void ViewManager::ClearCountDownUI(void)
//{
//	countDownUI_.release();
//}
//
//void ViewManager::DeleteMenuUI(void)
//{
//	menuUI_->Release();
//}

ViewManager::ViewManager()
{
}

ViewManager::~ViewManager()
{
}
