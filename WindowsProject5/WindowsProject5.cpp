#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{

    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR login[20], password[20];
    int score;
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON2)
        {
            GetDlgItemText(hWnd, IDC_EDIT1, login, 20);
            GetDlgItemText(hWnd, IDC_EDIT2, password, 20);
            if (_tcscmp(login, _T("admin")) == 0 && _tcscmp(password, _T("admin")) == 0)
            {
                MessageBox(hWnd, _T("Админ"), _T("Сообщение"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hWnd, _T("Неверно"), _T("Ошибка"), MB_OK | MB_ICONERROR);
            }
        }
        
    case WM_SHOWWINDOW:
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}