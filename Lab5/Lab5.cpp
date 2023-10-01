// Lab5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab5.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
            HPEN hPen;
            HBRUSH hBrush;

            //MoveToEx(hdc, 100, 100, NULL);
            hPen = CreatePen(PS_SOLID, 3, RGB(200, 70, 70));
            SelectObject(hdc, hPen);

            MoveToEx(hdc, 100, 200, NULL);
            LineTo(hdc, 150, 150);
            LineTo(hdc, 250, 150);
            LineTo(hdc, 300, 200);

            hPen = CreatePen(PS_SOLID, 3, RGB(50, 70, 200));
            hBrush = CreateSolidBrush(RGB(57, 175, 80));
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 50, 200, 300, 250);

            hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(250, 70, 140));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 75, 225, 125, 275);

            hBrush = CreateHatchBrush(HS_CROSS, RGB(80, 200, 140));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 225, 225, 275, 275);

            DeleteObject(hBrush);
            hPen = CreatePen(PS_SOLID, 2, RGB(80, 155, 245));
            hBrush = CreateSolidBrush(RGB(160, 200, 250));
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            Ellipse(hdc, 350, 175, 500, 250);
            Ellipse(hdc, 375, 125, 475, 175);
            
            int x1 = 400;
            int x2 = 450;
            int y1 = 120;
            int y2 = 130;
            hPen = CreatePen(PS_SOLID, 3, RGB(17, 208, 118));
            SelectObject(hdc, hPen);
            for (int i = 0; i < 10; i++) {
                Ellipse(hdc, x1, y1, x2, y2);
                y1 -= 1;
                y2 -= 1;
            }
            hPen = CreatePen(PS_SOLID, 3, RGB(80, 155, 245));
            SelectObject(hdc, hPen);
            Ellipse(hdc, 395, y1 - 30, 455, y2 + 5);

            hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
            SelectObject(hdc, hPen);
            MoveToEx(hdc, 415, 90, NULL);
            LineTo(hdc, 415, 90);
            MoveToEx(hdc, 430, 90, NULL);
            LineTo(hdc, 430, 90);
            MoveToEx(hdc, 422, 100, NULL);
            hPen = CreatePen(PS_SOLID, 2, RGB(250, 120, 45));
            hBrush = CreateSolidBrush(RGB(200, 70, 10));
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            POINT p[4] = { {422,100},{400,105},{422,110},{422,100} };
            Polygon(hdc, p, 4);
            
            hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hPen);
            MoveToEx(hdc, 375, 150, NULL);
            LineTo(hdc, 325, 125);
            LineTo(hdc, 300, 100);

            MoveToEx(hdc, 325, 125, NULL);
            LineTo(hdc, 325, 100);

            MoveToEx(hdc, 475, 150, NULL);
            LineTo(hdc, 525, 175);
            LineTo(hdc, 550, 200);

            MoveToEx(hdc, 525, 175, NULL);
            LineTo(hdc, 525, 200);

            hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hPen);
            hBrush = CreateSolidBrush(RGB(150, 90, 70));
            SelectObject(hdc, hBrush);
            MoveToEx(hdc, 75, 425, NULL);
            LineTo(hdc, 175, 325);
            Rectangle(hdc, 75, 425, 175, 475);
            Rectangle(hdc, 175, 325, 425, 475);
            hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(150, 90, 70));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 150, 450, 200, 500);
            Ellipse(hdc, 350, 450, 400, 500);
            // gorshok
            hPen = CreatePen(PS_SOLID, 3, RGB(165, 70, 0));
            SelectObject(hdc, hPen);
            hBrush = CreateSolidBrush(RGB(180, 90, 0));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 650, 275, 750, 300);
            POINT pe[4] = { {665, 300},{675,350},{725, 350},{735,300} };
            Polygon(hdc, pe, 4);
            // stvol
            hPen = CreatePen(PS_SOLID, 3, RGB(135, 70, 20));
            SelectObject(hdc, hPen);
            hBrush = CreateSolidBrush(RGB(150, 80, 10));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 675, 225, 725, 275);
            POINT pen[4] = { {725,250},{750, 225},{750, 250},{725,275} };
            Polygon(hdc, pen, 4);
            // krona
            hPen = CreatePen(PS_SOLID, 3, RGB(85, 215, 10));
            SelectObject(hdc, hPen);
            hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(95, 240, 12));
            SelectObject(hdc, hBrush);
            RoundRect(hdc, 625, 50, 775, 225, 25, 25);
            hPen = CreatePen(PS_SOLID, 2, RGB(75, 200, 10));
            SelectObject(hdc, hPen);
            hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(85, 220, 12));
            SelectObject(hdc, hBrush);
            RoundRect(hdc, 750, 215, 800, 265, 10, 10);

            //Ellipse(hdc, 50, 100, 250, 200);
            //Arc(hdc, 50, 100, 250, 200, 300, 150, 50, 250);

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

// Обработчик сообщений для окна "О программе".
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
