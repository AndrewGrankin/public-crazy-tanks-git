// program to test window size

#include <windows.h>
// #include <winuser.h>
#include <iostream>

int main()
{
    HWND consoleWindow = GetConsoleWindow();

    // SMALL_RECT zeroWindow = {0, 0, 0, 0};
    // COORD zBuffer = {1, 1};
    // SetConsoleWindowInfo(consoleWindow, TRUE, &zeroWindow); 
    // SetConsoleScreenBufferSize(consoleWindow, zBuffer);

    // SHORT screenWidth = 400;
    // SHORT screenHeight = 400;
    // COORD bufferSize = {screenWidth, screenHeight};
    // SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(screenWidth - 1), static_cast<SHORT>(screenHeight - 1)};
    // SetConsoleScreenBufferSize(consoleWindow, bufferSize);
    // SetConsoleWindowInfo(consoleWindow, TRUE, &windowSize);

    RECT ConsoleRect;
    GetWindowRect(consoleWindow, &ConsoleRect); 
    MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, 400, 400, TRUE);

    // HANDLE ConsoleInHandle = 0;
    // HANDLE ConsoleOutHandle = 0;

    // if(!InitializeConsole(&ConsoleInHandle, &ConsoleOutHandle))
    // {
    //   printf("Console initialization error. Error code: %d\n", GetLastError());
    //   getchar();
    //   return 1;
    // }

    // const char* ConsoleTitle = "Crazy Tanks";
    // SetConsoleTitle(ConsoleTitle);

    // if(!ConsoleInHandle || !ConsoleOutHandle)
    // {
    //     printf("Handles are not created. Error: %d\n", GetLastError());
    //     return(1);
    // }

    // //Buffer size
    // const ushort BufferWidth = 35;
    // const ushort BufferHeight = 70;
    // SMALL_RECT WriteRegion = {};
    // COORD BufferOfCharacterSize = {}; 
    // COORD BufferOfCharacterCoord = {};
    // WriteRegion.Left = 0;
    // WriteRegion.Top = 0;
    // WriteRegion.Right = BufferHeight - 1;
    // WriteRegion.Bottom = BufferWidth - 1;

    // SetConsoleWindowInfo(ConsoleOutHandle, TRUE, &WriteRegion);
    // SetConsoleScreenBufferSize(ConsoleOutHandle, BufferOfCharacterSize);

    std::cin.ignore();
    return 0;
}