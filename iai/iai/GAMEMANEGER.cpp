//GAMEMANEGER.cpp
//ゲームのシステムを管理するクラス

//############### ヘッダファイル読み込み ################
#include "GAMEMANEGER.hpp"

//############### クラス定義 ################

//コンストラクタ
GAMEMANEGER::GAMEMANEGER()
{
	//オブジェクトの生成
	this->fps = new FPS(GAME_FPS_SPEED);	//FPSクラスのオブジェクトを生成
	this->keydown = new KEYDOWN();			//KEYDOWNクラスのオブジェクトを生成

	//メンバー変数初期化
	this->NowScene = (int)SCENE_LOAD;		//最初のシーンは、ロード画面
	this->IsLoad = false;					//読み込み、未完了
	this->StartTime = 0;					//計測開始時間初期化
	this->WaitTime = 0;						//待ち時間初期化
	this->GameStartFlg = false;				//ゲーム始まっていない。
	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//プレイシーンの現在の段階を初期化
	this->PushFlg = false;					//キー押していない

	return;

}

//デストラクタ
GAMEMANEGER::~GAMEMANEGER()
{
	//オブジェクトの破棄
	delete this->fps;		//fps破棄
	delete this->keydown;	//keydown破棄
	delete this->back;		//back破棄
	delete this->mark;		//mark破棄
	delete this->player;	//player破棄
	delete this->enemy;		//enemy破棄
	delete this->se;		//se破棄
	delete this->bgm;		//bgm破棄
	delete this->effect;	//effect破棄
	delete this->font;		//font破棄
	delete this->save;		//save破棄

	return;

}

//ゲーム内で使用するデータの読み込み処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GAMEMANEGER::Load()
{

	//フォント関係
	this->font = new FONT(FONT_DIR, FONT_FILE_NAME, FONT_NAME);		//フォントを管理するオブジェクトを生成
	if (this->font->GetIsLoad() == false) { return false; }			//読み込み失敗

	//画像関係
	//背景画像
	this->back = new IMAGE(IMG_DIR_BACK, IMG_NAME_TITLE);	//背景画像を管理するオブジェクトを生成(タイトル画面の画像を読み込む)
	if (this->back->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->back->AddImage(IMG_DIR_BACK, IMG_NAME_PLAY) == false) { return false; }		//背景画像追加(プレイ画面)
	if (this->back->AddImage(IMG_DIR_BACK, IMG_NAME_END) == false) { return false; }		//背景画像追加(エンド画面)
	//マーク画像
	this->mark = new IMAGE(IMG_DIR_MARK, IMG_NAME_MARK);	//マーク画像を生成
	if (this->mark->GetIsLoad() == false) { return false; }	//読み込み失敗
	this->mark->SetIsDraw(false);							//最初は描画してはいけない

	//プレイヤー関係
	this->player = new PLAYER(IMG_DIR_PLAYER, IMG_NAME_PLAYER);		//プレイヤー生成
	if (this->player->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->player->AddImage(IMG_DIR_PLAYER, IMG_NAME_PLAYER_ACT) == false) { return false; }	//画像追加
	//位置調整
	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//プレイヤーの描画位置を初期化

	//敵関係
	this->enemy = new ENEMY(IMG_DIR_ENEMY, IMG_NAME_ENEMY);		//敵生成
	if (this->enemy->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->enemy->AddImage(IMG_DIR_ENEMY, IMG_NAME_ENEMY_ACT) == false) { return false; }	//画像追加
	//位置調整
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//敵の描画位置を初期化

	//音関係
	//SE
	this->se = new MUSIC(MUSIC_DIR_SE, SE_NAME_GAMESTART);		//SEを管理するオブジェクトを生成
	if (this->se->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_GAMEOVER) == false) { return false; }	//ゲームオーバーの音を追加
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_TEXT_SE) == false) { return false; }	//テキスト表示の音を追加
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_SLASH) == false) { return false; }		//斬る音を追加

	//BGM
	this->bgm = new MUSIC(MUSIC_DIR_BGM, BGM_NAME_TITLE_BGM);	//BGMを管理するオブジェクトを生成
	if (this->bgm->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->bgm->Add(MUSIC_DIR_BGM, BGM_NAME_END_BGM) == false) { return false; }	//エンド画面のBGM追加
	this->bgm->ChengePlayType(DX_PLAYTYPE_LOOP);				//再生方法をループ再生に変更
	this->bgm->ChengeVolume(50.0, (int)BGM_TYPE_TITLE);			//タイトルbgmの音量を50%に変更
	this->bgm->ChengeVolume(50.0, (int)BGM_TYPE_END);			//エンドbgmの音量を50%に変更

	//音量変更
	this->se->ChengeVolume(50.0, (int)SE_TYPE_GAMESTART);	//ゲームスタートの音量を50%に変更
	this->se->ChengeVolume(50.0, (int)SE_TYPE_RESULT);	//ゲームオーバーの音量を50%に変更

	//エフェクト関係
	this->effect = new EFFECT(EFFECT_DIR, EFFECT_NAME_SLASH, EFFECT_SLASH_ALL_CNT, EFFECT_SLASH_YOKO_CNT, EFFECT_SLASH_TATE_CNT, EFFECT_SLASH_WIDTH, EFFECT_SLASH_HEIGHT, EFFECT_SLASH_SPEED, false, this->fps->Getvalue());
	if (this->effect->GetIsLoad() == false) { return false; }	//読み込み失敗

	//セーブデータ関係
	this->save = new SAVEDATA();	//セーブデータを管理するオブジェクトを生成
	struct stat statbuf;			//ファイルの存在確認に使用
	std::string filepath = SAVEDATA_DIR;
	filepath += SAVEDATA_NAME;
	if (stat(filepath.c_str(), &statbuf) == 0)		//セーブデータ用のファイルが作成されている場合
	{
		if (this->save->Load() == false) { return false; }	//セーブデータ読み込み
	}

	return true;	//読み込み成功
}

