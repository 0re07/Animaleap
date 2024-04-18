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
	//オリジナルシェーダーの設定（ON）
	MV1SetUseOrigShader(true);

	//シェーダー設定（頂点）
	SetReserveVS();

	//シェーダー設定（ピクセル）
	SetReservePS();


	// テクスチャアドレスタイプの取得
	auto texA = materialBase_.GetTextureAddress();
	int texAType = static_cast<int>(texA);

	//テクスチャアドレスタイプの変更
	SetTextureAddressModeUV(texAType, texAType);

	// 描画
	MV1DrawModel(modelId_);

	//オリジナルシェーダーの設定（OFF）
	MV1SetUseOrigShader(false);

}

void ModelRenderer::SetReserveVS(void)
{
	//定数バッファハンドル
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

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cb);
	// 定数バッファを頂点シェーダー用定数バッファレジスタにセット
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_VERTEX, CONSTANT_BUF_SLOT_BEGIN_VS);

	// シェーダー設定
	SetUseVertexShader(materialBase_.GetShaderHandleVS());

}

void ModelRenderer::SetReservePS(void)
{
	//ピクセルシェーダーにテクスチャを転送
	const auto& textures = materialBase_.GetTextures();
	size_t size = textures.size();
	if (size == 0)
	{
		//前回使用分のテクスチャを引き継がないように
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


	//定数バッファハンドル
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

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cb);
	// 定数バッファをピクセルシェーダー用定数バッファレジスタにセット
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// シェーダー設定
	SetUsePixelShader(materialBase_.GetShaderHandlePS());
}
