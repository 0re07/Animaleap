#pragma once
#include <DxLib.h>
#include <memory>
#include "../Common/Vector2.h"
class GameScene;

class SoundController;

//プレイヤーライフ
constexpr int PLAYER_LIFE = 3;
//トランポリンの最低限の長さ
constexpr float TRAMPOLINE_MIN_LENGTH = 0.5f;
//トランポリンの生成上限
constexpr int TRAMPOLINE_CREATE_MAX_NUM = 3;

class Player
{
public:

	//プレイヤータイプ
	enum class PLAYER_TYPE
	{
		LEFT_PLAYER,
		RIGHT_PLAYER,
	};

	Player(GameScene& gameScene, PLAYER_TYPE playerType);
	~Player();

	void Init(void);
	void Update(void);
	void Draw(void);

	//残機の取得
	const int& GetPlayerLife(void)const { return playerLife_; }

	//プレイヤータイプのセット
	//※引数付きコンストラクタでやって良い
	void SetPlayerType(PLAYER_TYPE type);

	//カーソル操作
	void OperationCursol(void);

	//トランポリンの生成操作
	void OperationCreateTrampoline(void);

	//トランポリンオブジェクトの生成
	void CreateTrampoline(void);

	//残機減少処理
	void DecreaseLife(void);

	//1Pか判断（左プレイヤー）
	bool ChackLeftPlayer(void);

private:

	//入力方法
	enum class INPUT_TYPE
	{
		PAD,
		MOUSE
	};

	//入力方法
	INPUT_TYPE inputType = INPUT_TYPE::PAD;

	GameScene& gameScene_;

	//確認用
	//トランポリン生成座標；始点
	Vector2 testStartPos_;
	//トランポリン生成座標；終点
	Vector2 testEndPos_;

	//トランポリン生成座標；始点
	VECTOR createTrampolineStartPos_;
	//トランポリン生成座標；終点
	VECTOR createTrampolineEndPos_;

	//トランポリンを生成できる範囲
	Vector2 createablePosMin_;
	Vector2 createablePosMax_;
	
	//トランポリン生成ライン
	int createLineImg_;

	//std::unique_ptr<ImageMaterial> createLineMaterial_;
	//std::unique_ptr<ImageRenderer> createLineRenderer_;


	//カーソル画像
	int cursolImageHandle_;
	//トランポリン生成可能数フォント
	int creatableNumFontHandle_;
	//ライフ画像
	int lifeImage_;
	//操作説明フォント
	int operationFontHandle_;

	//カーソル位置
	Vector2 cursolPos_;

	//カーソルスピード
	int cursolSpeed_;

	//クリックカウント
	int clickCount_ = 0;

	//プレイヤーライフ
	int playerLife_;

	//プレイヤータイプ
	PLAYER_TYPE playerType_;

	//XY座標の中間を求める
	VECTOR CalcCenterPos(VECTOR start, VECTOR end);

	//自プレイヤーの生成しているトランポリンの数を取得
	const int& GetAliveTrampolineNum(void)const;


	//落下音
	std::unique_ptr<SoundController> fallSE_;

};

