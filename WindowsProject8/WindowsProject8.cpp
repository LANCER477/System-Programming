#include <windows.h>
#include <fstream>
#include "resource.h"
#include <commctrl.h>

using namespace std;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI CopyFileThread(LPVOID lpParam);

struct CopyData {
    HWND hWnd;
    char sourcePath[MAX_PATH];
    char pastePath[MAX_PATH];
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void StartCopying(HWND hWnd)
{
    CopyData* data = new CopyData;
    data->hWnd = hWnd;

    GetDlgItemTextA(hWnd, IDC_EDIT1, data->sourcePath, MAX_PATH);
    GetDlgItemTextA(hWnd, IDC_EDIT2, data->pastePath, MAX_PATH);

    CreateThread(NULL, 0, CopyFileThread, data, 0, NULL);
}

DWORD WINAPI CopyFileThread(LPVOID lpParam)
{
    CopyData* data = (CopyData*)lpParam;

    ifstream src(data->sourcePath, ios::binary);
    ofstream paste(data->pastePath, ios::binary);

    if (src && paste) {
        src.seekg(0, ios::end);
        long fileSize = src.tellg();
        src.seekg(0, ios::beg);

        char ch;
        long copiedSize = 0;
        HWND hProgress = GetDlgItem(data->hWnd, IDC_PROGRESS1);
        SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

        while (src.get(ch)) {
            Sleep(10);
            paste.put(ch);
            copiedSize++;
            if (fileSize > 0) { 
                int progress = (copiedSize * 100) / fileSize;
                SendMessage(hProgress, PBM_SETPOS, progress, 0);
            }
        }
        MessageBoxA(data->hWnd, "Скопировано", "Гуд", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBoxA(data->hWnd, "Ошибка", "Ошибка", MB_OK | MB_ICONERROR);
    }

    delete data;
    return 0;
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;

    case WM_INITDIALOG:
        SetDlgItemTextA(hWnd, IDC_EDIT1, "C:\\Users\\maksi\\OneDrive\\Рабочий стол\\example.txt");
        SetDlgItemTextA(hWnd, IDC_EDIT2, "C:\\Users\\maksi\\OneDrive\\Изображения\\copy.txt");
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDC_BUTTON2) {
            StartCopying(hWnd);
            return TRUE;
        }
        break;
    }
    return FALSE;
}