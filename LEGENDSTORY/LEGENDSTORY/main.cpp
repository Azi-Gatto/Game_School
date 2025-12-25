/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				　 */

//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "FONT.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MUSIC.hpp"
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"
#include "EFFECT.hpp"
#include "MSG.hpp"
#include "ITEM.hpp"
#include "SELECT.hpp"
#include "LIST_MGC.hpp"
#include "LIST_WEAPON.hpp"
#include "LIST_ARMOR.hpp"
#include "LIST_ITEM.hpp"
#include "NPC.hpp"
#include <direct.h>
#include <sys/stat.h>

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成

IMAGE *title;						//タイトル画像
IMAGE *back;						//背景画像
IMAGE *back_battle;					//戦闘画面の背景画像
IMAGE *description;						//説明画像
IMAGE *boss_mapimage;				//マップに描画するボスの画像

MUSIC *bgm;							//BGM
MUSIC *bt_se;						//戦闘で使用するSE
MUSIC *sys_se;						//システムのSE

EFFECT *Magic_effect;				//魔法エフェクト
EFFECT *Atack_effect;				//攻撃エフェクト
EFFECT *Enemy_Atk_effect;			//敵攻撃エフェクト
EFFECT *Boss_Atk_effect;			//ボス攻撃エフェクト

FONT *font;							//フォント
UI *ui;								//UI
DATA *data;							//データ
MESSAGE *bt_msg[BT_MSG_KIND];		//戦闘画面のメッセージ

PLAYER *player;						//主人公

ENEMY *enemy[ENEMY_KIND];			//敵

NPC *npc;							//NPC

MAP *mapdata[DRAW_MAP_KIND][MAP_DATA_KIND];		//マップデータ

//選択肢関係
SELECT *Title_select;	//タイトル画面の選択肢
SELECT *End_select;		//エンド画面の選択肢

//一覧関係
LIST_MGC *mgc_list;			//魔法一覧
LIST_WEAPON *weapon_list;	//武器一覧
LIST_ARMOR *armor_list;		//防具一覧
LIST_ITEM *item_list;		//アイテム一覧

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン
int GameSceneBefor;							//前のゲームシーン
int GameSceneNext;							//次のゲームシーン

int BattleStageNow = (int)WAIT_ACT;	//バトルシーンの現在の状態

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//マップの種類
int MapNowPos[2] = {0};											//現在のマップのX位置とY位置を格納
int NowDrawMapKind = (int)DRAW_FILED;							//現在の描画マップの種類(最初はフィールドマップ)
bool IsChengeDrawMap = false;									//描画するマップの種類を切り替えるか

int ChengeDrawCount = 0;	//フェードアウト処理に使用

int EncounteEnemyType = ENEMY_ENCOUNT_TYPE_NONE;	//遭遇した敵の種類
int Turn = (int)MY_TURN;	//ターン
int NowTurnCnt = 1;			//ターン数を格納する(1ターン目からスタート)
int TotalTurnCnt = 0;		//総合のターン数を格納する(戦闘が開始されたら、ターンごとに加算される)

bool GameEnd_Flg = false;	//ゲーム終了フラグ
bool Boss_flg = false;		//ボスフラグ
bool Clear_flg = false;		//クリアフラグ

bool IsLoad = false;		//読み込み完了フラグ
bool IsSetInit = false;		//ゲーム開始時の初期設定フラグ

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	SetWindowIconID(GAME_ICON_ID);								//ゲームのアイコン変更
	
	SetAlwaysRunFlag(TRUE);										//非アクティブに設定

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	SetUseASyncLoadFlag(TRUE);									//非同期読み込みに設定

	//ゲームデータ読み込み開始(非同期)
	if (LoadGameData() == false) { return -1; }		//読み込み失敗時、強制終了

	//ゲームのメインループ
	while (GameMainLoop())	
	{
		/*
		ループ内で異常が発生するまで無限ループ
		ゲーム終了やエラー等が発生したらループ終了
		*/
	}

	Delete_Class();			//使用したクラスを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//ロード画面の処理
void Load()
{
	if (GetASyncLoadNum() != 0)			//非同期で読み込んでいる処理が終わっていない時は
	{
		Load_Draw();					//ロード画面の描画処理
	}
	else								//非同期で読み込んでいる処理が終わった時は
	{

		SetUseASyncLoadFlag(FALSE);		//同期読み込みに設定

		if (IsSetInit == false)	//初期設定をしていなければ
		{
			SetGameInit();				//ゲームの初期設定
			IsSetInit = true;			//初期設定完了
		}

		if (!sys_se->GetIsPlayed((int)SYS_SE_LOAD))	//ロード音を鳴らしていなければ
		{
			sys_se->Play((int)SYS_SE_LOAD);	//ロード音を鳴らす
			sys_se->SetIsPlayed((int)SYS_SE_LOAD, true);	//再生済み
		}

		description->DrawNow(GAME_LEFT, GAME_TOP);	//説明画像描画

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			sys_se->Play((int)SYS_SE_KETTEI);	//決定音再生

			if (description->GetIsLast())	//最後の画像だったら
			{
				description->ResetNowImage();//説明画像をリセット

				IsLoad = true;					//読み込み完了
			}
			else	//最後の画像じゃなければ
			{
				description->NextImage();	//次の画像へ
			}
		}

	}

	return;

}

//タイトル画面の処理
void Title()
{

	Init();	//初期化処理

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (bgm->GetIsPlay((int)BGM_TITLE) == false)	//再生中じゃないとき
	{
		bgm->Stop();							//全てのBGMを止める
		bgm->Play((int)BGM_TITLE);				//BGMを再生
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	Title_Draw();		//タイトル画面の描画処理

	Title_select->SelectOperation(keydown, sys_se);		//選択肢のキー操作

	if (Title_select->GetSelectFlg())		//選択されたら
	{
		if (Title_select->GetSelectNum()==(int)TITLE_SELECT_START)		//スタートを選択したら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
		}
		else	//終了を選択したら
		{
			GameEnd_Flg = true;	//ゲーム終了
		}

		Title_select->NowSelectReset();		//現在選択している要素を先頭に戻す
		Title_select->SetSelectFlg(false);	//選択していない状態へ

	}

	return;
}

