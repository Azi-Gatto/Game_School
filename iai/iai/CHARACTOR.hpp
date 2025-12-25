//CHARACTOR.hpp
//キャラクタークラス

#pragma once

//###################### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"


//###################### マクロ定義 #######################

//###################### クラス定義 #######################
class CHARACTOR
{
private:
	IMAGE *image;				//画像

	int Draw_X;					//描画X位置
	int Draw_Y;					//描画Y位置

	bool IsArive;				//生きているか
	bool IsLoad;				//読み込めたか

public:

	CHARACTOR();				//コンストラクタ
	~CHARACTOR();				//デストラクタ

	void SetIsArive(bool);		//生きているかを設定
	void SetImage(const char*, const char*);	//画像設定
	bool AddImage(const char *, const char *);	//画像追加
	void ChengeImage(int);						//画像を変更する

	void SetImagePos(int, int);		//画像の位置を設定する

	int  GetWidth();			//横幅取得
	int GetHeight();			//高さ取得
	bool GetIsArive();			//生きているか取得
	bool GetIsLoad();			//読み込めたか取得

	void Operation(KEYDOWN *);	//操作

	void Draw();				//描画

	void SetInit();				//初期設定

	void SetFade(bool);			//フェードアウトするか設定
	void SetIsDraw(bool);		//描画するか設定
	bool GetFadeEnd();			//フェードエフェクトが終了したか取得

};

