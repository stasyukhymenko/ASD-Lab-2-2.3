#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

int n = 12;
double** T;
int GraphType;

double** randm(int n) {

    srand(2328);

    double** arr = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            arr[i][j] = (double)rand() / (double)RAND_MAX * 2.0;
        }
    }
    return arr;
}

void deallocateMemory(double** arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

void printArray(double** arr, int n) {

    for (int j = 0; j < n; j++) {
        if (j > 9) {
            printf("  %d ", j + 1);
        }
        else {
            printf("    %d", j + 1);
        }
    }
    printf("\n\n");
    for (int i = 0; i < n; i++) {
        if (i > 8) {
            printf("%d", i + 1);
        }
        else {
            printf(" %d", i + 1);
        }

        for (int j = 0; j < n; j++) {
            printf("  %d  ", (int)arr[i][j]);
        }
        printf("\n\n");
    }
}

void mulmr(double k, double** arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = round(k * arr[i][j]);
        }
    }
}

double** graphUndirected(double** arr, int n) {
    double** undirectedArr = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        undirectedArr[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            undirectedArr[i][j] = arr[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (undirectedArr[i][j] == 1 && undirectedArr[j][i] == 0) {
                undirectedArr[j][i] = 1;
            }
        }
    }

    return undirectedArr;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    double c = 1.0 - 2 * 0.02 - 8 * 0.005 - 0.25;

    T = randm(n);
    printf("%f", c);
    mulmr(c, T, n);
    wchar_t ProgName[] = L"ЛР3, ІМ-23 Юхименко Станіслав";
    printArray(T, n);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HBRUSH hBrush = CreateSolidBrush(RGB(30, 30, 30));
    AllocConsole();
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    while (consoleHandle == INVALID_HANDLE_VALUE)
    {
        Sleep(10);
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    FILE* pf;
    freopen_s(&pf, "CONOUT$", "w", stdout);
    printf_s("1) Directed graph;\n");
    printf_s("2) Undirected graph;\n");
    printf_s("Choose type: ");
    freopen_s(&pf, "CONIN$", "r", stdin);
    freopen_s(&pf, "CONOUT$", "w", stdout);
    scanf_s(" %d", &GraphType);

    if (GraphType == 1)
    {
        printf("Matrix for directed graph:\n\n");
        printArray(T, n);
    }
    else if (GraphType == 2)
    {
        graphUndirected(T, n);
        printf("Matrix for undirected graph:\n\n");
        printArray(T, n);
    }
    else {
        printf("Enter 1 or 2 :)");
        Sleep(1500);
        return 0;
    }

    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = hBrush;
    w.style = CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;
    if (!RegisterClass(&w))
        return 0;
    HWND hWnd;
    MSG lpMsg;
    hWnd = CreateWindow(ProgName,
        ProgName,
        WS_OVERLAPPEDWINDOW,
        800,
        100,
        800,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);
    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    deallocateMemory(T, n);
    return(lpMsg.wParam);
}

HDC hdc;
PAINTSTRUCT ps;

void arrow(int x, int y, int x2, int y2)
{
    HPEN ArrowPen = CreatePen(PS_SOLID, 2, RGB(85, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));

    SelectObject(hdc, ArrowPen);

    float theta = atan2((int)y2 - (int)y, (int)x2 - (int)x);
    float x_intsct = (int)x2 - (int)16 * cos(theta);
    float y_intsct = (int)y2 - (int)16 * sin(theta);

    int arrowLen = 15;
    int arrowX = x_intsct - arrowLen * cos(theta + PI / 8);
    int arrowY = y_intsct - arrowLen * sin(theta + PI / 8);

    MoveToEx(hdc, x_intsct, y_intsct, NULL);
    LineTo(hdc, arrowX, arrowY);

    arrowX = x_intsct - arrowLen * cos(theta - PI / 8);
    arrowY = y_intsct - arrowLen * sin(theta - PI / 8);

    MoveToEx(hdc, x_intsct, y_intsct, NULL);
    LineTo(hdc, arrowX, arrowY);
    SelectObject(hdc, KPen);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    switch (messg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        wchar_t* nn[12] = { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11", L"12" };
        int nx[12];
        int ny[12];
        int x0 = 150;
        int y0 = 600;
        int r = 80;
        int r2 = 120;
        int count = 1;
        int count2 = 1;
        int bY, bX;
        int side = n / 4;
        int dx = 25, dy = 25, dtx = 8;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(201, 24, 109));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));
        HPEN PenThick = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));
        SelectObject(hdc, BPen);

        double fi = 0.0;
        int x = 0, y = 0;

        for (int i = 0; i < n; i++)
        {
            if (i <= side) {
                x = x0;
                y = y0 - r * i * 2;
                bY = y;
            }
            else if (i > side && i <= side * 2) {
                x = x0 + r * count * 2;
                y = bY;
                count++;
                bX = x;
            }
            else if (i > side * 2 && i <= side * 3) {
                count = 1;
                x = bX;
                y = bY + r * count2 * 2;
                count2++;
            }
            else if (i > side * 3 && i <= side * 4) {
                x = bX - r * count * 2;
                y = y0;
                count++;
            }

            if (i == 10 || i == 11) {
                x = (nx[0] + nx[9]) / 2;
                y = (ny[0] + ny[9]) / 2;
                Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);

                x = (nx[0] + nx[9]) / 2;
                y = (ny[1] + ny[2]) / 2;
                Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);
            }

            Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);

            if (i == 10 || i == 11) {
                nx[10] = (nx[0] + nx[9]) / 2;
                ny[10] = ny[0];

                nx[11] = (nx[0] + nx[9]) / 2;
                ny[11] = (ny[1] + ny[2]) / 2;
            }
            nx[i] = x;
            ny[i] = y;
        }
        SelectObject(hdc, KPen);
        int i = 0;
        int oldj = 0;
        int j = 0;

        for (i = 0; i < n; i++)
        {
            oldj++;
            j = oldj;
            for (j; j < n; j++)
            {
                if (T[i][j] == 1)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY -= vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);
                    if (GraphType == 1)
                    {
                        arrow(centX, centY, nx[j], ny[j]);
                    }
                }
            }
        }
        oldj = 1;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < oldj; j++)
            {

                if (T[i][j] == 1 && T[j][i] == 0)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY -= vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);
                    if (GraphType == 1)
                    {
                        arrow(centX, centY, nx[j], ny[j]);
                    }
                }
                else if (T[i][j] == 1 && T[j][i] == 1 && GraphType == 1 && i != j)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY += vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);

                    arrow(centX, centY, nx[j], ny[j]);
                }
            }
            oldj++;
        }
        for (i = 0; i < n; i++)
        {
            if (T[i][i] == 1)
            {
                if (i > 7 && i < 12)
                {
                    Arc(hdc, nx[i] + 25, ny[i] + 50, nx[i] - 25, ny[i], nx[i] - 25, ny[i] + 5, nx[i] + 25, ny[i]);
                    if (GraphType == 1)
                        arrow((nx[i] + 3.5), (ny[i] + 2), nx[i], ny[i]);
                }
                else
                {
                    Arc(hdc, nx[i] - 25, ny[i] - 50, nx[i] + 25, ny[i], nx[i] + 25, ny[i] - 5, nx[i] - 25, ny[i]);
                    if (GraphType == 1)
                        arrow((nx[i] + 3.5), (ny[i] - 2), nx[i], ny[i]);
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            TextOut(hdc, nx[i] - 1, ny[i] - 2, nn[i], 2);
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
}