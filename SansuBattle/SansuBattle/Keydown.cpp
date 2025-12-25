/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* KeyDown.cpp     																				   */
/* KeyDownクラス																				   */
/* 一つのインスタンスのみにする																	   */

//########## ヘッダーファイル読み込み ##########
#include "KeyDown.hpp"

//########## クラスの定義 ##########

//インスタンスを生成
char KeyDown::AllKeyState[256];

//キーの入力状態を更新する
VOID KeyDown::KeyDownUpdate(VOID)
{
	char TempKey[256];			//一時的に、現在のキーの入力状態を格納する

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
BOOL KeyDown::IsKeyDown(int keycode)
{
	if (this->AllKeyState[keycode] != 0)
		return TRUE;
	else
		return FALSE;
}

//キーを押した瞬間だけtrueを返す
bool KeyDown::IsKeyDownOne(int keycode)
{
	if (this->AllKeyState[keycode] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//キー入力があるか取得
bool KeyDown::IsKeyInput()
{
	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) == 0)	//キー入力があれば
	{
		return true;
	}
	else	//なければ
	{
		return false;
	}
}

//入力中のキーコードを取得
//戻り値：int：入力中のキーコード、
//入力中のキーコードがない場合、－1を返す
int KeyDown::GetInputKeyCode()
{

	for (int i = 0; i < 256; i++)
	{
		if (this->AllKeyState[i] == 1)
		{
			return i;
		}
	}

	return -1;

}

//コンストラクタ
KeyDown::KeyDown()
{
}

//デストラクタ
KeyDown::~KeyDown()
{
}


//########## 外部オブジェクト ##########
extern KeyDown *keydown;