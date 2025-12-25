//Play.cpp
//プレイ画面の処理

//################# ヘッダファイル読み込み #################
#include "Play.hpp"

//################ クラス定義 ################

//コンストラクタ
Play::Play()
{
	StartFlg = false;
}

//デストラクタ
Play::~Play()
{
	for (auto t : target)
	{
		delete t;	//target破棄
	}
	//vectorの解放
	vector<Target*> v;
	target.swap(v);

	for (auto i : tg_img)
	{
		delete i;	//tg_img破棄
	}
	//vectorの解放
	vector<Image*> v2;
	tg_img.swap(v2);
	for (auto e : tg_effect)
	{
		delete e;	//tg_effect破棄
	}
	vector<Effect*> v3;
	tg_effect.swap(v3);

	/*
	anim,se,はeffect内で破棄
	effectはtarget内で破棄している
	*/
}

//データ読込
bool Play::DataLoad()
{
	//画像関係
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_PLAY)) { return false; }	//背景画像読み込み

	//BGM
	if (!bgm->Load(MUSIC_DIR_BGM, BGM_NAME_PLAY)) { return false; }	//BGM読み込み

	//的関係
	tg_img.push_back(new Image(IMG_TOY_DIR, IMG_NAME_TOY01));		//おもちゃ01
	tg_img.push_back(new Image(IMG_TOY_DIR, IMG_NAME_TOY02));		//おもちゃ02
	tg_img.push_back(new Image(IMG_TOY_DIR, IMG_NAME_TOY03));		//おもちゃ03
	tg_img.push_back(new Image(IMG_BOMB_DIR, IMG_NAME_BOMB01));		//爆弾1
	tg_img.push_back(new Image(IMG_BOMB_DIR, IMG_NAME_BOMB02));		//爆弾2
	tg_img.push_back(new Image(IMG_BOMB_DIR, IMG_NAME_BOMB03));		//爆弾3
	tg_img.push_back(new Image(IMG_ITEM_DIR, IMG_NAME_ITEM01));		//アイテム1
	tg_img.push_back(new Image(IMG_ITEM_DIR, IMG_NAME_ITEM02));		//アイテム2

	for (auto i : tg_img)
	{
		if (!i->GetIsLoad()) { return false; }
	}
	//アニメーション系
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_SHOT, ANIM_SHOT_ALL_CNT, ANIM_SHOT_YOKO_CNT, ANIM_SHOT_TATE_CNT,
		ANIM_SHOT_WIDTH, ANIM_SHOT_HEIGHT, ANIM_SHOT_SPEED, false));	//銃撃アニメーション
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_SHOT, ANIM_SHOT_ALL_CNT, ANIM_SHOT_YOKO_CNT, ANIM_SHOT_TATE_CNT,
		ANIM_SHOT_WIDTH, ANIM_SHOT_HEIGHT, ANIM_SHOT_SPEED, false));	//銃撃アニメーション
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_SHOT, ANIM_SHOT_ALL_CNT, ANIM_SHOT_YOKO_CNT, ANIM_SHOT_TATE_CNT,
		ANIM_SHOT_WIDTH, ANIM_SHOT_HEIGHT, ANIM_SHOT_SPEED, false));	//銃撃アニメーション

	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_EXPLOSION, ANIM_EXPLOSION_ALL_CNT, ANIM_EXPLOSION_YOKO_CNT, ANIM_EXPLOSION_TATE_CNT,
		ANIM_EXPLOSION_WIDTH, ANIM_EXPLOSION_HEIGHT, ANIM_EXPLOSION_SPEED, false));	//爆発アニメーション
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_EXPLOSION, ANIM_EXPLOSION_ALL_CNT, ANIM_EXPLOSION_YOKO_CNT, ANIM_EXPLOSION_TATE_CNT,
		ANIM_EXPLOSION_WIDTH, ANIM_EXPLOSION_HEIGHT, ANIM_EXPLOSION_SPEED, false));	//爆発アニメーション
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_EXPLOSION, ANIM_EXPLOSION_ALL_CNT, ANIM_EXPLOSION_YOKO_CNT, ANIM_EXPLOSION_TATE_CNT,
		ANIM_EXPLOSION_WIDTH, ANIM_EXPLOSION_HEIGHT, ANIM_EXPLOSION_SPEED, false));	//爆発アニメーション

	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_ITEM, ANIM_ITEM_ALL_CNT, ANIM_ITEM_YOKO_CNT, ANIM_ITEM_TATE_CNT,
		ANIM_ITEM_WIDTH, ANIM_ITEM_HEIGHT, ANIM_ITEM_SPEED, false));	//アイテムアニメーション
	eff_anim.push_back(new Animation(ANIM_DIR, ANIM_NAME_ITEM, ANIM_ITEM_ALL_CNT, ANIM_ITEM_YOKO_CNT, ANIM_ITEM_TATE_CNT,
		ANIM_ITEM_WIDTH, ANIM_ITEM_HEIGHT, ANIM_ITEM_SPEED, false));	//アイテムアニメーション

	for (auto a : eff_anim)
	{
		if (!a->GetIsLoad()) { return false; }	//読み込み失敗
	}

	//効果音
	eff_se.push_back(new Music(MUSIC_DIR_EFFECT, SE_NAME_EFFECT_SHOT));			//銃撃音追加
	eff_se.push_back(new Music(MUSIC_DIR_EFFECT, SE_NAME_EFFECT_EXPLOSION));	//爆発音追加
	eff_se.push_back(new Music(MUSIC_DIR_EFFECT, SE_NAME_EFFECT_ITEM));			//アイテム音追加
	for (auto s : eff_se)
	{
		if (!s->GetIsLoad()) { return false; }	//読み込み失敗
	}

	//エフェクト
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_SHOT01),eff_se.at(EF_SE_SHOT)));				//エフェクト（銃撃）追加
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_SHOT02), eff_se.at(EF_SE_SHOT)));			//エフェクト（銃撃）追加
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_SHOT03), eff_se.at(EF_SE_SHOT)));			//エフェクト（銃撃）追加

	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_EXPLOSION01), eff_se.at(EF_SE_EXPLOSION)));	//エフェクト（爆発）追加
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_EXPLOSION02), eff_se.at(EF_SE_EXPLOSION)));	//エフェクト（爆発）追加
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_EXPLOSION03), eff_se.at(EF_SE_EXPLOSION)));	//エフェクト（爆発）追加

	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_ITEM01), eff_se.at(EF_SE_ITEM)));			//エフェクト（アイテム）追加
	tg_effect.push_back(new Effect(eff_anim.at(EF_NAME_ITEM02), eff_se.at(EF_SE_ITEM)));			//エフェクト（アイテム）追加


	//的
	target.push_back(new Toy(tg_img.at(TG_NAME_TOY01),tg_effect.at(EF_NAME_SHOT01)));			//おもちゃ01
	target.push_back(new Toy(tg_img.at(TG_NAME_TOY02), tg_effect.at(EF_NAME_SHOT02)));			//おもちゃ02
	target.push_back(new Toy(tg_img.at(TG_NAME_TOY03), tg_effect.at(EF_NAME_SHOT03)));			//おもちゃ03
	target.push_back(new Bomb(tg_img.at(TG_NAME_BOMB01), tg_effect.at(EF_NAME_EXPLOSION01)));	//爆弾1
	target.push_back(new Bomb(tg_img.at(TG_NAME_BOMB02), tg_effect.at(EF_NAME_EXPLOSION02)));	//爆弾2
	target.push_back(new Bomb(tg_img.at(TG_NAME_BOMB03), tg_effect.at(EF_NAME_EXPLOSION03)));	//爆弾3
	target.push_back(new Item(tg_img.at(TG_NAME_ITEM01), tg_effect.at(EF_NAME_ITEM01)));		//アイテム1
	target.push_back(new Item(tg_img.at(TG_NAME_ITEM02), tg_effect.at(EF_NAME_ITEM02)));		//アイテム2

	//時間系
	limit = new Time(GAME_LIMIT_TIME);	//ゲームの制限時間を管理するオブジェクトを生成

	return true;
}

