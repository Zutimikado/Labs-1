
// Cipher.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCipherApp:
// Сведения о реализации этого класса: Cipher.cpp
//

class CCipherApp : public CWinApp
{
public:
	CCipherApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCipherApp theApp;