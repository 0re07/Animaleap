#pragma once
#include<DxLib.h>
#include<vector>
#include<map>
#include<string>



class MaterialBase 
{
public:
	struct ShaderData
	{
		int handle;				//�V�F�[�_�[�n���h��
		int constBufFloat4Size;	//FLOAT4�^�̒萔�o�b�t�@�̌�
	};

	// �e�N�X�`���A�h���X�^�C�v
	enum class TEXADDRESS
	{
		NONE = 0,
		WRAP,
		MIRROR,
		CLAMP,
		BORDER,
		MAX
	};

	MaterialBase();
	virtual ~MaterialBase();


	//������
	virtual void Init(void) = 0;


	//�e�N�X�`���̍X�V
	void SetTextures(int slot, int texDiffuse);

	//�e�N�X�`���z��̎擾
	const std::map<int, int>& GetTextures(void)const { return texture_; }

	//�e�N�X�`���A�h���X���擾
	TEXADDRESS GetTextureAddress(void)const { return texAddress_; }
	//�e�N�X�`���A�h���X��ݒ�
	void SetTextureAddress(TEXADDRESS texA) { texAddress_ = texA; }


private:

	//�e�N�X�`���A�h���X
	TEXADDRESS texAddress_;

	//�摜
	std::map<int, int> texture_;
	//std::vector<int> texture_;


};

