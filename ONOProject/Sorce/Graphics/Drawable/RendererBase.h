#pragma once
#include<DxLib.h>
class MaterialBase;

class RendererBase
{
public:


	//コンストラクタ
	RendererBase(int& modelId, MaterialBase& postEffectMaterial);
	~RendererBase();



private:
	// 頂点シェーダ用オリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_VS = 7;
	// ピクセルシェーダ用オリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;


	//モデルハンドル
	int& modelId_;

	//モデルマテリアル
	MaterialBase& materialBase_;

	//シェーダー設定（頂点）
	void SetReserveVS(void);

	//シェーダー設定（ピクセル）
	void SetReservePS(void);


};

