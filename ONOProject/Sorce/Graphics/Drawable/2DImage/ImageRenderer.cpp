#include "ImageMaterial.h"
#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(int& handle, ImageMaterial& material):
	handle_(handle), material_(material)
{
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Draw(void)
{
	//�I���W�i���V�F�[�_�[�̐ݒ�iON�j
	MV1SetUseOrigShader(true);

	// �V�F�[�_�[�ݒ�
	SetUsePixelShader(material_.GetShaderHandlePS());

	//�萔�o�b�t�@
	auto cb = material_.GetConstBufHandlePS();

	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`����]��
	const auto& textures = material_.GetTextures();
	size_t size = textures.size();
	if (size == 0)
	{
		//�O��g�p���̃e�N�X�`���������p���Ȃ��悤��
		SetUseTextureToShader(0, -1);
		SetUseTextureToShader(1, -1);
	}
	else
	{
		for (const auto& pair : textures)
		{
			SetUseTextureToShader(pair.first, pair.second);
		}
	}

	// �萔�o�b�t�@
	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(cb);
	const auto& constBufs = material_.GetConstBufsPS();
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

	// �e�N�X�`���A�h���X�^�C�v�̎擾
	auto texA = material_.GetTextureAddress();
	int texAType = static_cast<int>(texA);
	//�e�N�X�`���A�h���X�^�C�v�̕ύX
	SetTextureAddressModeUV(texAType, texAType);

	// �萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cb);
	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�p�萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	SetDrawMode(DX_DRAWMODE_NEAREST);
	// �`��
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_POLYGON);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�I���W�i���V�F�[�_�[�̐ݒ�iOFF�j
	MV1SetUseOrigShader(false);


}

void ImageRenderer::SetSquereVertex(Vector2 start, Vector2 end)
{
	int cnt = 0;
	float sX = static_cast<float>(start.x);
	float sY = static_cast<float>(start.y);
	float eX = static_cast<float>(end.x);
	float eY = static_cast<float>(end.y);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		vertexs_[i].rhw = 1.0f;
		vertexs_[i].dif = GetColorU8(255, 255, 255, 255);
		vertexs_[i].spc = GetColorU8(255, 255, 255, 255);
		vertexs_[i].su = 0.0f;
		vertexs_[i].sv = 0.0f;
	}

	// ����
	vertexs_[cnt].pos = VGet(sX, sY, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertexs_[cnt].pos = VGet(eX, sY, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertexs_[cnt].pos = VGet(eX, eY, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 1.0f;
	cnt++;

	// ����
	vertexs_[cnt].pos = VGet(sX, eY, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 1.0f;

	// ���_�C���f�b�N�X
	cnt = 0;
	indexes_[cnt++] = 0;
	indexes_[cnt++] = 1;
	indexes_[cnt++] = 3;

	indexes_[cnt++] = 1;
	indexes_[cnt++] = 2;
	indexes_[cnt++] = 3;
}


void ImageRenderer::SetReservePS(void)
{
}
