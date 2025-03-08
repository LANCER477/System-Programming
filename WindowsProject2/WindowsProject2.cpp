#include <windows.h>
#include <tchar.h>
#include <string>
#include "resource.h"

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void UpdateButtonText(HWND hWnd, int id);
bool CheckWinner(wchar_t symbol);
void ResetGame(HWND hWnd);

bool playerX = true;
int moveCount = 0;
wstring buttonText[9] = { L"-", L"-", L"-", L"-", L"-", L"-", L"-", L"-", L"-" };

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_SETCHECK, BST_CHECKED, 0);
        return TRUE;

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);

        // Обработка кнопок игрового поля (1-9)
        if (id >= IDC_BUTTON1 && id <= IDC_BUTTON9)
        {
            int index = id - IDC_BUTTON1;
            if (buttonText[index] == L"-") {
                wchar_t currentSymbol = playerX ? L'X' : L'O';
                UpdateButtonText(hWnd, index);
                moveCount++;

                // Проверка победителя после обновления символа
                if (CheckWinner(currentSymbol)) {
                    wstring message = (currentSymbol == L'X') ? L"X wins!" : L"O wins!";
                    MessageBox(hWnd, message.c_str(), L"Game Over", MB_OK);
                    ResetGame(hWnd);
                    return TRUE;
                }

                if (moveCount == 9) {
                    MessageBox(hWnd, L"Draw!", L"Game Over", MB_OK);
                    ResetGame(hWnd);
                    return TRUE;
                }
            }
            return TRUE;
        }

        // Обработка кнопки "Старт"
        if (id == IDC_BUTTON10) {
            ResetGame(hWnd);
            return TRUE;
        }

        // Блокировка изменения чекбокса после первого хода
        if (moveCount > 0 && id == IDC_CHECK1) return TRUE;

        // Установка первого хода
        if (id == IDC_CHECK1) {
            playerX = SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED;
        }

        return TRUE;
    }
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}

void UpdateButtonText(HWND hWnd, int id)
{
    buttonText[id] = playerX ? L"X" : L"O";
    SetWindowText(GetDlgItem(hWnd, IDC_BUTTON1 + id), buttonText[id].c_str());
    playerX = !playerX;
}

int winningCombinations[8][3] = {
    { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 },
    { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 },
    { 0, 4, 8 }, { 2, 4, 6 }
};

bool CheckWinner(wchar_t symbol)
{
    for(auto & combo : winningCombinations)
    {
        if (buttonText[combo[0]] != L"-" &&
            buttonText[combo[0]] == buttonText[combo[1]] &&
            buttonText[combo[0]] == buttonText[combo[2]])
        {
            return true;
        }
    }
    return false;
}

void ResetGame(HWND hWnd) {
    for (int i = 0; i < 9; i++) {
        buttonText[i] = L"-";
        SetWindowText(GetDlgItem(hWnd, IDC_BUTTON1 + i), L"-");
    }
    playerX = SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED;
    moveCount = 0;
}
