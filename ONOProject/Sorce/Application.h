#pragma once
#include <memory>
#include <random>

class SceneManager;
class DeltaTimeManager;
class Vector2;

class Application
{
public:
	static Application& GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Application();
		}
		return *instance_;
	}

	bool Init(void);
	void Run(void);
	void Destroy(void);

	std::mt19937 CreateRandomObject(void);
	DeltaTimeManager& GetDeltaTimeManager(void);
	const Vector2& GetScreenSize(void) const;

private:
	Application();
	~Application();

	Application(Application& other) = delete;
	void operator=(const Application&) = delete;

	bool EffekseerInit(void);

	static Application* instance_;

	std::unique_ptr<SceneManager> sceneManager_;
	std::unique_ptr<DeltaTimeManager> deltaTimeManager_;

	// ランダムオブジェクト（メルセンヌツイスター）
	std::mt19937 mt_;
};

