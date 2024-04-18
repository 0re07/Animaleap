#pragma once
#include <map>
#include <string>
#include <memory>
#include "Resource.h"

class ResourceManager
{

public:

	// ���\�[�X��
	enum class SRC
	{
		//3D���f��
		CHARACTER_DOG_MODEL,				//���F�L�����N�^�[
		CHARACTER_FISH_MODEL,				//���F�L�����N�^�[
		CHARACTER_CHICKEN_MODEL,			//�{�F�L�����N�^�[
		OBSTACLE_MODEL,					//���ז���
		CLOUD_MODEL,					//�_
		TRAMPOLINE_COLLSION_MODEL,		//�g�����|�����̃R���W����
		WALL_MODEL,						//��
		GOAL_MODEL,						//�S�[��
		CHARACTER_CANON_MODEL,			//�L�����N�^�[�C��
		OBSTACLE_CANON_MODEL,			//���ז��C��

		//�G�t�F�N�g
		HIT_EFFECT,						//�g�����|�����Ƃ̃q�b�g�G�t�F�N�g
		GOAL_LEFT_EFFECT,				//�S�[���������̃G�t�F�N�g(��)
		GOAL_RIGHT_EFFECT,				//�S�[���������̃G�t�F�N�g(�E)
		GOAL_OPEN_EFFECT,				//�S�[�����J���Ă���Ƃ��̃G�t�F�N�g

		//SE
		TITLE_BGM,
		GAME_BGM,
		BOUND_SE,
		GOAL_SE,
		SETTLEMENT_SE,
		FALL_SE,
		FIRE_SE,

		WIN_IMAGE_1,
		WIN_IMAGE_2

	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	const Resource& Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	// �������[�h
	Resource& _Load(SRC src);

};