//プレイ画面の処理
void Play()
{

	if (NowDrawMapKind == (int)DRAW_FILED)		//フィールドマップにいるときは
	{
		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if (bgm->GetIsPlay((int)BGM_FIELD) == false)	//再生中じゃないとき
		{
			bgm->Stop();							//全てのBGMを止める
			bgm->Play((int)BGM_FIELD);				//フィールドBGMを再生
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	}
	else if (NowDrawMapKind == (int)DRAW_CITY)	//街マップにいるときは
	{
		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if (bgm->GetIsPlay((int)BGM_CITY) == false)	//再生中じゃないとき
		{
			bgm->Stop();							//全てのBGMを止める
			bgm->Play((int)BGM_CITY);				//街のBGMを再生
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	}

	Play_Draw();		//描画処理

	if (!player->GetIsKeyOpe())	//プレイヤーのキー操作が不可能になっていた場合
	{
		player->SetIsKeyOpe(true);	//プレイヤーのキー操作を可能に
	}

	player->Operation(keydown, mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_NG));	//プレイヤーキー操作

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ マップ切り替え処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetChengeMapKind() != -1)		//マップの端に来た時
	{
		int chengekind = (int)MAP_CHENGE_NONE;	//マップ切り替えの種類

		//街へ移動するときは
		if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_WARP)))
		{
			if (NowDrawMapKind == (int)DRAW_FILED)		//描画マップがフィールドだったら
			{
				NowDrawMapKind = (int)DRAW_CITY;		//描画マップを街へ切り替える
			}
			else if (NowDrawMapKind == (int)DRAW_CITY)	//描画マップが街だったら
			{
				NowDrawMapKind = (int)DRAW_FILED;		//描画マップをフィールドへ切り替える
			}

			IsChengeDrawMap = true;	//描画マップを切り替える
		}
		else		//移動しないときは
		{
			IsChengeDrawMap = false;	//描画マップを切り替えない
		}

		//マップの切り替え処理
		chengekind = mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->ChengeMap(player->GetChengeMapKind(), MapNowPos, IsChengeDrawMap);

		if (chengekind != (int)MAP_CHENGE_NONE)	//マップ切り替えを行ったときは
		{

			player->SetChengePos(chengekind);		//プレイヤーの位置を修正

			player->ResetChengeMapKind();			//マップ切り替えの種類リセット

		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ マップ切り替え処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	if (player->GetIsMenu())		//メニュー描画中で
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_Q) ||	//Qキーを押された場合と
			!ui->MenuSelect->GetSelectFlg() && keydown->IsKeyDownOne(KEY_INPUT_BACK))//メニューを選んでいない状態で、バックスペースキーを押されたら
		{
			sys_se->Play((int)SYS_SE_CANSEL);	//キャンセル音を鳴らす
			sys_se->Reset();				//再生状態リセット
			player->SetIsMenu(false);		//メニュー描画終了
		}
	}		//メニュー描画中じゃないとき
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Qキーを押された瞬間
	{
		sys_se->Play((int)SYS_SE_MENU);	//メニューを開く音を鳴らす
		sys_se->Reset();				//再生状態リセット
		player->SetIsMenu(true);		//メニュー描画開始
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メニュー毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetIsMenu())			//メニュー描画中だったら
	{
		if (ui->MenuSelect->GetSelectFlg())	//選択していたら
		{

			switch (ui->MenuSelect->GetSelectNum())	//選択した内容毎
			{

			case (int)MENU_STATUS:		//ステータスを選んだとき

				if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//バックスぺースキーを押されたら
				{
					sys_se->Play((int)SYS_SE_CANSEL);	//キャンセル音を鳴らす
					ui->ResetMenu();					//メニューリセット
				}

				break;	//ステータスを選んだときここまで

			case (int)MENU_ITEM:		//アイテムを選んだとき

					ui->SelectUpdate(player->GetItemClass(), item_list);	//アイテムの選択肢の内容更新

					//アイテム画面の処理
					if (ui->MenuSelectItem(keydown, sys_se))	//アイテムを選択した場合
					{
						if (player->UseItem(ui->ItemSelect->GetSelectCode()))	//アイテムを使用できたら
						{
							sys_se->Play((int)SYS_SE_ITEM);	//アイテム使用の音を鳴らす
							ui->Yes_No->Default();			//はい、いいえの選択肢デフォルトへ
							ui->ItemSelect->Default();		//アイテムの選択肢デフォルトへ
						}
						else		//使用できなかったら
						{
							sys_se->Play((int)SYS_SE_BLIP);
							ui->Yes_No->Default();		//はい、いいえの選択肢デフォルトへ
							ui->ItemSelect->Default();	//アイテムの選択肢デフォルトへ
						}
					}

				break;	//アイテムを選んだときここまで

			case (int)MENU_EQUIPMENT:	//装備を選んだとき

				ui->SelectUpdate(player->GetWeaponClass(), weapon_list);	//武器の選択肢の内容を更新
				ui->SelectUpdate(player->GetArmorClass(), armor_list);		//防具の選択肢の内容を更新

				//装備画面の処理
				switch (ui->MenuSelectEquip(keydown,sys_se))	//武器、防具のどちらを選択したか
				{

				case (int)SELECT_EQUIP_WEAPON:	//武器を選択した場合

					//武器の装備処理
					//選択した武器の要素番号を取得し
					//武器装備処理の引数として渡す
					player->EquipWeapon(ui->WeaponSelect->GetSelectNum());	//武器を装備する
					ui->WeaponSelect->Default();							//武器の選択肢デフォルトへ


					break;	//武器を選択した場合ここまで

				case (int)SELECT_EQUIP_ARMOR:	//防具を選択した場合

					//防具の装備処理
					//選択した防具の要素番号を取得し
					//防具装備処理の引数として渡す
					player->EquipArmor(ui->ArmorSelect->GetSelectNum());	//防具を装備する
					ui->ArmorSelect->Default();								//防具の選択肢デフォルトへ

					break;	//防具を選択した場合ここまで

				default:
					break;
				}

				break;	//装備を選んだときここまで

			case (int)MENU_SETUMEI:		//説明を選んだとき

				if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
				{
					sys_se->Play((int)SYS_SE_KETTEI);	//音の再生

					if (description->GetIsLast())	//最後の画像だったら
					{
						ui->ResetMenu();	//メニューリセット
						description->ResetNowImage();	//描画する画像を最初に戻す
					}
					else	//最後じゃなければ
					{
						description->NextImage();	//次の説明へ
					}
				}
				else if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//バックスぺースキーを押されたら
				{
					sys_se->Play((int)SYS_SE_CANSEL);	//キャンセル音を鳴らす
					description->ResetNowImage();		//描画する画像を最初に戻す
					ui->ResetMenu();					//メニューリセット
				}


				break;	//説明を選んだときここまで

			case (int)MENU_SAVE:		//セーブを選んだとき

				if (Wait())			//待ち時間が過ぎたら
				{
					struct stat statbuf;	//ディレクトリの存在確認に使用
					
					if (stat(SAVE_DATA_DIR, &statbuf) != 0)//セーブデータ用のフォルダが作成されていない場合（初めてのセーブの場合）
					{
						_mkdir(SAVE_DATA_DIR);	//セーブデータを格納するフォルダを作成
					}

					player->Save(SAVE_DATA_DIR, PLAYER_DATA_NAME);								//プレイヤー情報のセーブ
					data->SaveMap(NowDrawMapKind, MapNowPos, SAVE_DATA_DIR, MAPPOS_DATA_NAME);	//マップ位置のセーブ

					sys_se->Play((int)SYS_SE_SAVE);		//セーブ音を鳴らす
					player->SetIsMenu(false);			//メニュー描画終了
				}

				break;	//セーブを選んだときここまで

			default:
				break;
			}

		}
		else			//選択をしていなかったら
		{
			ui->MenuSelect->SelectOperation(keydown, sys_se);			//メニューウィンドウキー操作
		}

	}
	else			//メニュー描画終了してたら
	{
		ui->ResetMenu();	//メニュー関係のリセット
	}


	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メニュー毎の処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	if (player->GetIsKeyDown())		//キー入力されてたら(プレイヤーが移動中だったら)
	{

			if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_ENCOUNT)))	//敵と遭遇するマップだったら
			{
				Enconte();			//敵との遭遇判定
			}

			//ボスマップへ移動するときは
			if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_WARP_BOSS)))
			{
				Boss_flg = true;		//ボスフラグを立てる
				MAPPOS_Y = BOSS_MAP_NUM_Y;	//現在のマップ位置をボスマップへ切り替え（X）
				MAPPOS_X = BOSS_MAP_NUM_X;	//現在のマップ位置をボスマップへ切り替え（Y)
				player->SetPosAbsolute(BOSS_PLAYER_X, BOSS_PLAYER_Y);	//プレイヤーの位置を修正
			}

	}

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	return;
}

