//Play.cpp
//プレイ画面の処理

//################# ヘッダファイル読み込み #################
#include "Play.hpp"

//################ クラス定義 ################

//コンストラクタ
Play::Play()
{

	//画像関係
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_PLAY)) { IsLoad = false; return; }	//背景画像読み込み
	circle = new Image(IMG_UI_DIR, IMG_CIRCLE_NAME);		//円の画像読み込み
	if (!circle->GetIsLoad()) { IsLoad = false; return; }	//読み込み失敗
	bord = new Image(IMG_UI_DIR, IMG_KOKUBAN_NAME);			//黒板の画像読み込み
	if (!bord->GetIsLoad()) { IsLoad = false; return; }		//読み込み失敗

	//BGM
	bgm.front()->Load(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM);				//BGM追加（+）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DIF));			//BGM追加（-）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_PRO));			//BGM追加（*）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DEA));			//BGM追加（/）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF));		//BGM追加（+-）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_PRO_DEA));		//BGM追加（*/）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_PRO));		//BGM追加（+*）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DEA));		//BGM追加（+/）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DIF_PRO));		//BGM追加（-*）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF_PRO));	//BGM追加（+-*）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF_DEA));	//BGM追加（+-/）
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_ALL));			//BGM追加（ + -*/ ）
	for (auto b : bgm) { if (!b->GetIsLoad()) { IsLoad = false; return; } }	//読み込み失敗

	se.push_back(new Music(MUSIC_DIR_SE, SE_NAME_FALSE));				//不正解のSE追加
	se.push_back(new Music(MUSIC_DIR_SE, SE_NAME_PL_DAMEGE));			//プレイヤーがダメージを受けたときのSE追加
	for (auto s : se) { if (!s->GetIsLoad()) { IsLoad = false; return; } }	//読み込み失敗

	//********************* キャラクター ******************************
	//プレイヤー
	player = new Player();	//プレイヤー生成

	//敵
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY01));	//敵1体目生成
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY02));	//敵2体目生成
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY03));	//敵3体目生成

	//時間
	limit = new Time(LIMIT_TIME);		//制限時間

	NowPhase = PHASE_OPERATION;	//最初は操作フェーズからスタート
	IsOperation = true;			//キー操作できる

	IsLoad = true;	//読み込み成功

}

//デストラクタ
Play::~Play()
{
	delete player;		//player破棄
	delete limit;		//limit破棄
	delete circle;		//circle破棄
	delete bord;		//bord破棄
	
	//敵
	for (auto e : enemy) { delete e; }	//enemy破棄
	vector<Enemy*> v;
	v.swap(enemy);	

	//SE
	for (auto s : se) { delete s; }		//se破棄
	vector<Music*> v2;
	v2.swap(se);

	//データ
	for (auto d : data) { delete d; }	//data破棄
	vector<Data*> v3;
	v3.swap(data);
}

//初期設定
void Play::SetInit()
{

	font.at(HDL_NR)->Chenge();	//フォントハンドルをノーマルに変更

	back->SetInit();	//背景画像初期設定
	circle->SetInit();	//円の画像
	bord->SetInit();	//黒板の画像
	for (auto b : bgm) { b->SetInit(DX_PLAYTYPE_LOOP, VOL_DEF); }	//BGM初期設定
	for (auto s : se) { s->SetInit(DX_PLAYTYPE_BACK, VOL_DEF); }	//SE初期設定

	//プレイヤー
	if (!player->SetInit()) { IsLoad = false; return; }	//初期設定
	//敵
	for (auto e : enemy)
	{
		if (!e->SetInit()) { IsLoad = false; return; }	//初期設定
	}
}

//プレイ画面の処理
void Play::Run()
{

	Start();	//シーンが変わるごとに1回だけ行う処理

	bgm.at(GameMode)->Play();			//BGMを流す
	back->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	Battle();					//戦闘の処理

}

//シーンが変わるごとに1回だけ行う処理
void Play::Start()
{
	if (!start)	//処理を行っていなければ
	{
		Score::Reset();											//スコアリセット
		quesiton.push_back(new Question(GameMode, GameLevel));	//問題を作成
		player->Init();											//プレイヤー初期化
		for (auto e : enemy) { e->Init(); }						//敵初期化
		Save::Load(&data,GameMode);								//データ読み込み
		limit->SetTime();										//制限時間の計測開始
		start = true;											//処理を行った

	}
}

