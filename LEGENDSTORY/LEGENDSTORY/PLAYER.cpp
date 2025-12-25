//PLAYER.cpp
//プレイヤークラス

//############## ヘッダファイル読み込み ################
#include "PLAYER.hpp"

//############## クラス定義 ##################

//コンストラクタ
PLAYER::PLAYER()
{

	this->Collision = new COLLISION();		//当たり判定の領域を作成

	this->sikaku_draw = new SIKAKU();		//描画領域を作成

	this->Weapon = new WEAPON();			//武器を生成
	this->Armor = new ARMOR();				//防具を生成

	this->Item = new ITEM();				//アイテムを生成

	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	delete this->Anime;				//Animeを破棄
	delete this->Collision;			//Collisionを破棄
	delete this->sikaku_draw;		//sikaku_drawを破棄
	delete this->Weapon;			//Weaponを破棄
	delete this->Armor;				//Armorを破棄
	delete this->Item;				//Itemを破棄

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Skil.swap(v);		//空と中身を入れ替える

	return;
}

//***************************** 初期化、設定関係 **********************************
//初期設定
bool PLAYER::SetInit()
{
	this->Dist = (int)FLONT;					//初期向き設定
	this->MoveSpeed = PLAYE_DEFAULT_MOVESPEED;	//初期移動速度設定

	//装備関係
	//読み込んだセーブデータから、武器、防具を装備しているか判定する
	if (this->Equip_WeaponCode != PLAYER_INIT_VALUE)	//武器コードが初期値じゃなければ
	{
		this->EquipAtk = this->Weapon->GetAtk(this->Equip_WeaponCode);	//装備コードを基に、装備の攻撃力を取得
		this->Weapon->SetEquipFlg(this->Equip_WeaponCode, true);		//武器を装備している
	}
	else		//初期値だった場合
	{
		this->EquipAtk = 0;	//初期化
	}

	if (this->Equip_ArmorCode != PLAYER_INIT_VALUE)	//防具コードが初期値じゃなければ
	{
		this->EquipDef = this->Armor->GetDef(this->Equip_ArmorCode);	//装備コードを基に、装備の防御力を取得
		this->Armor->SetEquipFlg(this->Equip_ArmorCode, true);			//防具を装備している
	}
	else	//初期値だった場合
	{
		this->EquipDef = 0;	//初期化
	}

	this->Anime->SetSize();	//画像のサイズ設定

	this->IsKeyDown = false;//キーボード押されていない
	this->IsKeyOperation = true;	//キー操作可能
	this->IsMenu = false;	//メニューウィンドウ描画されていない

	this->ChengeMapKind = (int) MAP_CHENGE_NONE;	//マップ切り替えなし

	this->BattleInit();		//戦闘関係の要素初期化


	//描画領域作成
	this->sikaku_draw->SetValue(this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->Anime->GetWidth(),
		this->Anime->GetHeight());

	//当たり判定領域作成
	this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->Anime->GetWidth() - RECT_STAGGER * 2,
		this->Anime->GetHeight());

	return true;
}

//アニメーション画像設定
/*
引　数：const char *：画像のディレクトリ
引　数：const char *：画像の名前
引　数：int：画像の総分割数
引　数：int：画像の横向きの分割数
引　数：int：画像の縦向きの分割数
引　数：int：画像の分割された横の大きさ
引　数：int：画像の分割された縦の大きさ
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
*/
bool PLAYER::SetAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->Anime = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->Anime->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}

//戦闘で使用するものを初期化する
void PLAYER::BattleInit(void)
{
	this->BP = START_BP;	//BPを初期化
	this->UseBPNum = 0;		//使用するBPを初期化

	this->ChoiseSkil = -1;	//使用するスキルリセット
	this->RecvDamege = 0;	//受けるダメージリセット

	this->IsActMsg = false;		//行動メッセージ表示中かリセット
	this->IsBattleWin = false;	//戦闘に勝利したかリセット
	this->LevelUp_flg = false;//レベルアップメッセージフラグリセット

	return;
}

//*********************** ステータス関係 ******************************
//セッタ

//現在のMP設定
void PLAYER::SetMP(int mp)
{
	this->NowMP = mp;
}

//使用するスキル設定
void PLAYER::SetChoiseSkil(int type)
{
	this->ChoiseSkil = this->Skil[type];		//指定されたスキルを、使用するスキルとして設定
	return;
}