//戦闘画面の処理
void Battle()
{

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (bgm->GetIsPlay((int)BGM_BATTLE) == false)	//再生中じゃないとき
	{
		bgm->Stop();							//全てのBGMを止める
		bgm->Play((int)BGM_BATTLE);				//戦闘BGMを再生
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	Battle_Draw();			//描画処理

	switch (BattleStageNow)		//現在のバトル状態
	{

	case (int)WAIT_ACT:		//プレイヤーの行動選択待ち状態の時

		Bt_WaitAct();		//行動待ち状態の処理

		break;				//行動選択待ち状態の処理ここまで

	case (int)DAMEGE_CALC:	//ダメージ計算状態の時

		Bt_DamegeCalc();	//ダメージ計算状態の処理

		break;				//ダメージ計算状態の時ここまで

	case (int)ACT_MSG:		//行動メッセージ表示状態

		Bt_ActMsg();		//行動メッセージ表示状態の処理

		break;				//行動メッセージ表示状態ここまで

	case (int)DRAW_EFFECT:	//エフェクト描画状態

		Bt_DrawEffect();	//エフェクト描画状態の処理

		break;				//エフェクト描画状態ここまで

	case (int)DRAW_DAMEGE:	//ダメージ描画状態
		
		Bt_DrawDamege();	//ダメージ描画状態の処理

		break;				//ダメージ描画状態の処理ここまで

	case (int)RESULT_MSG:	//戦闘終了後のメッセージを描画する状態

		Bt_ResultMsg();		//リザルトメッセージ描画状態の処理

		break;				//戦闘終了後のメッセージを描画する状態の処理ここまで

	default:
		break;

	}

	return;
}

//エンド画面の処理
void End()
{

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (bgm->GetIsPlay((int)BGM_END) == false)	//再生中じゃないとき
	{
		bgm->Stop();							//全てのBGMを止める
		bgm->Play((int)BGM_END);				//エンドBGMを再生
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	End_Draw();	//描画処理

	End_select->SelectOperation(keydown, sys_se);		//選択肢のキー操作

	if (End_select->GetSelectFlg())						//選択されたら
	{
		if (End_select->GetSelectNum()==(int)END_SELECT_TITLE)		//タイトルを選択したら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//次の画面はタイトル画面
		}
		else	//終了を選択したら
		{
			GameEnd_Flg = true;	//ゲーム終了
		}


		player->Recovery();	//回復

		End_select->NowSelectReset();	//選択状態リセット
		End_select->SetSelectFlg(false);//選択していない状態へ

	}


	return;
}

//画面遷移の演出をする処理
void Chenge()
{
	const int ChengeDrawCountMax = 60;	//フェードイン処理に使用

	switch (GameSceneBefor)		//どの画面からの遷移かで処理を分ける
	{
	case (int)GAME_SCENE_TITLE:	//タイトル画面からの遷移だったら

		Title_Draw();		//タイトル画面の描画処理

		break;

	case (int)GAME_SCENE_PLAY:	//プレイ画面からの遷移だったら

		Play_Draw();		//プレイ画面の描画処理

		break;

	case (int)GAME_SCENE_BATTLE://戦闘画面からの遷移だったら

		Battle_Draw();		//戦闘画面の描画処理

		break;

	case (int)GAME_SCENE_END:	//エンド画面からの遷移だったら

		End_Draw();			//エンド画面の描画処理

		break;

	default:
		break;
	}

	//フェードアウトの処理
	double ToukaPercent = ChengeDrawCount / (double)ChengeDrawCountMax;//透過％を求める
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//透過させる
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過をやめる

	//60フレーム分、待つ
	if (ChengeDrawCount < ChengeDrawCountMax)
	{
		ChengeDrawCount++;
	}
	else
	{
		ChengeDrawCount = 0;			//フェードイン用初期化
		GameSceneNow = GameSceneNext;	//次の画面にする
	}


	return;

}

//初期化処理
void Init()
{
	Clear_flg = false;	//クリアフラグリセット
}

//戦闘画面関係初期化
void BattleInit(void)
{

	ui->BattleInit();			//バトルコマンド初期化

	player->BattleInit();		//戦闘で使用する要素初期化

	bt_se->Reset();				//SEの再生状態をリセット

	if (EncounteEnemyType != ENEMY_ENCOUNT_TYPE_NONE)	//遭遇した敵の種類が入っていたら
	{
		enemy[EncounteEnemyType]->StateSetInit();		//遭遇した敵初期化
		EncounteEnemyType = ENEMY_ENCOUNT_TYPE_NONE;	//遭遇した敵の種類をリセット
	}

	BattleStageNow = (int)WAIT_ACT;	//バトル状態を、行動待ち状態へ

	NowTurnCnt = 1;				//次の戦闘に備えて、ターン数をリセット
	TotalTurnCnt = 0;			//次の戦闘に備えて、ターン数をリセット
	Turn = (int)MY_TURN;		//ターンを味方のターンに設定

	for (int i = 0; i < BT_MSG_KIND; ++i)	//メッセージの種類分
	{
		bt_msg[i]->ResetFlg();		//フラグリセット
	}

	return;

}

//シーンを変更する処理
void SceneChenge(int beforscene, int nextscene)
{
	GameSceneBefor = beforscene;				//現在のゲームシーンを前のゲームシーンとして保存
	GameSceneNow = (int)GAME_SCENE_CHENGE;		//遷移画面に変更
	GameSceneNext = nextscene;					//次のシーンを指定
	return;
}

//ロード画面の描画処理
void Load_Draw()
{
	std::string LoadMessage = LOAD_TEXT;		//ロード画面に描画する文字
	int Width = 0;								//横幅
	int Strlen = 0;								//文字数

	Strlen = strlen(LoadMessage.c_str());						//文字数取得
	Width = GetDrawStringWidth(LoadMessage.c_str(), Strlen);	//横幅取得

	DrawFormatString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GetColor(255, 255, 255),"%s",LoadMessage.c_str());	//ロード文字描画

	return;
}

//タイトル画面の描画処理
void Title_Draw()
{
	back->Draw(GAME_LEFT, GAME_TOP,(int)TITLE_BACK);	//背景画像描画

	title->Draw(GAME_LEFT, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//画面中央にタイトル描画

	font->SetSize(BIG_FONTSIZE);		//フォントサイズを大きくする

	Title_select->DrawCenter(GAME_WIDTH / 2, DEFAULT_TEXT_Y,(int)SELECT_TRIANGLE);	//選択肢描画
	
	return;

}

//プレイ画面の描画処理
void Play_Draw()
{
	font->SetSize(DEFAULT_FONTSIZE);	//フォントサイズを標準に戻す

	mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->Draw();	//マップ描画

	if (Boss_flg)		//ボスマップにいるときは
	{
		boss_mapimage->Draw(BOSS_MAP_X, BOSS_MAP_Y);			//ボスキャラ描画
	}

	//NPC描画処理
	npc->DrawNPC(NowDrawMapKind, MapKind[MAPPOS_Y][MAPPOS_X]);	//NPC描画

	player->DrawWalk();		//プレイヤー描画

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メニュー描画処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetIsMenu())	//メニュー描画中なら
	{
		ui->DrawMenu();			//メニューウィンドウ描画

		if (ui->MenuSelect->GetSelectFlg())	//選択したら
		{

			ui->DrawWindow(MENU_WINDOW_X, MENU_WINDOW_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画

			switch (ui->MenuSelect->GetSelectNum())		//選んだ内容ごとに処理を分ける
			{

			case (int)MENU_STATUS:	//ステータスを選んだ時の処理ここから

				ui->DrawMenuState(player);		//ステータス描画

				break;				//ステータスを選んだ時の処理ここまで

			case (int)MENU_ITEM:	//アイテムを選んだ時の処理ここから

				//アイテム描画処理
				if (ui->ItemSelect->GetSelectKind() != 0)	//アイテムを一種類以上持っていたら
				{
					ui->DrawItemSelect(MENU_TEXT_X,MENU_TEXT_TOP_Y, player->GetItemClass(),item_list);	//アイテム描画

					if (ui->ItemSelect->GetSelectFlg())		//アイテムを選択したら
					{
						ui->DrawMenuCheck();	//確認メッセージ描画
					}

				}

				break;				//アイテムを選んだときの処理ここまで

			case (int)MENU_EQUIPMENT:	//装備を選んだ時の処理ここから

				//装備描画処理

				ui->DrawMenuEquip(player->GetWeaponClass(), player->GetArmorClass());	//装備描画処理

				if (ui->GetMenuEquipDir() == (int)MENU_EQUIP_SELECT_DECISION)		//選択肢の段階が、はい、いいえの段階だったら
				{
					ui->DrawMenuCheck();	//確認メッセージ描画
				}

				break;				//装備を選んだ時の処理ここまで

			case (int)MENU_SETUMEI:	//操作説明を選んだ時の処理ここから

				description->DrawNow(GAME_LEFT, GAME_TOP);	//説明画像の描画

				break;				//操作説明を選んだ時の処理ここまで

			case (int)MENU_SAVE:	//セーブを選んだ時の処理ここから

				//セーブ時の描画処理
				DrawString(MENU_TEXT_X, MENU_TEXT_TOP_Y, SAVE_TEXT, GetColor(255, 255, 255));	//文字描画

				break;				//セーブを選んだ時の処理ここまで

			default:
				break;
			}

		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メニュー描画処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;

}

//戦闘画面の描画処理
void Battle_Draw()
{

	back_battle->Draw(GAME_LEFT, GAME_TOP, MapKind[MAPPOS_Y][MAPPOS_X]);	//背景画像を描画

	enemy[EncounteEnemyType]->Draw();	//敵描画

	ui->DrawStateWindow(player);		//ステータスウィンドウ描画

	ui->DrawCommand();					//バトルコマンド描画

	ui->DrawUiImage(BT_WINDOW_X, BT_WINDOW_Y, (int)UI_WINDOW);	//メッセージウィンドウ描画

	ui->DrawUiAnime(ui->GetUiImageWidth((int)UI_WINDOW) / 2 - TXT_POSE_WIDTH / 2, BT_TXT_POSE_Y);		//テキストポーズ描画

	return;

}

//エンド画面の描画処理
void End_Draw()
{

	back->Draw(GAME_LEFT, GAME_TOP, (int)END_BACK);	//背景画像描画

	if (Clear_flg)		//クリアしていたら
	{
		int Strlen = strlen(GAME_CLEAR_TEXT);
		int Width = GetDrawStringWidth(GAME_CLEAR_TEXT, Strlen);	//横幅取得

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GAME_CLEAR_TEXT, GetColor(255, 0, 0));		//クリア文字描画

		MAPPOS_Y = AF_CLEAR_MAP_NUM_Y;	//現在のマップ位置をボスマップの前へ切り替え（X）
		MAPPOS_X = AF_CLEAR_MAP_NUM_X;	//現在のマップ位置をボスマップの前へ切り替え（Y)
		player->SetPosAbsolute(PLAYER_AF_CLEAR_POS_X, PLAYRT_AF_CLEAR_POS_Y);	//プレイヤーの位置を修正
		Boss_flg = false;	//ボスフラグリセット


	}
	else				//クリアしていなかったら
	{
		int Strlen = strlen(GAME_OVER_TEXT);
		int Width = GetDrawStringWidth(GAME_OVER_TEXT, Strlen);	//横幅取得

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GAME_OVER_TEXT, GetColor(255, 0, 0));		//ゲームオーバー文字描画
	}

	font->SetSize(BIG_FONTSIZE);	//フォントサイズを大きくする

	End_select->DrawCenter(GAME_WIDTH / 2, DEFAULT_TEXT_Y, (int)SELECT_TRIANGLE,GetColor(0,0,0));		//選択肢描画

	return;

}

//敵との遭遇処理
void Enconte()
{

	for (int i = 0; i < ENEMY_KIND; ++i)		//敵の分だけループする
	{
		if (enemy[i]->GetEmergenceMap() == MapKind[MAPPOS_Y][MAPPOS_X])		//敵の出現MAPが現在のMAPだったら
		{
			//ランダムで遭遇判定
			int rand = GetRand(enemy[i]->GetEncounteRate());	//遭遇率の範囲内で乱数を生成

			if (rand%enemy[i]->GetEncounteRate() == 0)			//敵と遭遇した時
			{
				BattleInit();		//戦闘関係初期化

				player->SetIsKeyOpe(false);	//プレイヤーの動きを止める

				EncounteEnemyType = i;			//遭遇した敵を設定

				//描画文字設定
				switch (GetRand(ENCOUNT_TXT_KIND-1))
				{

				case (int)ENCOUNT_TXT_PATARN1:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_1);	//エンカウントテキスト設定


					break;

				case (int)ENCOUNT_TXT_PATARN2:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_2);		//エンカウントテキスト設定

					break;

				case (int)ENCOUNT_TXT_PATARN3:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_3);		//エンカウントテキスト設定

					break;
						
				default:
					break;
				}

				bt_msg[(int)BT_MSG_ACT]->AddText(enemy[EncounteEnemyType]->GetName());	//エンカウントした敵の名前取得
				bt_msg[(int)BT_MSG_ACT]->AddText(ENCOUNT_AF_TEXT);		//メッセージ内容追加
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_WAIT_ACT_TEXT);		//メッセージ追加

				sys_se->Play((int)SYS_SE_ENCOUNT);					//敵と遭遇した音を鳴らす
				sys_se->Reset();									//再生状態リセット

				SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//次の画面は戦闘画面

			}
		}
	}


	return;

}

