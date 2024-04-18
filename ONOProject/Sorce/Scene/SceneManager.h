#pragma once
#include <list>
#include <memory>
#include "../Player/Player.h"

class BaseScene;
class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init(void);
	void Update(float deltaSeconds);
	void Draw(void);

	// シーン変更
	void ChangeScene(std::unique_ptr<BaseScene>&& scene);
	// ポーズシーンなど前のシーンに重ねる
	void PushScene(std::unique_ptr<BaseScene>&& scene);
	// PushScene終了用
	void PopScene(void);

	Camera& GetCamera(void) const;

	Player::PLAYER_TYPE GetWinnerPlayerType(void) const;
	void SetWinnerPlayerType(Player::PLAYER_TYPE winnerPlayerType);

private:
	// 3D用初期化
	void Init3D(void);

	// シーンリスト（ポーズシーンをつけるため）
	std::list<std::unique_ptr<BaseScene>> sceneList_;

	std::unique_ptr<Camera> camera_;

	Player::PLAYER_TYPE winnerPlayerType_;

};

