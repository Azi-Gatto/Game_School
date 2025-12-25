//Play.hpp
//プレイ画面の処理

#pragma once

//############### ヘッダファイル読み込み ##############
#include "Scene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Question.hpp"
#include "Time.hpp"

//############### マクロ定義 #################
#define LIMIT_DRAW_X	740		//ゲームの制限時間描画X位置
#define LIMIT_DRAW_Y	20		//ゲームの制限時間描画Y位置
#define LIMIT_TIME		30		//ゲームの制限時間
#define MISS_MINUS_TIME	5		//間違えたときの減る時間

#define CIRCLE_X		720		//円の描画X位置
#define CIRCLE_Y		0		//円の描画Y位置
#define SCORE_Y			335		//スコアの描画Y位置

#define IMG_UI_DIR			R"(.\Image\Ui)"		//UI画像のディレクトリ

#define IMG_CIRCLE_NAME		R"(\circle.png)"	//円の画像の名前
#define IMG_KOKUBAN_NAME	 R"(\kokuban.png)"	//黒板の画像の名前

#define PHASE_TOUKA_PERCENT	0.8	//操作フェーズでの透過割合

using std::vector;

//############### 列挙型 ##################
enum SE_KIND
{
	SE_FALSE,		//不正解の時の効果音
	SE_DAMEGE		//ダメージを受けたときの効果音
};

enum PHASE_KIND
{
	PHASE_EFFECT,		//エフェクトフェーズ
	PHASE_OPERATION		//操作フェーズ
};

//############### クラス定義 #################
class Play : public Scene	//Sceneクラスを継承
{
private:

	Player* player;				//プレイヤー
	vector<Enemy*> enemy;		//敵
	vector<Question*> quesiton;	//問題
	Time* limit;				//制限時間
	vector<Music*> se;			//効果音
	Image* circle;				//円
	Image* bord;				//黒板

	bool IsOperation;			//操作できるか
	int NowPhase;				//現在のフェーズ

	void Start() override;		//シーンが変わるごとに1回だけ行う処理
	void Battle();				//バトルの処理

public:

	Play();						//コンストラクタ
	~Play();					//デストラクタ

	void SetInit() override;	//初期設定
	void Run() override;		//プレイ画面の処理

};
