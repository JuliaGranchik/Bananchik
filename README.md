# Bananchik
#include <windows.h>
#include <iostream>
#include <string>
#include  <tchar.h> 
#define width 640
#define height 480

LRESULT CALLBACK WindowProc(HWND   hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// точка входа
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	//локальная переменная
	HWND hwnd;
	MSG uMsg;

	//функцияя что-то заполняет(что заполнить, чем заполнить, сколько надо заполнить)
	memset(&windowClass, 0, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	//цвет фона
	windowClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	// курсор - это стрелочка
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// икона формы
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hInstance = hInstance;
	// параметр указатель на процесс обработки сообщения формы
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = _T ("Maze generator");

	RegisterClassEx(&windowClass);

	hwnd = CreateWindow(windowClass.lpszClassName, _T("Maze Generator"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		//чтобы окно было по центру экрана
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CXSCREEN) - height) / 4, width, height, NULL, NULL, NULL, NULL);

	//кнопка
	CreateWindow(TEXT("button"), TEXT("Generate"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, hwnd, (HMENU)100, hInstance, 0);

	//показать окно
	ShowWindow(hwnd, nCmdShow);


	while (GetMessage(&uMsg, hwnd, NULL, NULL))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}

	return uMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND   hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// кнопка	(но с ней прога не работает почему-то)
	case WM_CREATE:
	{
		CreateWindow(TEXT("button"), TEXT("Generate"),
			WS_CHILD | WS_VISIBLE,
			10, 10, 80, 20,
			hwnd, (HMENU)100, NULL, NULL
			);
		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 100)
		{
			MessageBox(hwnd, _T ("Пока что это все, ура!!!"), _T ("title"), MB_OK | MB_ICONINFORMATION);
		}
	}


	case WM_CLOSE:
		ExitProcess(0);
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
