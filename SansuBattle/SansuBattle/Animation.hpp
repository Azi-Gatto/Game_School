//Animation.hpp
//アニメーションを管理するクラス

#pragma once

//############ ヘッダファイル読み込み ###############
#include "Global.hpp"

//###################### マクロ定義：ファイルパス、名前 ######################
#define ANIM_DIR				R"(.\Anim)"			//アニメーションの画像ファイルの場所

#define ANIM_NAME_DAMEGE		R"(\Damege.png)"	//ダメージエフェクトの画像の名前

//###################### マクロ定義：エラーメッセージ ########################
#define ANIMATION_ERROR_TTILE	"ANIMATION_ERROR"						//エラータイトル
#define ANIMATION_ERROR_MSG		"アニメーションが読み込めませんでした"	//エラーメッセージ

//############ マクロ定義 ##############
//********************** サイズ ************************
#define ANIM_DAMEGE_WIDTH		240	//分割幅
#define ANIM_DAMEGE_HEIGHT		240	//分割高さ

//********************** 分割数 **************************
#define ANIM_DAMEGE_YOKO_CNT		7	//横分割数
#define ANIM_DAMEGE_TATE_CNT		1	//縦分割数

//************************ 総分割数 **************************
#define ANIM_DAMEGE_ALL_CNT	ANIM_DAMEGE_YOKO_CNT * ANIM_DAMEGE_TATE_CNT	//総分割数

//************************ 描画速度 ***************************
#define ANIM_DAMEGE_SPEED		0.08

//############## 列挙型 #################
enum ANIM_LIST
{
	ANIM_DAMEGE,	//攻撃
};

using std::vector;
using std::string;

//############ クラス定義 ##############
class Animation
{
private:

	static vector<vector<int>> AnimList;//アニメーション一覧

	vector<int> Handle;					//ハンドル
	vector<int>::iterator Handle_itr;	//ハンドルのイテレータ

	int Width;					//幅
	int Height;					//高さ

	double NextChangeSpeed;		//アニメーションを変更する速さ(秒)
	int ChangeCnt;				//アニメーションするフレームのカウント
	int ChangeMaxCnt;			//アニメーションするフレームの最大値

	bool IsAnimeLoop;			//アニメーションはループする？
	bool IsDrawEnd;				//描画終了したか
	bool IsNowDraw;				//描画中か

	bool IsLoad;				//読み込めたか？

public:

	static bool CreateList();		//リスト作成
	static void DeleteHandle();		//リストのハンドルを削除

	Animation(int, double, bool);	//コンストラクタ
	~Animation();					//デストラクタ

	void SetInit();			//初期設定

	int GetWidth();			//幅を取得
	int GetHeight();		//高さを取得

	bool GetIsLoad(void);	//読み込めた？
	bool GetIsDrawEnd();	//描画終了したか取得
	bool GetIsNowDraw();	//描画中か取得

	void Reset();			//リセット

	void Draw(int, int);	//描画
	void DrawCenter();		//画面中央に描画
	void DrawCenter(RECT);	//指定された領域内の中央に描画


};