//待つ処理
/*
戻り値：true：待つ時間が過ぎたら
戻り値：false：待っているとき
*/
bool Wait()
{
	static int WaitCnt = 0;		//カウント用

	if (WaitCnt == GAME_WAITCNT_MAX)		//待つ時間が過ぎたら
	{
		WaitCnt = 0;	//カウントリセット
		return true;
	}
	else
	{
		++WaitCnt;		//カウントアップ
		return false;
	}
}

//ゲーム内で使用したクラスを削除する処理
void Delete_Class()
{
	delete title;			//titleを破棄
	delete description;			//setumeiを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete bgm;				//bgmを破棄
	delete bt_se;			//bt_seを破棄
	delete sys_se;			//sys_seを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄
	delete back_battle;		//back_battleを破棄
	delete data;			//dataを破棄
	delete Magic_effect;	//effectを破棄
	delete boss_mapimage;	//boss_mapimageを破棄
	delete Title_select;	//title_select破棄
	delete End_select;		//end_select破棄
	delete mgc_list;		//mgc_listを破棄
	delete weapon_list;		//weapon_listを破棄
	delete armor_list;		//armor_listを破棄
	delete npc;				//npcを破棄

	//メッセージの削除
	for (int i = 0; i < BT_MSG_KIND; ++i)
	{
		delete bt_msg[i];				//bt_msgを破棄
	}

	//マップデータの削除
	for (int cnt = 0; cnt < DRAW_MAP_KIND; ++cnt)
	{
		for (int i = 0; i < MAP_DATA_KIND; i++)	//マップの種類分
		{
			delete mapdata[cnt][i];	//mapdataを破棄
		}

	}

	//敵の削除
	for (int i = 0; i < ENEMY_KIND; ++i)	//敵の種類分
	{
		delete enemy[i];			//enemyを破棄
	}
	return;

}

