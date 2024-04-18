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
	// �J����������
	camera_ = std::make_unique<Camera>();
	camera_->Init();

	// �ŏ��̃V�[�������iTitleScene�j
	//ChangeScene(SCENE_TYPE::TITLE);
	//ChangeScene(std::make_unique<TitleScene>(*this));
	sceneList_.emplace_front(std::make_unique<TitleScene>(*this));
	sceneList_.front()->Init();

	Init3D();
}

void SceneManager::Update(float deltaSeconds)
{
	// �V�[���̍X�V
	sceneList_.front()->Update(deltaSeconds);

	// �J�����X�V
	camera_->Update();

}

void SceneManager::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	camera_->CameraSetUp();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	// �V�[���̕`��
	for (auto rIt = sceneList_.rbegin(); rIt != sceneList_.rend(); rIt++)
	{
		(*rIt)->Draw();
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
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
			// ���ׂď���
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
	// �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);

	// ���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.0f, -0.7f, 0.8f });


	//// �t�H�O�ݒ�
	//SetFogEnable(true);
	//SetFogColor(5, 5, 5);
	//SetFogStartEnd(10000.0f, 20000.0f);
}
