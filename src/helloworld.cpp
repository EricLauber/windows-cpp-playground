//
// HelloWorld.cpp
//

#include "framework.h"
#include "helloworld.h"

#define MAX_LOADSTRING 100

// Global Variables
HINSTANCE   hInst;                          // Current Instance Handle
WCHAR       szTitle[MAX_LOADSTRING];        // Title Bar Text
WCHAR       szWindowClass[MAX_LOADSTRING];  // The main window class name

// Forward declarations of functions defined in this file but out of order.
// Defined in logical order (not dependency order)

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
HRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Main Entry point for the program

// hInstance: the current app
// hPrevInstance: holdover from the old days when you could know a previous app - null now
// lpCmdLine: arguments
// nCmdShow: start minimized, maximized, etc.
int APIENTRY wWinMain(_In_       HINSTANCE hInstance,
                     _In_opt_    HINSTANCE hPrevInstance,
                     _In_ LPWSTR lpCmdLine,
                     _In_ int    nCmdShow)
{
        UNREFERENCED_PARAMETER(hPrevInstance);
        UNREFERENCED_PARAMETER(lpCmdLine);
 
        // Magic happens here!
        
        
        
        // Load localized strings that are global
        // if the API ends with W, that's Wide Strings, Wide Characters. LoadStringA is for ANSI, LoadString can compile either
        LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(hInstance, IDC_HELLOWORLD, szWindowClass, MAX_LOADSTRING);
        
        MyRegisterClass(hInst);

        // Initialize app
        if (!InitInstance (hInstance, nCmdShow))
        {
            return FALSE;
        }

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HELLOWORLD));

        // Any time anything happens, Windows calls this to handle it.
        // It's the MAIN MESSAGE LOOP
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            // Accelerators are keyboard shortcuts defined in the resource file
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                // Converts the keystroke into a command
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // Use the wParam of the last successfully processed message as the return code
        return (int) msg.wParam;
}

//
//  Registers the window class
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // Define a type of window
    WNDCLASSEXW wcex;
    
    // Convention is to begin with the size
    wcex.cbSize = sizeof(WNDCLASSEX);

    // Repaint surface if height or width changes
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // Callback function that handles messages sent to our window
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    // PID
    wcex.hInstance      = hInstance;
    // Full size Icon
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLOWORLD));
    // Default cursor when mousing over this window
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // 0 is a null handle, but also a color index, so increment by 1? weird.
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HELLOWORLD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
// Creates the main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // Store instance handle in our global variable
    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    0,
    CW_USEDEFAULT,
    0,
    nullptr,
    nullptr,
    hInstance,
    nullptr);


    // If something goes wrong, just end it all here
    if (!hWnd)
        return FALSE;

    // otherwise, show the window and repaint it immediately. UpdateWindow bypasses the message queue
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // we made it!
    return TRUE;
    
}

// WndProc (HWND, UNIT, WPARAM, LPARAM)
//
// Process messages for the main window
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse out the menu selections
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
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT rect;
            HDC hdc = BeginPaint(hWnd, &ps);

            GetClientRect(hWnd, &rect);

            DrawText(hdc, L"Hello, World!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            EndPaint(hWnd, &ps);
            break;
        }

        case WM_DESTROY:
            // stops the message loop
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//
// About - Message Handler for the About dialog DialogBox
//

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