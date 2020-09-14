// A Game class for Crazy Tanks for Input/Logic/Drawing

#include <Game.h>

Game::Game()
{}

// Constructor for the Game class
Game::Game(HWND* consoleWindow)
{
    // /*==Digit output==*/
    // hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    // dwBytesWritten = 0;
    // SetConsoleActiveScreenBuffer(hConsole);

    // SHORT w = 60, h = 60;
    // //Сначала задаем минимальные значения
    // SMALL_RECT zeroWindow = {0, 0, 0, 0};
    // COORD zBuffer = {1, 1};
    // SetConsoleWindowInfo(hConsole, TRUE, &zeroWindow); 
    // SetConsoleScreenBufferSize(hConsole, zBuffer);
 
    // //А уже потом изменяем значения на нужные нам
    // COORD bufferSize = {w, h};
    // SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(w - 1), static_cast<SHORT>(h - 1)};
    // SetConsoleScreenBufferSize(hConsole, bufferSize);
    // SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    // /*================*/


    // set initial values
    // consoleWindow = GetConsoleWindow();
    m_p_consoleWindow = consoleWindow;

    isKeyPressed = false;
    endGame = false;
    endGameRound = false;
    m_armourIsPickedUp = false;
    direction = STOP;

    // set timer
    m_previousTimeSnapshot = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    m_timerMinutes = TIMER_MINUTES;
    m_timerSeconds = m_timerMinutes * 60;
    m_currentSeconds = 0;
    OutputTimerInfo();

    // set score
    UpdateScoreInfo();

    // define action space in pixel matrix (game objects are not allowed to move outside this space)
    m_p_MatrixActionRect = new RECT();
    m_p_MatrixActionRect->left = PMATRIX_BORDER;
    m_p_MatrixActionRect->top = PMATRIX_BORDER + DASHBOARD_HEIGHT;
    m_p_MatrixActionRect->right = PMATRIX_WIDTH - PMATRIX_BORDER;
    m_p_MatrixActionRect->bottom = PMATRIX_HEIGHT - PMATRIX_BORDER; 

    ResetMainDigitalMatrix();     // fill main digital matrix with initial values
    ArrangeGameField();     // arrange game field with game objects

    // set bitmap header for game field
    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = PMATRIX_WIDTH;
    bitmapInfo.bmiHeader.biHeight = -PMATRIX_HEIGHT;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    
    // create bitmap
    int bitmapMemorySize = (PMATRIX_WIDTH * PMATRIX_HEIGHT) * BYTES_PER_PIXEL; 
    m_p_bitmapMemory = VirtualAlloc(0, bitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
}

Game::~Game()
{
    m_objectsBox.Clear();
    m_statusBox.Clear();
    delete m_p_MatrixActionRect;
    VirtualFree(m_p_bitmapMemory, 0, MEM_RELEASE);      // free memory for pixel bitmap
}

/* Freezed draft functionality */
// void CreateTankSpawnGroup(Tank* tank, bool tankPosFixed)
// {
//     Brick* p_firstBrick;
//     Brick* p_secondBrick;
//     GameObject* p_leftWall;
//     GameObejct* p_topWall;
//     GameObject* p_rightWall;
//     GameObject* p_bottomWall;
//     RECT* p_spawnGroupRect;
//     int coordX;
//     int coordY;

//     if (tankPosFixed)
//     {
//         p_firstBrick = new Brick(BRICK);
//         p_secondBrick = new Brick(BRICK);
//         p_leftWall = new Wall(WALL, p_firstBrick, p_secondBrick, UP);
//         coordX = tank->GetDrawingStart().x - Utils::BRICK_PATTERN_WIDTH;
//         coordY = tank->GetDrawingStart().y;
//     }
// }

void Game::SpawnGameObject(eTag tag, int index, int seconds)
{
    int64_t currentTimeSnapshot = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    GameObject* p_gameObject;
    int positionX;
    int positionY;


    if (m_statusBox.Size() != 0)
    {
        if (currentTimeSnapshot - m_statusBox.GetElement(index)->GetDeathTime() >= seconds)
        {
            switch (tag)
            {
                case PLAYER:
                {
                    p_gameObject = new Tank(PLAYER, Utils::COLOR_RED);
                    positionX = PMATRIX_WIDTH / 2 - PMATRIX_BORDER / 2;
                    positionY = PMATRIX_HEIGHT - PMATRIX_BORDER - Utils::TANK_PATTERN_HEIGHT;
                    p_gameObject->SetDrawingStart(positionX, positionY);
                    ((Tank*)p_gameObject)->SetShootFlag(true);
                    ((Tank*)p_gameObject)->SetLifesCount(2);
                    ((Tank*)p_gameObject)->SetIndex(index);

                    // check if tank can be placed in it's place
                    if (CheckObjectsOverlay(&m_objectsBox, p_gameObject) == NULL)
                    {
                        m_objectsBox.Add(p_gameObject);
                        m_statusBox.GetElement(index)->SetStatus(1);

                        /* Create life icons */
                        GameObject* p_lifeIcon;
                        for (int i = 0; i < ((Tank*)p_gameObject)->GetLifesCount(); ++i)
                        {
                            p_lifeIcon = new Icon(LIFE_ICON, Utils::COLOR_RED);
                            p_lifeIcon->SetDrawingStart(20 + (25 * i), 20);
                            m_objectsBox.Add(p_lifeIcon);
                        }
                    }
                    else // else delete the tank and try again on next iteration
                    {
                        delete p_gameObject;
                    }

                    break; 
                }
                case NPC:
                {
                    p_gameObject = new Tank(NPC, Utils::COLOR_BLUE);
                    positionX = Utils::GetRandomRoundedNumber(20, (PMATRIX_WIDTH - PMATRIX_BORDER - 40 - 10));     // "20" and "-40" to get space for tank; "-10" because of rounding to highest number
                    positionY = Utils::GetRandomRoundedNumber(20, (PMATRIX_HEIGHT - PMATRIX_BORDER + DASHBOARD_HEIGHT - 40 - 10));     // "20" "-40" tank pattern size; "-10" because of rounding to highest number
                    p_gameObject->SetDrawingStart(positionX, positionY);
                    ((Tank*)p_gameObject)->SetShootFlag(true);
                    ((Tank*)p_gameObject)->SetLifesCount(2);
                    ((Tank*)p_gameObject)->SetIndex(index);

                    // check if tank can be placed in game field
                    if (CheckObjectsOverlay(&m_objectsBox, p_gameObject) == NULL)
                    {
                        m_objectsBox.Add(p_gameObject);
                        m_statusBox.GetElement(index)->SetStatus(1);
                    }
                    else  // else delete the tank and try again on next iteration
                    {
                        delete p_gameObject;
                    }

                    break;
                }
                case HEALTH_ICON:
                {
                    p_gameObject = new HealthIcon(HEALTH_ICON);
                    positionX = Utils::GetRandomRoundedNumber(20, (PMATRIX_WIDTH - PMATRIX_BORDER - 40 - 10));     // "20" and "-40" to get space for tank; "-10" because of rounding to highest number
                    positionY = Utils::GetRandomRoundedNumber(20, (PMATRIX_HEIGHT - PMATRIX_BORDER + DASHBOARD_HEIGHT - 40 - 10));     // "20" "-40" tank pattern size; "-10" because of rounding to highest number
                    p_gameObject->SetDrawingStart(positionX, positionY);
                    ((HealthIcon*)p_gameObject)->SetIndex(index);

                    // check if health icon can be placed in game field
                    if (CheckObjectsOverlay(&m_objectsBox, p_gameObject) == NULL)
                    {
                        m_objectsBox.Add(p_gameObject);
                        m_statusBox.GetElement(index)->SetStatus(1);
                    }   
                    else    // else delete the health icon and try again on next iteration
                    {
                        delete p_gameObject;
                    }

                    break; 
                }
                case ARMOUR_ICON:
                {
                    p_gameObject = new ArmourIcon(ARMOUR_ICON);
                    positionX = Utils::GetRandomRoundedNumber(20, (PMATRIX_WIDTH - PMATRIX_BORDER - 40 - 10));     // "20" and "-40" to get space for tank; "-10" because of rounding to highest number
                    positionY = Utils::GetRandomRoundedNumber(20, (PMATRIX_HEIGHT - PMATRIX_BORDER + DASHBOARD_HEIGHT - 40 - 10));     // "20" "-40" tank pattern size; "-10" because of rounding to highest number
                    p_gameObject->SetDrawingStart(positionX, positionY);
                    ((ArmourIcon*)p_gameObject)->SetIndex(index);

                    // check if armour icon can be placed in game field
                    if (CheckObjectsOverlay(&m_objectsBox, p_gameObject) == NULL)
                    {
                        m_objectsBox.Add(p_gameObject);
                        m_statusBox.GetElement(index)->SetStatus(1);
                    }   
                    else    // else delete the armour icon and try again on next iteration
                    {
                        delete p_gameObject;
                    }

                    break; 
                }
            }
        }
    }    
}

void Game::ArrangeGameField()
{   
    TankStatusVO* tankStatusVO;

    /* Create walls */
    Brick* p_firstBrick;
    Brick* p_secondBrick;
    GameObject* p_wall;
    for (unsigned int i = 0; i < WALL_COUNT; ++i)
    {
        p_firstBrick = new Brick(BRICK);
        p_secondBrick = new Brick(BRICK);
        p_wall = new Wall(WALL, p_firstBrick, p_secondBrick, Utils::GetRandomDirection());
        int randomX;
        int randomY;
        bool isOverlaid = true;

        // calculate start coordinates
        do
        {
            randomX = Utils::GetRandomRoundedNumber(m_p_MatrixActionRect->left, m_p_MatrixActionRect->right - (Utils::BRICK_PATTERN_WIDTH * 2));
            randomY = Utils::GetRandomRoundedNumber(m_p_MatrixActionRect->top, m_p_MatrixActionRect->bottom - (Utils::BULLET_PATTERN_HEIGHT * 2) - (Utils::TANK_PATTERN_HEIGHT * 2));
            p_wall->SetDrawingStart(randomX, randomY);
            if (CheckObjectsOverlay(&m_objectsBox, p_wall) == NULL)
            {
                isOverlaid = false;
            }
            else
            {
                isOverlaid = true;
            }
        } 
        while (isOverlaid);
        m_objectsBox.Add(p_wall);
    }

    /* Create player */
    GameObject* p_player = new Tank(PLAYER, Utils::COLOR_RED);
    int playerPosX = PMATRIX_WIDTH / 2 - PMATRIX_BORDER / 2;
    int playerPosY = PMATRIX_HEIGHT - PMATRIX_BORDER - Utils::TANK_PATTERN_HEIGHT;
    p_player->SetDrawingStart(playerPosX, playerPosY);
    ((Tank*)p_player)->SetShootFlag(true);           // player can fire for first time
    ((Tank*)p_player)->SetLifesCount(2);            // set 2 lifes to player
    m_objectsBox.Add(p_player);

    // create status object to collecting player's status, score and death time
    tankStatusVO = new TankStatusVO();
    tankStatusVO->SetTag(PLAYER);
    tankStatusVO->SetStatus(1);         // "0" - tank not exists, "1" - tank exists
    tankStatusVO->SetScore(0);
    m_statusBox.Add(tankStatusVO);
    ((Tank*)p_player)->SetIndex(m_statusBox.GetElementIndex(tankStatusVO));

    /* Create life icons */
    GameObject* p_lifeIcon;
    for (int i = 0; i < ((Tank*)p_player)->GetLifesCount(); ++i)
    {
        p_lifeIcon = new Icon(LIFE_ICON, Utils::COLOR_RED);
        p_lifeIcon->SetDrawingStart(20 + (25 * i), 20);
        m_objectsBox.Add(p_lifeIcon);
    }

    /* Create enemies */
    GameObject* p_tank;
    for (unsigned int i = 0; i < NPC_COUNT; ++i)
    {
        p_tank = new Tank(NPC, Utils::COLOR_BLUE);
        ((Tank*)p_tank)->SetShootFlag(false);       // can't shoot at the very beginning
        ((Tank*)p_tank)->SetLastShootTime(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());      // initialize lastShotTime variable
        ((Tank*)p_tank)->SetLifesCount(2);           // set 1 life to NPC
        int randomX;
        int randomY;
        bool isOverlaid = true;

        // calculate start coordinates
        do
        {
            randomX = Utils::GetRandomRoundedNumber(0, (PMATRIX_WIDTH - PMATRIX_BORDER - 20 - 10));     // "-20" tank pattern size; "0" and "-10" because of rounding to highest number
            randomY = Utils::GetRandomRoundedNumber(DASHBOARD_HEIGHT, (PMATRIX_HEIGHT - PMATRIX_BORDER + DASHBOARD_HEIGHT - 20 - 10));     // "-20" tank pattern size; "0" and "-10" because of rounding to highest number
            p_tank->SetDrawingStart(randomX, randomY);
            if (CheckObjectsOverlay(&m_objectsBox, p_tank) == NULL)
            {
                isOverlaid = false;
            }
            else
            {
                isOverlaid = true;
            }
        } 
        while (isOverlaid);
        m_objectsBox.Add(p_tank);

        // create status object to collecting tank's status, score and death time
        tankStatusVO = new TankStatusVO();
        tankStatusVO->SetTag(NPC);
        tankStatusVO->SetStatus(1);         // "0" - tank not exists, "1" - tank exists
        tankStatusVO->SetScore(0);
        m_statusBox.Add(tankStatusVO);
        ((Tank*)p_tank)->SetIndex(m_statusBox.GetElementIndex(tankStatusVO));
    }

    // create status object to collect health icon's status and death time
    tankStatusVO = new TankStatusVO();
    tankStatusVO->SetTag(HEALTH_ICON);
    tankStatusVO->SetStatus(0);         // "0" - icon not exists, "1" - icon exists
    tankStatusVO->SetScore(0);          // it is not required for health icon
    tankStatusVO->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    m_statusBox.Add(tankStatusVO);

    // create status object to collect armour icon's status and death time
    tankStatusVO = new TankStatusVO();
    tankStatusVO->SetTag(ARMOUR_ICON);
    tankStatusVO->SetStatus(0);         // "0" - icon not exists, "1" - icon exists
    tankStatusVO->SetScore(0);          // it is not required for health icon
    tankStatusVO->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    m_statusBox.Add(tankStatusVO);
    m_armourIsPickedUp = false;

    /* Freezed draft functionality */
    // /* create nodes to calculate routes */
    // // CreateNodesForRoutes();

    // /* calculate routes */
    // // CalculateRoutes();

}

/* Freezed draft functionality */
// void Game::CreateNodesForRoutes()
// {
//     /* fill nodes array with nodeVO objects */
//     uint16_t coordX = m_p_MatrixActionRect->left;
//     uint16_t coordY = m_p_MatrixActionRect->top;
//     NodeVO* p_nodeVO;

//     for (int y = 0; y < NODES_HEIGHT; ++y)
//     {
//         for (int x = 0; x < NODES_WIDTH; ++x)
//         {
//             p_nodeVO = new NodeVO();
//             p_nodeVO->SetNodeNumber((y * NODES_WIDTH + x) + 1);   // we start nodes count from 1 for valid path building
//             p_nodeVO->SetNodeCoords(coordX, coordY);

//             // check if node is near the wall
//             GameObject* p_testTank = new Tank(NPC, Utils::COLOR_BLUE);
//             p_testTank->SetDrawingStart(coordX, coordY);
//             GameObject* p_testObject = CheckObjectsOverlay(&m_objectsBox, p_testTank);
//             if (p_testObject != NULL)
//             {
//                 if (p_testObject->GetTag() == WALL)
//                 {
//                     p_nodeVO->SetAccess(false);
//                 }
//                 else
//                 {
//                     p_nodeVO->SetAccess(true);
//                 }
//             }
//             else
//             {
//                 p_nodeVO->SetAccess(true);
//             }
//             delete p_testTank;

//             p_nodeVO->SetColor(Utils::COLOR_WHITE);
//             m_nodesArray[y * NODES_WIDTH + x] = p_nodeVO;

//             coordX += Tank::STEP;
//         }
//         coordX = m_p_MatrixActionRect->left;
//         coordY += Tank::STEP;
//     }   
// }

/* Freezed draft functionality */
// void Game::CalculateRoutes()
// {
//     // constructing the nodes adjacency matrix
//     for (uint16_t i = 0; i < NODES_NUMBER; ++i)
//     {
//         for (uint16_t j = 0; j < NODES_NUMBER; ++j)
//         {
//             if (i == j)
//             {
//                 m_nodesAdjacencyMatrix[i * NODES_NUMBER + j] = 0;
//             }
//             else
//             {
//                 NodeVO* p_i_Node = m_nodesArray[i];
//                 NodeVO* p_j_Node = m_nodesArray[j];
//                 if (p_i_Node->IsAccessible() && p_j_Node->IsAccessible())
//                 {
                    
//                     uint16_t node_i_x = p_i_Node->GetNodeCoordX();
//                     uint16_t node_i_y = p_i_Node->GetNodeCoordY();
//                     uint16_t node_j_x = p_j_Node->GetNodeCoordX();
//                     uint16_t node_j_y = p_j_Node->GetNodeCoordY();

//                     if ( (abs(node_j_x - node_i_x) == Tank::STEP && node_j_y - node_i_y == 0) 
//                       || (abs(node_j_y - node_i_y) == Tank::STEP && node_j_x - node_i_x == 0) )
//                     {
//                         m_nodesAdjacencyMatrix[i * NODES_NUMBER + j] = 1;
//                     }
//                     else
//                     {
//                         m_nodesAdjacencyMatrix[i * NODES_NUMBER + j] = Utils::MAX_NUMBER;    
//                     }
//                 }
//                 else
//                 {
//                     m_nodesAdjacencyMatrix[i * NODES_NUMBER + j] = Utils::MAX_NUMBER;
//                 }
//             }
//         }
//     }

//     // action Floyd algorithm
//     for (uint16_t k = 0; k < NODES_NUMBER; ++k)
//     {
//         for (uint16_t y = 0; y < NODES_NUMBER; ++y)
//         {
//             for (uint16_t x = 0; x < NODES_NUMBER; ++x)
//             {
//                 uint16_t value_0 = m_nodesAdjacencyMatrix[y * NODES_NUMBER + x];
//                 uint16_t value_1 = m_nodesAdjacencyMatrix[y * NODES_NUMBER + k];
//                 uint16_t value_2 = m_nodesAdjacencyMatrix[k * NODES_NUMBER + x];

//                 if (value_1 + value_2 < value_0)
//                 {  
//                     m_nodesWeightMatrix[y * NODES_NUMBER + x] = value_1 + value_2;
//                     m_nodesPathMatrix[y * NODES_NUMBER + x] = k + 1;
//                 }
//                 else
//                 {
//                     m_nodesWeightMatrix[y * NODES_NUMBER + x] = value_0;
//                 }
//             }
//         }

//         // copy result matrix to source matrix
//         for (uint16_t y = 0; y < NODES_NUMBER; ++y)
//         {
//             for (uint16_t x = 0; x < NODES_NUMBER; ++x)
//             {
//                 m_nodesAdjacencyMatrix[y * NODES_NUMBER + x] = m_nodesWeightMatrix[y * NODES_NUMBER + x];
//             }
//         }
//     }
// }

void Game::ClearMainDigitalMatrix()
{
    for (int y = 0; y < PMATRIX_HEIGHT; ++y)
    {
        for (int x = 0; x < PMATRIX_WIDTH; ++x)
        {
            mainDigitalMatrix[y * PMATRIX_WIDTH + x] = Utils::GetColorIndex(Utils::COLOR_BLACK);      
            // mainDigitalMatrix[y * PMATRIX_WIDTH + x] = 1;      // digit output
        }
    }
}

void Game::ResetMainDigitalMatrix()
{
    for (int y = 0; y < PMATRIX_HEIGHT; ++y)
    {
        for (int x = 0; x < PMATRIX_WIDTH; ++x)
        {
            if ((x < PMATRIX_BORDER || x >= PMATRIX_WIDTH - PMATRIX_BORDER) ||
                (y < PMATRIX_BORDER || (y > DASHBOARD_HEIGHT && y < DASHBOARD_HEIGHT + PMATRIX_BORDER) || y >= PMATRIX_HEIGHT - PMATRIX_BORDER))
            {
                mainDigitalMatrix[y * PMATRIX_WIDTH + x] = Utils::GetColorIndex(Utils::COLOR_GAINSBORO);      
                // mainDigitalMatrix[y * PMATRIX_WIDTH + x] = 0;      // digit output
            }
            else
            {
                if (y <= DASHBOARD_HEIGHT)
                {
                    mainDigitalMatrix[y * PMATRIX_WIDTH + x] = Utils::GetColorIndex(Utils::COLOR_DARKGREY); 
                }
                else
                {
                    mainDigitalMatrix[y * PMATRIX_WIDTH + x] = Utils::GetColorIndex(Utils::COLOR_BLACK);       
                    // mainDigitalMatrix[y * PMATRIX_WIDTH + x] = 1;       // digit output
                }
            }
        }
    }
}

bool Game::InsideActionRect(GameObject* gameObject)
{
    bool isInside = false;
    POINT topLeft;
    POINT bottomRight;
    topLeft = gameObject->GetDrawingStart();
    bottomRight = gameObject->GetDrawingEnd();

    if (PtInRect(m_p_MatrixActionRect, topLeft) && PtInRect(m_p_MatrixActionRect, bottomRight))
    {
        isInside = true;
    }
    else
    {
        isInside = false;
    }

    return isInside;
}

GameObject* Game::CheckObjectsOverlay(Box<GameObject>* list, GameObject* gameObject)
{
    // bool isOverlaid = true;
    GameObject* returnObject;

    POINT topLeft;
    POINT topRight;
    POINT bottomRight;
    POINT bottomLeft;
    POINT middleTop;
    POINT middleRight;
    POINT middleBottom;
    POINT middleLeft;

    topLeft = gameObject->GetDrawingStart();
    bottomRight = gameObject->GetDrawingEnd();
    topRight.x = topLeft.x + (gameObject->GetPatternWidth() - 1);      // "-1" - we can't use pattern size for actual coordinates calculations
    topRight.y = topLeft.y;
    bottomLeft.x = bottomRight.x - (gameObject->GetPatternWidth() - 1);    // "-1" - we can't use pattern size for actual coordinates calculations
    bottomLeft.y = bottomRight.y;
    middleTop.x = topLeft.x + (gameObject->GetPatternWidth() / 2);
    middleTop.y = topLeft.y;
    middleRight.x = topRight.x;
    middleRight.y = topRight.y + (gameObject->GetPatternHeight() / 2);
    middleBottom.x = bottomLeft.x + (gameObject->GetPatternWidth() / 2);
    middleBottom.y = bottomLeft.y;
    middleLeft.x = topLeft.x;
    middleLeft.y = topLeft.y + (gameObject->GetPatternHeight() / 2);
    
    // adjust right and bottom lines because of PtInRect() function speciality
    topRight.x -= 1;
    middleRight.x -= 1;
    bottomRight.x -= 1;
    bottomLeft.y -= 1;
    middleBottom.y -= 1;
    bottomRight.y -= 1; 

    // check the Action border
    if (InsideActionRect(gameObject))
    {
        // check other game objects
        BoxItem<GameObject>* p_item = list->GetHead();

        // check if box is empty (if we use any other boxes)
        if (p_item == 0)
        {
            // isOverlaid = false;
            returnObject = NULL;
        }
        while (p_item != 0)
        {
            // check if it is not the same object
            if (p_item->GetCargo()->GetID() != gameObject->GetID())
            {
                if (PtInRect(p_item->GetCargo()->GetBoxCollider(), topLeft) || 
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), topRight) || 
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), bottomLeft) || 
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), bottomRight) ||
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), middleTop) ||
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), middleRight) ||
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), middleBottom) ||
                    PtInRect(p_item->GetCargo()->GetBoxCollider(), middleLeft))
                {
                    // isOverlaid = true;
                    returnObject = p_item->GetCargo();
                    break;
                }
                else
                {
                    // isOverlaid = false;
                    returnObject = NULL;
                }
            }
            else
            {
                returnObject = NULL;
            }
            p_item = p_item->GetNext();
        }
    }
    else
    { 
        // isOverlaid = true;
        returnObject = gameObject;      // if it is outside the action rectangle, then return the tested game object itself 
    }

    return returnObject;
}

