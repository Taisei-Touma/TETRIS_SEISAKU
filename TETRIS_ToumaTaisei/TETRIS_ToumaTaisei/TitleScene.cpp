#include"TitleScene.h"
#include"InputControl.h"
#include"SceneManager.h"
#include"DxLib.h"

/**************************
* マクロ定義
**************************/

/**************************
* 型定義
**************************/
enum
{
	E_TITLE_BGM,		//0
	E_TITLE_SE_CURSOR,	//1
	E_TITLE_SE_SELECT,	//2
	E_SOUND_MAX			//3
};

/**************************
* グローバル変数
**************************/
int cursor_number;
int sounds[E_SOUND_MAX];

/**************************
* プロトタイプ宣言
**************************/

/**************************
* タイトル画面：初期化処理
* 引数：なし
* 戻り値：エラー情報(-1:異常有, -1以外:正常終了)
**************************/
int TitleScene_Initialize(void)											//Initialize == 初期化
{
	int ret = 0;

	cursor_number = 0;

	sounds[E_TITLE_BGM] = LoadSoundMem("sounds/BGM041.ogg");			//sounds/BGM041.oggをロードし、識別番号をsounds[E_TITLE_BGM]に格納

	sounds[E_TITLE_SE_CURSOR] = LoadSoundMem("sounds/SE1.mp3");			//sounds/SE1.mp3をロードし、識別番号をsounds[E_TITLE_SE_CURSOR]に格納

	sounds[E_TITLE_SE_SELECT] = LoadSoundMem("sounds/SE2.mp3");			//sounds/SE2.mp3をロードし、識別番号をsounds[E_TITLE_SE_SELECT]に格納

	//ChangeVolumeSoundMem は 再生する音の音量を設定します。0は無音、255で最大音量です。
	ChangeVolumeSoundMem(120, sounds[E_TITLE_SE_CURSOR]);
	ChangeVolumeSoundMem(80, sounds[E_TITLE_SE_SELECT]);

	for (int i = 0; i < E_SOUND_MAX; i++)
	{
		if (sounds[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	return ret;
}

/**************************
* タイトル画面：更新処理
* 引数：なし
* 戻り値：なし
**************************/
void TitleScene_Update(void)
{
	//BGMが流れていない時に再生
	//CheckSoundMem は メモリに読み込んだ音声データが再生中か調べる　戻り値が1なら再生中、0なら再生してない。－１ならエラー
	if (CheckSoundMem(sounds[E_TITLE_BGM]) != TRUE)								//もしE_TITLE_BGM(sounds/BGM041.ogg)が再生中なら
	{
		//PlaySoundMem は メモリに読み込んだ音声データを再生する
		PlaySoundMem(sounds[E_TITLE_BGM], DX_PLAYTYPE_BACK, FALSE);				//E_TITLE_BGM(sounds/BGM041.ogg)をバックグラウンド再生する FALSEは再生位置を先頭に戻さないという意味(TRUEなら再生位置を先頭に戻す)
	}

	if (GetButtonDown(XINPUT_BUTTON_B) == TRUE)									//もしBボタンが押されたら
	{
		StopSoundMem(sounds[E_TITLE_BGM]);										//sounds[E_TITLE_BGMの再生を中断する
		PlaySoundMem(sounds[E_TITLE_SE_SELECT], DX_PLAYTYPE_BACK, FALSE);		//sounds[E_TITLE_SE_SELECTをバックグラウンド再生する

		switch (cursor_number)
		{
		case 0:								//cursor_numberが0なら
			Change_Scene(E_GAMEMAIN);		//シーン変更処理　E_GAMEMAIN
			break;							//このswitch分の処理を終了して次の処理に進む
		case 1:								//cursor_numberが1なら
			Change_Scene(E_RANKING);		//シーン変更処理　E_RANKING
			break;							//このswitch分の処理を終了して次の処理に進む
		case 2:								//cursor_numberが2なら
		default:							//どの定数にも一致しなかった場合
			Change_Scene(E_END);			//シーン変更処理　E_END
			break;							//このswitch分の処理を終了して次の処理に進む
		}
	}

	if (GetButtonDown(XINPUT_BUTTON_DPAD_UP) == TRUE)
	{
		PlaySoundMem(sounds[E_TITLE_SE_CURSOR], DX_PLAYTYPE_NORMAL, FALSE);

		if (cursor_number <= 0)
		{
			cursor_number = 0;
		}
		else
		{
			cursor_number--;
		}

	}
	if (GetButtonUp(XINPUT_BUTTON_DPAD_DOWN) == TRUE)
	{
		PlaySoundMem(sounds[E_TITLE_SE_CURSOR], DX_PLAYTYPE_NORMAL, FALSE);

		if (cursor_number >= 2)
		{
			cursor_number = 2;
		}
		else
		{
			cursor_number++;
		}
	}
}

/**************************
* タイトル画面：描画処理
* 引数：なし
* 戻り値：なし
**************************/
void TitleScene_Draw(void)
{
	SetFontSize(50);
	DrawString(100, 100, "テトリス", GetColor(255, 255, 255));
	DrawString(300, 300, "スタート", GetColor(255, 255, 255));
	DrawString(300, 350, "ランキング", GetColor(255, 255, 255));
	DrawString(300, 400, "エンド", GetColor(255, 255, 255));
	SetFontSize(20);

	DrawCircle(275, 325 + (cursor_number * 50), 15, GetColor(255, 0, 0));
}