//画像などのサイズを取得し、設定する
void GAMEMANEGER::SetSize()
{
	this->back->SetSize();			//背景画像、サイズ設定
	this->mark->SetSize();			//マーク画像サイズ設定
	this->effect->SetSize();		//エフェクトのサイズ設定
	return;
}

//初期設定をする
void GAMEMANEGER::SetInit()
{

	this->SetSize();			//サイズ設定

	this->player->SetInit();	//プレイヤーの初期設定
	this->enemy->SetInit();		//敵の初期設定

}

//ゲームのメインループ
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GAMEMANEGER::GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	this->keydown->KeyDownUpdate();	//キーの入力状態を更新する

	this->fps->Update();		//FPSの処理[更新]

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	this->ProcesScene();		//各シーンの処理

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	//this->fps->Draw(0, 0);		//FPS描画

	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	this->fps->Wait();			//FPSの処理[待つ]

	return true;				//正常

}

//各シーンの処理
void GAMEMANEGER::ProcesScene()
{
	switch (this->NowScene)		//現在のシーンの描画処理を実行
	{

	case (int)SCENE_LOAD:	//ロード画面のとき

		this->Draw_Scene_Load();	//ロード画面の描画処理

		this->Scene_Load();			//ロード画面の処理

		break;				//ロード画面のときここまで

	case (int)SCENE_TITLE:	//タイトル画面のとき

		this->Draw_Scene_Title();	//描画

		this->Scene_Title();		//処理

		break;				//タイトル画面のときここまで

	case (int)SCENE_PLAY:	//プレイ画面のとき

		this->Draw_Scene_Play();	//描画

		this->Scene_Play();		//処理

		break;				//プレイ画面のときここまで

	case (int)SCENE_END:	//エンド画面のとき

		this->Draw_Scene_End();	//描画

		this->Scene_End();		//処理

		break;				//エンド画面のときここまで

	default:
		break;
	}

	return;	

}

//***************************** シーン毎の処理 ********************************
//ロード画面の処理
void GAMEMANEGER::Scene_Load()
{
	if (this->IsLoad)	//読み込みが完了していたら
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			this->NowScene = (int)SCENE_TITLE;	//タイトル画面へ
		}
	}

	if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
	{

		SetUseASyncLoadFlag(FALSE);	//同期読み込みに設定

		this->SetInit();			//初期設定

		this->IsLoad = true;		//読み込み完了
	}

	return;		
}

//ロード画面の描画処理
void GAMEMANEGER::Draw_Scene_Load()
{
	this->font->SetSize(FONTSIZE_MINI);		//フォントサイズを小さくする
	DrawString(GAME_LEFT, GAME_TOP, SETUMEI_TEXT, COLOR_WHITE);
	this->font->SetSize(DEFAULT_FONTSIZE);	//フォントサイズを大きくする

	if (IsLoad)	//読み込みが完了したら
	{
		this->DrawTextCenter(PUSH_TEXT, COLOR_WHITE);					//エンターキーを押す、のテキストを描画
	}
	else		//完了していなければ
	{
		this->DrawTextCenter(LOAD_TEXT, COLOR_WHITE);					//読み込み中のテキストを描画
	}

	return;
}