bool Game::IsLegalMove(Tank aTank, eDirection dir)      // passing a copy of the Tank object to protect it from its changing
{
    bool isLegal = false;
    aTank.Move(dir);
    GameObject* p_overlayObject = CheckObjectsOverlay(&m_objectsBox, &aTank);
    if (p_overlayObject == NULL)
    {
        isLegal = true;
    }
    else if (p_overlayObject->GetTag() == EXPLOSION ||
             p_overlayObject->GetTag() == HEALTH_ICON ||
             p_overlayObject->GetTag() == ARMOUR_ICON)
        {
            isLegal = true;
        }
        else
        {   
            isLegal = false;
        }

    return isLegal;
}

void Game::ValidateShootFlag(Tank* aTank, int64_t interval)
{
    int64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t result = currentTime - aTank->GetLastShootTime();
    if (result >= interval)
    {
        aTank->SetShootFlag(true);
    }
    else
    {
        aTank->SetShootFlag(false);
    }
}

void Game::CheckIfGameRoundEnded()
{
    if (endGameRound)
    {
        // set shoot flag of each tank to false 
        BoxItem<GameObject>* p_currentItem = m_objectsBox.GetHead();
        while (p_currentItem != 0)
        {
            if (p_currentItem->GetCargo()->GetTag() == NPC || p_currentItem->GetCargo()->GetTag() == PLAYER)
            {
                ((Tank*)p_currentItem->GetCargo())->SetShootFlag(false);
            }
            p_currentItem = p_currentItem->GetNext();
        }
    }
}

