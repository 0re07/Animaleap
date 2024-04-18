#pragma once
#include <memory>
#include <list>

class SceneUI;

enum class UI_TYPE
{
	TITLE,
	MENU,
	GAME
};

class ViewManager
{
public:
	
	static ViewManager& GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new ViewManager();
		}
		return *instance_;
	}

	void Init(void);
	void Draw(void);

	// UI�쐬
	void CreateGameSceneUI(void);

	// �����SceneUI�̎擾
	template<typename T>
	SceneUI& GetSceneUI(void) const
	{
		for (const auto& sceneUI : sceneUIs_)
		{
			if (typeid(*sceneUI) == typeid(T))
			{
				return *sceneUI;
			}
		}
		return NULL;
	}

	// �����SceneUI�̍폜
	template<typename T>
	void DeleteSceneUI(void) const
	{
		sceneUIs_.remove_if([](const std::unique_ptr<SceneUI>& sceneUI) { return typeid(*sceneUI) == typeid(T); });
	}

	void Destroy(void);

	/*void CreateTitleUI(void);
	void CreatePlayerUIManager(void);
	void CreateCountDownUI(const std::vector<int>& imageHandles);
	void CreateMenuUI(void);

	TitleUI& GetTitleUI(void) const;
	PlayerUIManager& GetPlayerUIManager(void) const;
	CountDownUI& GetCountDownUI(void) const;
	MenuUI& GetMenuUI(void) const;

	void DeleteTitleUI(void);
	void ClearCountDownUI(void);
	void DeleteMenuUI(void);*/



private:
	ViewManager();
	~ViewManager();

	ViewManager(ViewManager& other) = delete;
	ViewManager(const ViewManager&) = delete;
	void operator=(const ViewManager&) = delete;

	static ViewManager* instance_;

	// �eUI�I�u�W�F�N�g
	std::list<std::unique_ptr<SceneUI>> sceneUIs_;

};

