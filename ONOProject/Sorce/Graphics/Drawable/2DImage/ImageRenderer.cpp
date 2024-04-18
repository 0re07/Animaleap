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
	//オリジナルシェーダーの設定（ON）
	MV1SetUseOrigShader(true);

	// シェーダー設定
	SetUsePixelShader(material_.GetShaderHandlePS());

	//定数バッファ
	auto cb = material_.GetConstBufHandlePS();

	//ピクセルシェーダーにテクスチャを転送
	const auto& textures = material_.GetTextures();
	size_t size = textures.size();
	if (size == 0)
	{
		//前回使用分のテクスチャを引き継がないように
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

	// 定数バッファ
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

	// テクスチャアドレスタイプの取得
	auto texA = material_.GetTextureAddress();
	int texAType = static_cast<int>(texA);
	//テクスチャアドレスタイプの変更
	SetTextureAddressModeUV(texAType, texAType);

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cb);
	// 定数バッファをピクセルシェーダー用定数バッファレジスタにセット
	SetShaderConstantBuffer(
		cb, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	SetDrawMode(DX_DRAWMODE_NEAREST);
	// 描画
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_POLYGON);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//オリジナルシェーダーの設定（OFF）
	MV1SetUseOrigShader(false);


}

void ImageRenderer::SetSquereVertex(Vector2 start, Vector2 end)
{
	int cnt = 0;
	float sX = static_cast<float>(start.x);
	float sY = static_cast<float>(start.y);
	float eX = static_cast<float>(end.x);
	float eY = static_cast<float>(end.y);

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		vertexs_[i].rhw = 1.0f;
		vertexs_[i].dif = GetColorU8(255, 255, 255, 255);
		vertexs_[i].spc = GetColorU8(255, 255, 255, 255);
		vertexs_[i].su = 0.0f;
		vertexs_[i].sv = 0.0f;
	}

	// 左上
	vertexs_[cnt].pos = VGet(sX, sY, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// 右上
	vertexs_[cnt].pos = VGet(eX, sY, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// 右下
	vertexs_[cnt].pos = VGet(eX, eY, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 1.0f;
	cnt++;

	// 左下
	vertexs_[cnt].pos = VGet(sX, eY, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 1.0f;

	// 頂点インデックス
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