//ゲッタ
//名前取得
const char * PLAYER::GetName(void)
{
	return this->Name.c_str();
}

//レベル取得
int PLAYER::GetLevel(void)
{
	return this->Level;
}

//経験値の最大値取得
int PLAYER::GetMaxEXP(void)
{
	return this->MaxEXP;
}

//現在の経験値取得
int PLAYER::GetEXP(void)
{
	return this->NowEXP;
}

//最大体力取得
int PLAYER::GetMaxHP(void)
{
	return this->MaxHP;
}

//現在の体力取得
int PLAYER::GetHP(void)
{
	return this->NowHP;
}

//最大MP取得
int PLAYER::GetMaxMP(void)
{
	return this->MaxMP;
}

//現在のMP取得
int PLAYER::GetMP(void)
{
	return this->NowMP;
}

//攻撃力取得
int PLAYER::GetATK(void)
{
	return this->ATK;
}

//防御力取得
int PLAYER::GetDEF(void)
{
	return this->DEF;
}

//速度取得
int PLAYER::GetSPD(void)
{
	return this->SPD;
}

//使用するスキルを取得
int PLAYER::GetChoiseSkil(void)
{
	return this->ChoiseSkil;
}

//生きているか取得
bool PLAYER::GetIsArive()
{
	return this->IsArive;
}

//*************************** キー関係 *****************************
//キー操作可能か設定
void PLAYER::SetIsKeyOpe(bool iskeyope)
{
	this->IsKeyOperation = iskeyope;
	if (!this->IsKeyOperation)	//キー操作不可のときは
	{
		this->IsKeyDown = false;	//キー操作不可のときは、キー入力なしに設定
	}
	return;
}

//キーボード操作できるか取得
bool PLAYER::GetIsKeyOpe()
{
	return this->IsKeyOperation;
}

//キー入力があるか取得
bool PLAYER::GetIsKeyDown()
{
	return this->IsKeyDown;
}

//キー処理関係
//操作
void PLAYER::Operation(KEYDOWN *keydown, COLLISION *map[][MAP_YOKO])
{
	if (this->IsKeyOperation)	//キー操作可能なら
	{
		if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_W))		//メニュー描画中でなく、Wキーを押しているとき
		{
			this->IsKeyDown = true;		//キー入力あり
			this->Dist = BACK;			//移動方向を上にする

			//領域を少し上へずらす
			this->Collision->Top -= RECT_STAGGER;
			this->Collision->Bottom -= RECT_STAGGER;

			//マップとの当たり判定
			if (this->CheckDetectionMap(map) == false)	//通行できるなら
			{
				this->MoveUp();				//上へ移動
			}

		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//メニュー描画中でなく、Sキーを押しているとき
		{
			this->IsKeyDown = true;		//キー入力あり
			this->Dist = FLONT;			//移動方向下

			//領域を少し下へずらす
			this->Collision->Top += RECT_STAGGER;
			this->Collision->Bottom += RECT_STAGGER;

			//マップとの当たり判定
			if (this->CheckDetectionMap(map) == false)	//通行できるなら
			{
				this->MoveDown();				//下へ移動
			}


		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//メニュー描画中でなく、Aキーを押しているとき
		{
			this->IsKeyDown = true;		//キー入力あり
			this->Dist = LEFT;			//移動方向左

			//領域を少し左へずらす
			this->Collision->Left -= RECT_STAGGER;
			this->Collision->Right -= RECT_STAGGER;

			//マップとの当たり判定
			if (this->CheckDetectionMap(map) == false)	//通行できるなら
			{
				this->MoveLeft();				//左へ移動
			}

		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//メニュー描画中でなく、Dキーを押しているとき
		{
			this->IsKeyDown = true;		//キー入力あり
			this->Dist = RIGHT;			//移動方向右

			//領域を少し右へずらす
			this->Collision->Left += RECT_STAGGER;
			this->Collision->Right += RECT_STAGGER;

			//マップとの当たり判定
			if (this->CheckDetectionMap(map) == false)	//通行できるなら
			{
				this->MoveRight();				//右へ移動
			}

		}
		else
		{
			this->IsKeyDown = false;	//キー入力なし
		}

		//描画領域再設定
		this->sikaku_draw->SetValue(
			this->sikaku_draw->Left,
			this->sikaku_draw->Top,
			this->sikaku_draw->Width,
			this->sikaku_draw->Height);

		//領域再設定
		this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
			this->sikaku_draw->Top,
			this->Anime->GetWidth() - RECT_STAGGER * 2,
			this->Anime->GetHeight());

	}

	return;

}

