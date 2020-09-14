// Header file for Game class

#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <chrono> 
#include <array>

/* Custom types */
#include <Tank.h>
#include <Bullet.h>
#include <Icon.h>
#include <HealthIcon.h>
#include <ArmourIcon.h>
#include <Brick.h>
#include <Wall.h>
#include <Utils.h>
#include <TankStatusVO.h>
#include <Box.h>
#include <ExplosionEffect.h>
// #include <NodeVO.h>     /* Test data for optimal routes. Should be deleted */

class Game 
{
    public:
        static const int PMATRIX_WIDTH = 400;
        static const int PMATRIX_HEIGHT = 350;
        static const int BULLET_FIRE_RANGE = 100;
        
    public:
        Game(HWND* consoleWindow);
        ~Game();
        void Input();
        void Logic();
        void Draw();
        void CheckGameEnd(bool* game);

    private:

        // /*== Digit output ==*/
        // HANDLE hConsole;
        // DWORD dwBytesWritten;
        // /*================*/

        HWND* m_p_consoleWindow;
        HDC deviceContext;
        BITMAPINFO bitmapInfo;
        void* m_p_bitmapMemory;

        static const int DASHBOARD_HEIGHT = 50;
        static const int PMATRIX_BORDER = 10;       // game field border
        static const int PMATRIX_ACTION_RECT_WIDTH = PMATRIX_WIDTH - (PMATRIX_BORDER * 2);
        static const int PMATRIX_ACTION_RECT_HEIGHT = PMATRIX_HEIGHT - DASHBOARD_HEIGHT - (PMATRIX_BORDER * 2);
        static const int OFFSET_LEFT = 20;          // offset to strat drawing not from exact left
        static const int OFFSET_TOP = 40;           // offset to start drawing not from exact top
        static const int BYTES_PER_PIXEL = 4;       // how many bytes allocate for each pixel
        static const int NPC_COUNT = 10;
        static const int WALL_COUNT = 20;
        static const int TIMER_MINUTES = 1;

        /* ==== Test data for optimal routes. Should be deleted ==== */
        // static const int NODES_WIDTH = (PMATRIX_ACTION_RECT_WIDTH - Utils::TANK_PATTERN_WIDTH + Tank::STEP) / Tank::STEP;
        // static const int NODES_HEIGHT = (PMATRIX_ACTION_RECT_HEIGHT - Utils::TANK_PATTERN_HEIGHT + Tank::STEP) / Tank::STEP;
        // static const int NODES_NUMBER = NODES_WIDTH * NODES_HEIGHT;
        /* ==================== */

        int m_timerMinutes;
        int m_timerSeconds;
        int m_currentSeconds;
        int64_t m_previousTimeSnapshot;     // is used for countdown
        int64_t m_armourPickUpTime;          // holds the time when armour is picked up by anyone
        
        int mainDigitalMatrix[PMATRIX_WIDTH * PMATRIX_HEIGHT];
        RECT* m_p_MatrixActionRect;
        bool endGame;
        bool endGameRound;
        bool isKeyPressed;
        bool m_armourIsPickedUp;
        eKey key;
        eDirection direction;
        std::string m_timerString;
        std::string m_scoreString;
        std::string m_armourString;
        std::string m_outputString0;
        std::string m_outputString1;
        std::array<int, NPC_COUNT> m_tanksList;

        /* ==== Test data for optimal routes. Should be deleted ==== */
        // std::array<NodeVO*, NODES_NUMBER> m_nodesArray;
        // std::array<uint16_t, NODES_NUMBER * NODES_NUMBER> m_nodesAdjacencyMatrix;
        // std::array<uint16_t, NODES_NUMBER * NODES_NUMBER> m_nodesWeightMatrix;
        // std::array<uint16_t, NODES_NUMBER * NODES_NUMBER> m_nodesPathMatrix;
        /* ==================== */

        Box<GameObject> m_objectsBox;
        Box<TankStatusVO> m_statusBox;

    private: 
        Game();

        void ClearMainDigitalMatrix();
        void ResetMainDigitalMatrix();
        // void CreateTankSpawnGroup(Tank* tank, bool tankPosFixed);        /* Freezed draft functionality*/ // surrounds input tank with walls and adds it to the objects box
        void SpawnGameObject(eTag tag, int index, int seconds);
        void ArrangeGameField();
        // void CreateNodesForRoutes();                                     /* Freezed draft functionality */ creates nodes to calculater optimal routes
        // void CalculateRoutes();                                          /* Freezed draft functionality */ calculate optimal routes using Floyd's algorithm
        bool InsideActionRect(GameObject* gameObject);                                      // check if object within the action rectangle border
        // bool CheckObjectsOverlay(Box<GameObject>* list, RECT* rect);     /* Freezed draft functionality*/ // check if object overlays with tested rectangle
        GameObject* CheckObjectsOverlay(Box<GameObject>* list, GameObject* gameObject);     // check if object overlays with other objects in the box
        bool IsLegalMove(Tank aTank, eDirection dir);                                       // passing a copy of the GameObject object to protect it from original object changing
        void ValidateShootFlag(Tank* aTank, int64_t interval);
        void CheckIfGameRoundEnded();
        void RestartGameRound();

        /* ==== Test data for optimal routes. Should be deleted ==== */
        // // TEST. TO DELETE: drawing functions
        // void DrawLine(int startX, int startY, int endX, int endY, uint32_t lineColor);
        /* ========================================== */

        // little AI function
        void Behave(Tank* aTank);

        // text output functions
        void OutputTimerInfo();
        void UpdateScoreInfo();
        void OutputArmourInfo();
        void SetScoreString0(POINT p1, POINT p2, POINT p3, POINT p4);
        void SetScoreString1(POINT p1, POINT p2, POINT p3, POINT p4);
        void SetGameObjectsInfoOutput(Box<GameObject>* list);
        void ClearOutputStrings();
        std::string GetTimeString();
        std::string GetScoreString();
        std::string GetArmourInfoString();
        std::string GetOutputString0();
        std::string GetOutputString1();
};

#endif