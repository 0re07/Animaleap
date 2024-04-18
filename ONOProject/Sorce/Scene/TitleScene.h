#pragma once
#include <memory>
#include "BaseScene.h"
#include "../Common/Vector2.h"
class SoundController;
class TitleBoundObject;

class TitleScene :
    public BaseScene
{
public:
	TitleScene(SceneManager& sceneManager);
	virtual ~TitleScene();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

private:

	//�^�C�g���摜
	int titleImg_;

	//�t�H���g�n���h��
	int fontHandle_;

	//�X�^�[�g���W
	Vector2 startPos_;

	//BGM
	std::unique_ptr<SoundController> bgm_;

	//�f���^�^�C��
	float deltaTime_;

	//���˂�I�u�W�F�N�g
	std::vector<std::unique_ptr<TitleBoundObject>> boundObjcts_;
};