//ゲーム内で使用するデータ等を読み込む処理
/*
戻り値：true：読み込み成功
戻り値：false：読み込み失敗
*/
bool LoadGameData()
{

	//フォント関係
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { return false; }				//読み込み失敗時

	//画像関係
	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//タイトル画像を生成
	if (title->GetIsLoad() == false) { return false; }				//読み込み失敗時

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_TITLE);			//背景画像を生成
	if (back->GetIsLoad() == false) { return false; }					//読み込み失敗時
	back->AddImage(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_END);	//エンド画面の背景画像読み込み
	if (back->GetIsLoad() == false) { return false; }							//読み込み失敗

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SOUGEN);		//戦闘画面(草原)の背景画像読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_FOREST);		//戦闘画面（森）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_OCEAN);		//戦闘画面（海）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_AUTUMN);		//戦闘画面（秋）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_BOSS);			//戦闘画面（ボス）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SPRING);		//戦闘画面（春）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_WINTER);		//戦闘画面（冬）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_REMAINS);		//戦闘画面（遺跡）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_CASTLE);		//戦闘画面（城）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return false; }					//読み込み失敗


	description = new IMAGE(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_PLAY_NAME);		//説明画像の読み込み
	if (description->GetIsLoad() == false) { return false; }					//読み込み失敗
	description->AddImage(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_BATTLE_NAME);		//説明画像追加
	if (description->GetIsLoad() == false) { return false; }					//読み込み失敗
	description->AddImage(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_BP_NAME);			//説明画像追加
	if (description->GetIsLoad() == false) { return false; }					//読み込み失敗

	//音関係
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_BGM_NAME_TITLE);		//BGMを生成
	if (bgm->GetIsLoad() == false) { return false; }						//読み込み失敗時
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_FIELD) == false) { return false; }	//フィールドのBGM追加
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_CITY) == false) { return false; }	//街のBGM追加
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_BATTLE) == false) { return false; }//戦闘画面のBGM追加
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_END) == false) { return false; }//エンド画面のBGM追加

	//戦闘で使用するSE
	bt_se = new MUSIC(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_LEVUP);	//SEを生成
	if (bt_se->GetIsLoad() == false) { return false; }						//読み込み失敗時
	bt_se->ChengePlayType(DX_PLAYTYPE_BACK);								//再生方法変更
	//音の追加処理
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_SLASH) == false) { return false; }		//斬るときの音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_THUNDER) == false) { return false; }		//雷の音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_NIGERU) == false) { return false;	}		//逃げるときの音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_DAMEGE) == false) { return false; }		//ダメージ音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_RECOVERY) == false) { return false; }		//回復音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPPLUS) == false) { return false; }		//使用するBPを増やす音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPMINUS) == false) { return false; }		//使用するBPを減らす音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPCHARGE) == false) { return false; }		//BPチャージ音追加

	//システムで使用するSE
	sys_se = new MUSIC(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CURSOR);	//システム用SE生成
	if (sys_se->GetIsLoad() == false) { return false; }							//読み込み失敗
	sys_se->ChengePlayType(DX_PLAYTYPE_BACK);									//再生方法変更
	//音の追加処理
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CANSEL) == false) { return false; }		//キャンセル音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_KETTEI) == false) { return false; }		//決定音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_MENU) == false) { return false; }		//メニューを開いた時の音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_ENCOUNT) == false) { return false; }	//敵と遭遇した時の音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_SAVE) == false) { return false; }		//セーブの音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_BLIP) == false) { return false; }		//選択できないときの音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_ITEM) == false) { return false; }		//アイテムを使用したときの音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_EQUIP) == false) { return false; }		//装備したときの音追加
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_LOAD) == false) { return false; }		//ロードしたときの音追加


	data = new DATA();		//データ

	//メッセージ関係
	for (int cnt = 0; cnt < BT_MSG_KIND; ++cnt)
	{
		bt_msg[cnt] = new MESSAGE();	//メッセージ作成
	}

	//エフェクト関係
	//魔法エフェクト
	Magic_effect = new EFFECT(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, MAGIC_EFFECT_KIND);
	if (Magic_effect->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (Magic_effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return false; }	//読み込み失敗

	//攻撃エフェクト
	Atack_effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false, ATACK_EFFECT_KIND);
	if (Atack_effect->GetIsLoad() == false) { return false; }		//読み込み失敗

	//敵攻撃エフェクト
	Enemy_Atk_effect = new EFFECT(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TUME, ENE_ATK_TUME_ALL_CNT, ENE_ATK_TUME_YOKO_CNT, ENE_ATK_TUME_TATE_CNT, ENE_ATK_TUME_WIDTH, ENE_ATK_TUME_HEIGHT, ENE_ATK_TUME_SPEED, false, ENE_ATK_EFFECT_KIND);
	if (Enemy_Atk_effect->GetIsLoad() == false) { return false; }		//読み込み失敗
	//敵攻撃エフェクト追加
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_KIBA, ENE_ATK_KIBA_ALL_CNT, ENE_ATK_KIBA_YOKO_CNT, ENE_ATK_KIBA_TATE_CNT, ENE_ATK_KIBA_WIDTH, ENE_ATK_KIBA_HEIGHT, ENE_ATK_KIBA_SPEED, false, (int)ENE_ATK_KIBA) == false) { return false; }	//読み込み失敗
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TAIL_BIG, ENE_ATK_TAIL_BIG_ALL_CNT, ENE_ATK_TAIL_BIG_YOKO_CNT, ENE_ATK_TAIL_BIG_TATE_CNT, ENE_ATK_TAIL_BIG_WIDTH, ENE_ATK_TAIL_BIG_HEIGHT, ENE_ATK_TAIL_BIG_SPEED, false, (int)ENE_ATK_TAIL_BIG) == false) { return false; }	//読み込み失敗

	//ボス攻撃エフェクト
	Boss_Atk_effect = new EFFECT(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_LASER, BOSS_ATK_LEASER_ALL_CNT, BOSS_ATK_LEASER_YOKO_CNT, BOSS_ATK_LEASER_TATE_CNT, BOSS_ATK_LEASER_WIDTH, BOSS_ATK_LEASER_HEIGHT, BOSS_ATK_LEASER_SPEED, false, BOSS_ATK_EFFECT_KIND);
	if (Boss_Atk_effect->GetIsLoad() == false) { return false; }		//読み込み失敗
	//ボス攻撃エフェクト追加
	if (Boss_Atk_effect->Add(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_TOGE, BOSS_ATK_TOGE_ALL_CNT, BOSS_ATK_TOGE_YOKO_CNT, BOSS_ATK_TOGE_TATE_CNT, BOSS_ATK_TOGE_WIDTH, BOSS_ATK_TOGE_HEIGT, BOSS_ATK_TOGE_SPEED, false, (int)BOSS_ATK_TOGE) == false) { return false; }	//読み込み失敗


	//プレイヤー関係
	player = new PLAYER();		//プレイヤー生成
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return false; } //読み込み失敗

	//UI関係
	ui = new UI();		//UI作成

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵関係ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	enemy[(int)ENE_SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//スライム作成
	if (enemy[(int)ENE_SLIME]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_BAT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BAT);	//こうもり作成
	if (enemy[(int)ENE_BAT]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_GOBURIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GOBURIN);	//ゴブリン作成
	if (enemy[(int)ENE_GOBURIN]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_MATANGO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MATANGO);	//マタンゴ作成
	if (enemy[(int)ENE_MATANGO]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_SEED] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SEED);	//悪魔の種作成
	if (enemy[(int)ENE_SEED]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_TREANT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_TREANT);	//トレント作成
	if (enemy[(int)ENE_TREANT]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_YADOKARI] = new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//ヤドカリ作成
	if (enemy[(int)ENE_YADOKARI]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_SCORPION] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SCORPION);	//サソリ作成
	if (enemy[(int)ENE_SCORPION]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_OCTPUS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_OCTPUS);	//タコ作成
	if (enemy[(int)ENE_OCTPUS]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_COBRA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_COBRA);		//コブラ作成
	if (enemy[(int)ENE_COBRA]->GetIsLoad() == false) { return false; }		//読み込み失敗

	enemy[(int)ENE_PUMPKIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PUMPKIN);	//パンプキン作成
	if (enemy[(int)ENE_PUMPKIN]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_PAPILLON] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PAPILLON);	//パピオン作成
	if (enemy[(int)ENE_PAPILLON]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_HARPY] = new ENEMY(ENEMY_DIR, ENEMY_NAME_HARPY);	//ハーピー作成
	if (enemy[(int)ENE_HARPY]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_FLOWER] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FLOWER);	//デスフラワー作成
	if (enemy[(int)ENE_FLOWER]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_MANTIS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MANTIS);	//マンティス作成
	if (enemy[(int)ENE_MANTIS]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_CRYSTAL] = new ENEMY(ENEMY_DIR, ENEMY_NAME_CRYSTAL);	//クリスタル作成
	if (enemy[(int)ENE_CRYSTAL]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_ICICLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_ICICLE);	//アイシクル作成
	if (enemy[(int)ENE_ICICLE]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_SNOWMAN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SNOWMAN);	//スノーマン作成
	if (enemy[(int)ENE_SNOWMAN]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_FARAO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FARAO);	//ファラオ作成
	if (enemy[(int)ENE_FARAO]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_AKUMA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_AKUMA);	//デーモン作成
	if (enemy[(int)ENE_AKUMA]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_BONEBEAST] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BONEBEAST);	//ボーンビースト作成
	if (enemy[(int)ENE_BONEBEAST]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_IFRIT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_IFRIT);	//イフリート作成
	if (enemy[(int)ENE_IFRIT]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_GARGOYLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GARGOYLE);	//ガーゴイル作成
	if (enemy[(int)ENE_GARGOYLE]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_PROMINENCE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PROMINENCE);	//プロミネンス作成
	if (enemy[(int)ENE_PROMINENCE]->GetIsLoad() == false) { return false; }	//読み込み失敗

	enemy[(int)ENE_BOSS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BOSS);	//ボス作成
	if (enemy[(int)ENE_BOSS]->GetIsLoad() == false) { return false; }	//読み込み失敗


	boss_mapimage = new IMAGE(ENEMY_DIR, ENEMY_NAME_BOSS_MAP);		//マップに描画するボスの画像を生成
	if (boss_mapimage->GetIsLoad() == false) { return false; }					//読み込み失敗時

	//敵のデータをcsvファイルから読み込み
	if (data->LoadEnemy(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME) == false) { return false; }		//読み込み失敗
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵関係ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ マップデータ読み込み開始 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	//フィールドマップ読み込み
	mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SOUGEN);	//草原マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SOUGEN_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_FOREST] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_FOREST);	//森マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_FOREST]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_FOREST_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_OCEAN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_OCEAN);		//海マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_OCEAN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_OCEAN_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_AUTUMN);	//秋マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_AUTUMN_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_BOSS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_BOSS);	//ボスマップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_BOSS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_BOSS_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_SPRING] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SPRING);			//春マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_SPRING]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SPRING_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_WINTER] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_WINTER);			//冬マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_WINTER]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_WINTER_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_REMAINS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_REMAINS);					//遺跡マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_REMAINS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_REMAINS_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_FILED][(int)MAP_CASTLE] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_CASTLE);					//魔王城マップ生成
	if (mapdata[(int)DRAW_FILED][(int)MAP_CASTLE]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_CASTLE_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	//街マップ読み込み
	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NW);	//北西マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NW_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_W] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_W);	//西マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_W]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_W_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SW);		//南西マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SW_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_N] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_N);	//北マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_N]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_N_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_CENTER);	//中央マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_CENTER_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_S] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_S);			//南マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_S]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_S_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NE);			//北東マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NE_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_E] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_E);					//東マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_E]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_E_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SE);					//南東マップ生成
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SE_ATARI) == false) { return false; }	//当たり判定読み込み失敗

	//マップの種類を二次元配列で管理
	for (int yoko = 0; yoko < MAP_DATA_YOKO_KIND; yoko++)
	{
		static int cnt = 0;
		for (int tate = 0; tate < MAP_DATA_TATE_KIND; tate++)
		{
			MapKind[tate][yoko] = cnt;
			cnt++;
		}
	}

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ マップデータ読み込みここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	//*************** セーブデータ読み込み *******************

	struct stat statbuf;	//セーブデータのディレクトリの存在確認に使用

	if (stat(SAVE_DATA_DIR, &statbuf) == 0)	//セーブデータが存在したら
	{
		//セーブデータから読み込み

		//プレイヤーのデータをcsvファイルから読み込み
		if (player->LoadData(SAVE_DATA_DIR, PLAYER_DATA_NAME) == false) { return false; }	//読み込み失敗

		//現在のマップ位置を読み込んで設定
		if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, SAVE_DATA_DIR, MAPPOS_DATA_NAME) == false) { return false; }	//読み込み失敗

	}
	else		//セーブデータが存在しなかったら
	{
		//初期データから読み込み
		//プレイヤーのデータをcsvファイルから読み込み
		//if(player->LoadData(PLAYER_DATA_DIR, PLAYER_DATA_NAME) == false) { return false; }	//読み込み失敗
		//プレイヤーの初期データver
		if (player->LoadData(PLAYER_DATA_DIR, PLATER_DATA_INIT_NAME) == false) { return false; }	//読み込み失敗

		//現在のマップ位置を読み込んで設定
		//if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME) == false) { return false; }	//読み込み失敗
		//現在のマップ位置を読み込んで設定(初期ver)
		if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_INITDATA_NAME) == false) { return false; }	//読み込み失敗

	}

	//*************** セーブデータ読み込み *******************

	//一覧関係
	mgc_list = new LIST_MGC(LIST_DIR, MGC_LIST_NAME);		//魔法一覧を生成
	if (mgc_list->GetIsLoad() == false) { return false; }	//読み込み失敗

	weapon_list = new LIST_WEAPON(LIST_DIR, WEAPON_LIST_NAME);	//武器一覧を生成
	if (weapon_list->GetIsLoad() == false) { return false; }	//読み込み失敗

	armor_list = new LIST_ARMOR(LIST_DIR, ARMOR_LIST_NAME);		//防具一覧を生成
	if (armor_list->GetIsLoad() == false) { return false; }		//読み込み失敗

	item_list = new LIST_ITEM(LIST_DIR, ITEM_LIST_NAME);		//アイテム一覧を生成
	if (item_list->GetIsLoad() == false) { return false; }		//読み込み失敗


	//選択肢関係
	Title_select = new SELECT(TITLE_SELECT_START_TEXT, TITLE_SELECT_END_TEXT);	//タイトル画面の選択肢生成
	End_select = new SELECT(END_SELECT_TITLE_TEXT, END_SELECT_END_TEXT);		//エンド画面の選択肢生成

	//魔法一覧から、戦闘画面で使用するための、魔法の選択肢を作成
	for (int i = 0; i < mgc_list->GetListSize(); ++i)			//魔法の種類分ループさせる
	{
		ui->MgcSelect->AddSelect(std::to_string(mgc_list->GetCost(i)).c_str());//消費MP設定
		ui->MgcSelect->AddText(i, MGC_SELECT_MP_TEXT);							//文字列追加
		ui->MgcSelect->AddText(i, mgc_list->GetName(i));						//魔法名設定
	}

	//NPC関係
	npc = new NPC(NPC_IMAGE_DIR, NPC_IMAGE_DATA1_NAME);						//NPCを生成
	if (npc->GetImageIsLoad() == false) { return false; }					//読み込み失敗
	//NPC追加処理
	if (npc->AddImage(NPC_IMAGE_DIR, NPC_IMAGE_DATA2_NAME) == false) { return false; }	//NPC画像を追加
	if (npc->AddImage(NPC_IMAGE_DIR, NPC_IMAGE_DATA3_NAME) == false) { return false; }	//NPC画像を追加
	if (npc->AddImage(NPC_IMAGE_DIR, NPC_IMAGE_DATA4_NAME) == false) { return false; }	//NPC画像を追加
	if (npc->AddImage(NPC_IMAGE_DIR, NPC_IMAGE_DATA5_NAME) == false) { return false; }	//NPC画像を追加
	if (npc->Load(NPC_DATA_DIR, NPC_DATA_NAME) == false) { return false; }	//NPCデータ読み込み

	return true;		//全ての読み込みに成功

}

