#pragma once
#include "BoundObject.h"
class Obstacle :
    public BoundObject
{
public:
	//�����蔻��̔��a
	static constexpr float HIT_SIZE_RADIOUS = 10;

	/// <summary>
	/// ���ז��ʂ̃R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="scl">�傫��</param>
	/// <param name="rot">�p�x</param>
	/// <param name="playerType">�v���C���[�^�C�v</param>
	/// <param name="moveDir">�ړ�����</param>
	/// <param name="fallingPow">������</param>
	Obstacle(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType, const VECTOR& moveDir, const float& fallingPow);
	virtual ~Obstacle();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

	//�W�����v����
	void JumpProcess(const VECTOR& jumpDir, const float& jumpRate)override;


private:

	//virtual void InitCollisionAfter(void) override;


};

