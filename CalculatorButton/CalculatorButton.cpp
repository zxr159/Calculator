// CalculatorButton.cpp : Defines the entry point for the>
#include "stdafx.h"
#include <windows.h> 
#include <string>
#include <iostream>
#include<vector>
#include <stdlib.h>

#include "Calculator.h"

using namespace std;
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
	BS_PUSHBUTTON,        TEXT("+/_"),
	BS_PUSHBUTTON,        TEXT("C"),
	BS_PUSHBUTTON,        TEXT("8"),
	BS_PUSHBUTTON,        TEXT("5"),
	BS_PUSHBUTTON,		  TEXT("2"),
	BS_PUSHBUTTON,        TEXT("0"),
	BS_PUSHBUTTON,        TEXT("<-"),
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

enum Clear {
		clearOne,clearAll
	} Clear;
enum Operator {
		add, subtraction, multipli, division
	} Operator;
	
class calculator {
public :
	vector<float> data;
    string TempBuffer ;
	float Number;
	string  symbol;
	//bool isNumbr;
	string  SymbolType;
	bool isSymbol(bool isSymbol);
	void isNumber(bool isNumber, float Number, calculator & calculator);
	void  atSymbol(bool isSymbol, string symbol, calculator & calculator);
	calculator getNumber(calculator &calculator, bool isSymbol);
	void  TempBufferclear(calculator& calculator);
	float add(float NumberOne, float NumberTwo);
	float subtraction(float NumberOne, float NumberTwo);
	float multipli(float NumberOne, float NumberTwo);
	float division(float NumberOne, float NumberTwo);
	void  paint( HDC hdc, int cxChar, int cyChar);
	void  paint(float ResultNum, HDC hdc, int cxChar, int cyChar);
	void  paint(calculator &calculator, HDC hdc, int cxChar, int cyChar);
	void  paint(calculator &calculator, float ResultNum, HDC hdc, int cxChar, int cyChar);
	void clear();