//上へ移動
void PLAYER::MoveUp()
{
	if (this->sikaku_draw->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->MoveSpeed;	//当たり判定と、描画位置を上へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_UP;//切り替え方向、上
	}

	return;
}

//下へ移動
void PLAYER::MoveDown()
{
	if (this->sikaku_draw->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->sikaku_draw->Top += this->MoveSpeed;	//下へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_DOWN;	//切り替え方向、下
	}
	return;
}

//左へ移動
void PLAYER::MoveLeft()
{
	if (this->sikaku_draw->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->MoveSpeed;	//左へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_LEFT;	//切り替え方向、左
	}
	return;
}

//右へ移動
void PLAYER::MoveRight()
{
	if (this->sikaku_draw->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->sikaku_draw->Left += this->MoveSpeed;	//右へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_RIGHT;	//切り替え方向、右
	}
	return;
}

//********************** 位置関係 *****************************
//位置を設定
//引数：int：X位置を相対的に指定
//引数：int：Y位置を相対的に指定
void PLAYER::SetPosRelative(int x, int y)
{
	this->Collision->Left += x;	//X位置を設定
	this->Collision->Top += y;	//Y位置を設定

	this->sikaku_draw->Left += x;
	this->sikaku_draw->Top += y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//位置を設定
//引数：int：X位置を絶対値で指定
//引数：int：Y位置を絶対値で指定
void PLAYER::SetPosAbsolute(int x, int y)
{
	this->Collision->Left = x;	//X位置を設定
	this->Collision->Top = y;	//Y位置を設定

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//現在の位置を取得
/*
引数：int *：X位置をセットする
引数：int *：Y位置をセットする
*/
void PLAYER::GetNowPos(int *x, int *y)
{
	*x = this->sikaku_draw->Left;	//X位置設定
	*y = this->sikaku_draw->Top;	//Y位置設定
	return;
}

//現在の位置を設定
/*
引数：int：現在のX位置
引数：int：現在のY位置
*/
void PLAYER::SetNowPos(int x, int y)
{
	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//領域再設定
	this->Collision->SetValue(
		this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width - RECT_STAGGER * 2,
		this->sikaku_draw->Height);


}

//********************************* マップ関係 ***********************************
//マップ切り替えの種類リセット
void PLAYER::ResetChengeMapKind(void)
{
	this->ChengeMapKind = PLAYER_INIT_VALUE;	//初期化
	return;
}

//マップ切り替えをしたときにプレイヤーの位置を設定
//引数：int：切り替えた方向
void PLAYER::SetChengePos(int kind)
{
	switch (kind)	//切り替え方向毎に処理
	{

	case (int)MAP_CHENGE_UP:	//上へ切り替えるとき、ここから

		this->SetPosRelative(0, GAME_HEIGHT - (this->Collision->Height + RECT_STAGGER));	//位置を修正

		break;

	case (int)MAP_CHENGE_DOWN:	//下へ切り替えるとき、ここから

		this->SetPosRelative(0, -(this->Collision->Top - RECT_STAGGER));	//位置を修正

		break;

	case (int)MAP_CHENGE_LEFT:	//左へ切り替えるとき、ここから

		this->SetPosRelative(GAME_WIDTH - (this->Collision->Width + RECT_STAGGER), 0);	//位置を修正

		break;

	case (int)MAP_CHENGE_RIGHT:	//右へ切り替えるとき、ここから

		this->SetPosRelative(-(this->Collision->Left - RECT_STAGGER), 0);	//位置を修正

		break;

	default:
		break;
	}

	return;

}

//切り替えるマップの種類を取得
int PLAYER::GetChengeMapKind()
{
	return this->ChengeMapKind;
}

//マップとの当たり判定(当たった場所を取得しない)
bool PLAYER::CheckDetectionMap(COLLISION * map[][MAP_YOKO])
{

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			//キャラクターの当たっている場所を取得
			if (map[tate][yoko]->DetectionCheck(this->Collision))
			{
				return true;
			}
		}
	}

	return false;
}

