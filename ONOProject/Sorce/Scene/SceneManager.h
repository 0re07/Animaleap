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

	// �V�[���ύX
	void ChangeScene(std::unique_ptr<BaseScene>&& scene);
	// �|�[�Y�V�[���ȂǑO�̃V�[���ɏd�˂�
	void PushScene(std::unique_ptr<BaseScene>&& scene);
	// PushScene�I���p
	void PopScene(void);

	Camera& GetCamera(void) const;

	Player::PLAYER_TYPE GetWinnerPlayerType(void) const;
	void SetWinnerPlayerType(Player::PLAYER_TYPE winnerPlayerType);

private:
	// 3D�p������
	void Init3D(void);

	// �V�[�����X�g�i�|�[�Y�V�[�������邽�߁j
	std::list<std::unique_ptr<BaseScene>> sceneList_;

	std::unique_ptr<Camera> camera_;

	Player::PLAYER_TYPE winnerPlayerType_;

};

