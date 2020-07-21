// This is to try graphics output

#include <windows.h>
#include <iostream>

using namespace std;

HWND consoleWindow;
HDC deviceContext;

const int BOARD_WIDTH = 216;        // board width in pixels
const int BOARD_HEIGHT = 216;       // board height in pixels
const int OFFSET_LEFT = 20;         // offset to strat drawing not from exact left
const int OFFSET_TOP = 40;          // offset to start drawing not from exact top

enum eDirection {STOP, UP, DOWN};
eDirection dir;

POINT tankRED[] = {{10,0}, {0,20}, {20,20}};
POINT tankBLUE[] = {{35,20}, {55,10}, {55,30}};

HPEN penRED = CreatePen(PS_SOLID, 1, RGB(255,0,0));
HBRUSH brushRED = CreateSolidBrush(RGB(255,0,0));
HBRUSH brushBLUE = CreateSolidBrush(RGB(0,0,255));

COLORREF colorWHITE = RGB(255, 255, 255);
COLORREF colorBLACK = RGB(0, 0, 0);
COLORREF colorRED = RGB(255, 0, 0);
COLORREF colorBLUE = RGB(0, 0, 255);


void Input()
{
    if (GetAsyncKeyState(VK_UP))
    {
        dir = UP;
    } 
    else if (GetAsyncKeyState(VK_DOWN))
    {
        dir = DOWN;
    }
    else
    {
        dir = STOP;
    }
}

void Draw()
{
    deviceContext = GetDC(consoleWindow);
        
    // // draw line
    // MoveToEx(deviceContext, 10, 10, NULL);
    // LineTo(deviceContext, 50, 50);

    // // draw polygon
    // SelectObject(deviceContext, brushRED);
    // Polygon(deviceContext, tankRED, 3);

    // // draw rectangle
    // SelectObject(deviceContext, brushBLUE);
    // Rectangle(deviceContext, 0, 0, 20, 20);

    POINT point;
    RECT rectFront, rectBack, rectBarrel, rectOuterBorder, rectInnerBorder;
    SetRect(&rectFront, 4, 0, 16, 8);
    SetRect(&rectBack, 4, 16, 16, 20);
    SetRect(&rectBarrel, 8, 4, 12, 8);
    SetRect(&rectOuterBorder, OFFSET_LEFT, OFFSET_TOP, BOARD_WIDTH + OFFSET_LEFT, BOARD_HEIGHT + OFFSET_TOP);
    SetRect(&rectInnerBorder, OFFSET_LEFT + 8, OFFSET_TOP + 8, BOARD_WIDTH + OFFSET_LEFT - 8, BOARD_HEIGHT + OFFSET_TOP - 8);



    // for (int i = 0; i < 20; ++i)
    // {
    //     for (int j = 0; j < 20; ++j)
    //     {
    //         point.x = j;
    //         point.y = i;
    //         if (PtInRect(&rectFront, point) || PtInRect(&rectBack, point))
    //         {
    //             if(PtInRect(&rectBarrel, point))
    //             {
    //                 SetPixel(deviceContext, point.x, point.y, colorWHITE);         
    //             }
    //             else
    //             {
    //                 SetPixel(deviceContext, point.x, point.y, colorBLACK);
    //             }
    //         }
    //         else
    //         {
    //             SetPixel(deviceContext, point.x, point.y, colorWHITE);
    //         }
    //     }
    // }


    for (int i = OFFSET_TOP; i < BOARD_HEIGHT + OFFSET_TOP; ++i)
    {
        for (int j = OFFSET_LEFT; j < BOARD_WIDTH + OFFSET_LEFT; ++j)
        {
            point.x = j;
            point.y = i;
            if (PtInRect(&rectOuterBorder, point) && !PtInRect(&rectInnerBorder, point))
            {
                SetPixel(deviceContext, point.x, point.y, colorWHITE);
            }
            else
            {
                SetPixel(deviceContext, point.x, point.y, colorBLACK);
            }
        }
    }
    

    ReleaseDC(consoleWindow, deviceContext);
}

int main()
{
    // // Get window handle to console, and device context
    // HWND consoleWindow = GetConsoleWindow();
    // HDC deviceContext = GetDC(consoleWindow);

    // // Here a 5 pixels wide RED line [from initial 0,0] to 300,300
    // HPEN pen = CreatePen(PS_SOLID, 5, RGB(255,0,0));
    // SelectObject(deviceContext, pen);
    // LineTo(deviceContext, 300, 300);
    // ReleaseDC(consoleWindow, deviceContext);


    
    consoleWindow = GetConsoleWindow();
    
    

    while (true)
    {
        Input();
        Draw();
    }
    

    // HBRUSH brush = CreateSolidBrush(RGB(255,0,0));
    // SelectObject(deviceContext, brush);
    // POINT vertices[] = {{10,10}, {5,15}, {15,15}};
    // Polygon(deviceContext, vertices, sizeof(vertices));

    
    // cin.ignore();       // to keep the console opened
    return 0;
}