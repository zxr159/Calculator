// CalculatorButton.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h> 
struct {
	int     iStyle;
	TCHAR *   szText;
}
button[] =
{
	BS_PUSHBUTTON,        TEXT("CE"),
	BS_PUSHBUTTON,		  TEXT("7"),
	BS_PUSHBUTTON,        TEXT("4"),
	BS_PUSHBUTTON,		  TEXT("1"),
	BS_PUSHBUTTON,        TEXT("（）"),
	BS_PUSHBUTTON,        TEXT("<-"),
	BS_PUSHBUTTON,        TEXT("8"),
	BS_PUSHBUTTON,        TEXT("5"),
	BS_PUSHBUTTON,		  TEXT("2"),
	BS_PUSHBUTTON,        TEXT("0"),
	BS_PUSHBUTTON,        TEXT("%"),
	BS_PUSHBUTTON,        TEXT("9"),
	BS_PUSHBUTTON,        TEXT("6"),
	BS_PUSHBUTTON,        TEXT("3"),
	BS_PUSHBUTTON,        TEXT("."),
	BS_PUSHBUTTON,        TEXT("/"),
	BS_PUSHBUTTON,        TEXT("x"),
	BS_PUSHBUTTON,        TEXT("-"),
	BS_PUSHBUTTON,        TEXT("+"),
	BS_PUSHBUTTON,        TEXT("=")
};

#define NUM (sizeof button / sizeof button[0]) 

enum Operator {
	add, subtraction, multipli, division
} Operator;



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR  szAppName[] = TEXT("计算器");
	HWND             hwnd;
	MSG              msg;
	WNDCLASS      wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, TEXT("计算器"), WS_OVERLAPPEDWINDOW, 200, 200, 400, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND   hwndButton[NUM];
	static HWND	  hwndTEXT;
	static RECT  rect;
	//static TCHAR  szTop[1024]=TEXT(" 2222");
	static int    cxChar, cyChar;
	HDC            hdc = GetDC(hwnd);
	PAINTSTRUCT   ps;
	int           j, i, clicked ;
	
	LPRECT rec = (RECT*)malloc(sizeof(RECT));
	GetClientRect(hwnd, rec);
	switch (message)
	{
	case  WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j <5; j++)
				hwndButton[j*i] = CreateWindow(TEXT("button"), button[j + 5 * i].szText, WS_CHILD | WS_VISIBLE | button[j].iStyle,
					cxChar * 11 * i+20 , cyChar * (2 + 3 * j) + 70, 10 * cxChar+5, 7 * cyChar / 2, hwnd, (HMENU)(j + 5 * i), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		hwndTEXT = CreateWindow(L"EditText", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL
			, 0, 10,200 ,50 , hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		

		//SetFocus(hwndTEXT);
		//MoveWindow(hwndTEXT, 100, 5, 100, 50, TRUE);

		return 0;
	case  WM_SIZE:
		rect.left = 24 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		return 0;




	case  WM_PAINT:
		InvalidateRect(hwnd, &rect, FALSE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		static TCHAR buffer[100];
		
		EndPaint(hwnd, &ps);
		return 0;
	                
	case  WM_DRAWITEM:
		break;
	case  WM_COMMAND:
	{
		rect.left = 50;
		rect.top = 50;
		rect.right = 350;
		rect.bottom = 70;
		wchar_t TempBuff[256],Text[256];
		int TempNum=0, ResultNum=0, flag=0;
		
		//wsprintf(text, L"LOWORD(wParam)：%d  HIWORD(wParam)：%d", LOWORD(wParam), HIWORD(wParam));
		//DrawText(hdc, text, wcslen(text), &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_END_ELLIPSIS |DT_BOTTOM);
		
		switch (LOWORD(wParam))
		{
			
		case 0:
			
			break;
			//DrawText(hdc, text, wcslen(text), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
		case 1:
			lstrcat(Text, _T("7"));
			
			wsprintf(TempBuff, L"7");
			
			TextOut(hdc, rect.left+(clicked*cxChar), 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP );
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			
			clicked++;
			break;
			
		case 2:
			lstrcat(Text, _T("4"));
			wsprintf(TempBuff, L"4");
			
			TextOut(hdc, rect.left + (clicked*cxChar)+10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;
		case 3:
			lstrcat(Text, _T("1"));
			wsprintf(TempBuff, L"1");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;
		case 4:
			if (flag % 2 == 0)
			{
				lstrcat(Text, TEXT(")"));
				wsprintf(TempBuff, L")");

				TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
				SetTextAlign(hdc, TA_LEFT | TA_TOP);
				//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
				ReleaseDC(hwnd, hdc);
				clicked++;
			}
			else
			{
				
				lstrcat(Text, TEXT("("));
				wsprintf(TempBuff, L"(");

				TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
				SetTextAlign(hdc, TA_LEFT | TA_TOP);
				//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
				ReleaseDC(hwnd, hdc);
				clicked++;

			}	
			flag  += 1;
			break;
		//case 5:
			//删除一个数
		case 6:

			lstrcat(Text, TEXT("8"));
			wsprintf(TempBuff, L"8");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;

			break;

		case 7:
			lstrcat(Text, TEXT("5"));
			wsprintf(TempBuff, L"5");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;
		case 8:
			lstrcat(Text, TEXT("2"));
			wsprintf(TempBuff, L"2");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			
			break;
		case 9:
			lstrcat(Text, _T("0"));
			wsprintf(TempBuff, L"0");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;

		case 10:
			
			wsprintf(TempBuff, L"%");
			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			TempNum = _ttoi(Text);
			ResultNum *= TempNum;
			ResultNum /= 100;
			memset(Text, 0, wcslen(Text));
			clicked++;
			break;
		case 11:
			lstrcat(Text, _T("9"));
			wsprintf(TempBuff, L"9");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			
			ReleaseDC(hwnd, hdc);
			clicked++;

			break;
		case 12:
			lstrcat(Text, _T("6"));
			wsprintf(TempBuff, L"6");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;

		case 13:
			lstrcat(Text, _T("3"));
			wsprintf(TempBuff, L"3");

			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			clicked++;
			break;
		case 14:
			lstrcat(TempBuff, TEXT("."));
			break;
		case 15:
			
			wsprintf(TempBuff, L"/");
			TextOut(hdc, rect.left + (clicked*cxChar) + 10, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
			//DrawText(hdc, TempBuff, wcslen(TempBuff), &rect, DT_RIGHT | DT_SINGLELINE | DT_END_ELLIPSIS | DT_BOTTOM);
			ReleaseDC(hwnd, hdc);
			TempNum = _ttoi(Text);
			ResultNum /= TempNum;
			memset(Text, 0, wcslen(Text));
			clicked++;
			
			
			clicked++;
			break;
		case 16:
			lstrcat(TempBuff, TEXT("x"));
			break;
		case 17:
			lstrcat(TempBuff, TEXT("-"));
			ResultNum -= TempNum;
			clicked++;
			break;
		case 18:
			lstrcat(TempBuff, TEXT("+"));
			ResultNum += TempNum;
			clicked++;

			break;
		case 19:
			//wsprintf(Text, _T("="));
			
			wsprintf(TempBuff, L" %d", ResultNum);
			TextOut(hdc, 5 * cxChar, 4 * cyChar, TempBuff, lstrlen(TempBuff));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, &rect);
			break;
		}
		
	}
	break;

	case  WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}