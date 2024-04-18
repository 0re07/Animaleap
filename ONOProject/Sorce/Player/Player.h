#pragma once
#include <DxLib.h>
#include <memory>
#include "../Common/Vector2.h"
class GameScene;

class SoundController;

//�v���C���[���C�t
constexpr int PLAYER_LIFE = 3;
//�g�����|�����̍Œ���̒���
constexpr float TRAMPOLINE_MIN_LENGTH = 0.5f;
//�g�����|�����̐������
constexpr int TRAMPOLINE_CREATE_MAX_NUM = 3;

class Player
{
public:

	//�v���C���[�^�C�v
	enum class PLAYER_TYPE
	{
		LEFT_PLAYER,
		RIGHT_PLAYER,
	};

	Player(GameScene& gameScene, PLAYER_TYPE playerType);
	~Player();

	void Init(void);
	void Update(void);
	void Draw(void);

	//�c�@�̎擾
	const int& GetPlayerLife(void)const { return playerLife_; }

	//�v���C���[�^�C�v�̃Z�b�g
	//�������t���R���X�g���N�^�ł���ėǂ�
	void SetPlayerType(PLAYER_TYPE type);

	//�J�[�\������
	void OperationCursol(void);

	//�g�����|�����̐�������
	void OperationCreateTrampoline(void);

	//�g�����|�����I�u�W�F�N�g�̐���
	void CreateTrampoline(void);

	//�c�@��������
	void DecreaseLife(void);

	//1P�����f�i���v���C���[�j
	bool ChackLeftPlayer(void);

private:

	//���͕��@
	enum class INPUT_TYPE
	{
		PAD,
		MOUSE
	};

	//���͕��@
	INPUT_TYPE inputType = INPUT_TYPE::PAD;

	GameScene& gameScene_;

	//�m�F�p
	//�g�����|�����������W�G�n�_
	Vector2 testStartPos_;
	//�g�����|�����������W�G�I�_
	Vector2 testEndPos_;

	//�g�����|�����������W�G�n�_
	VECTOR createTrampolineStartPos_;
	//�g�����|�����������W�G�I�_
	VECTOR createTrampolineEndPos_;

	//�g�����|�����𐶐��ł���͈�
	Vector2 createablePosMin_;
	Vector2 createablePosMax_;
	
	//�g�����|�����������C��
	int createLineImg_;

	//std::unique_ptr<ImageMaterial> createLineMaterial_;
	//std::unique_ptr<ImageRenderer> createLineRenderer_;


	//�J�[�\���摜
	int cursolImageHandle_;
	//�g�����|���������\���t�H���g
	int creatableNumFontHandle_;
	//���C�t�摜
	int lifeImage_;
	//��������t�H���g
	int operationFontHandle_;

	//�J�[�\���ʒu
	Vector2 cursolPos_;

	//�J�[�\���X�s�[�h
	int cursolSpeed_;

	//�N���b�N�J�E���g
	int clickCount_ = 0;

	//�v���C���[���C�t
	int playerLife_;

	//�v���C���[�^�C�v
	PLAYER_TYPE playerType_;

	//XY���W�̒��Ԃ����߂�
	VECTOR CalcCenterPos(VECTOR start, VECTOR end);

	//���v���C���[�̐������Ă���g�����|�����̐����擾
	const int& GetAliveTrampolineNum(void)const;


	//������
	std::unique_ptr<SoundController> fallSE_;

};

