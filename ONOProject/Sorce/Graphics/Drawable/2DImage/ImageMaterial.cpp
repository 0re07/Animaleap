#include "ImageMaterial.h"

ImageMaterial::ImageMaterial(const PS_TYPE& psType)
{
	psType_ = psType;

	Init();
}

ImageMaterial::~ImageMaterial()
{
}

void ImageMaterial::Init(void)
{
	//シェーダーデータの初期化
	InitShaderData();

	//空の定数バッファの確保
	for (int i = 0; i < constBufFloat4SizePS_; i++)
	{
		AddConstBufPS(FLOAT4{});
	}

	// ピクセルシェーダー用の定数バッファを作成
	constBufPS_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * constBufFloat4SizePS_);

	//テクスチャアドレス
	SetTextureAddress(TEXADDRESS::CLAMP);
}

void ImageMaterial::SetConstBufPS(int idx, const FLOAT4& constBuf)
{
}

void ImageMaterial::InitShaderData(void)
{

	std::string pathPS = "Data/Shader/Pixel/";


	auto setShaderDataPS = [&](std::string path, int constBufSize)
	{
		path = pathPS + path;
		shaderHandlePS_ = LoadPixelShader(path.c_str());
		constBufFloat4SizePS_ = constBufSize;
	};


	switch (psType_)
	{
	case PS_TYPE::NORMAL:
		setShaderDataPS("ImageNormalPixelShader.pso", 0);
		break;
	default:
		break;
	}

}

void ImageMaterial::AddConstBufPS(const FLOAT4& constBuf)
{
}
