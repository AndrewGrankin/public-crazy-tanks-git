// Crazy Tanks console game

#include <iostream>
#include <Game.h>

using namespace std;

int gameMatrixWidth = Game::PMATRIX_WIDTH;
int gameMatrixHeight = Game::PMATRIX_HEIGHT;
int paddingWidth = 74;
int paddingHeight = 130;

void ClearScreen()
{
    system("cls");
}

void ShowGameTitle()
{
    cout << endl << "    **** Crazy Tanks ****" << endl << endl;
}

int ShowOptions()
{
    int choise;
    cout << "  Select option:" << endl;
    cout << "  ==============" << endl;
    cout << "    Option 1 - Play" << endl;
    cout << "    Option 2 - Controls" << endl;
    cout << "    Option 0 - Exit" << endl;
    cout << endl;
    cout << "  Option> ";
    cin >> choise;
    return choise;
}

int ShowControls()
{
    int choise;
    cout << "  Controls:" << endl;
    cout << "  =========" << endl;
    cout << "    Arrows - movement UP/DOWN/LEFT/RIGHT" << endl;
    cout << "     Space - shooting" << endl;
    cout << "         P - pause" << endl;
    cout << "       ESC - go to menu" << endl;
    cout << endl;
    cout << "   Option '1' to go back" << endl;
    cout << "   Option> ";
    cin >> choise;
    return choise;
}

int main() 
{
    HWND consoleWindow = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(consoleWindow, &ConsoleRect); 
    MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, gameMatrixWidth + paddingWidth, gameMatrixHeight + paddingHeight, TRUE);

    bool menu = true;
    
    while (menu)
    {
        ClearScreen();
        ShowGameTitle();
        switch (ShowOptions())
        {
            case 1:
            {
                ClearScreen();
                ShowGameTitle();

                bool game = true;
                Game* aGame = new Game(&consoleWindow);

                while (game)
                {
                    aGame->Input();
                    aGame->Logic();
                    aGame->Draw();
                    aGame->CheckGameEnd(&game);
                    Sleep(50);  // game timing
                }

                delete aGame;

                break;
            }
            case 2: 
            {
                int controls = 0;
                while (controls != 1)
                {
                    ClearScreen();
                    ShowGameTitle();
                    controls = ShowControls();
                }
                break;
            }
            case 0:
            {
                menu = false;
                break;
            }  
        }
    }

}
