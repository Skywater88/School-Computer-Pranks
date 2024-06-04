#include <windows.h>
#include <stdlib.h>
#include <time.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void GetDesktopResolution(int* horizontal, int* vertical);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SampleWindowClass";

    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "HEHEHE!!!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    HWND hStatic = CreateWindowEx(
        0,
        "STATIC",
        "\n\n\n!!!HATA OLUÞTU!!!",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        0, 0, 300, 150,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Get screen resolution
    int screenWidth, screenHeight;
    GetDesktopResolution(&screenWidth, &screenHeight);

    // Initial position and speed
    int x = (screenWidth / 2) - 150; // Start at center of screen
    int y = (screenHeight / 2) - 75; // Adjust for window size
    int dx = 2; // Increase the step size for faster movement
    int dy = 2;

    // Message loop
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // Move the window
            SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            // Update position
            x += dx;
            y += dy;

            // Check for collision with screen edges and reverse direction if necessary
            if (x < 0 || x > screenWidth - 300) dx = -dx;
            if (y < 0 || y > screenHeight - 150) dy = -dy;

            // Delay for a short period
            Sleep(10); // Reduce the sleep duration for faster updates
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GetDesktopResolution(int* horizontal, int* vertical) {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    *horizontal = desktop.right;
    *vertical = desktop.bottom;
}