//タイトル画面の処理
void GAMEMANEGER::Scene_Title()
{

	this->back->ChengeImage((int)TITLE_BACK);	//背景画像変更

	this->bgm->Play((int)BGM_TYPE_TITLE);		//bgmを再生

	this->player->ResetWinNum();		//勝ち数をリセット

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->bgm->Stop((int)BGM_TYPE_TITLE);	//BGMを止める
		this->NowScene = (int)SCENE_PLAY;	//プレイ画面へ
	}

	return;
}

//タイトル画面の描画処理
void GAMEMANEGER::Draw_Scene_Title()
{

	this->back->Draw(GAME_LEFT,GAME_TOP);	//背景描画

	this->DrawTextCenter(TITLE_TEXT_Y, TITLE_TEXT, COLOR_WHITE);	//テキスト描画

	return;
}

//プレイ画面の処理
void GAMEMANEGER::Scene_Play()
{

	this->back->ChengeImage((int)PLAY_BACK);	//背景画像変更

	switch (this->Play_NowStage)		//現在の段階ごとに処理を分ける
	{

	case (int)PLAY_STAGE_TEXT_DRAW:		//テキスト表示段階のとき

		this->PlayStage_DrawText();		//テキスト表示段階の処理

		break;			//テキスト表示段階ここまで

	case (int)PLAY_STAGE_MAIN:		//ゲームプレイ中のとき

		this->PlayStage_Main();		//ゲームプレイ中のときの処理

		break;		//ゲームプレイ中のときここまで

	case (int)PLAY_STAGE_RESULT:	//結果表示のとき

		this->PlayStage_Result();	//結果表示段階の処理

		break;		//結果表示ここまで

	default:
		break;
	}

	return;
}

//プレイ画面の描画処理
void GAMEMANEGER::Draw_Scene_Play()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);	//背景画像描画

	this->player->Draw();		//プレイヤー描画
	this->enemy->Draw();		//敵描画

	return;
}

//エンド画面の処理
void GAMEMANEGER::Scene_End()
{

	this->back->ChengeImage((int)END_BACK);	//背景画像変更

	this->bgm->Play((int)BGM_TYPE_END);		//bgmを再生

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->bgm->Stop((int)BGM_TYPE_END);	//BGMを止める
		this->NowScene = (int)SCENE_TITLE;	//タイトル画面へ
	}

	return;
}

//エンド画面の描画処理
void GAMEMANEGER::Draw_Scene_End()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);		//背景描画
	this->font->SetSize(FONTSIZE_DRAW_RANKING);	//フォントサイズ変更
	this->save->Draw();							//ランキング描画
	this->font->SetSize(DEFAULT_FONTSIZE);		//フォントサイズを元の大きさに

	return;
}


//******************** プレイ画面で使用する処理関係 ***********************
//スタート時間まで待つ
bool GAMEMANEGER::WaitStartTime()
{

	if ((GetNowCount() - this->StartTime) / 1000 < this->WaitTime)	//待ち時間が過ぎていなければ
	{
		return false;
	}
	else 			//待ち時間が過ぎたら
	{
		return true;
	}
}

//プレイ画面で使用するものをリセット
void GAMEMANEGER::PlayReset()
{

	this->player->SetIsDraw(true);			//プレイヤーを描画する
	this->enemy->SetIsDraw(true);			//敵を描画する

	this->player->ChengeImage((int)PLAYER_IMG_NORMAL);		//描画するプレイヤーの画像を通常時の画像に変更
	this->enemy->ChengeImage((int)ENEMY_IMG_NORMAL);		//描画する敵の画像を通常時の画像に変更

	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//プレイヤーの描画位置を初期化
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//敵の描画位置を初期化

	this->mark->SetIsDraw(false);			//マークを描画してはいけない
	this->GameStartFlg = false;				//ゲームスタートしない

	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//プレイシーンの現在の段階を初期化

	this->se->PlayReset();	//効果音の再生状態をリセット

	this->PushFlg = false;	//キーを押していない

	this->effect->ResetIsAnime((int)EFFECT_SLASH);	//エフェクトの再生状態をリセット

	this->StartTime = GetNowCount();	//計測開始時間取得
	this->WaitTime = GetRand((GAME_START_WAITTIME_MAX / 2)) + GAME_START_WAITTIME_MIN;	//待ち時間を設定

	return;

}

