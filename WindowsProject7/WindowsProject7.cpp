#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

HWND hList, hCombo, hEdit, hRadio1, hRadio2, hRadio3, hRadio4;
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void FillCharacterList(HWND hWnd);
void ShowWeaponEfficiency(HWND hWnd, int weaponIndex);

vector<vector<string>> characters = {
    {"Гэндальф", "Саруман", "Радагаст"},
    {"Гимли", "Глоин", "Двалин"},
    {"Арагорн", "Боромир", "Фарамир"},
    {"Фродо", "Сэм", "Голлум"},
    {"Леголас", "Трандуил", "Тауриэль"},
};

vector<vector<vector<int>>> efficiency = {
    { {8, 7, 5, 6}, {7, 6, 4, 5}, {6, 5, 4, 6} },
    { {5, 8, 9, 7}, {4, 7, 8, 6}, {6, 7, 9, 5} },
    { {9, 6, 5, 7}, {8, 5, 4, 6}, {7, 5, 3, 8} },
    { {6, 4, 7, 10}, {5, 3, 6, 9}, {4, 2, 5, 8} },
    { {3, 4, 2, 5}, {2, 3, 1, 4}, {1, 2, 1, 3} }
};

int currentWeapon = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    srand((unsigned int)time(NULL));
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;

    case WM_INITDIALOG:
        hCombo = GetDlgItem(hWnd, IDC_COMBO1);
        hList = GetDlgItem(hWnd, IDC_LIST1);
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);
        hRadio1 = GetDlgItem(hWnd, IDC_RADIO1);
        hRadio2 = GetDlgItem(hWnd, IDC_RADIO2);
        hRadio3 = GetDlgItem(hWnd, IDC_RADIO3);
        hRadio4 = GetDlgItem(hWnd, IDC_RADIO4);
        SendMessage(hCombo, CB_SETDROPPEDWIDTH, 150, 0);
        SetWindowPos(hCombo, NULL, 0, 0, 200, 300, SWP_NOMOVE | SWP_NOZORDER);



        SendMessage(hCombo, CB_RESETCONTENT, 0, 0);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Люди"));
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Эльфы"));
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Гномы"));
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Волшебники"));
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Хоббиты"));

        SendMessage(hCombo, CB_SETCURSEL, 0, 0);
        FillCharacterList(hWnd);
        return TRUE;

    case WM_COMMAND:
        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_COMBO1) {
            FillCharacterList(hWnd);
        }
        else if (HIWORD(wParam) == BN_CLICKED) {
            if (LOWORD(wParam) == IDC_RADIO1) currentWeapon = 0;
            else if (LOWORD(wParam) == IDC_RADIO2) currentWeapon = 1;
            else if (LOWORD(wParam) == IDC_RADIO3) currentWeapon = 2;
            else if (LOWORD(wParam) == IDC_RADIO4) currentWeapon = 3;

            ShowWeaponEfficiency(hWnd, currentWeapon);
        }
        break;
    }
    return FALSE;
}

void FillCharacterList(HWND hWnd)
{
    int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
    if (index == CB_ERR) return;

    SendMessage(hList, LB_RESETCONTENT, 0, 0);

    vector<string> group = characters[index % characters.size()];
    for (const string& name : group)
    {
        SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)name.c_str());
    }
}

void ShowWeaponEfficiency(HWND hWnd, int weaponIndex)
{
    int characterIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
    if (characterIndex == LB_ERR) return;

    int raceIndex = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
    if (raceIndex == CB_ERR) return;

    int score = efficiency[raceIndex][characterIndex][weaponIndex];

    TCHAR scoreStr[3];
    _stprintf_s(scoreStr, _T("%d"), score);

    SetWindowText(hEdit, scoreStr);
}
