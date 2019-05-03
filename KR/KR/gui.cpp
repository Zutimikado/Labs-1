#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <winuser.h>
#include <atlstr.h>
#include <string>
#include <fstream>
#include "Station.h"
#include <sstream>
#include <iomanip>

bool is_date_in_range(tm from, tm to, tm val)
{
	val.tm_hour = val.tm_min = 0;
	return mktime(&from) <= mktime(&val) && mktime(&val) <= mktime(&to);
}

bool is_sort = false;

int CALLBACK wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR lpCmdLine, const int nShowCmd)
{
	static station station;
	std::ifstream file("flights.csv");
	while (!file.eof())
	{
		file >> station;
	}
	station.sort_by_date();

	static HWND SearchControl, OutputControl, FromDateControl, ToDateControl, SortControl;
	static HFONT myFont_SC, myFont_OC;
	MSG msg{};
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
		case WM_CREATE:
		{
			myFont_SC = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE,
				FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				VARIABLE_PITCH, "Arial");
			myFont_OC = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE,
				FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				VARIABLE_PITCH, "Arial");
			FromDateControl = CreateWindowExA(NULL, "SysDateTimePick32", nullptr,
				WS_BORDER | WS_CHILD | WS_VISIBLE,
				0, 0, 200, 40, hWnd, nullptr, nullptr, nullptr);
			ToDateControl = CreateWindowExA(NULL, "SysDateTimePick32", nullptr,
				WS_BORDER | WS_CHILD | WS_VISIBLE,
				200, 0, 200, 40, hWnd, nullptr, nullptr, nullptr);
			SearchControl = CreateWindowExA(NULL, "edit", nullptr,
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				0, 40, 300, 40, hWnd, nullptr, nullptr, nullptr);
			SendMessage(SearchControl, WM_SETFONT, WPARAM(myFont_SC), 0);
			OutputControl = CreateWindowExA(NULL, "edit", nullptr,
				WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_CLIENTEDGE | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
				0, 120, 400, 180, hWnd, nullptr, nullptr, nullptr);
			SendMessage(OutputControl, WM_SETFONT, WPARAM(myFont_OC), 0);
			CreateWindowExA(NULL, "button", "Search",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300, 40, 100, 40, hWnd, reinterpret_cast<HMENU>(1), nullptr, nullptr);
			CreateWindowExA(NULL, "button", "Show all",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300, 80, 100, 40, hWnd, reinterpret_cast<HMENU>(2), nullptr, nullptr);
		}
		return 0;

		case WM_COMMAND:
		{
			if (LOWORD(wParam) == 1)
			{
				tm date_from, date_to;
				const auto date_from_s = new char[100];
				GetWindowTextA(FromDateControl, date_from_s, 100);
				std::stringstream ss1(date_from_s);
				ss1 >> std::get_time(&(date_from), "%d.%m.%Y");
				const auto date_to_s = new char[100];
				GetWindowTextA(ToDateControl, date_to_s, 100);
				std::stringstream ss2(date_to_s);
				ss2 >> std::get_time(&(date_to), "%d.%m.%Y");
				date_from.tm_hour = date_from.tm_min = date_to.tm_hour = date_to.tm_min = 0;

				const auto text_length = GetWindowTextLengthA(SearchControl) + 1;
				const auto search_text = new char[text_length];
				GetWindowTextA(SearchControl, search_text, text_length);

				std::string output_text;
				char dateFrom[20];
				char dateTo[20];

				for (const auto& f : station)
				{
					if ((text_length == 0 || f.start_city.find(search_text) != std::string::npos) &&
						is_date_in_range(date_from, date_to, f.start_time))
					{
						strftime(dateFrom, 20, "%b %d %Y %H:%M", &(f.start_time));
						strftime(dateTo, 20, "%b %d %Y %H:%M", &(f.end_time));
						output_text += f.start_city + " to " + f.end_city + "; " + dateFrom + " - " +  dateTo + "; " + std::to_string(f.remaining_ticket) + "/" + std::to_string(f.capasity) + "\n";
					}
				}
				SetWindowTextA(OutputControl, output_text.c_str());
			}
			if (LOWORD(wParam) == 2)
			{
				tm date_from, date_to;
				const auto date_from_s = new char[100];
				GetWindowTextA(FromDateControl, date_from_s, 100);
				std::stringstream ss1(date_from_s);
				ss1 >> std::get_time(&(date_from), "%d.%m.%Y");
				const auto date_to_s = new char[100];
				GetWindowTextA(ToDateControl, date_to_s, 100);
				std::stringstream ss2(date_to_s);
				ss2 >> std::get_time(&(date_to), "%d.%m.%Y");
				date_from.tm_hour = date_from.tm_min = date_to.tm_hour = date_to.tm_min = 0;

				const auto text_length = GetWindowTextLengthA(SearchControl) + 1;
				const auto search_text = new char[text_length];
				GetWindowTextA(SearchControl, search_text, text_length);

				std::string output_text;
				char dateFrom[20];
				char dateTo[20];

				for (const auto& f : station)
				{
					strftime(dateFrom, 20, "%b %d %Y %H:%M", &(f.start_time));
					strftime(dateTo, 20, "%b %d %Y %H:%M", &(f.end_time));
					output_text += f.start_city + " to " + f.end_city + "; " + dateFrom + " - " + dateTo + "; " + std::to_string(f.remaining_ticket) + "/" + std::to_string(f.capasity) + "\n";
				}
				SetWindowTextA(OutputControl, output_text.c_str());
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = CString(L"station");
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}
	const auto hwnd = CreateWindow(wc.lpszClassName,
		CString(L"Station"),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
		415, 340, nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}