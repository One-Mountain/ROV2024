// ROV_Controller.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ROV_Controller.h"
#include <XInput.h>
#pragma comment(lib, "XInput.lib")


#define MAX_LOADSTRING 100
WCHAR g_keyPressed[256] = L""; // Buffer to hold the key press message


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void CheckControllerState();
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROVCONTROLLER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROVCONTROLLER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //Call the controller state check
        CheckControllerState();
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROVCONTROLLER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROVCONTROLLER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // Create a font of size 45
            HFONT hFont = CreateFont(
                65, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

            // Select the font into the device context
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Set the text color
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text color

            // Get the size of the window
            RECT rect;
            GetClientRect(hWnd, &rect);

            // Calculate the width and height of the text
            SIZE textSize;
            GetTextExtentPoint32(hdc, g_keyPressed, wcslen(g_keyPressed), &textSize);

            // Calculate the position to center the text
            int x = (rect.right - textSize.cx) / 2;
            int y = (rect.bottom - textSize.cy) / 2;

            // Draw the key press message stored in g_keyPressed at the center of the window
            TextOut(hdc, x, y, g_keyPressed, wcslen(g_keyPressed));

            // Cleanup: Restore the old font and delete the created font
            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void CheckControllerState()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    DWORD result = XInputGetState(0, &state);

    if (result == ERROR_SUCCESS)
    {
        WORD buttons = state.Gamepad.wButtons;

        if (buttons & XINPUT_GAMEPAD_A)
            wcscpy_s(g_keyPressed, L"Key A was pressed");
        else if (buttons & XINPUT_GAMEPAD_B)
            wcscpy_s(g_keyPressed, L"Key B was pressed");
        else if (buttons & XINPUT_GAMEPAD_X)
            wcscpy_s(g_keyPressed, L"Key X was pressed");
        else if (buttons & XINPUT_GAMEPAD_Y)
            wcscpy_s(g_keyPressed, L"Key Y was pressed");
        else if (buttons & XINPUT_GAMEPAD_DPAD_UP)
            wcscpy_s(g_keyPressed, L"Up arrow was pressed");
        else if (buttons & XINPUT_GAMEPAD_DPAD_DOWN)
            wcscpy_s(g_keyPressed, L"Down arrow was pressed");
        else if (buttons & XINPUT_GAMEPAD_DPAD_LEFT)
            wcscpy_s(g_keyPressed, L"Left arrow was pressed");
        else if (buttons & XINPUT_GAMEPAD_DPAD_RIGHT)
            wcscpy_s(g_keyPressed, L"Right arrow was pressed");
        else if (buttons & XINPUT_GAMEPAD_START)
            wcscpy_s(g_keyPressed, L"Start button was pressed");
        else if (buttons & XINPUT_GAMEPAD_BACK)
            wcscpy_s(g_keyPressed, L"Back button was pressed");
        else if (buttons & XINPUT_GAMEPAD_LEFT_SHOULDER)
            wcscpy_s(g_keyPressed, L"Left shoulder was pressed");
        else if (buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            wcscpy_s(g_keyPressed, L"Right shoulder was pressed");
        else
            wcscpy_s(g_keyPressed, L"No button pressed");
    }
    else
    {
        wcscpy_s(g_keyPressed, L"Controller not connected");
    }

    // Force a repaint of the window
    InvalidateRect(NULL, NULL, TRUE);
}



// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