//初期設定
void Play::SetInit()
{
	back->SetInit();	//背景画像初期設定
	bgm->SetInit(DX_PLAYTYPE_LOOP, 30);		//BGM初期設定
	for (auto t : target)
	{
		t->SetInit();	//初期設定
	}
}

//プレイ画面の処理
void Play::Run()
{

	Start();	//シーンが変わったら、一回だけ行う処理

	bgm->Play();	//BGMを流す
	back->Draw(GAME_LEFT, GAME_TOP);	//背景描画
	Score::Draw();	//スコア描画

	//的関係
	for (auto t : target)
	{
		t->Draw();	//的の描画

		t->UpDate();//更新

		if (t->OnClick())	//クリックされたら
		{
			t->SetEventFlg(true);	//イベントフラグ
		}

		if (t->GetEventFlg())	//イベントフラグが立っていたら
		{
			t->Event(limit);	//イベント処理
		}

	}

	//時間系
	limit->UpDate();									//更新
	limit->Draw(GAME_LIMIT_DRAW_X, GAME_LIMIT_DRAW_Y);	//描画
	if (limit->GetIsLimit())//制限時間を過ぎたら
	{
		StartFlg = false;
		bgm->Stop();			//BGMを止める
		data.push_back(new Data(Score::GetScore()));	//データを追加
		Save::Sort(&data);		//ソート
		Save::DataSave(data);	//セーブ
		NowScene = SCENE_RANKING;	//エンド画面へ
	}

}

//シーンが変わって1回目だけ行う処理
void Play::Start()
{
	if (!StartFlg)
	{
		Score::Reset();			//スコアリセット
		limit->StartCount();	//制限時間のカウントスタート
		StartFlg = true;
	}
}