//*************************** メニュー関係 *******************************
//メニュー描画中か設定
void PLAYER::SetIsMenu(bool ismenu)
{
	this->IsMenu = ismenu;
	return;
}

//メニュー描画中か取得
bool PLAYER::GetIsMenu()
{
	return this->IsMenu;
}

//************************* 戦闘関係 ****************************
//戦闘に勝ったか取得
void PLAYER::SetIsBattleWin(bool isbattlewin)
{
	this->IsBattleWin = isbattlewin;
	return;
}

//レベルアップしたか取得
void PLAYER::SetLevelUpFlg(bool start_flg)
{
	this->LevelUp_flg = start_flg;
	return;
}

//受けるダメージを取得
int PLAYER::GetRecvDamege()
{
	return this->RecvDamege;
}

//行動メッセージ表示中か取得
bool PLAYER::GetIsActMsg()
{
	return this->IsActMsg;
}

//戦闘に勝ったか取得
bool PLAYER::GetIsBattleWin()
{
	return this->IsBattleWin;
}

//レベルアップフラグ取得
bool PLAYER::GetLevelUpFlg()
{
	return this->LevelUp_flg;
}

//************************** 装備関係 *********************************
//武器関係
//装備攻撃力取得
int PLAYER::GetEquipAtk(void)
{
	return this->EquipAtk;	//装備攻撃力取得
}

//武器を装備する
void PLAYER::EquipWeapon(int element)
{

	this->Equip_WeaponCode = this->Weapon->GetCode(element);	//装備のコード番号を取得

	this->EquipAtk = this->Weapon->GetAtk(this->Equip_WeaponCode);	//装備コードを基に、装備の攻撃力を取得

	this->Weapon->SetEquipFlg(this->Equip_WeaponCode, true);	//武器を装備している

	return;

}

//武器クラスを取得
WEAPON * PLAYER::GetWeaponClass(void)
{
	return this->Weapon;
}

//武器の攻撃力を設定
void PLAYER::SetWeaponAtk(LIST_WEAPON *list_weapon)
{

	for (int i = 0; i < this->Weapon->GetSize(); ++i)	//武器数分繰り返し
	{
		this->Weapon->SetAtk(list_weapon->GetPower(this->Weapon->GetCode(i)));	//武器攻撃力設定
	}

	return;
}

//ドロップした武器の追加
void PLAYER::AddDropWeapon(int code, int value)
{
	//武器登録
	if (this->Weapon->Add(code))		//未登録だったら
	{
		this->Weapon->SetAtk(value);	//攻撃力登録
	}
	return;
}

//防具関係
//装備防御力取得
int PLAYER::GetEquipDef(void)
{
	return this->EquipDef;	//装備防御力取得
}

//防具を装備する
void PLAYER::EquipArmor(int element)
{

	this->Equip_ArmorCode = this->Armor->GetCode(element);	//装備のコード番号を取得

	this->EquipDef = this->Armor->GetDef(this->Equip_ArmorCode);	//装備コードを基に、装備の防御力を取得

	this->Armor->SetEquipFlg(this->Equip_ArmorCode, true);	//防具を装備している

	return;

}

//防具クラスを取得
ARMOR * PLAYER::GetArmorClass(void)
{
	return this->Armor;
}

//防具の防御力設定
void PLAYER::SetArmorDef(LIST_ARMOR *list_armor)
{
	for (int i = 0; i < this->Armor->GetSize(); ++i)	//防具数分繰り返し
	{
		this->Armor->SetDef(list_armor->GetDefense(this->Armor->GetCode(i)));	//防具防御力設定
	}
	return;
}

//ドロップした防具の追加
void PLAYER::AddDropArmor(int code, int value)
{
	//防具登録
	if (this->Armor->Add(code))	//防具が未登録だったら
	{
		this->Armor->SetDef(value);	//防御力設定
	}
	return;
}