//戦闘の処理
void Play::Battle()
{
	static bool end = false;	//戦闘終了したか

	enemy.at(Enemy::GetNowEnemyNum())->Draw();	//敵キャラ描画
	player->Draw();								//プレイヤー（HP）描画

	bord->Draw(GAME_LEFT, SCORE_Y);		//黒板の画像を描画
	RECT rect = { GAME_LEFT,SCORE_Y,GAME_LEFT + bord->GetWidth(), SCORE_Y + bord->GetHeight() };	//黒板の領域を取得
	font.at(HDL_MINI)->Chenge();		//フォント変更
	Score::DrawCenter(rect);			//現在のスコア描画
	font.at(HDL_NR)->Chenge();			//フォント変更

	switch (NowPhase)		//フェーズごとに分岐
	{

	case PHASE_EFFECT:		//エフェクトフェーズの時

		if (enemy.at(Enemy::GetNowEnemyNum())->GetIsEffectEnd())			//エフェクト終了したら
		{
			enemy.at(Enemy::GetNowEnemyNum())->SendDamege();				//敵にダメージを与える
			player->InpReset();												//入力情報リセット
			quesiton.push_back(new Question(GameMode, GameLevel));			//次の問題を生成
			Score::AddScore(GameMode, GameLevel, limit->GetElapsedTime());	//スコア加算
			if (!enemy.at(Enemy::GetNowEnemyNum())->GetIsArive())			//敵が死んでいるときは
			{
				enemy.at(Enemy::GetNowEnemyNum())->Kill();	//敵を殺す
			}
			else	//敵が生きているときは
			{
				NowPhase = PHASE_OPERATION;	//操作フェーズ
			}
			limit->SetTime();												//制限時間の再計測開始
		}

		if (enemy.at(Enemy::GetNowEnemyNum())->GetFadeEnd())	//フェードアウト終了したら
		{
			Enemy::NextEnemy();			//次の敵へ
			if (Enemy::GetAllEnemyKilled())	//全ての敵を倒したら
			{
				end = true;	//バトル終了
			}
			else	//倒していなかったら
			{
				NowPhase = PHASE_OPERATION;	//操作フェーズへ
			}
		}


		break;				//エフェクトフェーズの時ここまで

	case PHASE_OPERATION:	//操作フェーズの時

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, PHASE_TOUKA_PERCENT * TOUKA_MAX_VALUE);	//透過させる
		DrawBox(GAME_LEFT, GAME_TOP, GAME_LEFT + GAME_WIDTH, GAME_TOP + GAME_HEIGHT, COLOR_GRAY,true);	//画面全体を薄く灰色にする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);										//透過をやめる

		bord->DrawCenter();				//画面中央に黒板の画像を描画
		player->DrawInputNum();			//入力中の値を描画

		//*************** 問題の描画 *******************
		font.at(HDL_MINI)->Chenge();		//フォントを変更
		quesiton.back()->DrawQuestion();	//問題描画
		font.at(HDL_NR)->Chenge();			//フォントを変更

		if (player->CheckInputKey())	//キー入力が完了したら
		{
			if (quesiton.back()->JudgAnser(player->GetAns()))	//プレイヤーの回答が正解だったら
			{
				enemy.at(Enemy::GetNowEnemyNum())->SetDamegeFlg(true);		//敵にダメージフラグを立てる
				NowPhase = PHASE_EFFECT;//エフェクトフェーズに変更
				IsOperation = false;	//操作不可に
			}
			else		//不正解だったら
			{
				limit->MinusLimitTime(MISS_MINUS_TIME);	//制限時間を減らす
				se.at(SE_FALSE)->Play();				//不正解の音を再生
				player->InpReset();						//入力情報リセット
			}

		}

		break;				//操作フェーズの時ここまで

	default:
		break;
	}


	//************* 制限時間の描画 *******************
	circle->Draw(CIRCLE_X, CIRCLE_Y);	//円の画像描画
	limit->UpdateLimitTime();			//制限時間の更新
	font.at(HDL_NR_POP)->Chenge();		//フォント変更
	limit->DrawLimitTime(LIMIT_DRAW_X, LIMIT_DRAW_Y);	//制限時間描画
	font.at(HDL_NR)->Chenge();			//フォントを変更

	if (limit->GetIsLimit())	//制限時間を超えたら
	{
		se.at(SE_DAMEGE)->Play();	//ダメージの効果音を再生
		player->SendDamege();		//プレイヤーにダメージを与える
		if (!player->GetIsArive())	//プレイヤーが死んだら
		{
			end = true;	//バトル終了
		}
		else	//死んでいなければ
		{
			quesiton.push_back(new Question(GameMode, GameLevel));	//次の問題を作成
			limit->SetTime();		//制限時間の再計測開始
		}
	}

	if (end)	//バトルが終了したら
	{
		if (FadeOut())	//フェードアウトが終了したら
		{
			DrawBox(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT, COLOR_BLACK, true);	//黒い四角を描画
			data.push_back(new Data(Score::GetScore()));	//データを追加
			Save::Sort(&data);					//ソート
			Save::DataSave(data, GameMode);		//セーブ
			start = false;						//次に備えてstartフラグをリセット
			end = false;						//エンドフラグリセット
			bgm.at(GameMode)->Stop();			//BGMを止める
			NowScene = SCENE_RANKING;			//ランキング画面へ
		}
	}
}
