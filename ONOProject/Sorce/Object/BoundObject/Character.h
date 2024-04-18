#pragma once
#include <memory>
#include "../../Player/Player.h"
#include "BoundObject.h"
class ModelMaterial;
class ModelRenderer;

class Character :
    public BoundObject
{
public:
	//�����蔻��̔��a
	static constexpr float HIT_SIZE_RADIOUS = 20;

	//�L�������x��
	enum class CHARACTOR_LEVEL
	{
		LEVEL_1,
		LEVEL_2,
		LEVEL_3
	};

	/// <summary>
	/// �L�����N�^�[�̃R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="scl">�傫��</param>
	/// <param name="rot">�p�x</param>
	/// <param name="playerType">�v���C���[�^�C�v</param>
	/// <param name="moveDir">�ړ�����</param>
	/// <param name="fallingPow">������</param>
	Character(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~Character();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

	//�L�������x���̎擾
	const CHARACTOR_LEVEL& GetCharaLevel(void)const {return level_;}
	//�v���C���[�^�C�v�̎擾
	const Player::PLAYER_TYPE& GetPlayerType(void)const { return playerType_; }
	//�v���C���[�^�C�v�̐ݒ�
	const void SetPlayerType(const Player::PLAYER_TYPE& type){ playerType_ = type; }

	//�W�����v����
	void JumpProcess(const VECTOR& jumpDir, const float& jumpRate)override;

	//�L�������x���A�b�v�̃`�F�b�N
	void CheckLevelUp(void);

private:
	//���x���ʃ��f��
	int dogModelHandle_;
	int fishModelHandle_;
	int chickenModelHandle_;
	
	//�o�E���h��
	int boundCount_;

	//�L�����N�^�[���x��
	CHARACTOR_LEVEL level_;

	//���[�J�����W�i���f�������炷�����j
	VECTOR localPos;

	std::unique_ptr<ModelMaterial> testMaterial_;
	std::unique_ptr<ModelRenderer> testRenderer_;


};

