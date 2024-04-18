#pragma once
#include "../MaterialBase.h"
class ImageMaterial :
    public MaterialBase
{
public:
	enum class PS_TYPE
	{
		NORMAL,
	};


	ImageMaterial(const PS_TYPE& psType);
	virtual ~ImageMaterial();


	//������
	void Init(void)override;


	//�萔�o�b�t�@�̍X�V
	void SetConstBufPS(int idx, const FLOAT4& constBuf);

	//�V�F�[�_�[�n���h���̎擾
	const int& GetShaderHandlePS(void)const { return shaderHandlePS_; }

	//�萔�o�b�t�@�n���h���̎擾
	const int& GetConstBufHandlePS(void)const { return constBufPS_; }

	//�萔�o�b�t�@�z��̎擾
	const std::vector<FLOAT4>& GetConstBufsPS(void)const { return constBufsPS_; }


	//�V�F�[�_�[�^�C�v����f�[�^�̐ݒ�
	void InitShaderData(void);

private:


	//�V�F�[�_�[�f�[�^
	//std::map<VS_TYPE, ShaderData>vsShaderDatas_;

	//�V�F�[�_�[�^�C�v
	PS_TYPE psType_;
	//�V�F�[�_�[�n���h��
	int shaderHandlePS_;
	//�萔�o�b�t�@�̊m�ۃT�C�Y
	int constBufFloat4SizePS_;
	//�萔�o�b�t�@�n���h��
	int constBufPS_;

	//�萔�o�b�t�@�z��
	std::vector<FLOAT4> constBufsPS_;

	//�萔�o�b�t�@�̒ǉ�
	void AddConstBufPS(const FLOAT4& constBuf);


};