//************************** アイテム関係 ***************************
//アイテム使用処理
bool PLAYER::UseItem(int code)
{
	if (this->Item->GetItemType(code) == ITEM_TYPE_HP)	//アイテムタイプがHP回復の場合
	{

		if (this->NowHP == this->MaxHP)	//現在のHPが満タンだったら
		{
			return false;		//アイテムは使用できない
		}

		this->NowHP += this->Item->GetRecovery(code);	//回復量を取得し、現在のHPに加える

		if (this->NowHP > this->MaxHP)	//最大HPより多くなったら
		{
			this->NowHP = this->MaxHP;	//現在のHPを最大HPと同じにする
		}

	}
	else if (this->Item->GetItemType(code) == ITEM_TYPE_MP)	//アイテムタイプがMP回復の場合
	{

		if (this->NowMP == this->MaxMP)		//現在のMPが満タンだったら
		{
			return false;		//アイテムは使用できない
		}

		this->NowMP += this->Item->GetRecovery(code);	//回復量を取得し、現在のMPに加える

		if (this->NowMP > this->MaxMP)		//最大MPより多くなったら
		{
			this->NowMP = this->MaxMP;		//現在のMPを最大MPと同じにする
		}
	}

	this->Item->DecreasePossession(code);	//アイテムの所持数を減らす

	return true;
}

//アイテムクラスを取得
ITEM * PLAYER::GetItemClass(void)
{
	return this->Item;
}

//アイテムの回復量を設定
void PLAYER::SetItemRecovery(LIST_ITEM *list_item)
{
	for (int i = 0; i < this->Item->GetSize(); ++i)	//アイテム数分繰り返し
	{
		this->Item->SetRecovery(list_item->GetRecovery(this->Item->GetCode(i)),	//アイテム回復量設定
			list_item->GetItemType(this->Item->GetCode(i)));					//アイテムタイプ設定	
	}
}

//アイテムの追加処理
void PLAYER::AddDropItem(int code, int value, char type)
{
	this->Item->AddItem(code, value, type);	//アイテム追加

	return;
}

//************************ セーブデータ関係 ***************************
//セーブデータ読み込み
bool PLAYER::LoadData(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->Name = buf.c_str();		//名前読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->Level = atoi(buf.c_str());//レベル読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxEXP = atoi(buf.c_str());//経験値の最大値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowEXP = atoi(buf.c_str());//現在の経験値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxHP = atoi(buf.c_str());//最大HP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowHP = atoi(buf.c_str());//現在のHP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxMP = atoi(buf.c_str());//最大MP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowMP = atoi(buf.c_str());//現在のMP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->ATK = atoi(buf.c_str());	//ATK読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->DEF = atoi(buf.c_str());	//DEF読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->SPD = atoi(buf.c_str());	//SPD読み込み

	int x = 0, y = 0;				//位置取得用
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	x = atoi(buf.c_str());			//X位置格納
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	y = atoi(buf.c_str());			//Y位置格納

	this->SetNowPos(x, y);			//現在位置設定

	int size = 0;					//要素数を入れる変数
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	size = atoi(buf.c_str());		//スキルの数を取得

	int check = 0;					//改行が入っていないか確認するために使用
	for (int i = 0; i < size; ++i)	//スキルの数だけ繰り返し
	{

		if (i == size - 1)	//最後の要素だったら
		{
			std::getline(ifs, buf, '\n');	//改行まで読み込み
		}
		else	//最後じゃなければ
		{
			std::getline(ifs, buf, ',');	//カンマまで読み込み
		}

		this->Skil.push_back(atoi(buf.c_str()));	//スキル読み込み
	}


	//******************* アイテムデータ読み込み ************************
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	size = atoi(buf.c_str());		//アイテム数読み込み

	int code = 0, posse = 0;		//コード番号と所持数

	for (int i = 0; i < size; ++i)	//アイテム数だけ繰り返し
	{
		std::getline(ifs, buf, ',');	//カンマまで読み込み
		code = (atoi(buf.c_str()));		//アイテムコード読み込み

		if (i == size - 1)	//最後の要素だったら
		{
			std::getline(ifs, buf, '\n');	//改行まで読み込み
		}
		else	//最後じゃなければ
		{
			std::getline(ifs, buf, ',');	//カンマまで読み込み
		}

		posse = (atoi(buf.c_str()));		//所持数設定

		this->Item->LoadData(code, posse);	//読み込んだアイテムデータを設定
	}

	//************************ 武器データ読み込み ****************************
	std::getline(ifs, buf, ',');		//カンマまで読み込み
	size = atoi(buf.c_str());			//武器数読み込み

	for (int i = 0; i < size; ++i)	//武器数分繰り返し
	{
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		code = atoi(buf.c_str());			//武器コード読み込み

		if (i == size - 1)	//最後の要素だったら
		{
			std::getline(ifs, buf, '\n');	//改行まで読み込み
		}
		else	//最後じゃなければ
		{
			std::getline(ifs, buf, ',');		//カンマまで読み込み
		}

		posse = atoi(buf.c_str());			//所持数読み込み

		this->Weapon->LoadData(code, posse);	//読み込んだデータを設定

	}

	//*********************** 防具データ読み込み ****************************
	std::getline(ifs, buf, ',');		//カンマまで読み込み
	size = atoi(buf.c_str());			//防具数読み込み
	for (int i = 0; i < size; ++i)	//防具数分繰り返し
	{
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		code = atoi(buf.c_str());			//防具コード読み込み

		if (i == size - 1)	//最後の要素だったら
		{
			std::getline(ifs, buf, '\n');	//改行まで読み込み
		}
		else	//最後じゃなければ
		{
			std::getline(ifs, buf, ',');		//カンマまで読み込み
		}

		posse = atoi(buf.c_str());			//所持数読み込み

		this->Armor->LoadData(code, posse);	//読み込んだデータを設定

	}

	//装備している武器と防具のコード番号を読み込み
	std::getline(ifs, buf, ',');				//カンマまで読み込み
	this->Equip_WeaponCode = atoi(buf.c_str());	//武器コード設定

	std::getline(ifs, buf, ',');				//カンマまで読み込み
	this->Equip_ArmorCode = atoi(buf.c_str());	//防具コード設定

	return true;	//読み込み成功

}