void Game::RestartGameRound()
{
    endGameRound = false;
    m_previousTimeSnapshot = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    m_timerMinutes = TIMER_MINUTES;
    m_timerSeconds = m_timerMinutes * 60;    
    m_currentSeconds = 0;

    m_objectsBox.Clear();
    m_statusBox.Clear();

    ResetMainDigitalMatrix();
    ArrangeGameField();
}

/* Experimental functionality */
// void Game::Behave(Tank* aTank)
// {
//     if (aTank->GetEnemyObject() == NULL)
//     {
//         aTank->SetEnemyObject(&m_statusBox);
//     }
//     else if (aTank->GetEnemyObject()->GetStatus() == 0)
//     {
//         aTank->SetEnemyObject(&m_statusBox);
//     }

//     // выбрать танк для атаки
//     // начать сближение
//     // в радиусе атаки начать обстреливать

//     int coordX = aTank->GetDrawingStart().x;
//     int coordY = aTank->GetDrawingStart().y;
//     int enemyCoordX = aTank->GetEnemyObject()->GetLocation().x;
//     int enemyCoordY = aTank->GetEnemyObject()->GetLocation().y;

//     // set random axis change every random path length
//     if (aTank->GetPathLength() == 0)
//     {
//         aTank->SetXAxisDirection(Utils::GetRandomFlag());
//         aTank->SetPathLength(Utils::GetRandomNumber(1, 10));
//     }

