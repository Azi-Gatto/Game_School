/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* Image.cpp     																				　 */
/* 画像クラス 																					　 */

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "Global.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

//########## マクロ定義：画像のファイルパスと名前 ##########
#define IMG_DIR_BACK		R"(.\Image\Back)"			//背景画像のファイルの場所
#define CHAR_IMG_DIR		R"(.\Image\Charactor)"		//キャラの画像ファイルのディレクトリ

#define PLAYER_IMG_NAME		R"(\player.png)"			//プレイヤーの画像ファイルの名前
#define ENEMY1_IMG_NAME		R"(\enemy1.png)"			//敵キャラ1の画像ファイルの名前
#define ENEMY2_IMG_NAME		R"(\enemy2.png)"			//敵キャラ2の画像ファイルの名前
#define ENEMY3_IMG_NAME		R"(\enemy3.png)"			//敵キャラ3の画像ファイルの名前
#define ENEMY4_IMG_NAME		R"(\enemy4.png)"			//敵キャラ4の画像ファイルの名前
#define ENEMY5_IMG_NAME		R"(\enemy5.png)"			//敵キャラ5の画像ファイルの名前
#define ENEMY6_IMG_NAME		R"(\enemy6.png)"			//敵キャラ6の画像ファイルの名前

#define IMG_NAME_TITLE		R"(\title.jpg)"				//タイトル画面の背景画像の名前
#define IMG_NAME_PLAY		R"(\play.jpg)"				//プレイ画面の背景画像の名前
#define IMG_NAME_RANKING	R"(\ranking.jpg)"			//ランキング画面の背景画像の名前

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
	RANKING_BACK	//ランキング画面
};

using std::string;

//########## クラスの定義 ##########
class Image
{
private:
	string FilePath;	//パス
	string FileName;	//名前

	int Handle;			//ハンドル

	int X;				//X
	int Y;				//Y
	int CenterX;		//中央X
	int CenterY;		//中央Y
	int Width;			//幅
	int Height;			//高さ

	bool IsLoad;		//読み込めたか？
	bool IsDraw;		//描画してよいか
	bool IsFade;		//フェードアウトするか
	bool FadeEnd;		//フェードエフェクトが終わったか

public:
	Image(const char *,const char *);	//コンストラクタ
	Image();							//コンストラクタ
	virtual ~Image();					//デストラクタ

	bool Load(const char*, const char*);//読み込み

	string GetFileName(void);	//名前を取得

	void SetInit(void);				//初期設定
	void SetPos(int, int);			//描画位置設定

	int GetCenterX();				//中央X取得
	int GetCenterY();				//中央Y取得
	int GetWidth();					//幅を取得
	int GetHeight();				//高さを取得

	bool GetIsLoad(void);			//読み込めた？
	bool GetIsDraw();				//描画してよいか取得
	void SetIsDraw(bool);			//描画してよいか設定

	void Draw();					//画像を描画
	void Draw(int, int);			//画像を描画（指定された位置）
	void DrawCenter();				//画像を描画（中央）
	void DrawCenterY(int);			//画像を描画（上下中央）
	void DrawCenterX(int);			//画像を描画（左右中央）

	void SetIsFade(bool);			//フェードアウトするか設定
	bool GetFadeEnd();				//フェードエフェクトが終了しているか取得

};

