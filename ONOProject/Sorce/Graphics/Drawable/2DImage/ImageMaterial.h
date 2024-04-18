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


	//初期化
	void Init(void)override;


	//定数バッファの更新
	void SetConstBufPS(int idx, const FLOAT4& constBuf);

	//シェーダーハンドルの取得
	const int& GetShaderHandlePS(void)const { return shaderHandlePS_; }

	//定数バッファハンドルの取得
	const int& GetConstBufHandlePS(void)const { return constBufPS_; }

	//定数バッファ配列の取得
	const std::vector<FLOAT4>& GetConstBufsPS(void)const { return constBufsPS_; }


	//シェーダータイプからデータの設定
	void InitShaderData(void);

private:


	//シェーダーデータ
	//std::map<VS_TYPE, ShaderData>vsShaderDatas_;

	//シェーダータイプ
	PS_TYPE psType_;
	//シェーダーハンドル
	int shaderHandlePS_;
	//定数バッファの確保サイズ
	int constBufFloat4SizePS_;
	//定数バッファハンドル
	int constBufPS_;

	//定数バッファ配列
	std::vector<FLOAT4> constBufsPS_;

	//定数バッファの追加
	void AddConstBufPS(const FLOAT4& constBuf);


};

