//EFFECT.hpp
//エフェクトクラス

/*
エフェクト追加方法
・基本は、ANIMATIONクラスと同じ
・オブジェクト生成後は、Add処理を使用することで、エフェクトの追加をすることができる
*/

#pragma once

//###################### ヘッダファイル読み込み #########################
#include "DxLib.h"
#include <vector>
#include <string>
#include "FPS.hpp"
#include "IMAGE.hpp"

//###################### マクロ定義：ファイルパス、名前 ######################
#define EFFECT_DIR				R"(.\MY_EFFECT)"				//エフェクトの画像ファイルの場所

#define EFFECT_NAME_SLASH		R"(\slash.png)"					//スラッシュエフェクトの画像の名前

//###################### マクロ定義：エラーメッセージ ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//エラータイトル
#define EFFECT_ERROR_MSG	"エフェクトが読み込めませんでした"	//エラーメッセージ

//###################### マクロ定義 #################################

//********************** サイズ ************************
#define EFFECT_SLASH_WIDTH		880	//分割幅
#define EFFECT_SLASH_HEIGHT		640	//分割高さ


//********************** 分割数 **************************
#define EFFECT_SLASH_YOKO_CNT		3	//横分割数
#define EFFECT_SLASH_TATE_CNT		3	//縦分割数

//************************ 総分割数 **************************
#define EFFECT_SLASH_ALL_CNT	EFFECT_SLASH_YOKO_CNT * EFFECT_SLASH_TATE_CNT	//総分割数

//************************ 描画速度 ***************************

#define EFFECT_SLASH_SPEED		0.02

//****************** その他 ***********************
#define INIT_VALUE		0	//初期値

//###################### 列挙型 ##########################
enum EFFECT_KIND
{
	EFFECT_SLASH		//スラッシュエフェクト
};

//###################### クラス定義 ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;				//ハンドル
	std::vector<std::vector<int>::iterator> Handle_itr;	//ハンドルのイテレータ
	
	std::vector<int> Width;				//幅
	std::vector<int> Height;			//高さ

	std::vector<double> NextChangeSpeed;		//アニメーションを変更する速さ(秒)
	int ChangeCnt;								//アニメーションするフレームのカウント
	std::vector<int> ChangeMaxCnt;				//アニメーションするフレームの最大値

	std::vector<bool> IsAnimeLoop;			//アニメーションはループする？
	std::vector<bool> IsAnimeStop;			//アニメーションはストップしたか？

	bool IsDrawEnd;				//描画終了したか

	bool IsLoad;				//読み込めたか？

	bool IsFadeout;				//フェードアウト処理を行うか
	bool IsFadein;				//フェードイン処理を行うか

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool,int);	//コンストラクタ	

	~EFFECT();					//デストラクタ

	int GetWidth(int);			//幅を取得
	int GetHeight(int);			//高さを取得

	bool GetIsLoad(void);		//読み込めた？

	bool GetIsAnimeStop(int);	//アニメーションはストップしたかを取得

	bool GetIsDrawEnd();		//描画終了したか取得

	void SetIsDrawEnd(bool);	//描画終了したか設定

	void ResetIsAnime(int);		//アニメーションがストップしたかをリセット

	void Draw(int, int, int);	//描画

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//エフェクト追加

	void SetSize();						//サイズ設定

	void SetIsFadeout(bool);			//フェードアウトをするか設定
	void SetIsFadein(bool);				//フェードインをするか設定

	bool FadeOut(int,int,int,int);		//フェードアウトエフェクト
	bool FadeIn(int, int, int, int);	//フェードインエフェクト

};
