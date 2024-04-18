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
		int handle;				//シェーダーハンドル
		int constBufFloat4Size;	//FLOAT4型の定数バッファの個数
	};

	// テクスチャアドレスタイプ
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


	//初期化
	virtual void Init(void) = 0;


	//テクスチャの更新
	void SetTextures(int slot, int texDiffuse);

	//テクスチャ配列の取得
	const std::map<int, int>& GetTextures(void)const { return texture_; }

	//テクスチャアドレスを取得
	TEXADDRESS GetTextureAddress(void)const { return texAddress_; }
	//テクスチャアドレスを設定
	void SetTextureAddress(TEXADDRESS texA) { texAddress_ = texA; }


private:

	//テクスチャアドレス
	TEXADDRESS texAddress_;

	//画像
	std::map<int, int> texture_;
	//std::vector<int> texture_;


};