//セーブ
bool PLAYER::Save(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//プレイヤー情報を書き出す
	ofs << this->Name << ',';		//名前書き出し
	ofs << this->Level << ',';		//レベル
	ofs << this->MaxEXP << ',';		//経験値の最大値
	ofs << this->NowEXP << ',';		//現在の経験値

	ofs << this->MaxHP << ',';		//最大HP
	ofs << this->NowHP << ',';		//現在のHP
	ofs << this->MaxMP << ',';		//最大MP
	ofs << this->NowMP << ',';		//現在のMP

	ofs << this->ATK << ',';		//攻撃力
	ofs << this->DEF << ',';		//防御力
	ofs << this->SPD << ',';		//速さ

	int x = 0, y = 0;				//現在の位置取得用
	this->GetNowPos(&x, &y);		//現在位置取得
	ofs << x << ',' << y << ',';	//現在位置セーブ

	ofs << this->Skil.size() << ',';//スキル数書き込み

	for (int i = 0; i < this->Skil.size(); ++i)		//スキルの数分書き込む
	{
		if (i == this->Skil.size() - 1)			//最後スキルの書き込みだったら
		{
			ofs << this->Skil[i] << '\n';			//スキル書き込み(最後は改行)
		}
		else	//最後じゃなかったら
		{
			ofs << this->Skil[i] << ',';			//スキル書き込み(カンマで区切る)
		}

	}

	//************************* アイテムデータ書き込み *******************************
	ofs << this->Item->GetSize() << ',';	//アイテム数書き込み

	for (int i = 0; i < this->Item->GetSize(); ++i)	//登録してあるアイテムの数分繰り返す
	{
		ofs << this->Item->GetCode(i) << ',';		//アイテムコード書き出し
		if (i == this->Item->GetSize() - 1)	//最後の書き込みだったら
		{
			ofs << this->Item->GetPossession(this->Item->GetCode(i)) << '\n';	//所持数書き出し(最後は改行)
		}
		else	//最後じゃなかったら
		{
			ofs << this->Item->GetPossession(this->Item->GetCode(i)) << ',';	//所持数書き出し(カンマで区切る)
		}

	}

	//************************* 武器データ書き出し *********************************
	ofs << this->Weapon->GetSize() << ',';	//武器数書き出し

	for (int i = 0; i < this->Weapon->GetSize(); ++i)//武器の数分繰り返す
	{
		ofs << this->Weapon->GetCode(i) << ',';	//武器コード書き出し
		if (i == this->Weapon->GetSize() - 1)	//最後の書き込みだったら
		{
			ofs << this->Weapon->GetPossession(this->Weapon->GetCode(i)) << '\n';	//所持数書き出し(最後は改行)
		}
		else	//最後じゃなかったら
		{
			ofs << this->Weapon->GetPossession(this->Weapon->GetCode(i)) << ',';	//所持数書き出し(カンマで区切る)
		}
	}

	//**************************** 防具データ書き出し ******************************
	ofs << this->Armor->GetSize() << ',';	//防具数書き出し

	for (int i = 0; i < this->Armor->GetSize(); ++i)	//防具数分繰り返す
	{
		ofs << this->Armor->GetCode(i) << ',';			//防具コード書き出し
		if (i == this->Armor->GetSize() - 1)	//最後の書き込みだったら
		{
			ofs << this->Armor->GetPossession(this->Armor->GetCode(i)) << '\n';	//所持数書き出し(最後は改行)
		}
		else	//最後じゃなかったら
		{
			ofs << this->Armor->GetPossession(this->Armor->GetCode(i)) << ',';	//所持数書き出し(カンマで区切る)
		}
	}

	//装備している装備コード書き出し
	ofs << this->Equip_WeaponCode << ',';	//装備している武器コード書き出し
	ofs << this->Equip_ArmorCode << '\n';	//装備している防具コード書き出し

	return true;		//セーブ成功

}