//     bool isXAxisDirection = aTank->IsXAxisDirection();
//     switch (isXAxisDirection)
//     {
//         case true: 
//         {
//             if (coordX > enemyCoordX)
//             {
//                 bool check = IsLegalMove(*aTank, LEFT);     
//                 if (check)
//                 {
//                     aTank->Move(LEFT);
//                 }
//             }
//             else if (coordX < enemyCoordX)
//             {
//                 bool check = IsLegalMove(*aTank, RIGHT);     
//                 if (check)
//                 {
//                     aTank->Move(RIGHT);
//                 }
//             }
//             break;
//         }
//         case false: 
//         {
//             if (coordY > enemyCoordY)
//             {
//                 bool check = IsLegalMove(*aTank, UP);     
//                 if (check)
//                 {
//                     aTank->Move(UP);
//                 }
//             }
//             else if (coordY < enemyCoordY)
//             {
//                 bool check = IsLegalMove(*aTank, DOWN);     
//                 if (check)
//                 {
//                     aTank->Move(DOWN);
//                 }
//             }
//             break;
//         }
//     }

//     // decrease the NPC's path lenght
//     aTank->DecreasePath();
// }

void Game::Input()
{
    if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_SPACE))
    {
        direction = LEFT;
        isKeyPressed = true;
        key = KEYBOARD_LEFT_AND_SPACE;
    } 
    else if (GetAsyncKeyState(VK_LEFT)) 
    {
        direction = LEFT;
        isKeyPressed = true;
        key = KEYBOARD_LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_SPACE))
    {
        direction = RIGHT;
        isKeyPressed = true;
        key = KEYBOARD_RIGHT_AND_SPACE;
    }
    else if (GetAsyncKeyState(VK_RIGHT)) 
    {     
        direction = RIGHT;
        isKeyPressed = true;
        key = KEYBOARD_RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_SPACE))
    {
        direction = UP;
        isKeyPressed = true;
        key = KEYBOARD_UP_AND_SPACE;
    }
    else if (GetAsyncKeyState(VK_UP)) 
    { 
        direction = UP;
        isKeyPressed = true;
        key = KEYBOARD_UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_SPACE))
    {
        direction = DOWN;
        isKeyPressed = true;
        key = KEYBOARD_DOWN_AND_SPACE;
    }
    else if (GetAsyncKeyState(VK_DOWN)) 
    {
        direction = DOWN;
        isKeyPressed = true;
        key = KEYBOARD_DOWN;
    }
    else if (GetAsyncKeyState(VK_SPACE))
    {
        isKeyPressed = true;
        key = KEYBOARD_SPACE;
    }
    else if (GetAsyncKeyState(0x52))
    {
        isKeyPressed = true;
        key = KEYBOARD_R;
    }
    else if (GetAsyncKeyState(VK_ESCAPE))
    {
        endGame = true;
    }
    else
    {
        isKeyPressed = false;
    }  
}

