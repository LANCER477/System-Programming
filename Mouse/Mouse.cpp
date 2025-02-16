#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "resource.h"
#include <time.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("ААА");

HCURSOR hcursor1;
HCURSOR hcursor2;
HCURSOR hcursor3;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	hcursor1 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	hcursor2 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
	hcursor3 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR3));
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Что то"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		int x = LOWORD(lParam);
		if (x >= 0 && x <= rect.right / 3) {
			MessageBox(hWnd, TEXT("1"), TEXT("Окно"), MB_OK);
		}
		else if (x >= 2 * rect.right / 3 && x <= rect.right) {
			MessageBox(hWnd, TEXT("3"), TEXT("Окно"), MB_OK);
		}
		else {
			MessageBox(hWnd, TEXT("2"), TEXT("Окно"), MB_OK);
		}
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) MoveWindow(hWnd, 0, 0, 300, 300, true);
		else if (wParam == VK_ESCAPE) KillTimer(hWnd, 1);
		break;


