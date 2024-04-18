#include "ModelMaterial.h"
#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(int& modelId, ModelMaterial& material) :
	modelId_(modelId), materialBase_(material)
{
}

ModelRenderer::~ModelRenderer()
{
}


void ModelRenderer::Draw(void)
{
	//�I���W�i���V�F�[�_�[�̐ݒ�iON�j
	MV1SetUseOrigShader(true);

	//�V�F�[�_�[�ݒ�i���_�j
	SetReserveVS();

	//�V�F�[�_�[�ݒ�i�s�N�Z���j
	SetReservePS();


	// �e�N�X�`���A�h���X�^�C�v�̎擾
	auto texA = materialBase_.GetTextureAddress();
	int texAType = static_cast<int>(texA);

	//�e�N�X�`���A�h���X�^�C�v�̕ύX
	SetTextureAddressModeUV(texAType, texAType);

	// �`��
	MV1DrawModel(modelId_);

	//�I���W�i���V�F�[�_�[�̐ݒ�iOFF�j
	MV1SetUseOrigShader(false);

}

void ModelRenderer::SetReserveVS(void)
{
	//�萔�o�b�t�@�n���h��
	auto cb = materialBase_.GetConstBufHandleVS();

	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(cb);
	const auto& constBufs = materialBase_.GetConstBufsVS();
	size_t size = constBufs.size();
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			constBufsPtr++;
		}
		constBufsPtr->x = constBufs[i].x;
		constBufsPtr->y = constBufs[i].y;
		constBufsPtr->z = constBufs[i].z;
		constBufsPtr->w = constBufs[i].w;
	}

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cb);
	// �萔�o�b�t�@�𒸓_�V�F�[�_�[�p�萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_VERTEX, CONSTANT_BUF_SLOT_BEGIN_VS);

	// �V�F�[�_�[�ݒ�
	SetUseVertexShader(materialBase_.GetShaderHandleVS());

}

void ModelRenderer::SetReservePS(void)
{
	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`����]��
	const auto& textures = materialBase_.GetTextures();
	size_t size = textures.size();
	if (size == 0)
	{
		//�O��g�p���̃e�N�X�`���������p���Ȃ��悤��
		SetUseTextureToShader(0, -1);
		SetUseTextureToShader(1, -1);
		//SetUseTextureToShader(2, -1);
		//SetUseTextureToShader(3, -1);
		//SetUseTextureToShader(4, -1);
	}
	else
	{
		for (const auto& pair : textures)
		{
			SetUseTextureToShader(pair.first, pair.second);
		}
	}


	//�萔�o�b�t�@�n���h��
	auto cb = materialBase_.GetConstBufHandlePS();

	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(cb);
	const auto& constBufs = materialBase_.GetConstBufsPS();
	size = constBufs.size();
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			constBufsPtr++;
		}
		constBufsPtr->x = constBufs[i].x;
		constBufsPtr->y = constBufs[i].y;
		constBufsPtr->z = constBufs[i].z;
		constBufsPtr->w = constBufs[i].w;
	}

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cb);
	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�p�萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// �V�F�[�_�[�ݒ�
	SetUsePixelShader(materialBase_.GetShaderHandlePS());
}
