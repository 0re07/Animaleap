#include <DxLib.h>
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	using RES = Resource;
	using RES_T = RES::TYPE;
	/*static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;*/

	
	static std::string PATH_IMAGE = "Data/Image/";
	static std::string PATH_MODEL = "Data/Model/";
	static std::string PATH_EFFECT = "Data/Effect/";
	static std::string PATH_SOUND = "Data/Sound/";

	std::unique_ptr<Resource> res;

	//3D���f��
	//�L�����N�^�[�i���j
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "BoundObject/Character/Dog.mv1");
	resourcesMap_.emplace(SRC::CHARACTER_DOG_MODEL, std::move(res));
	//�L�����N�^�[�i���j
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "BoundObject/Character/Fish.mv1");
	resourcesMap_.emplace(SRC::CHARACTER_FISH_MODEL, std::move(res));
	//�L�����N�^�[�i�{�j
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "BoundObject/Character/Chicken.mv1");
	resourcesMap_.emplace(SRC::CHARACTER_CHICKEN_MODEL, std::move(res));
	//���ז���
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "BoundObject/Obstacle/Obstacle.mv1");
	resourcesMap_.emplace(SRC::OBSTACLE_MODEL, std::move(res));
	//�_
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "Trampoline/cloud.mv1");
	resourcesMap_.emplace(SRC::CLOUD_MODEL, std::move(res));
	//�g�����|�����R���W����
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "Trampoline/TrampolineCollision.mv1");
	resourcesMap_.emplace(SRC::TRAMPOLINE_COLLSION_MODEL, std::move(res));
	//��
	res = std::make_unique<RES>(RES_T::MODEL , PATH_MODEL + "Stage/Wall/wall_2.mv1");
	resourcesMap_.emplace(SRC::WALL_MODEL, std::move(res));
	//�S�[��
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MODEL + "Stage/Goal/goal.mv1");
	resourcesMap_.emplace(SRC::GOAL_MODEL, std::move(res));
	//�L�����N�^�[�C��
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MODEL + "Stage/CharacterCanon/canon.mv1");
	resourcesMap_.emplace(SRC::CHARACTER_CANON_MODEL, std::move(res));
	//���ז��C��
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MODEL + "Stage/ObstacleCanon/canon.mv1");
	resourcesMap_.emplace(SRC::OBSTACLE_CANON_MODEL, std::move(res));

	//�G�t�F�N�g�f�[�^
	//�q�b�g�G�t�F�N�g
	res = std::make_unique<RES>(RES_T::EFFEKSEER, PATH_EFFECT + "Trampoline/HitEffect.efkefc");
	resourcesMap_.emplace(SRC::HIT_EFFECT, std::move(res));
	//�����v���C���[�S�[���G�t�F�N�g
	res = std::make_unique<RES>(RES_T::EFFEKSEER, PATH_EFFECT + "Goal/GoalLeftEffect.efkefc");
	resourcesMap_.emplace(SRC::GOAL_LEFT_EFFECT, std::move(res));
	//�E���v���C���[�S�[���G�t�F�N�g
	res = std::make_unique<RES>(RES_T::EFFEKSEER, PATH_EFFECT + "Goal/GoalRightEffect.efkefc");
	resourcesMap_.emplace(SRC::GOAL_RIGHT_EFFECT, std::move(res));
	//�E���v���C���[�S�[���G�t�F�N�g
	res = std::make_unique<RES>(RES_T::EFFEKSEER, PATH_EFFECT + "Goal/GoalEffect.efkefc");
	resourcesMap_.emplace(SRC::GOAL_OPEN_EFFECT, std::move(res));

	//SE
	//�^�C�g��BGM
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "Title_BGM.mp3");
	resourcesMap_.emplace(SRC::TITLE_BGM, std::move(res));
	//�Q�[��BGM
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "Game_BGM.mp3");
	resourcesMap_.emplace(SRC::GAME_BGM, std::move(res));
	//�o�E���gSE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "SE/BounsShoutSE.mp3");
	resourcesMap_.emplace(SRC::BOUND_SE, std::move(res));
	//�S�[��SE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "SE/GoalSE.mp3");
	resourcesMap_.emplace(SRC::GOAL_SE, std::move(res));
	//����SE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "SE/Settlement.mp3");
	resourcesMap_.emplace(SRC::SETTLEMENT_SE, std::move(res));
	//����SE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "SE/FallSE.mp3");
	resourcesMap_.emplace(SRC::FALL_SE, std::move(res));
	//���CSE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SOUND + "SE/FireSE.mp3");
	resourcesMap_.emplace(SRC::FIRE_SE, std::move(res));

	res = std::make_unique<RES>(RES_T::IMG, PATH_IMAGE + "ResultImage_1.png");
	resourcesMap_.emplace(SRC::WIN_IMAGE_1, std::move(res));
	res = std::make_unique<RES>(RES_T::IMG, PATH_IMAGE + "ResultImage_2.png");
	resourcesMap_.emplace(SRC::WIN_IMAGE_2, std::move(res));
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		/*delete res.second;*/
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ���[�h�ς݃`�F�b�N
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// ���\�[�X�o�^�`�F�b�N
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// �o�^����Ă��Ȃ�
		return dummy_;
	}

	// ���[�h����
	rPair->second->Load();

	// �O�̂��߃R�s�[�R���X�g���N�^
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