//どちらが勝ったか判定
void GAMEMANEGER::Judg()
{
	//キーを押すまでにかかった時間を基に、どちらが勝ったか判定する
	if (this->player->GetPushTime() < enemy->GetSpeed())		//押すのにかかった時間が、敵のスピードより速かったら
	{
		this->player->IncreaseWinNum();					//勝ち数を増やす
		this->enemy->SpeedUp();							//敵の速度を早くする
		this->enemy->SetFade(true);						//敵をフェードアウト
		this->player->SetResult((int)RESULT_WIN);		//結果を設定(勝利)
	}
	else if (this->player->GetPushTime() > enemy->GetSpeed())		//敵より遅かったら
	{
		this->player->SetResult((int)RESULT_LOSE);		//結果を設定(敗北)
		this->player->SetFade(true);					//自分をフェードアウト
		this->enemy->SpeedReset();						//速さをリセット
	}
	else		//引き分けだったら
	{
		this->player->SetResult((int)RESULT_DRAW);		//結果を設定(引き分け)
	}

	return;

}

//プレイ段階、テキスト表示のときの処理
void GAMEMANEGER::PlayStage_DrawText()
{

	this->PlayReset();	//プレイ関係リセット

	this->se->Play((int)SE_TYPE_GAMESTART);		//ゲームスタートのSEを鳴らす

	this->effect->SetIsFadeout(true);	//フェードアウトを行う

	if (this->effect->FadeOut(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT))	//フェードアウト処理が終わったら
	{
		this->Play_NowStage = (int)PLAY_STAGE_MAIN;	//ゲームプレイ段階へ
	}


	return;
}

//プレイ段階、ゲーム中のときの処理
void GAMEMANEGER::PlayStage_Main()
{

	DrawBox(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT,COLOR_BLACK,TRUE);	//真っ暗な画面	

	this->mark->DrawCenter(GAME_WIDTH, MARK_DRAW_Y);	//マーク描画

	if (this->GameStartFlg)	//ゲームが始まったら
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			this->PushFlg = true;	//キーを押した
		}

	}
	else					//ゲームが始まっていなかったら
	{

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{

			this->se->Stop();		//効果音の再生を止める

			this->player->SetResult((int)RESULT_OTETUKI);	//結果をお手付きに設定

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//結果表示段階へ

		}

		//ゲームが始まるまで待つ
		if (this->WaitStartTime())	//スタート時間になったら
		{
			this->mark->SetIsDraw(true);		//マークを描画してよい
			this->StartTime = GetNowCount();	//マークを描画し始めた時間をスタート時間に設定
			this->GameStartFlg = true;			//ゲームスタート
		}
	}

	if (this->PushFlg)		//キーを押されたら
	{
		this->player->ChengeImage((int)PLAYER_IMG_ACT);				//描画するプレイヤーの画像をアクション後の画像に変更
		this->player->SetImagePos(PLAYER_AFTER_X, PLAYER_AFTER_Y);	//描画する位置をアクション後の位置に変更
		this->enemy->ChengeImage((int)ENEMY_IMG_ACT);				//描画する敵の画像をアクション後の画像に変更
		this->enemy->SetImagePos(ENEMY_AFTER_X, ENEMY_AFTER_Y);		//描画位置をアクション後の位置に変更

		this->mark->SetIsDraw(false);	//マーク非表示

		this->player->SetPushTime((GetNowCount() - this->StartTime));	//押すまでにかかった時間を設定

		this->effect->Draw(GAME_LEFT, GAME_TOP, (int)EFFECT_SLASH);	//エフェクト描画

		this->se->PlayOne((int)SE_TYPE_SLASH);	//斬る効果音を再生

		if (this->effect->GetIsDrawEnd())	//エフェクト描画が終わったら
		{

			this->Judg();	//どちらが勝ったか判定

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//結果表示段階へ
		}

	}

	return;

}