//ゲームの初期設定を行う処理
void SetGameInit()
{

	SetSize();		//ゲーム内で使用する画像などのサイズを設定

	player->SetWeaponAtk(weapon_list);		//武器攻撃力設定
	player->SetArmorDef(armor_list);		//防具防御力設定
	player->SetItemRecovery(item_list);		//回復量設定

	//******************** 初期設定ここから ***************************
	player->SetInit();	//プレイヤーの初期設定

	//敵の初期設定
	for (int i = 0; i < ENEMY_KIND; ++i)		//敵の数だけ初期設定
	{
		enemy[i]->SetInit();					//初期設定
		enemy[i]->StateSetInit();				//ステータス初期設定
	}

	ui->Init();		//UI関係初期化
	//******************** 初期設定ここまで ***************************

	ui->SelectUpdate(player->GetWeaponClass(), weapon_list);	//武器の選択肢更新
	ui->SelectUpdate(player->GetArmorClass(), armor_list);		//防具の選択肢更新
	ui->SelectUpdate(player->GetItemClass(), item_list);		//アイテムの選択肢更新

	return;

}

//ゲームで使用する画像などのサイズを設定する処理
void SetSize()
{
	//画像関係
	title->SetSize();			//タイトル画像のサイズ設定
	back->SetSize();			//背景画像のサイズ設定
	back_battle->SetSize();		//戦闘画面の画像サイズ設定
	description->SetSize();			//説明画像のサイズ設定
	boss_mapimage->SetSize();	//ボスのマップでの画像サイズ設定

	//UI関係
	ui->SetSize();				//UI画像のサイズ設定

	//選択肢関係
	Title_select->SetSize();	//選択肢の画像サイズ設定
	
	//エフェクト関係
	Magic_effect->SetSize();	//魔法エフェクトのサイズ設定
	Atack_effect->SetSize();	//攻撃エフェクトのサイズ設定
	Enemy_Atk_effect->SetSize();//敵攻撃エフェクトのサイズ設定
	Boss_Atk_effect->SetSize();	//ボス攻撃エフェクトのサイズ設定

	return;

}

//無限ループ内のゲーム処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	keydown->KeyDownUpdate();	//キーの入力状態を更新する

	fps->Update();				//FPSの処理[更新]

	if (IsLoad == false)		//読み込みが終了していなければ
	{
		Load();					//ロード画面の処理
	}
	else						//読み込みが終了していれば
	{
		//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:		//タイトル画面だったら

			Title();					//タイトル画面の処理

			break;

		case (int)GAME_SCENE_PLAY:		//プレイ画面だったら

			Play();						//プレイ画面の処理

			break;

		case (int)GAME_SCENE_BATTLE:	//戦闘画面だったら

			Battle();					//戦闘画面の処理

			break;

		case (int)GAME_SCENE_END:		//エンド画面だったら

			End();						//エンド画面の処理

			break;

		case (int)GAME_SCENE_CHENGE:	//シーン遷移画面だったら

			Chenge();					//シーン遷移画面の処理

			break;

		default:
			break;

		}
		//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	}

	if (GameEnd_Flg)		//ゲーム終了フラグが立っていたら
	{
		return false;				//ループを抜け、ゲーム終了
	}


	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	fps->Wait();				//FPSの処理[待つ]

	return true;				//正常

}