//************************* BP関係 ***************************
//BP取得
int PLAYER::GetBP(void)
{
	return this->BP;
}

//BP加算
bool PLAYER::AddBP(void)
{
	if (this->BP < MAX_BP)	//現在のBPがBPの最大値より小さかったら
	{
		++this->BP;
		return true;	//BPを増やせた
	}
	return false;		//BPを増やせなかった
}

//使用するBPを取得
int PLAYER::GetUseBP(void)
{
	return this->UseBPNum;
}

//使用するBPを増やす
bool PLAYER::PlusUseBP(void)
{
	if (this->UseBPNum < this->BP)	//使用するBPが現在持っているBPよりも少なかったら
	{
		if (this->UseBPNum < MAX_USE_BP)	//現在の使用BPが、一回で使用できるBPよりも少なかったら
		{
			++this->UseBPNum;	//使用するBPを増やす
			return true;	//増やせた
		}
	}
	return false;	//増やせなかった
}

//使用するBPを減らす
bool PLAYER::MinusUseBP(void)
{
	if (this->UseBPNum > 0)	//使用するBPが0より多かったら
	{
		--this->UseBPNum;		//使用するBPを減らす
		return true;		//減らせた
	}
	return false;	//減らせなかった
}

//使用するBPをリセットする
void PLAYER::ResetUseBP(void)
{
	this->UseBPNum = 0;	//使用するBPをリセット
	return;
}

//BPによって強化される倍率を取得(ダメージ計算内で使用)
double PLAYER::GetBPBoostValue(void)
{
	switch (this->UseBPNum)	//使用するBPの数によって、返す強化倍率を変える
	{

	case (int)USE_BP_1:	//使用するBPが1個の場合

		return BP_BOOST_LEVEL1;

		break;	//使用するBPが1個のときここまで

	case (int)USE_BP_2:	//BP2個のとき

		return BP_BOOST_LEVEL2;

		break;	//BP2個のときここまで

	case (int)USE_BP_3:	//BP3個のとき

		return BP_BOOST_LEVEL3;

		break;	//BP3個のときここまで

	default:	//それ以外のとき(BP未使用の時など)

		return BP_BOOST_LEVEL0;

		break;
	}
}

//BPを使用する
void PLAYER::BPUse(void)
{
	this->BP -= this->UseBPNum;	//使用した分BPを減らす
	this->UseBPNum = 0;			//使用するBPをリセット
	return;
}

