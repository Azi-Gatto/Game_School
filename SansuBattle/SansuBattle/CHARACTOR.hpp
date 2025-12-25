//CHARACTOR.hpp
//キャラクタークラス

#pragma once

//###################### ヘッダファイル読み込み ###################
#include "Global.hpp"
#include "KeyDown.hpp"
#include "Image.hpp"
#include <vector>

//###################### マクロ定義 #######################
#define HP_INIT_VALUE	5	//HPの初期値

using std::vector;

//###################### クラス定義 #######################
class Charactor
{
protected:

	Image* hp_img;				//HP画像

	int HP_X;					//HP　X位置
	int HP_Y;					//HP  Y位置

	int HP;						//HP
	bool reverse;				//反転描画するか

	bool IsArive;				//生きているか
	bool KillFlg;				//キルフラグ

public:

	Charactor();				//コンストラクタ
	~Charactor();				//デストラクタ

	virtual void Init();		//初期化
	virtual bool SetInit();		//初期設定

	bool GetIsArive();			//生きているか取得

	void SendDamege();			//ダメージを与える
	void Kill();				//キャラを殺す
	virtual void Draw();		//描画
	int GetHp();				//HP取得

};

