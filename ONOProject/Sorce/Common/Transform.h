#pragma once
#include <DxLib.h>
#include "Quaternion.h"

class Transform
{
public:
	Transform(void);
	Transform(int model);
	Transform(VECTOR pos, VECTOR scl, VECTOR rot);
	Transform(int model, VECTOR pos, VECTOR scl, VECTOR rot);
	~Transform(void);

	// モデルのハンドルID
	int modelId_;

	// 大きさ
	VECTOR scl_;

	// 大きさ（動的変更）
	VECTOR scaling_;

	// 回転
	VECTOR rot_;		// デバッグ用
	// 位置
	VECTOR pos_;

	MATRIX matScl_;
	MATRIX matRot_;
	MATRIX matPos_;

	// 回転
	Quaternion quaRot_;

	// ローカル回転
	Quaternion quaRotLocal_;

	/// <summary>
	/// モデル制御の基本情報更新
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	void SetModel(int model);

	// 前方方向を取得
	VECTOR GetForward(void) const;

	// 後方方向を取得
	VECTOR GetBack(void) const;

	// 右方向を取得
	VECTOR GetRight(void) const;

	// 左方向を取得
	VECTOR GetLeft(void) const;

	// 上方向を取得
	VECTOR GetUp(void) const;

	// 下方向を取得
	VECTOR GetDown(void) const;

	// 対象方向を取得
	VECTOR GetDir(VECTOR vec) const;

private:

};

