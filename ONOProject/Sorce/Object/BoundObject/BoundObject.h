#pragma once
#include "../../Common/Vector2.h"
#include "../../Player/Player.h"
#include "../Object.h"

//�o�E���h�I�u�W�F�N�g�����S���鍂��
constexpr float DEATH_HIGHT = -300.0f;
//�I�u�W�F�N�g����������d�͉����x
constexpr float GRAVITY_POWER = 0.05f;
//�I�u�W�F�N�g�̃W�����v��
constexpr float JUMP_POW = 5.0f;

class SoundController;

class BoundObject :
    public Object
{
public:

	BoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~BoundObject();

	virtual void Init(void);
	virtual void Release(void) = 0;
	virtual void Update(float deltaSeconds) = 0;
	virtual void Draw(void) = 0;

	//�v���C���[�^�C�v
	const void SetPlayerType(Player::PLAYER_TYPE type) { playerType_ = type; }
	Player::PLAYER_TYPE GetPlayerType(void) const { return playerType_; }

	//���S����
	void DeathProcess(void);
	//�d�͏���
	void GravityProcess(void);
	//��������
	void FallProcess(void);
	//��]����
	void RotateProcess(void);
	//�W�����v����
	virtual void JumpProcess(const VECTOR& jumpDir, const float& jumpRate);

	//X���W�̈ړ������𔽓]
	void ReverseMoveDirX(void);
	//�g�����|�����Ƃ̔��˃x�N�g�������߂�
	VECTOR CalcReflection(const VECTOR& moveDIr,const VECTOR& trampolineVec);

protected:

	virtual void InitCollisionAfter(void) override;

	// �����蔻��㏈��
	void JumpAfterTrampolineCollision(const CollisionAfterData& collisionData, Object& hitObject);
	void GoalAfterGoalCollision(const CollisionAfterData& collisionData, Object& hitObject);
	void GoalAfterWallCollision(const CollisionAfterData& collisionData, Object& hitObject);

	float speed_;		//�ړ����x
	VECTOR moveDir_;    //�ړ�����
	VECTOR movePow_;    //�ړ���
	VECTOR movedPos_;   //�ړ���̍��W
	float fallingPow_;	//������

	VECTOR rotateDir_;	//��]����
	float rotateSpeed_;	//��]�X�s�[�h

	//�v���C���[�^�C�v
	//Player::PLAYER_TYPE playerType_ = Player::PLAYER_TYPE::LEFT_PLAYER;
	Player::PLAYER_TYPE playerType_;

private:
	//��������
	bool isAlive_;


	//�q�b�g�G�t�F�N�g
	int hitEffect_;

	//����
	std::unique_ptr< SoundController>boundSE_;
	//�S�[��SE
	std::unique_ptr<SoundController> goalSE_;

};

