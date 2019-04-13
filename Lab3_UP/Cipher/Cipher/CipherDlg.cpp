
// CipherDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Cipher.h"
#include "CipherDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "encr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CCipherDlg



CCipherDlg::CCipherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIPHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCipherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, _language);
	DDX_Control(pDX, IDC_EDIT2, Key);
	DDX_Control(pDX, IDC_EDIT3, input_file);
	DDX_Control(pDX, IDC_EDIT4, output_file);
	DDX_Control(pDX, IDC_COMBO2, _non_alphabetic_char);
}

BEGIN_MESSAGE_MAP(CCipherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CIPHER, &CCipherDlg::OnBnClickedButtonCipher)
END_MESSAGE_MAP()


// Обработчики сообщений CCipherDlg

BOOL CCipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	_language.AddString(L"English");
	_language.AddString(L"Russian");
	_non_alphabetic_char.AddString(L"Delete");
	_non_alphabetic_char.AddString(L"Nothing");
	_non_alphabetic_char.AddString(L"Following");

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCipherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCipherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCipherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCipherDlg::OnBnClickedButtonCipher()
{
	setlocale(LC_ALL, "rus");
	CString infile, outfile, key_cs, language_cs, notletter_cs;
	input_file.GetWindowTextW(infile);
	output_file.GetWindowTextW(outfile);
	Key.GetWindowTextW(key_cs);

	std::fstream input(infile);
	char before[128];
	input.getline(before, 128);
	/*for (int i = 0; i < std::strlen(before); i++)
	{
		if (isupper(before[i]))
		{
			before[i] = tolower(before[i]);
		}
	}*/
	input.close();
	auto after = new char[strlen(before)];

	_language.GetLBText(_language.GetCurSel(), language_cs);
	char language[50];
	sprintf_s(language, "%S", language_cs);
	_non_alphabetic_char.GetLBText(_non_alphabetic_char.GetCurSel(), notletter_cs);
	char notletter[40];
	sprintf_s(notletter, "%S", notletter_cs);

	auto alphabet = new char;
	if (strcmp(language, "English") == 0)
	{
		alphabet = "abcdefghijklmnopqrstuvwxyz";
	}
	else if (strcmp(language, "Russian") == 0)
	{
		alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	}

	char key[120];
	sprintf_s(key, "%S", key_cs);

	encrypt(after, before, key, language, alphabet, notletter);

	std::ofstream out(outfile);
	out << after;
	out.close();
	AfxMessageBox(L"Successfully encrypted!");
}