//************************** ダメージ関係 ************************
//ダメージ計算
void PLAYER::DamegeCalc(ENEMY *enemy, int choiecommand)
{

	double bp_value = this->GetBPBoostValue();	//BPによる強化倍率を取得
	switch (choiecommand)		//選択したコマンド
	{

	case(int)COMMANDE_ATACK:				//攻撃を選んだ時の処理ここから

		//与えるダメージ計算
		//自分攻撃力(攻撃+装備攻撃) * BPの強化倍率 - 敵防御力
		enemy->SetRecvDamege((this->ATK + this->EquipAtk) * bp_value - enemy->GetDEF());

		//受けるダメージ計算
		//敵攻撃力 - 自分防御力(防御+装備防御) * BPの強化倍率
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//攻撃を選んだ時の処理ここまで

	case (int)COMMANDE_DEFENSE:			//防御を選んだ時の処理ここから

		//与えるダメージ計算
		enemy->SetRecvDamege(0);		//敵、受けるダメージ0

		//受けるダメージ計算
		//防御力を強化してダメージ計算
		//敵攻撃力 - 自分防御力((防御+装備防御) * 防御強化値) * BPの強化倍率
		this->RecvDamege = enemy->GetATK() - ((this->DEF + this->EquipDef) * DEF_BOOST) * bp_value;

		break;					//防御を選んだ時の処理ここまで

	case (int)COMMANDE_MAGIC:			//魔法を選んだ時の処理ここから

		//与えるダメージ計算
		//自分の攻撃力を強化してダメージ計算
		//魔法攻撃力を追加して、通常攻撃と分ける予定
		//自分攻撃力((攻撃+装備攻撃) * 魔法強化値) * BPの強化倍率 - 敵防御力
		enemy->SetRecvDamege(((this->ATK + this->EquipAtk) * ATK_BOOST) * bp_value - enemy->GetDEF());

		//受けるダメージ計算
		//敵攻撃力 - 自分防御力(防御+装備防御) * BPの強化倍率
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//魔法を選んだ時の処理ここまで

	case(int)COMMANDE_ITEM:				//アイテムを選んだ時の処理ここから

		//与えるダメージ計算
		//与えるダメージ0
		enemy->SetRecvDamege(0);

		//受けるダメージ計算
		//敵攻撃力 - 自分防御力(防御+装備防御) * BPの強化倍率
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//アイテムを選んだ時の処理ここまで

	default:
		break;
	}

	if (this->RecvDamege < 0)	//受けるダメージが0より少ないときは
	{
		this->RecvDamege = 0;	//受けるダメージ0
	}

	if (enemy->GetRecvDamege() < 0)	//敵に与えるダメージが0より少ないときは
	{
		enemy->SetRecvDamege(0);	//与えるダメージ0
	}

	this->BPUse();	//BPを使用する

	return;
}

//ダメージを与える
void PLAYER::DamegeSend(void)
{
	this->NowHP -= this->RecvDamege;	//現在のHPから、受けるダメージを引く

	if (this->NowHP <= 0)	//HPが0以下になったら
	{
		this->NowHP = 0;		//HPは0
		this->IsArive = false;	//死亡
	}

	return;

}

//************************* 描画関係 ******************************
//描画できるか取得
bool PLAYER::GetIsDraw()
{
	return this->IsDraw;
}

//描画
void PLAYER::DrawWalk()
{
	if (this->IsDraw)		//描画してよい時
	{
		if (this->IsArive)	//生きているとき
		{
			if (this->IsKeyDown)		//キーボードが押されているとき
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, true);	//アニメーションで描画

			}
			else						//キーボードが押されていないとき
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, false);	//通常描画
			}
		}
	}
}

//************************* その他処理関係 ************************
//経験値追加処理
void PLAYER::AddExp(int exp)
{
	this->NowEXP += exp;	//現在の経験値に加算する

	if (this->NowEXP >= this->MaxEXP)		//現在の経験値が経験値の最大値以上になったら
	{
		int work = 0;	//退避用変数
		work = this->NowEXP - this->MaxEXP;	//最大値を超過した分を保管

		this->MaxEXP += EXP_INCREASE_VALUE * this->Level;	//経験値の最大値を増やす(経験値の増え幅 * 現在のレベル)
		this->NowEXP = 0;		//現在の経験値を0に戻す
		this->NowEXP += work;	//超過した分の経験値を加算する

		//ステータスの増加処理
		this->MaxHP += HP_INCREASE_VALUE;	//最大HPを増やす
		this->MaxMP += MP_INCREASE_VALUE;	//最大MPを増やす
		this->ATK += ATK_INCREASE_VALUE;	//攻撃力を増やす
		this->DEF += DEF_INCREASE_VALUE;	//防御力を増やす
		this->SPD += SPD_INCREASE_VALUE;	//速さを増やす

		//HPとMPを全回復させる
		this->NowHP = this->MaxHP;
		this->NowMP = this->MaxMP;

		this->Level++;			//レベルを一つ上げる
		this->LevelUp_flg = true;	//レベルアップメッセージの表示をスタートする
	}
	return;
}

//回復させる
void PLAYER::Recovery(void)
{
	this->NowHP = this->MaxHP;	//HP回復
	this->NowMP = this->MaxMP;	//MP回復

	this->IsArive = true;		//生きている

	return;
}
