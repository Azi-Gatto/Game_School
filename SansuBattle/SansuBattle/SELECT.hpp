//Select.hpp
//選択画面の処理

#pragma once

//############# ヘッダファイル読み込み ##############
#include "Scene.hpp"
#include "Button.hpp"
#include "Group.hpp"

//############# マクロ定義 ##############
#define BT_MODE_DRAW_X		40	//ゲームモードの選択肢の描画開始X位置
#define BT_MODE_DRAW_Y		40	//ゲームモードの選択肢の描画開始Y位置
#define BT_LEVEL_DRAW_X		0	//レベルの選択肢の描画開始X位置
#define BT_LEVEL_DRAW_Y		250	//レベルの選択肢の描画開始Y位置
#define BT_NEXT_DRAW_X		620	//矢印（右）の描画X位置
#define BT_PREV_DRAW_X		50	//矢印（左）の描画X位置

#define BT_MODE_INTERVAL_SIDE		30		//ゲームモード選択肢の間隔(横)
#define BT_MODE_INTERVAL_VERTICAL	150		//ゲームモード選択肢の間隔(縦)
#define BT_LEVEL_INTERVAL_SIDE		10		//レベル選択肢の間隔(縦)
#define BT_LEVEL_INTERVAL_VERTICAL	0		//レベル選択肢の間隔(横)
#define BT_START_INTERVAL_SIDE		80		//スタートの選択肢の間隔（横）

//############# クラス定義 ##############
class Select : public Scene	//Sceneを継承
{
private:

	vector<Button*> mode;		//ゲームモード
	vector<Image*> mode_img;	//ゲームモード画像
	vector<Button*> level;		//ゲームレベル
	vector<Image*> level_img;	//ゲームレベル画像
	Button* next;				//次のページへ移動するボタン
	Button* prev;				//前のページへ移動するボタン
	Button* cancel;				//レベル選択から、モード選択へ戻るボタン

	Group* mode_group;			//ゲームモードのグループ
	Group* level_group;			//ゲームレベルのグループ

	void Start() override;		//シーンが変わるごとに1回だけ行う処理

public:

	Select();			//コンストラクタ
	~Select();			//デストラクタ

	void SetInit() override;	//初期設定
	void Run() override;		//選択画面の処理

};