//************************ 戦闘画面の各処理 *****************************
//戦闘画面行動待ち状態の処理
void Bt_WaitAct()
{
	if (Turn == (int)MY_TURN)		//味方のターンだったら
	{
		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

		if (bt_msg[(int)BT_MSG_ACT]->GetIsLastMsg())	//最後のメッセージだったら
		{

			//1ターンに1回だけ行う処理
			if (TotalTurnCnt < NowTurnCnt)	//ターンが始まって最初の処理だったら
			{
				if (player->AddBP())	//BPを増やせたら
				{
					bt_se->Play((int)BT_SE_BP_CHARGE);	//チャージ音を鳴らす
				}
				++TotalTurnCnt;		//総合のターン数を加算する
			}

			ui->SetIsDrawUIAnime(false);		//UIのアニメーション非表示

			if (!ui->BattleCommand->GetSelectFlg())	//コマンドを選択していないときは
			{
				ui->BattleCommand->SelectOperation(keydown, sys_se);	//バトルコマンドキー操作

				if (keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//スペースキーを押されたら
				{
					if (player->PlusUseBP())	//使用するBPを増やせたら
					{
						bt_se->Play((int)BT_SE_BP_PLUS);	//使用するBP増加の音を鳴らす
					}
				}
				else if (keydown->IsKeyDownOne(KEY_INPUT_LSHIFT))	//左シフトキーを押されたら
				{
					if (player->MinusUseBP())	//使用するBPを減らせたら
					{
						bt_se->Play((int)BT_SE_BP_MINUS);	//使用するBP減少の音を鳴らす
					}
				}

			}

		}
		else				//メッセージが残っていれば
		{
			if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
			{
				sys_se->Play((int)SYS_SE_KETTEI);				//決定音を鳴らす

				bt_msg[(int)BT_MSG_ACT]->NextMsg();				//次のメッセージへ
			}
		}


		if (ui->BattleCommand->GetSelectFlg())	//コマンドを選択したら
		{
			//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ バトルコマンド毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
			switch (ui->BattleCommand->GetSelectNum())		//どのコマンドを選んだか
			{
			case (int)COMMANDE_ATACK:					//攻撃を選んだ時

				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)COMMANDE_DEFENSE:		//防御を選んだ時

				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)COMMANDE_MAGIC:		//魔法を選んだ時

				ui->DrawWindow(BT_LIST_WIN_X, BT_LIST_WIN_Y, GAME_WIDTH - BT_LIST_WIN_X, BT_LIST_WIN_HEIGHT);	//ウィンドウ描画
				ui->MgcSelect->Draw(BT_LIST_TXT_X, BT_LIST_TXT_Y);	//魔法一覧を描画

				ui->MgcSelect->SelectOperation(keydown, sys_se);	//魔法一覧のキー操作

				if (ui->MgcSelect->GetBackFlg())	//戻る選択をしたら
				{
					ui->BattleCommand->SetSelectFlg(false);	//選択してない
					ui->MgcSelect->SetBackFlg(false);		//戻る選択リセット
					ui->MgcSelect->NowSelectReset();		//現在の選択リセット
				}
				else if (ui->MgcSelect->GetSelectFlg())	//選択された時は
				{
					//選んだ魔法の消費MPが残っているMPより多かったら(魔法が使えない処理)
					if (player->GetMP() < mgc_list->GetCost(ui->MgcSelect->GetSelectNum()))
					{
						sys_se->Play((int)SYS_SE_BLIP);			//選択できない時の音を鳴らす
					}
					else		//選んだ魔法が使えた時は
					{
						player->SetChoiseSkil(ui->MgcSelect->GetSelectNum());	//選択した内容を使用する魔法として設定する
						ui->MgcSelect->NowSelectReset();						//選択要素を先頭に戻す
						ui->MgcSelect->SetSelectFlg(false);						//選択してない状態へ
						BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ
					}

				}

				break;

			case (int)COMMANDE_ITEM:			//アイテムを選んだ時

				ui->SelectUpdate(player->GetItemClass(), item_list);	//選択肢更新

				ui->DrawWindow(BT_LIST_WIN_X, BT_LIST_WIN_Y, GAME_WIDTH - BT_LIST_WIN_X, BT_LIST_WIN_HEIGHT);	//ウィンドウ描画

				if (ui->ItemSelect->GetSelectKind() != 0)	//アイテムを持っていたら
				{

					ui->DrawItemSelect(BT_LIST_TXT_X, BT_LIST_TXT_Y, player->GetItemClass());	//持っているアイテムを描画

					ui->ItemSelect->SelectOperation(keydown, sys_se);	//アイテム選択肢キー操作

					if (ui->ItemSelect->GetSelectFlg())	//アイテムを選択したら
					{

						if (player->UseItem(ui->ItemSelect->GetSelectCode()))	//アイテムを使用出来たら
						{
							bt_se->Play((int)BT_SE_RECOVERY);					//回復音を鳴らす

							//アイテムにはBPを使用できないため、使うBPをリセットする
							player->ResetUseBP();

							BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

						}
						else		//使用できなかったら
						{
							sys_se->Play((int)SYS_SE_BLIP);			//使用できない音を鳴らす
							ui->ItemSelect->SetSelectFlg(false);	//選択していない状態へ
						}
					}

					if (ui->ItemSelect->GetBackFlg())	//戻る選択をしたら
					{
						ui->BattleCommand->SetSelectFlg(false);	//選択していない
						ui->ItemSelect->SetBackFlg(false);		//戻る選択リセット
						ui->ItemSelect->NowSelectReset();		//現在の選択リセット
					}

				}
				else		//アイテムを持っていなかったら
				{
					if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//バックスペースキーを押されたら
					{
						ui->BattleCommand->SetSelectFlg(false);	//コマンドを選択していない
					}
				}

				break;

			case (int)COMMANDE_ESCAPE:		//逃げるを選んだ時

				bt_msg[(int)BT_MSG_ACT]->SetMsg(BT_ESCAPE_TEXT);	//文字列設定

				BattleStageNow = (int)ACT_MSG;	//メッセージ描画状態

				break;

			default:
				break;
			}
			//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ バトルコマンド毎の処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

		}

	}
	else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
	{
		//敵の行動選択決定処理
		enemy[EncounteEnemyType]->ActDecision();		//行動決定処理

		BattleStageNow = (int)DAMEGE_CALC;	//ダメージ計算へ

	}

	return;


}

//戦闘画面ダメージ計算状態の処理
void Bt_DamegeCalc()
{
	if (Turn == (int)MY_TURN)		//味方のターンだったら
	{
		player->DamegeCalc(enemy[EncounteEnemyType], ui->BattleCommand->GetSelectNum());		//ダメージ計算

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メッセージ設定処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

		ui->SetIsDrawUIAnime(true);			//UIのアニメーション表示

		//味方
		if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_DEFENSE)	//防御を選んだ時
		{

			bt_msg[(int)BT_MSG_ACT]->SetMsg(player->GetName());	//名前設定
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_DEF_TEXT_1);	//メッセージ内容追加
			bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_DEF_TEXT_2);		//メッセージ追加

		}
		else if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ITEM)	//アイテムを選んだ時
		{
			bt_msg[(int)BT_MSG_ACT]->SetMsg(item_list->GetName(ui->ItemSelect->GetSelectCode()));	//使用したアイテム名設定
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ITEM_TEXT_1);		//メッセージ内容追加
			if (item_list->GetItemType(ui->ItemSelect->GetSelectCode()) == ITEM_TYPE_HP)	//HP回復アイテムだったら
			{
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_ITEM_TEXT_HP);				//メッセージ追加
			}
			else if (item_list->GetItemType(ui->ItemSelect->GetSelectCode()) == ITEM_TYPE_MP)	//MP回復アイテムだったら
			{
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_ITEM_TEXT_MP);				//メッセージ追加
			}
			bt_msg[(int)BT_MSG_ACT]->AddText(std::to_string(item_list->GetRecovery(ui->ItemSelect->GetSelectCode())).c_str());	//回復量設定
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ITEM_TEXT_2);	//メッセージ内容追加

			ui->ItemSelect->NowSelectReset();					//アイテムの選択をリセット
			ui->ItemSelect->SetSelectFlg(false);				//選択していない状態へ

		}
		else					//それ以外の時
		{
			bt_msg[(int)BT_MSG_ACT]->SetMsg(player->GetName());	//名前設定
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_TEXT);		//メッセージ内容追加
			bt_msg[(int)BT_MSG_ACT]->AddMsg(std::to_string(enemy[EncounteEnemyType]->GetRecvDamege()).c_str());	//与えたダメージ設定
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_SEND_TEXT);	//メッセージ内容追加
		}

		//敵
		bt_msg[(int)BT_MSG_ACT]->AddMsg(enemy[EncounteEnemyType]->GetName());	//敵の名前設定
		bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_TEXT);		//メッセージ内容追加
		bt_msg[(int)BT_MSG_ACT]->AddMsg(std::to_string(player->GetRecvDamege()).c_str());	//受けるダメージ設定
		bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_RECV_TEXT);	//メッセージ内容追加
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メッセージ設定処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

		BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示状態へ

	}
	else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
	{
		//ダメージ計算
		BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示へ

	}

	return;

}

//戦闘画面行動メッセージ描画状態の処理
void Bt_ActMsg()
{
	bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//決定音を鳴らす

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ESCAPE)		//逃げるを選んだら
			{
				bt_se->Play((int)BT_SE_NIGERU);	//逃げるときの音を鳴らす
				bt_se->Reset();					//再生状態リセット
				SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
			}
		}

		bt_msg[(int)BT_MSG_ACT]->NextMsg();	//次のメッセージへ
		BattleStageNow = (int)DRAW_EFFECT;	//エフェクト表示状態へ
	}

	return;

}

