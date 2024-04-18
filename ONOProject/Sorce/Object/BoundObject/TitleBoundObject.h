#pragma once
#include "../Object.h"
class TitleBoundObject :
    public Object
{
public:
	TitleBoundObject(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~TitleBoundObject();

	void Init(void)override;
	void Release(void)override;
	void Update(float deltaSeconds)override;
	void Draw(void)override;


	//�d�͏���
	void GravityProcess(void);
	//��������
	void FallProcess(void);
	//��]����
	void RotateProcess(void);
	//�W�����v����
	void JumpProcess();

	//X���W�̈ړ������𔽓]
	void ReverseMoveDirX(void);


protected:
	// �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
	void InitCollisionAfter(void)override;

	float speed_;		//�ړ����x
	VECTOR moveDir_;    //�ړ�����
	VECTOR movePow_;    //�ړ���
	VECTOR movedPos_;   //�ړ���̍��W
	float fallingPow_;	//������

	VECTOR rotateDir_;	//��]����
	float rotateSpeed_;	//��]�X�s�[�h

private:


};

