#include "ModelMaterial.h"

ModelMaterial::ModelMaterial(const VS_TYPE& vsType, const PS_TYPE& psType)
{
	vsType_ = vsType;
	psType_ = psType;

	Init();
}

ModelMaterial::~ModelMaterial()
{
}

void ModelMaterial::Init(void)
{
	//シェーダーデータの初期化
	InitShaderData();



	//空の定数バッファの確保
	for (int i = 0; i < constBufFloat4SizeVS_; i++)
	{
		AddConstBufVS(FLOAT4{});
	}
	for (int i = 0; i < constBufFloat4SizePS_; i++)
	{
		AddConstBufPS(FLOAT4{});
	}

	// 頂点シェーダー用の定数バッファを作成
	constBufVS_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * constBufFloat4SizeVS_);
	// ピクセルシェーダー用の定数バッファを作成
	constBufPS_ = CreateShaderConstantBuffer(sizeof(FLOAT4) * constBufFloat4SizePS_);

	//テクスチャアドレス
	SetTextureAddress(TEXADDRESS::CLAMP);



}

void ModelMaterial::SetConstBufVS(int idx, const FLOAT4& constBuf)
{
	if (idx >= constBufsVS_.size())return;

	constBufsVS_[idx] = constBuf;
}

void ModelMaterial::SetConstBufPS(int idx, const FLOAT4& constBuf)
{
	if (idx >= constBufsPS_.size())return;

	constBufsPS_[idx] = constBuf;
}


void ModelMaterial::InitShaderData(void)
{
	//vsShaderDatas_.emplace(
	//	VS_TYPE::MODEL_NORMAL_1FRAME,
	//	ShaderData{0,3});
	//auto& res = ResourceManager::GetInstance();
	////頂点シェーダの登録
	//shaderHandleVS_ = res.Load(shaderTypeVS_).handleId_;
	//assert(shaderHandleVS_ >= 1, "頂点シェーダーをロードできませんでした。");


	std::string pathVS = "Data/Shader/Vertex/";
	std::string pathPS = "Data/Shader/Pixel/";

	auto setShaderDataVS = [&](std::string path, int constBufSize)
	{
		path = pathVS + path;
		shaderHandleVS_ = LoadVertexShader(path.c_str());
		constBufFloat4SizeVS_ = constBufSize;
	};

	auto setShaderDataPS = [&](std::string path, int constBufSize)
	{
		path = pathPS + path;
		shaderHandlePS_ = LoadPixelShader(path.c_str());
		constBufFloat4SizePS_ = constBufSize;
	};

	switch (vsType_)
	{
	case VS_TYPE::MODEL_NORMAL_1FRAME:
		setShaderDataVS("ModelNormal1FrameVertexShader.vso",0);
		break;
	default:
		break;
	}

	switch (psType_)
	{
	case PS_TYPE::MODEL_NORMAL_1FRAME:
		setShaderDataPS("ModelNormalPixelShader.pso", 0);
		break;
	case PS_TYPE::MODEL_TOON_1FRAME:
		setShaderDataPS("ModelToonPixelShader.pso", 0);
		break;
	default:
		break;
	}

}

void ModelMaterial::AddConstBufVS(const FLOAT4& constBuf)
{
	if (constBufFloat4SizeVS_ > constBufsVS_.size())
	{
		constBufsVS_.emplace_back(constBuf);
	}
}

void ModelMaterial::AddConstBufPS(const FLOAT4& constBuf)
{
	if (constBufFloat4SizePS_ > constBufsPS_.size())
	{
		constBufsPS_.emplace_back(constBuf);
	}
}
