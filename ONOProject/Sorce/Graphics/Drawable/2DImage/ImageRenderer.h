#pragma once
#include<DxLib.h>
#include"../../../Common/Vector2.h"
class ImageMaterial;

class ImageRenderer
{
public:
	//コンストラクタ
	ImageRenderer(int& handle, ImageMaterial& material);
	~ImageRenderer();

	//描画
	void Draw(void);

	//描画矩形の生成
	void SetSquereVertex(Vector2 start, Vector2 end);

private:
	// ピクセルシェーダ用オリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;
	// 頂点数
	static constexpr int NUM_VERTEX = 4;
	// 頂点インデックス数
	static constexpr int NUM_VERTEX_IDX = 6;
	// ポリゴン数
	static constexpr int NUM_POLYGON = 2;

	//座標
	Vector2 pos_;
	//描画サイズ
	Vector2 size_;

	//頂点
	VERTEX2DSHADER vertexs_[NUM_VERTEX];

	//頂点インデックス
	WORD indexes_[NUM_VERTEX_IDX];

	//モデルハンドル
	int& handle_;

	//イメージマテリアル
	ImageMaterial& material_;

	//シェーダー設定（ピクセル）
	void SetReservePS(void);
};

