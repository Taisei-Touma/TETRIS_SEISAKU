#include"TitleScene.h"
#include"InputControl.h"
#include"SceneManager.h"
#include"DxLib.h"

/**************************
* �}�N����`
**************************/

/**************************
* �^��`
**************************/
enum
{
	E_TITLE_BGM,		//0
	E_TITLE_SE_CURSOR,	//1
	E_TITLE_SE_SELECT,	//2
	E_SOUND_MAX			//3
};

/**************************
* �O���[�o���ϐ�
**************************/
int cursor_number;
int sounds[E_SOUND_MAX];

/**************************
* �v���g�^�C�v�錾
**************************/

/**************************
* �^�C�g����ʁF����������
* �����F�Ȃ�
* �߂�l�F�G���[���(-1:�ُ�L, -1�ȊO:����I��)
**************************/
int TitleScene_Initialize(void)											//Initialize == ������
{
	int ret = 0;

	cursor_number = 0;

	sounds[E_TITLE_BGM] = LoadSoundMem("sounds/BGM041.ogg");			//sounds/BGM041.ogg�����[�h���A���ʔԍ���sounds[E_TITLE_BGM]�Ɋi�[

	sounds[E_TITLE_SE_CURSOR] = LoadSoundMem("sounds/SE1.mp3");			//sounds/SE1.mp3�����[�h���A���ʔԍ���sounds[E_TITLE_SE_CURSOR]�Ɋi�[

	sounds[E_TITLE_SE_SELECT] = LoadSoundMem("sounds/SE2.mp3");			//sounds/SE2.mp3�����[�h���A���ʔԍ���sounds[E_TITLE_SE_SELECT]�Ɋi�[

	//ChangeVolumeSoundMem �� �Đ����鉹�̉��ʂ�ݒ肵�܂��B0�͖����A255�ōő剹�ʂł��B
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
* �^�C�g����ʁF�X�V����
* �����F�Ȃ�
* �߂�l�F�Ȃ�
**************************/
void TitleScene_Update(void)
{
	//BGM������Ă��Ȃ����ɍĐ�
	//CheckSoundMem �� �������ɓǂݍ��񂾉����f�[�^���Đ��������ׂ�@�߂�l��1�Ȃ�Đ����A0�Ȃ�Đ����ĂȂ��B�|�P�Ȃ�G���[
	if (CheckSoundMem(sounds[E_TITLE_BGM]) != TRUE)								//����E_TITLE_BGM(sounds/BGM041.ogg)���Đ����Ȃ�
	{
		//PlaySoundMem �� �������ɓǂݍ��񂾉����f�[�^���Đ�����
		PlaySoundMem(sounds[E_TITLE_BGM], DX_PLAYTYPE_BACK, FALSE);				//E_TITLE_BGM(sounds/BGM041.ogg)���o�b�N�O���E���h�Đ����� FALSE�͍Đ��ʒu��擪�ɖ߂��Ȃ��Ƃ����Ӗ�(TRUE�Ȃ�Đ��ʒu��擪�ɖ߂�)
	}

	if (GetButtonDown(XINPUT_BUTTON_B) == TRUE)									//����B�{�^���������ꂽ��
	{
		StopSoundMem(sounds[E_TITLE_BGM]);										//sounds[E_TITLE_BGM�̍Đ��𒆒f����
		PlaySoundMem(sounds[E_TITLE_SE_SELECT], DX_PLAYTYPE_BACK, FALSE);		//sounds[E_TITLE_SE_SELECT���o�b�N�O���E���h�Đ�����

		switch (cursor_number)
		{
		case 0:								//cursor_number��0�Ȃ�
			Change_Scene(E_GAMEMAIN);		//�V�[���ύX�����@E_GAMEMAIN
			break;							//����switch���̏������I�����Ď��̏����ɐi��
		case 1:								//cursor_number��1�Ȃ�
			Change_Scene(E_RANKING);		//�V�[���ύX�����@E_RANKING
			break;							//����switch���̏������I�����Ď��̏����ɐi��
		case 2:								//cursor_number��2�Ȃ�
		default:							//�ǂ̒萔�ɂ���v���Ȃ������ꍇ
			Change_Scene(E_END);			//�V�[���ύX�����@E_END
			break;							//����switch���̏������I�����Ď��̏����ɐi��
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
* �^�C�g����ʁF�`�揈��
* �����F�Ȃ�
* �߂�l�F�Ȃ�
**************************/
void TitleScene_Draw(void)
{
	SetFontSize(50);
	DrawString(100, 100, "�e�g���X", GetColor(255, 255, 255));
	DrawString(300, 300, "�X�^�[�g", GetColor(255, 255, 255));
	DrawString(300, 350, "�����L���O", GetColor(255, 255, 255));
	DrawString(300, 400, "�G���h", GetColor(255, 255, 255));
	SetFontSize(20);

	DrawCircle(275, 325 + (cursor_number * 50), 15, GetColor(255, 0, 0));
}
