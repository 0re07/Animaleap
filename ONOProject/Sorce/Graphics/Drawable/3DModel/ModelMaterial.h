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
	/// 引数付きコンストラクタ
	/// </summary>
	/// <param name="vsType">頂点シェーダーのタイプ</param>
	/// <param name="psType">ピクセルシェーダーのタイプ</param>
	ModelMaterial(const VS_TYPE& vsType, const PS_TYPE& psType);
	virtual ~ModelMaterial();


	//初期化
	void Init(void)override;


	//定数バッファの更新
	void SetConstBufVS(int idx, const FLOAT4& constBuf);
	void SetConstBufPS(int idx, const FLOAT4& constBuf);

	//シェーダーハンドルの取得
	const int& GetShaderHandleVS(void)const { return shaderHandleVS_; }
	const int& GetShaderHandlePS(void)const { return shaderHandlePS_; }

	//定数バッファハンドルの取得
	const int& GetConstBufHandleVS(void)const { return constBufVS_; }
	const int& GetConstBufHandlePS(void)const { return constBufPS_; }

	//定数バッファ配列の取得
	const std::vector<FLOAT4>& GetConstBufsVS(void)const { return constBufsVS_; }
	const std::vector<FLOAT4>& GetConstBufsPS(void)const { return constBufsPS_; }


	//シェーダータイプからデータの設定
	void InitShaderData(void);

private:


	//シェーダーデータ
	//std::map<VS_TYPE, ShaderData>vsShaderDatas_;

	//シェーダータイプ
	VS_TYPE vsType_;
	PS_TYPE psType_;
	//シェーダーハンドル
	int shaderHandleVS_;
	int shaderHandlePS_;
	//定数バッファの確保サイズ
	int constBufFloat4SizeVS_;
	int constBufFloat4SizePS_;
	//定数バッファハンドル
	int constBufVS_;
	int constBufPS_;

	//定数バッファ配列
	std::vector<FLOAT4> constBufsVS_;
	std::vector<FLOAT4> constBufsPS_;

	//定数バッファの追加
	void AddConstBufVS(const FLOAT4& constBuf);
	void AddConstBufPS(const FLOAT4& constBuf);

};

