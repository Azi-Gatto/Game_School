//Load.hpp
//読み込み画面のクラス（Sceneクラスから派生）

#pragma once

//################### ヘッダファイル読み込み #################
#include "Scene.hpp"

//################### マクロ定義 ###################
#define TEXT_DISCRIPTION	"左ClickでStart!"
#define TEXT_LOAD_MSG		"準備中…"	//読み込み中のメッセージ

//座標関係
#define TEXT_DISCRIPTION_X	30					//説明のテキスト描画X位置
#define TEXT_DISCRIPTION_Y	30					//説明のテキスト描画Y位置

//################### クラス定義 ###################
class Load : public Scene	//Sceneクラスを継承
{
private:

	bool IsGameStart;	//ゲームスタートできるか
	static bool LoadEnd;//読み込みが終わったか

public:

	Load();	//コンストラクタ 
	~Load();				//デストラクタ

	void SetInit() override;	//初期設定
	void Run() override;		//ロード画面の処理
	static bool IsLoadEnd();	//読み込みが終わったか取得

};