//戦闘画面エフェクト描画状態の処理
void Bt_DrawEffect()
{
	if (Turn == (int)MY_TURN)		//味方のターンだったら
	{
		if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ATACK)	//攻撃を選んでいたら
		{
			//フェードアウトなしで描画
			Atack_effect->DrawNormal(ATK_DRAW_X, ATK_DRAW_Y, (int)NOMAL_ATACK);	//攻撃エフェクト描画

			if (bt_se->GetIsPlayed((int)BT_SE_SLASH) == false)		//再生済みでなければ
			{
				if (bt_se->GetIsPlay((int)BT_SE_SLASH) == false)		//再生中じゃなければ
				{
					bt_se->Play((int)BT_SE_SLASH);						//斬るときのSEを鳴らす
					bt_se->SetIsPlayed((int)BT_SE_SLASH, true);			//再生済み
				}

			}

			if (Atack_effect->GetIsDrawEnd())	//攻撃エフェクトの描画が終わったら
			{
				enemy[EncounteEnemyType]->DamegeSend();			//ダメージを与える
				Atack_effect->ResetIsAnime((int)NOMAL_ATACK);	//攻撃エフェクトリセット
				BattleStageNow = (int)DRAW_DAMEGE;				//ダメージ描画状態へ
			}

		}
		else if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_MAGIC)	//魔法を選んでいたら
		{
			//フェードアウトなしで描画
			Magic_effect->DrawNormal((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), player->GetChoiseSkil());	//魔法エフェクト描画

			if (bt_se->GetIsPlayed((int)BT_SE_THUNDER) == false)		//再生済みでなければ
			{
				if (bt_se->GetIsPlay((int)BT_SE_THUNDER) == false)		//再生中じゃなければ
				{
					bt_se->Play((int)BT_SE_THUNDER);						//雷のSEを鳴らす
					bt_se->SetIsPlayed((int)BT_SE_THUNDER, true);			//再生済み
				}

			}

			if (Magic_effect->GetIsDrawEnd())	//魔法エフェクトの描画が終わったら
			{
				player->SetMP(player->GetMP() - mgc_list->GetCost(player->GetChoiseSkil()));	//使った魔法に応じたMPを減らす
				Magic_effect->ResetIsAnime(player->GetChoiseSkil());							//魔法エフェクトリセット

				enemy[EncounteEnemyType]->DamegeSend();	//ダメージを与える
				BattleStageNow = (int)DRAW_DAMEGE;		//ダメージ描画状態へ
			}

		}
		else		//エフェクト描画のないコマンドを選んでいたら(防御、アイテム)
		{
			enemy[EncounteEnemyType]->DamegeSend();	//ダメージを与える
			BattleStageNow = (int)DRAW_DAMEGE;		//ダメージ描画状態へ
		}

	}
	else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
	{

		if (Boss_flg)		//ボス戦だったら
		{
			//ボスのエフェクト描画
			Boss_Atk_effect->DrawNormal((GAME_WIDTH / 2 - Boss_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				(GAME_HEIGHT / 2 - Boss_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				enemy[EncounteEnemyType]->GetChoiseSkil());

		}
		else	//ボス戦じゃなければ
		{
			//敵のエフェクト表示
			Enemy_Atk_effect->Draw((GAME_WIDTH / 2 - Enemy_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				(GAME_HEIGHT / 2 - Enemy_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				enemy[EncounteEnemyType]->GetChoiseSkil());

		}

		if (Enemy_Atk_effect->GetIsDrawEnd() || Boss_Atk_effect->GetIsDrawEnd())		//エフェクト描画終了したら
		{

			//音の再生
			if (bt_se->GetIsPlayed((int)BT_SE_DAMEGE) == false)		//再生済みでなければ
			{
				if (bt_se->GetIsPlay((int)BT_SE_DAMEGE) == false)		//再生中じゃなければ
				{
					bt_se->Play((int)BT_SE_DAMEGE);						//ダメージ野SEを鳴らす
					bt_se->SetIsPlayed((int)BT_SE_DAMEGE, true);		//再生済み
				}

			}

			//*************** エフェクトリセット処理 **************
			Enemy_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//エフェクトリセット
			Boss_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//エフェクトリセット（ボス）

			player->DamegeSend();	//プレイヤーにダメージを与える

			BattleStageNow = (int)DRAW_DAMEGE;	//ダメージ描画状態へ

		}

	}

	return;

}

//戦闘画面ダメージ描画状態の処理
void Bt_DrawDamege()
{
	//ダメージ描画
	bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//決定音を鳴らす

		bt_se->Reset();	//SEの再生状態をリセット

		if (Turn == (int)MY_TURN)			//味方のターンの時
		{
			Turn = (int)ENEMY_TURN;			//敵のターンへ
		}
		else if (Turn == (int)ENEMY_TURN)	//敵のターンの時
		{

			bt_msg[(int)BT_MSG_ACT]->SetMsg(BT_WAIT_ACT_TEXT);	//文字列設定

			++NowTurnCnt;			//ターンを加算する
			Turn = (int)MY_TURN;	//味方のターンへ
		}

		if (player->GetIsArive()==false)	//自分が死亡していたら
		{
			player->SetIsBattleWin(false);	//戦闘に敗北

			bt_msg[(int)BT_MSG_RESULT]->SetMsg(BT_LOSE_TEXT);	//リザルトメッセージ設定

			BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ

		}
		else if (enemy[EncounteEnemyType]->GetIsArive()==false)	//敵のHPが0になったら
		{
			player->SetIsBattleWin(true);						//戦闘に勝利
			player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//経験値加算

			//ドロップ処理
			//戻り値は、ドロップした物の名前
			std::string drop_name = JudgeDrop();	

			//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ リザルトメッセージ設定処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
			bt_msg[(int)BT_MSG_RESULT]->SetMsg(enemy[EncounteEnemyType]->GetName());	//名前設定
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_RESULT_TEXT);						//メッセージ内容追加

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(enemy[EncounteEnemyType]->GetName());	//敵の名前を設定
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_MIDLE_TEXT);					//メッセージ内容追加
			bt_msg[(int)BT_MSG_RESULT]->AddText(drop_name.c_str());						//ドロップした物の名前を設定
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_AF_TEXT);						//メッセージ内容追加

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(drop_name.c_str());	//ドロップした物の名前を設定
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_GET_TEXT);	//メッセージ内容追加

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(std::to_string(enemy[EncounteEnemyType]->GetEXP()).c_str());	//経験値設定
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_RESULT_GET_EXP_TEXT);				//メッセージ内容追加

			if (player->GetLevelUpFlg())		//レベルアップしたときは
			{
				bt_msg[(int)BT_MSG_RESULT]->AddMsg(BT_LEVELUP_BF_TEXT);		//メッセージ内容追加
				bt_msg[(int)BT_MSG_RESULT]->AddText(std::to_string(player->GetLevel()).c_str());	//レベル設定
				bt_msg[(int)BT_MSG_RESULT]->AddText(BT_LEVELUP_AF_TEXT);	//メッセージ内容追加
			}
			//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ リザルトメッセージ設定処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

			BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ

		}
		else	//敵、味方ともに死亡していなかったら
		{
			BattleStageNow = (int)WAIT_ACT;		//行動選択状態へ
		}

		bt_msg[(int)BT_MSG_ACT]->NextMsg();	//次のメッセージへ

		ui->BattleInit();				//バトルコマンドリセット

	}

	return;

}

//戦闘画面リザルトメッセージ描画状態の処理
void Bt_ResultMsg()
{
	bt_msg[(int)BT_MSG_RESULT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたとき
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//決定音を鳴らす

		bt_msg[(int)BT_MSG_RESULT]->NextMsg();	//次のメッセージへ

		if (bt_msg[(int)BT_MSG_RESULT]->GetIsLastMsg())		//最後のメッセージだったら
		{
			if (player->GetLevelUpFlg())			//レベルアップしていたら
			{
				if (bt_se->GetIsPlay((int)BT_SE_LEVELUP) == false)		//再生中じゃなければ
				{
					bt_se->Play((int)BT_SE_LEVELUP);	//レベルアップのSEを鳴らす
					bt_se->SetIsPlayed((int)BT_SE_SLASH, true);			//再生済み
					player->SetLevelUpFlg(false);	//レベルアップ終了
				}
			}

			if (bt_msg[(int)BT_MSG_RESULT]->GetIsMsgEnd())	//全てのメッセージ描画が終了したら
			{
				if (player->GetIsBattleWin())		//戦闘に勝利していたら
				{
					if (Boss_flg)					//倒したのがボスだったら
					{
						Clear_flg = true;			//クリアフラグを立てる
						SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//次の画面はエンド画面
					}
					else							//倒したのがボス以外だったら
					{
						SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
					}
				}
				else if (player->GetIsBattleWin() == false)	//戦闘に敗北していたら
				{
					SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//次の画面はエンド画面
				}

				BattleStageNow = (int)WAIT_ACT;		//行動選択待ち状態へ

			}

		}

	}

	return;

}

//ドロップした物の種類を判別する
//戻り値：ドロップした物の名前
const char * JudgeDrop()
{
	int drop_code = enemy[EncounteEnemyType]->Drop();	//ドロップ処理をし、ドロップしたもののコード番号を取得する

	/*
	ドロップするものには、コード番号がついている
	種類によってコード番号が異なる
	0番台　(0～99)　　：アイテム
	100番台(100～199) ：武器
	200番台(200～299) ：防具
	コード番号を、100(DROP_JUDGE_NUM)で割った結果によって種類を判別できる
	*/
	switch (drop_code / DROP_JUDGE_NUM)	//ドロップした物のコード番号から種類を判定
	{

	case (int)DROP_TYPE_ITEM:	//アイテムだった場合

		player->AddDropItem(drop_code, item_list->GetRecovery(drop_code), item_list->GetItemType(drop_code));	//アイテムを追加

		return item_list->GetName(drop_code);	//ドロップしたアイテムの名前を返す

		break;	//アイテムだった場合ここまで

	case (int)DROP_TYPE_WEAPON:	//武器だった場合

		player->AddDropWeapon(drop_code, weapon_list->GetPower(drop_code));	//武器を追加

		return weapon_list->GetName(drop_code);	//ドロップした武器の名前を返す

		break;	//武器だった場合ここまで

	case (int)DROP_TYPE_ARMOR:	//防具だった場合

		player->AddDropArmor(drop_code, armor_list->GetDefense(drop_code));	//防具を追加

		return armor_list->GetName(drop_code);	//ドロップした防具の名前を返す

	default:
		break;
	}

}
