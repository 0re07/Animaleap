#pragma once
#include "../Player/Player.h"
#include "Object.h"
class Trampoline :
    public Object
{
public:
	//�g�����|�����������鎞��
	static constexpr float DISAPPEAR_TIME = 3.0f;

	/// <summary>
	/// �g�����|�����̃R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="scl">�傫��</param>
	/// <param name="rot">�p�x</param>
	/// <param name="playerType">�v���C���[�^�C�v</param>
	/// <param name="length">����</param>
	Trampoline(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot,const Player::PLAYER_TYPE& playerType, const float& length);
	~Trampoline();

	void Init(void);
	void Release(void);
	void Update(float deltaSeconds);
	void Draw(void);

	//�v���C���[�^�C�v�̎擾
	const Player::PLAYER_TYPE& GetPlayerType(void)const { return playerType_; }

	//�����̎擾
	const float& GetLength(void)const { return length_; }

	//��莞�Ԍo�߂Ńg�����|��������
	void ExtinctionTrampoline(void);

private:

	virtual void InitCollisionAfter(void) override;

	// �����蔻��㏈��
	void HitCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject);

	//��������
	float generationTime_;

	//�v���C���[�^�C�v
	Player::PLAYER_TYPE playerType_;

	//�_
	Transform cloudTransform_;

	//����
	float length_;

};

