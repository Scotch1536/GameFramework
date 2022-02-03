//!
//!	@file
//!	@brief �A�v���P�[�V�����V�X�e���̃w�b�_�[�t�@�C��
//!

#pragma once

#include	<Windows.h>
#include	<stdio.h>
#include	<cinttypes>

class CGame;

//! @brief �A�v���P�[�V�����N���X
class CApplication
{
public:
	static const char* WINDOW_TITLE;						//!< �E�B���h�E�^�C�g��
	static const char* WINDOW_CLASS_NAME;					//!< �E�B���h�E�N���X��

	static const uint32_t WINDOW_STYLE_WINDOWED;			//!< �E�B���h�E�X�^�C��
	static const uint32_t WINDOW_EX_STYLE_WINDOWED;			//!< �E�B���h�E�X�^�C��EX
	static const uint32_t WINDOW_STYLE_FULL_SCREEN;			//!< �E�B���h�E�X�^�C���t���X�N���[��
	static const uint32_t WINDOW_EX_STYLE_FULL_SCREEN;		//!< �E�B���h�E�X�^�C��EX�t���X�N���[��

	static const uint32_t CLIENT_WIDTH;						//!< �E�B���h�E����
	static const uint32_t CLIENT_HEIGHT;					//!< �E�B���h�E�c��

	static const float FPS;									//!< FPS

private:
	HWND mHWnd;					//!< Window�n���h��
	HINSTANCE mHInstance;		//!< �C���X�^���X�n���h��
	CGame* mGame;				//!< �Q�[���V�X�e��

	//�R�s�[�֎~
	CApplication(const CApplication&);
	CApplication& operator= (const CApplication&) {}

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃A�v���P�[�V���������L����Q�[���V�X�e��
	//!
	CApplication(CGame& partner):mGame(&partner) {};

	//!
	//! @brief ������
	//! @param[in] hInstance �C���X�^���X�n���h��
	//!
	void Init(HINSTANCE hInstance);

	//!
	//! @brief ���C�����[�v
	//! @return unsigned long �E�B���h�E���b�Z�[�W
	//!
	unsigned long MainLoop();

	HWND GetHWnd()const
	{
		return mHWnd;
	}

	HINSTANCE GetHInst()const
	{
		return mHInstance;
	}

};