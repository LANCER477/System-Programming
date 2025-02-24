#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{

    // создаём главное окно приложения на основе модального диалога
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int score = 0;
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1) {
            score = 0;

            // Проверка правильных ответов (по одному на вопрос)
            if (IsDlgButtonChecked(hWnd, IDC_RADIO2) == BST_CHECKED) score += 20; // Альберт
            if (IsDlgButtonChecked(hWnd, IDC_RADIO5) == BST_CHECKED) score += 20; // Кольцо
            if (IsDlgButtonChecked(hWnd, IDC_RADIO8) == BST_CHECKED) score += 20; // Фура
            if (IsDlgButtonChecked(hWnd, IDC_CHECK5) == BST_CHECKED) score += 20; // C++
            if (IsDlgButtonChecked(hWnd, IDC_CHECK9) == BST_CHECKED) score += 20; // Фродо

            wchar_t buffer[20];
            swprintf(buffer, 20, L"%d/100", score);
            SetWindowText(GetDlgItem(hWnd, IDC_STATIC), buffer); // Исправлен ID для корректного обновления текста
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}