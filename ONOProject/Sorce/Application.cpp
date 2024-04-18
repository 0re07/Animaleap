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
	// �X�N���[���ݒ�
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
	
	// �C���v�b�g�֘A������
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	// ���\�[�X�}�l�[�W���[������
	ResourceManager::CreateInstance();

	// �V�[���}�l�[�W���[������
	sceneManager_ = std::make_unique<SceneManager>();
	sceneManager_->Init();

	// �f���^�^�C��������
	deltaTimeManager_ = std::make_unique<DeltaTimeManager>();

	std::random_device randomDevice;
	mt_.seed(randomDevice());

	return true;

}

void Application::Run(void)
{

	// ���C�����[�v
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		// �f���^�^�C���X�V
		deltaTimeManager_->Update();

		// �C���v�b�g�X�V
		InputManager::GetInstance().Update();

		// �V�[��
		sceneManager_->Update(deltaTimeManager_->GetDeltaSconds());
		sceneManager_->Draw();

	}
}

void Application::Destroy(void)
{
	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	sceneManager_.release();

	// Effekseer���I������B
	Effkseer_End();

	// DxLib�I��
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
	// �G�t�F�N�V�A�̏�����
	if (Effekseer_Init(8000) == -1)
	{
		return false;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	return true;
}
