#pragma once
#include <DxLib.h>
#include "Quaternion.h"

class Transform
{
public:
	Transform(void);
	Transform(int model);
	Transform(VECTOR pos, VECTOR scl, VECTOR rot);
	Transform(int model, VECTOR pos, VECTOR scl, VECTOR rot);
	~Transform(void);

	// ���f���̃n���h��ID
	int modelId_;

	// �傫��
	VECTOR scl_;

	// �傫���i���I�ύX�j
	VECTOR scaling_;

	// ��]
	VECTOR rot_;		// �f�o�b�O�p
	// �ʒu
	VECTOR pos_;

	MATRIX matScl_;
	MATRIX matRot_;
	MATRIX matPos_;

	// ��]
	Quaternion quaRot_;

	// ���[�J����]
	Quaternion quaRotLocal_;

	/// <summary>
	/// ���f������̊�{���X�V
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	void SetModel(int model);

	// �O���������擾
	VECTOR GetForward(void) const;

	// ����������擾
	VECTOR GetBack(void) const;

	// �E�������擾
	VECTOR GetRight(void) const;

	// ���������擾
	VECTOR GetLeft(void) const;

	// ��������擾
	VECTOR GetUp(void) const;

	// ���������擾
	VECTOR GetDown(void) const;

	// �Ώە������擾
	VECTOR GetDir(VECTOR vec) const;

private:

};