void Game::Logic()
{ 
    Tank* p_player = 0;
    BoxItem<GameObject>* p_item;

    // get player object and draw it's animation if any
    // also populate it's coordinates
    p_item = m_objectsBox.GetHead();
    while (p_item != 0)
    {
        if (p_item->GetCargo()->GetTag() == PLAYER)
        {
            p_player = (Tank*)(p_item->GetCargo());
            p_player->Animate();

            if (m_statusBox.Size() != 0)
            {
                m_statusBox.GetElement(p_player->GetIndex())->SetLocation(p_player->GetDrawingStart().x, p_player->GetDrawingStart().y);
            }

            break;
        }
        p_item = p_item->GetNext();
    }


    if (isKeyPressed)
    {
        if (key == KEYBOARD_UP || 
            key == KEYBOARD_DOWN || 
            key == KEYBOARD_LEFT || 
            key == KEYBOARD_RIGHT ||
            key == KEYBOARD_RIGHT_AND_SPACE ||
            key == KEYBOARD_LEFT_AND_SPACE ||
            key == KEYBOARD_UP_AND_SPACE ||
            key == KEYBOARD_DOWN_AND_SPACE)
        {
            // check if player can move
            if (p_player != 0)
            {
                bool check = IsLegalMove(*p_player, direction);
                if (check)
                {
                    p_player->Move(direction);

                    if (m_statusBox.Size() != 0)
                    {
                        m_statusBox.GetElement(p_player->GetIndex())->SetLocation(p_player->GetDrawingStart().x, 
                                                                                  p_player->GetDrawingStart().y);
                    }

                    // check if player hits health or armour icon
                    GameObject* p_overlayObject = CheckObjectsOverlay(&m_objectsBox, p_player);
                    if (p_overlayObject != NULL)
                    {
                        // if it is health
                        if (p_overlayObject->GetTag() == HEALTH_ICON)
                        {
                            if (m_statusBox.Size() != 0)
                            {
                                m_statusBox.GetElement(((HealthIcon*)p_overlayObject)->GetIndex())->SetStatus(0);
                                m_statusBox.GetElement(((HealthIcon*)p_overlayObject)->GetIndex())->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                            }
                            m_objectsBox.MarkToRemove(p_overlayObject);

                            // calculate lifes delta: how many lifes we can add
                            int currentLifes = p_player->GetLifesCount();
                            int lifesDelta = p_player->GetMaxLifesCount() - currentLifes; 
                            p_player->SetLifesCount(p_player->GetLifesCount() + lifesDelta);

                            /* Create life icons */
                            GameObject* p_lifeIcon;
                            for (int i = 0; i < lifesDelta; ++i)
                            {
                                p_lifeIcon = new Icon(LIFE_ICON, Utils::COLOR_RED);
                                p_lifeIcon->SetDrawingStart(20 + (25 * (i + currentLifes)), 20);
                                m_objectsBox.Add(p_lifeIcon);
                            }

                        }
                        // else if it is armour
                        else if (p_overlayObject->GetTag() == ARMOUR_ICON)
                        {
                            int64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                            if (m_statusBox.Size() != 0)
                            {
                                m_statusBox.GetElement(((ArmourIcon*)p_overlayObject)->GetIndex())->SetStatus(0);
                                m_statusBox.GetElement(((ArmourIcon*)p_overlayObject)->GetIndex())->SetDeathTime(currentTime);
                            }
                            m_objectsBox.MarkToRemove(p_overlayObject);

                            p_player->PickUpArmour();
                            m_armourPickUpTime = currentTime;
                            m_armourIsPickedUp = true;
                        }
                    }
                }
            } 
        }

        // shoot a bullet 
        if (key == KEYBOARD_SPACE ||
            key == KEYBOARD_RIGHT_AND_SPACE ||
            key == KEYBOARD_LEFT_AND_SPACE ||
            key == KEYBOARD_UP_AND_SPACE ||
            key == KEYBOARD_DOWN_AND_SPACE)
        {
            // if player can shoot
            if (p_player != 0)
            {
                if (p_player->GetShootFlag() == true)
                {
                    // then shoot a bullet
                    p_player->SetLastShootTime(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                    GameObject* newBullet = new Bullet(BULLET, Utils::COLOR_YELLOW, p_player->GetDirection());
                    POINT drawingStart = p_player->GetShootingPosition(p_player->GetDirection());
                    newBullet->SetDrawingStart(drawingStart.x, drawingStart.y);
                    ((Bullet*)newBullet)->BelongTo(PLAYER);
                    ((Bullet*)newBullet)->SetTankIndex(p_player->GetIndex());
                    m_objectsBox.Add(newBullet);
                }

                ValidateShootFlag(p_player, 200);
            }
        }    
    }

    // manage other objects in the Box
    p_item = m_objectsBox.GetHead();
    while (p_item != 0)
    {
        // move every NPC, make them shoot and animate something if any
        if (p_item->GetCargo()->GetTag() == NPC)
        {
            Tank* p_newNPCTank = (Tank*)(p_item->GetCargo());

            /* Experimental functionality*/    
            // Behave(p_newNPCTank);
            
            if (m_statusBox.Size() != 0)
            {
                m_statusBox.GetElement(p_newNPCTank->GetIndex())->SetLocation(p_newNPCTank->GetDrawingStart().x, p_newNPCTank->GetDrawingStart().y);
            }

            // set random direction every random path length
            if (p_newNPCTank->GetPathLength() == 0)     
            {
                p_newNPCTank->SetDirection(Utils::GetRandomDirection());
                p_newNPCTank->SetPathLength(Utils::GetRandomNumber(1, 20));
            }
            eDirection dir = p_newNPCTank->GetDirection();

            // check if NPC can move
            bool check = IsLegalMove(*p_newNPCTank, dir);     
            if (check)
            {
                p_newNPCTank->Move(dir);

                // check if NPC hits health or armour icon
                GameObject* p_overlayObject = CheckObjectsOverlay(&m_objectsBox, p_newNPCTank);
                if (p_overlayObject != NULL)
                {
                    // check if it is health
                    if (p_overlayObject->GetTag() == HEALTH_ICON)
                    {
                        // set zero status for correspoding status object
                        if (m_statusBox.Size() != 0)
                        {
                            m_statusBox.GetElement(((HealthIcon*)p_overlayObject)->GetIndex())->SetStatus(0);
                            m_statusBox.GetElement(((HealthIcon*)p_overlayObject)->GetIndex())->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                        }

                        // mark health icon object to remove
                        m_objectsBox.MarkToRemove(p_overlayObject);

                        // calculate lifes delta: how many lifes we can add to NPC tank
                        int currentLifes = p_newNPCTank->GetLifesCount();
                        int lifesDelta = p_newNPCTank->GetMaxLifesCount() - currentLifes; 
                        p_newNPCTank->SetLifesCount(p_newNPCTank->GetLifesCount() + lifesDelta);
                    }
                    // else if it is armour
                    else if (p_overlayObject->GetTag() == ARMOUR_ICON)
                    {
                        int64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                        
                        // set zero status for correspoding status object
                        if (m_statusBox.Size() != 0)
                        {
                            m_statusBox.GetElement(((ArmourIcon*)p_overlayObject)->GetIndex())->SetStatus(0);
                            m_statusBox.GetElement(((ArmourIcon*)p_overlayObject)->GetIndex())->SetDeathTime(currentTime);
                        }

                        // mark armour icon object to remove
                        m_objectsBox.MarkToRemove(p_overlayObject);

                        // pick up armour
                        p_newNPCTank->PickUpArmour();
                        m_armourPickUpTime = currentTime;
                        m_armourIsPickedUp = true;
                    }
                }
            }

            // decrease the NPC's path lenght
            p_newNPCTank->DecreasePath();

            // if NPC can shoot
            if (p_newNPCTank->GetShootFlag() == true)
            {
                // then shoot
                p_newNPCTank->SetLastShootTime(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                GameObject* newBullet = new Bullet(BULLET, Utils::COLOR_YELLOW, p_newNPCTank->GetDirection());
                POINT drawingStart = p_newNPCTank->GetShootingPosition(p_newNPCTank->GetDirection());
                newBullet->SetDrawingStart(drawingStart.x, drawingStart.y);
                ((Bullet*)newBullet)->BelongTo(NPC);
                ((Bullet*)newBullet)->SetTankIndex(p_newNPCTank->GetIndex());
                m_objectsBox.Add(newBullet);
            }

            // wait for some time to be able shoot again
            ValidateShootFlag(p_newNPCTank, Utils::GetRandomNumber(500, 2000));

            // animate something if any
            p_newNPCTank->Animate();
        }

        // move every bullet which exists and mark to remove some if required
        if (p_item->GetCargo()->GetTag() == BULLET)
        {
            Bullet* p_currentBullet = (Bullet*)(p_item->GetCargo());
            // if current bullet has zero path or go outside the action rectangle, then mark it to remove
            if (p_currentBullet->GetPathLength() <= 0 || !InsideActionRect(p_currentBullet))
            {
                m_objectsBox.MarkToRemove(p_currentBullet);
            }
            else
            {
                p_currentBullet->Move(p_currentBullet->GetDirection());

                // check if bullet hit someone
                GameObject* p_testedGameObject = CheckObjectsOverlay(&m_objectsBox, p_currentBullet);
                if (p_testedGameObject != NULL)
                {
                    /* ===== if bullet shot by NPC and hit the player ===== */
                    if (p_currentBullet->ShotBy() == NPC && p_testedGameObject->GetTag() == PLAYER)
                    {
                        // then mark player and bullet to remove if lifes count equals 1
                        if (((Tank*)p_testedGameObject)->GetLifesCount() == 0)
                        {
                            // tank is attacked
                            ((Tank*)p_testedGameObject)->TakeLife();
                            m_objectsBox.MarkToRemove(p_currentBullet);

                            // if no armor then kill it
                            if (((Tank*)p_testedGameObject)->HasArmour() == false)
                            {
                                if (m_statusBox.Size() != 0)
                                {
                                    m_statusBox.GetElement(((Tank*)p_testedGameObject)->GetIndex())->SetStatus(0);
                                    m_statusBox.GetElement(((Tank*)p_testedGameObject)->GetIndex())->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                                    m_statusBox.GetElement(p_currentBullet->GetTankIndex())->IncreaseScore(1);
                                }
                                m_objectsBox.MarkToRemove(p_testedGameObject);

                                // create explosion effect
                                ExplosionEffect* p_explosionEffect = new ExplosionEffect(EXPLOSION);
                                p_explosionEffect->SetDrawingStart(p_testedGameObject->GetDrawingStart().x, p_testedGameObject->GetDrawingStart().y);
                                m_objectsBox.Add(p_explosionEffect);
                            }
                        }
                        // otherwise take player's life and mark bullet to remove
                        else
                        {
                            ((Tank*)p_testedGameObject)->TakeLife();
                            m_objectsBox.MarkToRemove(p_currentBullet);
                        }
                    }
                    /* ===== if bullet shot by player or NPC and hit NPC ===== */
                    else if ((p_currentBullet->ShotBy() == PLAYER || p_currentBullet->ShotBy() == NPC) && p_testedGameObject->GetTag() == NPC)
                    {
                        // check that bullet was shoot not from tested game object
                        if (((Tank*)p_testedGameObject)->GetIndex() != p_currentBullet->GetTankIndex())
                        {
                            // then mark NPC and bullet to remove if lifes count equals 1
                            if (((Tank*)p_testedGameObject)->GetLifesCount() == 0)
                            {
                                // tank is attacked
                                ((Tank*)p_testedGameObject)->TakeLife();
                                m_objectsBox.MarkToRemove(p_currentBullet);

                                // if no armor then kill it
                                if (((Tank*)p_testedGameObject)->HasArmour() == false)
                                {
                                    if (m_statusBox.Size() != 0)
                                    {
                                        m_statusBox.GetElement(((Tank*)p_testedGameObject)->GetIndex())->SetStatus(0);
                                        m_statusBox.GetElement(((Tank*)p_testedGameObject)->GetIndex())->SetDeathTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                                        m_statusBox.GetElement(p_currentBullet->GetTankIndex())->IncreaseScore(1);
                                    }
                                    
                                    m_objectsBox.MarkToRemove(p_testedGameObject);
                                    
                                    // create explosion effect
                                    ExplosionEffect* p_explosionEffect = new ExplosionEffect(EXPLOSION);
                                    p_explosionEffect->SetDrawingStart(p_testedGameObject->GetDrawingStart().x, p_testedGameObject->GetDrawingStart().y);
                                    m_objectsBox.Add(p_explosionEffect);
                                }
                            }
                            // otherwise take NPC's life and mark bullet to remove
                            else
                            {
                                ((Tank*)p_testedGameObject)->TakeLife();
                                m_objectsBox.MarkToRemove(p_currentBullet);
                            }
                        }
                    }

                    // if current bullet hit the wall, then change wall color (or mark wall to remove) and mark current bullet to remove
                    if (p_testedGameObject->GetTag() == WALL)
                    {
                        // if wall has last life, then mark it to remove
                        if (((Wall*)p_testedGameObject)->GetLifesCount() == 1)
                        {
                            ((Wall*)p_testedGameObject)->TakeLife();
                            m_objectsBox.MarkToRemove(p_testedGameObject);
                            m_objectsBox.MarkToRemove(p_currentBullet);
                        }
                        // otherwise take wall's life, change it's color and mark current bullet to remove
                        else 
                        {
                            ((Wall*)p_testedGameObject)->TakeLife();
                            ((Wall*)p_testedGameObject)->ChangeColor();
                            m_objectsBox.MarkToRemove(p_currentBullet);
                        }
                    }
                }
            }  
        }

        // animate explosion objects or mark them to remove if needed
        if (p_item->GetCargo()->GetTag() == EXPLOSION)
        {
            ExplosionEffect* p_explosionEffect = (ExplosionEffect*)(p_item->GetCargo());

            if (p_explosionEffect->IsLifeEnded())
            {
                m_objectsBox.MarkToRemove(p_explosionEffect);
            }
            else
            {
                p_explosionEffect->Animate();
            }
        }

        p_item = p_item->GetNext();
    }

    // mark to remove life icons if needed
    if (p_player != 0)
    {
        int iconsCount = 0;
        p_item = m_objectsBox.GetHead();
        while (p_item != 0)
        {
            if (p_item->GetCargo()->GetTag() == LIFE_ICON)
            {
                iconsCount++;
                if (iconsCount > p_player->GetLifesCount())
                {
                    m_objectsBox.MarkToRemove(p_item->GetCargo());
                }
            }
            p_item = p_item->GetNext();
        }
    }

    // remove objects that were marked to remove
    m_objectsBox.Cleanup();

    // respawn objects if needed
    BoxItem<TankStatusVO>* p_tankStatusItem;
    p_tankStatusItem = m_statusBox.GetHead();
    while (p_tankStatusItem != 0)
    {
        if (p_tankStatusItem->GetCargo()->GetStatus() == 0)
        {
            switch (p_tankStatusItem->GetCargo()->GetTag())
            {
                case PLAYER: { SpawnGameObject(PLAYER, p_tankStatusItem->GetIndex(), 4); break; }
                case NPC: { SpawnGameObject(NPC, p_tankStatusItem->GetIndex(), 6); break; }
                case HEALTH_ICON: { SpawnGameObject(HEALTH_ICON, p_tankStatusItem->GetIndex(), 5); break; }
                case ARMOUR_ICON: { SpawnGameObject(ARMOUR_ICON, p_tankStatusItem->GetIndex(), 5 + Tank::ARMOUR_DURATION_TIME); break; }
            }
            
        }
        p_tankStatusItem = p_tankStatusItem->GetNext();
    }

    
    ClearOutputStrings();
    OutputTimerInfo();
    UpdateScoreInfo();
    OutputArmourInfo();
    CheckIfGameRoundEnded();
    // SetGameObjectsInfoOutput(&m_objectsBox);

    // restart game round if it was ended and R button is pressed
    if (isKeyPressed)
    {
        if (key == KEYBOARD_R && endGameRound == true)
        {
            RestartGameRound();
        }
    }
}

/* ==== Test data for optimal routes. Should be deleted ==== */
// void Game::DrawLine(int startX, int startY, int endX, int endY, uint32_t lineColor)
// {
//       int lengthX = abs(endX - startX);
//       int lengthY = abs(endY - startY);

//       uint8_t* p_row;
//       uint32_t* p_pixel;

//        // draw start line point
//       p_row = (uint8_t*)m_p_bitmapMemory;
//       p_pixel = (uint32_t*)p_row;
//       p_pixel += startY * PMATRIX_WIDTH + startX;
//       *p_pixel = lineColor;   

//       if (lengthX > lengthY)
//       {
//             /* find coords for each X */
            
//             int trueStartX = startX;
//             int trueEndX = endX;
//             if (startX > endX)
//             {
//                   trueStartX = endX;
//                   trueEndX = startX;
//             }
                                                           
//             for (int x = trueStartX + 1; x < trueEndX; ++x)
//             {
//                   int y = startY + (x - startX) * (endY - startY) / (endX - startX);

//                   // draw line point
//                   p_row = (uint8_t*)m_p_bitmapMemory;
//                   p_pixel = (uint32_t*)p_row;
//                   p_pixel += y * PMATRIX_WIDTH + x;
//                   *p_pixel = lineColor; 
//             }     
//       }
//       else
//       {
//             /* find coords for each Y */

//             int trueStartY = startY;
//             int trueEndY = endY;
//             if (startY > endY)
//             {
//                   trueStartY = endY;
//                   trueEndY = startY;
//             }

//             for (int y = trueStartY + 1; y < trueEndY; ++y)
//             {
//                   int x = startX + (endX - startX) * (y - startY) / (endY - startY);

//                   // draw line point
//                   p_row = (uint8_t*)m_p_bitmapMemory;
//                   p_pixel = (uint32_t*)p_row;
//                   p_pixel += y * PMATRIX_WIDTH + x;
//                   *p_pixel = lineColor; 
//             }
//       }

//       // draw end line point
//       p_row = (uint8_t*)m_p_bitmapMemory;
//       p_pixel = (uint32_t*)p_row;
//       p_pixel += endY * PMATRIX_WIDTH + endX;
//       *p_pixel = lineColor; 
// }
/* =============================== */

void Game::Draw()
{
    ResetMainDigitalMatrix();

    // fill the pixel matrix with data of all objects in the objects box (add small matrix of all objects into global matrix)
    BoxItem<GameObject>* p_item = m_objectsBox.GetHead();
    while (p_item != 0)
    {
        // set object start position in pixel matrix
        int pixMatStartX = p_item->GetCargo()->GetDrawingStart().x;
        int pixMatStartY = p_item->GetCargo()->GetDrawingStart().y;
        int object_y = 0;
        for (int y = pixMatStartY; y < p_item->GetCargo()->GetPatternHeight() + pixMatStartY; ++y)
        {
            int object_x = 0;
            for (int x = pixMatStartX; x < p_item->GetCargo()->GetPatternWidth() + pixMatStartX; ++x)
            {
                mainDigitalMatrix[y * PMATRIX_WIDTH + x] = (p_item->GetCargo()->GetCurrentPattern())[object_y * p_item->GetCargo()->GetPatternWidth() + object_x];
                object_x++;
            }
            object_y++;
        }

        p_item = p_item->GetNext();
    }


    // // cout mainDigitalMatrix
    // system("cls");
    // for (int i = 0; i < PMATRIX_SIZE; ++i)
    // {
    //     for (int j = 0; j < PMATRIX_SIZE; ++j)
    //     {
    //         cout << mainDigitalMatrix[i * PMATRIX_SIZE + j];
    //     }
    //     cout << endl;
    // }

    // /*==Digit output==*/ 
    // for (int y = 0; y < PMATRIX_SIZE; ++y)
    // {
    //     std::stringstream ss;
    //     std::string line;
    //     for (int x = 0; x < PMATRIX_SIZE; ++x)
    //     {
    //         ss << mainDigitalMatrix[y * PMATRIX_SIZE + x];            
    //     }
    //     line = ss.str();
    //     WriteConsoleOutputCharacter(hConsole, line.c_str(), PMATRIX_SIZE, {0,static_cast<SHORT>(y + 0)}, &dwBytesWritten);
    // }
    // /*================*/
    
    // if game ended then clear pixel matrix before exit
    if (endGame)
    {
        ClearMainDigitalMatrix();
    }

    // set pixel map variables
    int colorIndex;
    COLORREF color;
    int pitch;
    uint8_t* p_row;

    // arrange pixels for game field
    pitch = PMATRIX_WIDTH * BYTES_PER_PIXEL;     // row size in bytes
    p_row = (uint8_t*)m_p_bitmapMemory;         //cast to uint8 for valid pointer arithmetic (to add by 1 byte (8 bits) at a time)    
    for (int y = 0; y < PMATRIX_HEIGHT; ++y)
    {
        uint32_t* p_pixel = (uint32_t*)p_row;
        for (int x = 0; x < PMATRIX_WIDTH; ++x)
        {
            colorIndex = mainDigitalMatrix[y * PMATRIX_WIDTH + x];
            color = Utils::GetColor(colorIndex);
            uint8_t blue = GetBValue(color);
            uint8_t green = GetGValue(color);
            uint8_t red = GetRValue(color);
            uint8_t pixelPadding = 0;

            *p_pixel = ((pixelPadding << 24) | (red << 16) | (green << 8) | blue);
            ++p_pixel;
        }
        p_row += pitch;
    }

    /* ==== Test data for optimal routes. Should be deleted ==== */
    // // fill the memory matrix with nodeVO objects
    // for (int y = 0; y < NODES_HEIGHT; ++y)
    // {
    //     for (int x = 0; x < NODES_WIDTH; ++x)
    //     {
    //         NodeVO* p_checkNode = m_nodesArray[y * NODES_WIDTH + x];
            
    //         int rect_x = p_checkNode->GetNodeCoordX();
    //         int rect_y = p_checkNode->GetNodeCoordY();
    //         int rect_width = 2;
    //         int rect_height = 2;
    //         uint32_t rect_color = p_checkNode->GetColor();

    //         p_row = (uint8_t*)m_p_bitmapMemory; 
    //         p_row += (pitch * rect_y);
    //         for (int i = rect_y; i < rect_height + rect_y; ++i)
    //         {
    //             uint32_t* p_pixel = (uint32_t*)p_row;
    //             p_pixel += rect_x;
    //             for (int j = rect_x; j < rect_width + rect_x; ++j)
    //             {	
    //                 *p_pixel = rect_color;
    //                 ++p_pixel;
    //             }
    //             p_row += pitch;
    //         }
    //     }
    // } 

    // // draw lines for connected nodes
    // for (uint16_t i = 0; i < NODES_NUMBER; ++i)
    // {
    //     for (uint16_t j = 0; j < NODES_NUMBER; ++j)
    //     {   
    //         if (m_nodesAdjacencyMatrix[i * NODES_NUMBER + j] == 1)
    //         {
    //             NodeVO* p_i_Node = m_nodesArray[i];
    //             NodeVO* p_j_Node = m_nodesArray[j];
    //             uint16_t node_i_x = p_i_Node->GetNodeCoordX();
    //             uint16_t node_i_y = p_i_Node->GetNodeCoordY();
    //             uint16_t node_j_x = p_j_Node->GetNodeCoordX();
    //             uint16_t node_j_y = p_j_Node->GetNodeCoordY();
    //             DrawLine(node_i_x, node_i_y, node_j_x, node_j_y, 0x00ffffff);
    //         }
    //     }
    // }
    /* ==== Test data. End ==== */

    
    // draw to the screen
    deviceContext = GetDC(*m_p_consoleWindow);

    HFONT hFont; 
    SetTextColor(deviceContext, Utils::COLOR_BLACK);
    SetBkColor(deviceContext, Utils::COLOR_DARKGREY);
    
    // screen output for game field
    StretchDIBits(
                deviceContext,
                OFFSET_LEFT, OFFSET_TOP,
                PMATRIX_WIDTH, PMATRIX_HEIGHT,
                0, 0,
                PMATRIX_WIDTH, PMATRIX_HEIGHT,
                m_p_bitmapMemory, &bitmapInfo,
                DIB_RGB_COLORS,
                SRCCOPY
                );

    // create custorm font for time and score strings
    hFont = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);
    SelectObject(deviceContext, hFont); 
    TextOut(deviceContext, 290, 55, GetTimeString().c_str(), GetTimeString().size());
    TextOut(deviceContext, 290, 70, GetScoreString().c_str(), GetScoreString().size());
    DeleteObject(hFont);

    // create custom font for armour info
    hFont = CreateFont(40,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
    SelectObject(deviceContext, hFont);
    TextOut(deviceContext, 130, 50, GetArmourInfoString().c_str(), GetArmourInfoString().size());
    DeleteObject(hFont);

    // create custom font for score table
    hFont = CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
    SelectObject(deviceContext, hFont);

    // score info output into the table
    int coordY = 110;
    if (endGameRound)
    {
        for (int i = 0; i < m_statusBox.Size(); ++i)
        {
            eTag tag = m_statusBox.GetElement(i)->GetTag(); 
            if (tag != HEALTH_ICON && tag != ARMOUR_ICON)
            {
                std::string info = m_statusBox.GetElement(i)->GetStatusInfo(i);
                TextOut(deviceContext, 70, coordY, info.c_str(), info.size());
                coordY += 20; 
            }
        }

        // restart info
        TextOut(deviceContext, 100, coordY += 3, TEXT(" Press 'R' to restart the game.  "), strlen(" Press 'R' to restart the game.  "));
        TextOut(deviceContext, 100, coordY += 20, TEXT(" Press 'ESC' to go to the menu. "), strlen(" Press 'ESC' to go to the menu. "));
    }
    DeleteObject(hFont);

    // hFont = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);
    // SelectObject(deviceContext, hFont); 
    // TextOut(deviceContext, 20, 40, GetOutputString1().c_str(), GetOutputString1().size());

    
    ReleaseDC(*m_p_consoleWindow, deviceContext);

}

void Game::CheckGameEnd(bool* game)
{
    if (endGame)
    {
        *game = false;
        Draw();
    }
}

void Game::OutputTimerInfo()
{
    int64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    if (currentTime > m_previousTimeSnapshot && m_timerSeconds != 0)
    {
        if (m_currentSeconds == 0)
        {
            m_timerMinutes--;
            m_currentSeconds = 59;
        }
        else
        {
            m_currentSeconds--;
        }

        m_timerSeconds--;
    }

    if (m_timerSeconds <= 0)
    {
        endGameRound = true;
        m_timerSeconds = 0;
    }

    m_previousTimeSnapshot = currentTime;

    std::stringstream ss;
    // std::stringstream minutesStream;
    // std::stringstream secondsStream;

    ss << "TIME: ";

    if (m_timerMinutes < 10)
    {
        ss << "0" << m_timerMinutes;
    }
    else
    {
        ss << m_timerMinutes;
    }

    ss << ":";

    if (m_currentSeconds < 10)
    {
        ss << "0" << m_currentSeconds;
    }
    else
    {
        ss << m_currentSeconds;
    }
    
    m_timerString = ss.str();
}

void Game::UpdateScoreInfo()
{
    std::stringstream ss;
    ss << "SCORE: ";
    if (m_statusBox.Size() != 0)
    {
        ss << m_statusBox.GetElement(0)->GetScore();
    }
    
    m_scoreString = ss.str();
}

void Game::OutputArmourInfo()
{
    std::stringstream ss;

    if (m_armourIsPickedUp)
    {
        int64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int64_t delta = currentTime - m_armourPickUpTime;
        int seconds = Tank::ARMOUR_DURATION_TIME - (int)delta;
        ss << "ARMOUR: " << seconds;

        if (seconds <= 0)
        {
            m_armourIsPickedUp = false;
        }
    }
    else
    {
        ss << "      ";
    }
    
    m_armourString = ss.str();
}

void Game::SetScoreString0(POINT p1, POINT p2, POINT p3, POINT p4)
{
    std::stringstream ss;
    ss << p1.x << " " << p1.y << " " << p2.x << " " << p2.y;
    ss << " " << p3.x << " " << p3.y << " " << p4.x << " " << p4.y;
    m_outputString0 = ss.str();
}

void Game::SetScoreString1(POINT p1, POINT p2, POINT p3, POINT p4)
{
    std::stringstream ss;
    ss << p1.x << " " << p1.y << " " << p2.x << " " << p2.y;
    ss << " " << p3.x << " " << p3.y << " " << p4.x << " " << p4.y;
    m_outputString1 = ss.str();
}

void Game::SetGameObjectsInfoOutput(Box<GameObject>* list)
{
    std::stringstream ss;

    BoxItem<GameObject>* p_item = list->GetHead();
    while (p_item != 0)
    {
        if (p_item->GetCargo()->GetTag() == BULLET)
        {
            Bullet* newBullet = (Bullet*)(p_item->GetCargo());
            ss << newBullet->GetPathLength() << "  ";
        }
        p_item = p_item->GetNext();
    }

    ss << "ItemsCount: " << list->Size() << "                        ";

    // ss << "StartX: " << p1.x << " StartY: " << p1.y << " EndX: " << p2.x << " EndY: " << p2.y << " | ";
    // ss << " StX: " << p3.x << " StY: " << p3.y << " EndX: " << p4.x << " EndY: " << p4.y << " "; 
    m_outputString0 = ss.str();
}

void Game::ClearOutputStrings()
{
    std::stringstream ss;
    ss << "                                     ";
    m_timerString = ss.str();
    m_outputString0 = ss.str();
    m_outputString1 = ss.str();
}

std::string Game::GetTimeString()
{
    return m_timerString;
}

std::string Game::GetScoreString()
{
    return m_scoreString;
}

std::string Game::GetArmourInfoString()
{
    return m_armourString;
}

std::string Game::GetOutputString0()
{
    return m_outputString0;
}

std::string Game::GetOutputString1()
{
    return m_outputString1;
}