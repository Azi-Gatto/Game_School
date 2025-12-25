/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				　 */
/* 画像クラス 																					　 */

/*
追加方法
・フォルダ名とファイル名をマクロ定義する
・Add処理を使用して、画像を読み込む
*/

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <string>
#include <vector>

//########## マクロ定義：画像のファイルパスと名前 ##########
#define IMG_DIR_BACK		R"(.\MY_IMG\Back)"				//背景画像のファイルの場所
#define IMG_DIR_MARK		R"(.\MY_IMG\Mark)"				//マーク画像のファイルの場所

#define IMG_NAME_TITLE		R"(\Title.jpg)"					//タイトル画面の背景画像の名前
#define IMG_NAME_PLAY		R"(\Play.jpg)"					//プレイ画面の背景画像の名前
#define IMG_NAME_END		R"(\end.png)"					//エンド画面の背景画像の名前

#define IMG_NAME_MARK		R"(\Mark.png)"					//マーク画像の名前

#define MARK_DRAW_Y			100		//マーク画像の描画Y位置

#define FADE_MAX_CNT	60	//フェード処理のカウント最大値
#define TOUKA_MAX_VALUE	255	//透過の最大値

//########## マクロ定義：エラーメッセージ##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG	"画像が読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ################
enum BACK_IMAGE
{
	TITLE_BACK,		//タイトル画面の背景画像
	PLAY_BACK,		//プレイ画面の背景画像
	END_BACK		//エンド画面の背景画像
};

//########## クラスの定義 ##########

class IMAGE
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<int> Handle;				//ハンドル

	std::vector<int> Width;					//幅
	std::vector<int> Height;				//高さ

	int ImageKind;				//読み込んだ画像の種類
	int Draw_Num;				//描画する画像の番号

	bool IsLoad;				//読み込めたか？
	std::vector<bool> IsDraw;	//描画してよいか
	std::vector<bool> IsFade;	//フェードアウトするか
	std::vector<bool> FadeEnd;	//フェードエフェクトが終わったか

public:
	IMAGE(const char *,const char *);	//コンストラクタ
	virtual ~IMAGE();					//デストラクタ

	std::string GetFileName(void);	//名前を取得

	void SetSize(void);				//サイズをセット

	int GetWidth();		//幅を取得
	int GetHeight();	//高さを取得

	bool GetIsLoad(void);			//読み込めた？
	void SetIsDraw(bool);			//描画してよいか設定

	void Draw(int, int);		//画像を描画
	void DrawCenter(int ,int);	//画像を描画（中央）

	bool AddImage(const char *, const char *);	//画像を追加
	void ChengeImage(int);						//描画する画像を変更

	void SetIsFade(bool);		//フェードアウトするか設定
	bool GetFadeEnd();			//フェードエフェクトが終了しているか取得

};