//プレイ段階、結果表示のときの処理
void GAMEMANEGER::PlayStage_Result()
{

	if (this->player->GetFadeEnd() ||		//自分のフェードエフェクトが終わったか、
		this->enemy->GetFadeEnd() ||		//敵のフェードエフェクトが終わったか、
		this->player->GetResult()==(int)RESULT_OTETUKI)	//結果がお手付きだったら		
	{

		//結果表示処理開始

		if (this->player->GetResult() != (int)RESULT_OTETUKI)	//お手付き以外のときは
		{
			this->se->PlayOne((int)SE_TYPE_RESULT);		//結果表示の音を鳴らす
		}
		else	//お手付きのときは
		{
			this->se->PlayOne((int)SE_TYPE_TEXT);	//テキスト表示の音を鳴らす
		}

		//結果毎に処理を分岐
		switch (this->player->GetResult())
		{

		case (int)RESULT_WIN:		//プレイヤーが勝った時

			this->DrawTextCenter(RESULT_TEXT_Y, RESULT_WIN_TEXT);		//勝利文字描画

			this->DrawNumTextCenter(DRAW_WIN_NUM_Y, WIN_NUM_DRAW_TEXT, this->player->GetWinNum());	//勝ち数を描画

			break;		//プレイヤーが勝った時ここまで

		case (int)RESULT_LOSE:		//プレイヤーが負けたとき

			this->DrawTextCenter(RESULT_TEXT_Y, RESULT_LOSE_TEXT);	//敗北文字描画

			break;		//プレイヤーが負けたときここまで

		case (int)RESULT_DRAW:		//引き分けのとき

			this->DrawTextCenter(RESULT_TEXT_Y, RESLUT_DRAW_TEXT);	//引き分け文字描画

			break;		//引き分けのときここまで

		case (int)RESULT_OTETUKI:		//お手付きのとき

			this->DrawTextCenter(RESULT_TEXT_Y, RESULT_OTETUKI_TEXT);	//お手付き文字描画

			break;		//お手付きのときここまで

		default:
			break;
		}

		//キー入力処理
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{

			this->se->Stop();	//効果音の再生を止める

			this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//テキスト表示段階へ

			if (this->player->GetResult() == (int)RESULT_LOSE)	//負けたときは
			{

				this->save->Add(this->player->GetWinNum());	//セーブデータ追加

				this->save->Sort();							//ソート処理

				this->NowScene = (int)SCENE_END;			//エンド画面へ

			}

		}

	}

	return;
}


//渡された文字列を画面中央に描画する(高さは自分で指定する)
//引数：int：描画Y位置
//引数：const char *：描画する文字列
//引数：unsigned int：描画色：指定しない場合は、黒
void GAMEMANEGER::DrawTextCenter(int y,const char *text,unsigned int color)
{
	int Strlen = 0;		//文字列の長さ取得用
	int Width = 0;		//文字列の幅取得用

	Strlen = strlen(text);	//文字列長さを取得
	Width = GetDrawStringWidth(text, Strlen);	//横幅取得

	DrawString((GAME_WIDTH / 2) - (Width / 2), y, text, color);		//文字列を描画

	return;

}

//渡された文字列を画面中央に描画する(上下左右、中央)
//引数：const char *：描画する文字列
//引数：unsigned int：描画色：指定しない場合は、黒
void GAMEMANEGER::DrawTextCenter(const char* text, unsigned int color)
{
	int Strlen = 0;		//文字列の長さ取得用
	int Width = 0;		//文字列の幅取得用
	int Height = 0;		//文字列の高さ取得用

	Strlen = strlen(text);	//文字列長さを取得
	Width = GetDrawStringWidth(text, Strlen);	//横幅取得
	Height = GetFontSize();						//高さ取得

	DrawString((GAME_WIDTH / 2) - (Width / 2), (GAME_HEIGHT / 2) - (Height / 2), text, color);		//文字列を描画

	return;

}

//書式付き(数字)文字列を中央に描画する(高さは自分で指定する)
//引数：int：描画Y位置
//引数：const char *：描画する文字列
//引数：int：書式指定子で描画する数字
void GAMEMANEGER::DrawNumTextCenter(int y, const char *text, int num)
{
	std::string draw_text = text;										//描画文字列
	int keypos = draw_text.find(FORMAT_KEY_WORD);						//置換開始位置を取得
	draw_text.replace(keypos, FORMAT_REPLACE_NUM, std::to_string(num));	//置換

	int Strlen = 0;		//文字列の長さ取得用
	int Width = 0;		//文字列の幅取得用

	Strlen = strlen(draw_text.c_str());						//文字列長さを取得
	Width = GetDrawStringWidth(draw_text.c_str(), Strlen);	//横幅取得

	DrawString((GAME_WIDTH / 2) - (Width / 2), y, draw_text.c_str(), COLOR_BLACK);		//文字列を描画

}

//セーブ
void GAMEMANEGER::Save()
{
	this->save->Save();
	return;
}