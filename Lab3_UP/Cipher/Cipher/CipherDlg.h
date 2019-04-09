﻿
// CipherDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CCipherDlg
class CCipherDlg : public CDialogEx
{
// Создание
public:
	CCipherDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIPHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox _language;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonCipher();
	CEdit Key;
	CEdit input_file;
	CEdit output_file;
	CComboBox _non_alphabetic_char;
};