	wstring ANSIToUnicode(const string& str)
	{
		int  len = 0;
		len = str.length();
		int  unicodeLen = ::MultiByteToWideChar(CP_ACP,
			0,
			str.c_str(),
			-1,
			NULL,
			0);
		wchar_t *  pUnicode;
		pUnicode = new  wchar_t[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
		::MultiByteToWideChar(CP_ACP,
			0,
			str.c_str(),
			-1,
			(LPWSTR)pUnicode,
			unicodeLen);
		wstring  rt;
		rt = (wchar_t*)pUnicode;
		delete  pUnicode;

		return  rt;
	}
};
bool calculator::isSymbol(bool isSymbol)
{
	if (isSymbol == true)
		return true;
	else
		return false;
}
void  calculator::isNumber(bool isNumber, float Number, calculator & calculator)
{
	if (isNumber == true)
	{
		calculator.data.push_back(Number);	
		
	}
}
void  calculator::atSymbol(bool isSymbol, string symbol, calculator& calculator)
{

	if (isSymbol == true)
	{
		calculator.TempBuffer.append(calculator.symbol);
	}
	
}

calculator calculator::getNumber(calculator &calculator,bool Symbol)
{
	char *temp = new char[500];
	for (int i = 0; i < calculator.data.size(); i++)
	{
		
		sprintf_s(temp, 500,"%lf", calculator.data[i]);
		calculator.TempBuffer.append(temp);
		calculator.Number = atof(temp);
		if (calculator.isSymbol(Symbol) == true)
		{
			calculator.data.clear();

		}
		
	}
	delete temp;
	return calculator;
}

float calculator::add(float NumberOne,float NumberTwo)
{
	float ResultNum = NumberOne + NumberTwo;
	return ResultNum;
}
float calculator::subtraction(float NumberOne, float NumberTwo)
{
	float ResultNum = NumberOne - NumberTwo;
	return ResultNum;
}
float calculator::multipli(float NumberOne, float NumberTwo)
{
	float ResultNum = NumberOne * NumberTwo;
	return ResultNum;

}
float calculator::division(float NumberOne, float NumberTwo)
{
	float ResultNum = NumberOne / NumberTwo;
	return ResultNum;
}
void  calculator::paint(HDC hdc ,int cxChar,int cyChar)
{	
	TextOut(hdc, 5 * cxChar, 4 * cyChar, TEXT("0"), lstrlen(TEXT("0")));

}
void calculator::paint(calculator &calculator, HDC hdc, int cxChar, int cyChar)
{//显示123数字或者是数字和字符串
	wstring a = ANSIToUnicode(calculator.TempBuffer);
	wstring* pa = &a;
	const wchar_t* add = a.c_str();

	//wsprintf(tempbuffer, L"%s", calculator.TempBuffer.c_str());
	//cout << "字符串是：" << tempbuffer;
	TextOut(hdc, 5 * cxChar, 4 * cyChar, a.c_str(), a.size());
	SetTextAlign(hdc, TA_LEFT | TA_TOP);
	
}
void  calculator::paint(float ResultNum, HDC hdc, int cxChar, int cyChar)
{//显示结果
	
	WCHAR tempbuffer[256];
	wsprintf(tempbuffer, L"%d", ResultNum);
	cout << "字符串是：" << tempbuffer;
	TextOut(hdc, 5 * cxChar, 4 * cyChar, tempbuffer, lstrlen(tempbuffer));
	SetTextAlign(hdc, TA_LEFT | TA_TOP);
}
//把一整行的公式显示在上一行。
void  calculator::paint(calculator &calculator, float ResultNum, HDC hdc, int cxChar, int cyChar)
{
	char *temp = new char[500];
	sprintf_s(temp, 500, "%lf", ResultNum);
	calculator.TempBuffer.append(temp);
	WCHAR tempbuffer[256];
	wsprintf(tempbuffer, L"%d", calculator.TempBuffer);
	cout << "字符串是：" << tempbuffer;
	TextOut(hdc, 5 * cxChar, 2 * cyChar, tempbuffer, lstrlen(tempbuffer));
	SetTextAlign(hdc, TA_LEFT | TA_TOP);
	delete temp;
}
void calculator::TempBufferclear(calculator& calculator)
{
	calculator.TempBuffer.clear();//存储字串清空
}
void calculator::clear()//输出框清空
{
	
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void test()
{
	//benson::Calulator c;

	//c.AddNumber(1);
	//c.AddOperator(benson::Operator::multipli);
	//c.AddNumber(3);
	//c.AddOperator(benson::Operator::add);
	//c.AddNumber(456);
	//wstring str = c.GetExpressionString();
	//double value = c.GetResult();
}


benson::Calculator c;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	test();
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

	c.clear();

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
	calculator calculator;
	int           j, i,flag = 0 ;
	
	float ResultNum=0.0,NumOne,NumTwo,NumThree,NumFour;
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
	{
		InvalidateRect(hwnd, &rect, TRUE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		//SetBkMode(hdc, TRANSPARENT);

		wstring s = c.GetExpressionString();
		TextOut(hdc, 5, 5, s.c_str(), s.size());

		wstring s2 = c.buffer.GetStrValue();
		TextOut(hdc, 5, 40, s2.c_str(), s2.size());

		calculator.paint(hdc, cxChar, cyChar);
		EndPaint(hwnd, &ps);
	}
		return 0;
	                
	case  WM_DRAWITEM:
		break;
	case  WM_COMMAND:
	{
		rect.left = 50;
		rect.top = 50;
		rect.right = 350;
		rect.bottom = 70;
		switch (LOWORD(wParam))
		{
		
		case 0:
			//Clear = clearAll;

			c.buffer.clear();

			break;
		case 1:
			//
			//calculator.isNumber(true, 7, calculator);
			////DrawText()
			////TextOut(hdc, 10 * cxChar, 2 * cyChar, calculator.TempBuffer, lstrlen(calculator.TempBuffer));
			//calculator = calculator.getNumber(calculator, false);
			//
			////calculator.paint(calculator, hdc, cxChar, cyChar);

			////ReleaseDC(hwnd, hdc);

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}

			c.buffer.AppendNumber(7);

			break;
			
		case 2:
			/*calculator.isNumber(true, 4, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			*/

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(4);

			break;
		case 3:
			/*calculator.isNumber(true, 1, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			
			*/

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(1);

			break;
		case 4:
			//if (flag % 2 == 0)//所有值取正数
			//{
			//	calculator.atSymbol(true, "+", calculator);
			//	calculator = calculator.getNumber(calculator,true);
			//	
			//}
			//else//所有值取负数
			//{
			//	calculator.atSymbol(true, "-", calculator);
			//	calculator = calculator.getNumber(calculator,true);
			//	calculator.Number = -calculator.Number;

			//}	
			//flag  += 1;
			//if (flag > 2)
			//	flag = 0;



			if (!c.IsCurrentOp())
			{
				c.buffer.switchPosNag();
			}

			break;
		case 5:
			//Clear = clearOne;
			c.clear();
			break;
		case 6:
/*
			calculator.isNumber(true, 8, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			*/

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(8);

			break;

		case 7:
			/*calculator.isNumber(true, 5, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			*/

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(5);

			break;
		case 8:
			/*calculator.isNumber(true, 2, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
*/
			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(2);

			break;
		case 9:
			/*calculator.isNumber(true, 0, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			*/

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(0);

			
			break;

		case 10:
			//calculator.atSymbol(true, "", calculator);
			c.buffer.popBack();

			break;
		case 11:
			//calculator.isNumber(true, 9, calculator);
			//calculator = calculator.getNumber(calculator, false);
			//calculator.paint(calculator, hdc, cxChar, cyChar);

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(9);

			break;
		case 12:
			//calculator.isNumber(true, 6, calculator);
			//calculator = calculator.getNumber(calculator, false);
			//calculator.paint(calculator, hdc, cxChar, cyChar);

			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(6);


			break;

		case 13:
			/*calculator.isNumber(true, 3, calculator);
			calculator = calculator.getNumber(calculator, false);
			calculator.paint(calculator, hdc, cxChar, cyChar);
			*/
			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendNumber(3);

			break;
		case 14:

			//calculator.atSymbol(true, ".", calculator);
			if (c.IsCurrentOp())
			{
				c.SetCurrentOpStatus(false);
				c.buffer.clear();
			}
			c.buffer.AppendPoint();

			
			break;
		case 15:
			
			//calculator.atSymbol(true, "/", calculator);
			//calculator = calculator.getNumber(calculator, true);
			//NumOne = calculator.Number;
			//calculator.SymbolType = "/";
			//Operator = division;
			
			if (!c.IsCurrentOp())
			{
				double value = c.buffer.getValue();
				c.AddNumber(value);
			}

			c.AddOperator(benson::division);

			break;
		case 16:
			//calculator.atSymbol(true, "*", calculator);
			//calculator = calculator.getNumber(calculator, true);
			//NumTwo = calculator.Number;
			//calculator.SymbolType = "*";
			//Operator = multipli;

			if (!c.IsCurrentOp())
			{
				double value = c.buffer.getValue();
				c.AddNumber(value);
			}

			c.AddOperator(benson::multipli);

			break;
		case 17:
			//calculator.atSymbol(true, "-", calculator);
			//calculator = calculator.getNumber(calculator, true);
			//NumThree = calculator.Number;
			//calculator.SymbolType = "-";
			//Operator = subtraction;
			//

			if (!c.IsCurrentOp())
			{
				double value = c.buffer.getValue();
				c.AddNumber(value);
			}

			c.AddOperator(benson::subtraction);

			break;
		case 18:
			//calculator.atSymbol(true, "+", calculator);
			//calculator = calculator.getNumber(calculator, true);
			//NumFour = calculator.Number;
			//calculator.SymbolType = "+";
			//Operator = add;

			if (!c.IsCurrentOp())
			{
				double value = c.buffer.getValue();
				c.AddNumber(value);
			}

			c.AddOperator(benson::add);


			break;
		case 19:
			//calculator.atSymbol(true, "=", calculator);
			//calculator.paint(ResultNum, hdc, cxChar, cyChar);
			//calculator.paint(calculator, ResultNum, hdc, cxChar, cyChar);
			////calculator.TempBufferclear(calculator);

			double value = c.GetResult();
			c.SaveLastResult(c.doubleToPerfectString(value));
			c.clear();

			break;
		}

		InvalidateRect(hwnd, NULL, TRUE);

		//switch (Clear)
		//{
		//case clearOne:
		//	
		//	break;
		//case clearAll:
		//	break;
		//default:
		//	break;
		//}
		//switch (Operator)
		//{
		//case add:
		//	if (calculator.SymbolType == "-")
		//	{
		//		ResultNum = calculator.add(NumFour, NumThree);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "+")
		//	{
		//		ResultNum = calculator.add(NumFour, NumFour);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "*")
		//	{
		//		ResultNum = calculator.add(NumFour, NumTwo);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "/")
		//	{
		//		ResultNum = calculator.add(NumFour, NumOne);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	break;
		//case subtraction:
		//	if (calculator.SymbolType == "-")
		//	{
		//		ResultNum = calculator.subtraction(NumThree, NumThree);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "+")
		//	{
		//		ResultNum = calculator.subtraction(NumThree, NumFour);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "*")
		//	{
		//		ResultNum = calculator.subtraction(NumThree, NumTwo);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "/")
		//	{
		//		ResultNum = calculator.subtraction(NumThree, NumOne);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	break;
		//case multipli:
		//	if (calculator.SymbolType == "-")
		//	{
		//		ResultNum = calculator.multipli(NumTwo, NumThree);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "+")
		//	{
		//		ResultNum = calculator.multipli(NumTwo, NumFour);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "*")
		//	{
		//		ResultNum = calculator.multipli(NumTwo, NumTwo);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "/")
		//	{
		//		ResultNum = calculator.multipli(NumTwo, NumOne);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	break;
		//case division:
		//	if (calculator.SymbolType == "-")
		//	{
		//		ResultNum = calculator.division(NumOne, NumThree);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "+")
		//	{
		//		ResultNum = calculator.division(NumOne, NumFour);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "*")
		//	{
		//		ResultNum = calculator.division(NumOne, NumTwo);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	if (calculator.SymbolType == "/")
		//	{
		//		ResultNum = calculator.division(NumOne, NumOne);
		//		calculator.paint(calculator, hdc, cxChar, cyChar);
		//		calculator.paint(ResultNum, hdc, cxChar, cyChar);
		//	}
		//	break;
		//default:
		//	break;
		//}
		//
	}
	break;

	case  WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}