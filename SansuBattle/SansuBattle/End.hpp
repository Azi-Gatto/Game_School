//End.hpp
//エンド画面の処理

#pragma once

//############# ヘッダファイル読み込み ##############
#include "Scene.hpp"

//############# マクロ定義 ##############

//############# クラス定義 ##############
class End : public Scene	//Sceneを継承
{
private:

public:

	End();			//コンストラクタ
	~End();			//デストラクタ

	void SetInit() override;	//初期設定
	void Run() override;		//エンド画面の処理

};
