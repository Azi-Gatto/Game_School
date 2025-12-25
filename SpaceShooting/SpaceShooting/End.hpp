//End.hpp
//エンド画面の処理

#pragma once

//############# ヘッダファイル読み込み ##############
#include "Scene.hpp"
#include "Enemy.hpp"

//############# マクロ定義 ##############
#define RESULT_TEXT	"%d機撃ち落とした!!!"		//結果表示のテキスト

//############# クラス定義 ##############
class End : public Scene	//Sceneを継承
{
private:

public:

	End();			//コンストラクタ
	~End();			//デストラクタ

	void SetInit() override;	//初期設定
	void PlayScene() override;	//エンド画面の処理

};
