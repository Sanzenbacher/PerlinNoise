#include <windows.h>
#include <stdint.h>
#include "../PerlinNoise/PerlinNoiseGenerator.h"
#define internal static 
#define local_persist static 
#define global_variable static

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

global_variable bool Running;

global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable int BitmapWidth;
global_variable int BitmapHeight;
global_variable int BytesPerPixel = 4;


internal void
Win32ResizeDIBSection(int Width, int Height)
{
	if (BitmapMemory)
	{
		VirtualFree(BitmapMemory, 0, MEM_RELEASE);
	}
	else
	{
		BitmapMemory = new char[Width*Height*4]; //RGB    32 bpp, 8 bpc, kCGImageAlphaNoneSkipFirst
	}

	BitmapWidth = Width;
	BitmapHeight = Height;

	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = BitmapWidth;
	BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;

	int BitmapMemorySize = (BitmapWidth*BitmapHeight)*BytesPerPixel;
	BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
	gradient_bild((unsigned char*)BitmapMemory, BitmapHeight, BitmapWidth); //Bitmap "malen"
}

internal void
Win32UpdateWindow(HDC Ziel_hdc, RECT *ClientRect, int X, int Y, int Width, int Height)
{
	int WindowWidth = Width; int WindowHeight = Height;
	WindowWidth = ClientRect->right - ClientRect->left;
	WindowHeight = ClientRect->bottom - ClientRect->top;
	StretchDIBits(Ziel_hdc,
		/* X, Y, Width, Height, ->Dest=DeviceContext
		   X, Y, Width, Height, ->Src 	*/
		X, Y, BitmapWidth, BitmapHeight,
		X, Y, WindowWidth, WindowHeight,
		BitmapMemory, /* Pointer zu Bilddaten in form eines Arrays in Bytes*/
		&BitmapInfo,  /* Point zur Beschreibung der DIB als BITMAPINFO-Struktur*/
		DIB_RGB_COLORS, /*RGB Daten sind im Array gespeichert*/
		SRCCOPY); /*Blitting-Modus*/
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
	UINT Message,
	WPARAM WParam,
	LPARAM LParam)
{
	LRESULT Result = 0;

	PAINTSTRUCT Paint;
	HDC DeviceContext;

	switch (Message)
	{
	case WM_SIZE:
	{
		RECT ClientRect;
		GetClientRect(Window, &ClientRect);
		int Width = ClientRect.right - ClientRect.left;
		int Height = ClientRect.bottom - ClientRect.top;
		Win32ResizeDIBSection(Width, Height);
	} break;

	case WM_CLOSE:
	{
		// TODO(casey): Handle this with a message to the user?
		Running = false;
	} break;

	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
	} break;

	case WM_DESTROY:
	{
		// TODO(casey): Handle this as an error - recreate window?
		Running = false;
	} break;

	case WM_PAINT:
	{
		DeviceContext = BeginPaint(Window, &Paint);
		int X = Paint.rcPaint.left;
		int Y = Paint.rcPaint.top;
		int Width = Paint.rcPaint.right - Paint.rcPaint.left;
		int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;

		RECT ClientRect;
		GetClientRect(Window, &ClientRect);

		Win32UpdateWindow(DeviceContext, &ClientRect, X, Y, Width, Height);
		EndPaint(Window, &Paint);
	} break;

	default:
	{
		//            OutputDebugStringA("default\n");
		Result = DefWindowProc(Window, Message, WParam, LParam);
	} break;
	}

	return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR CommandLine,
	int ShowCode)
{
	if (ShowCode){};
	if (CommandLine){};
	if (PrevInstance){};
	WNDCLASSA WindowClass = {};

	// TODO(casey): Check if HREDRAW/VREDRAW/OWNDC still matter
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	WindowClass.hInstance = Instance;
	//    WindowClass.hIcon;
	WindowClass.lpszClassName = (LPCSTR)"HandmadeHeroWindowClass";

	if (RegisterClassA(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(
				0,
				WindowClass.lpszClassName,
				"Perlin Noise 12.03.2017",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				Instance,
				0);
		if (Window)
		{
			vector_im_einheitszkreis(); //Zufallszahlen generieren
			gradient_bild((unsigned char*)BitmapMemory, BitmapHeight, BitmapWidth); //Bitmap "malen"
			Running = true;

			while (Running)
			{
				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					if (Message.message == WM_QUIT)
					{
						Running = false;
					}

					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				}
			}
		}
		else
		{
			// TODO(casey): Logging
		}
	}
	else
	{
		// TODO(casey): Logging
	}

	return(0);
}
