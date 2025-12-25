//Ranking.hpp
//ランキング画面の処理

#pragma once

//############# ヘッダファイル読み込み ##############
#include "Scene.hpp"

//############# マクロ定義 ##############

//############# クラス定義 ##############
class Ranking : public Scene	//Sceneを継承
{
private:

public:

	Ranking();			//コンストラクタ
	~Ranking();					//デストラクタ

	void SetInit() override;	//初期設定
	bool DataLoad() override;	//データ読込
	void Run() override;	//エンド画面の処理

};
