#pragma once
#include "../MaterialBase.h"
class ModelMaterial :
    public MaterialBase
{
public:
	enum class VS_TYPE
	{
		MODEL_NORMAL_1FRAME,
	};

	enum class PS_TYPE
	{
		MODEL_NORMAL_1FRAME,
		MODEL_TOON_1FRAME,
	};


	/// <summary>
	/// �����t���R���X�g���N�^
	/// </summary>
	/// <param name="vsType">���_�V�F�[�_�[�̃^�C�v</param>
	/// <param name="psType">�s�N�Z���V�F�[�_�[�̃^�C�v</param>
	ModelMaterial(const VS_TYPE& vsType, const PS_TYPE& psType);
	virtual ~ModelMaterial();


	//������
	void Init(void)override;


	//�萔�o�b�t�@�̍X�V
	void SetConstBufVS(int idx, const FLOAT4& constBuf);
	void SetConstBufPS(int idx, const FLOAT4& constBuf);

	//�V�F�[�_�[�n���h���̎擾
	const int& GetShaderHandleVS(void)const { return shaderHandleVS_; }
	const int& GetShaderHandlePS(void)const { return shaderHandlePS_; }

	//�萔�o�b�t�@�n���h���̎擾
	const int& GetConstBufHandleVS(void)const { return constBufVS_; }
	const int& GetConstBufHandlePS(void)const { return constBufPS_; }

	//�萔�o�b�t�@�z��̎擾
	const std::vector<FLOAT4>& GetConstBufsVS(void)const { return constBufsVS_; }
	const std::vector<FLOAT4>& GetConstBufsPS(void)const { return constBufsPS_; }


	//�V�F�[�_�[�^�C�v����f�[�^�̐ݒ�
	void InitShaderData(void);

private:


	//�V�F�[�_�[�f�[�^
	//std::map<VS_TYPE, ShaderData>vsShaderDatas_;

	//�V�F�[�_�[�^�C�v
	VS_TYPE vsType_;
	PS_TYPE psType_;
	//�V�F�[�_�[�n���h��
	int shaderHandleVS_;
	int shaderHandlePS_;
	//�萔�o�b�t�@�̊m�ۃT�C�Y
	int constBufFloat4SizeVS_;
	int constBufFloat4SizePS_;
	//�萔�o�b�t�@�n���h��
	int constBufVS_;
	int constBufPS_;

	//�萔�o�b�t�@�z��
	std::vector<FLOAT4> constBufsVS_;
	std::vector<FLOAT4> constBufsPS_;

	//�萔�o�b�t�@�̒ǉ�
	void AddConstBufVS(const FLOAT4& constBuf);
	void AddConstBufPS(const FLOAT4& constBuf);

};

