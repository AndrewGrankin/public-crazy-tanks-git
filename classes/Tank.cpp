// Class to hold Tank objects

#include <Tank.h>

Tank::~Tank()
{}

Tank::Tank(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    m_index = -1;
    m_tempColor = color;
    m_currentDirection = UP;
    m_pathLength = 0;
    m_isAttacked = false;
    m_hasArmour = false;

    m_isXAxisDirection = false;
    m_p_enemyObject = NULL;

    SetBasePattern();
    SetCurrentPattern();
}

Tank::Tank(const Tank& aTank)       // copy constructor to make a deep copy because of pointer members
{
    m_tag = aTank.m_tag;
    m_id = aTank.m_id;
    m_color = aTank.m_color;
    m_patternWidth = aTank.m_patternWidth;
    m_patternHeight = aTank.m_patternHeight;
    m_drawingStart = aTank.m_drawingStart;
    m_drawingEnd = aTank.m_drawingEnd;
    m_index = aTank.m_index;
    m_tempColor = aTank.m_tempColor;
    m_currentDirection = aTank.m_currentDirection;
    m_lastShootTime = aTank.m_lastShootTime;
    m_shootFlag = aTank.m_shootFlag;
    m_pathLength = aTank.m_pathLength;
    m_lifes = aTank.m_lifes;
    m_maxLifes = aTank.m_maxLifes;
    m_isAttacked = aTank.m_isAttacked;
    m_framesCount = aTank.m_framesCount;
    m_hasArmour = aTank.m_hasArmour;

    m_isXAxisDirection = aTank.m_isXAxisDirection;
    m_p_enemyObject = aTank.m_p_enemyObject;    // we don't need to create a new enemyObject, just copy it's adress

    m_p_boxCollider = new RECT();
    m_p_boxCollider->left = aTank.m_p_boxCollider->left;
    m_p_boxCollider->top = aTank.m_p_boxCollider->top;
    m_p_boxCollider->right = aTank.m_p_boxCollider->right;
    m_p_boxCollider->bottom = aTank.m_p_boxCollider->bottom;
    
    m_p_basePattern = new int[m_patternWidth * m_patternHeight];
    m_p_currentPattern = new int[m_patternWidth * m_patternHeight];

    for (int i = 0; i < m_patternWidth * m_patternHeight; ++i)
    {
        m_p_basePattern[i] = aTank.m_p_basePattern[i];
        m_p_currentPattern[i] = aTank.m_p_currentPattern[i];
    }
}

void Tank::SetBasePattern() const
{
    std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT> tempArray;

    if (m_hasArmour)
    {
        tempArray = Utils::GetTankArmouredPattern(m_tempColor);
    }
    else
    {
        tempArray = Utils::GetTankPattern(m_tempColor);
    }

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void Tank::SetCurrentPattern() const
{
    switch (m_currentDirection)
    {
        case UP:
        {
            for (int y = 0; y < m_patternHeight; ++y)
            {
                for (int x = 0; x < m_patternWidth; ++x)
                {
                    m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
                }
            }
            break;
        }
        case DOWN:
        {
            for (int y = 0; y < m_patternHeight; ++y)
            {
                for (int x = 0; x < m_patternWidth; ++x)
                {
                    m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[((m_patternHeight - 1) - y) * m_patternWidth + x];
                }
            }
            break;
        }
        case LEFT:
        {
            int basePatternWidth = Utils::TANK_PATTERN_WIDTH;
            int basePatternHeigth = Utils::TANK_PATTERN_HEIGHT;
            for (int y = 0; y < m_patternHeight; ++y)
            {
                for (int x = 0; x < m_patternWidth; ++x)
                {
                    m_p_currentPattern[((m_patternHeight - 1) - y) * m_patternWidth + ((m_patternWidth - 1) - x)] = m_p_basePattern[((basePatternHeigth - 1) - x) * basePatternWidth + y];
                }
            }
            break;
        }
        case RIGHT:
        {
            int basePatternWidth = Utils::TANK_PATTERN_WIDTH;
            int basePatternHeigth = Utils::TANK_PATTERN_HEIGHT;
            for (int y = 0; y < m_patternHeight; ++y)
            {
                for (int x = 0; x < m_patternWidth; ++x)
                {
                    m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[((basePatternHeigth - 1) - x) * basePatternWidth + y];
                }
            }
            break;
        }
    }
}

int* Tank::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void Tank::SetIndex(int index)
{
    m_index = index;
}

int Tank::GetIndex()
{
    return m_index;
}

void Tank::Move(eDirection direction, int step)
{
    if (m_currentDirection == direction)
    {
        switch (direction)
        {
            case UP: SetDrawingStart(GetDrawingStart().x, GetDrawingStart().y - step); break;
            case DOWN: SetDrawingStart(GetDrawingStart().x, GetDrawingStart().y + step); break;
            case LEFT: SetDrawingStart(GetDrawingStart().x - step, GetDrawingStart().y); break;
            case RIGHT: SetDrawingStart(GetDrawingStart().x + step, GetDrawingStart().y); break;
        }
    }
    else
    {
        SetDirection(direction);
    }
}

POINT Tank::GetShootingPosition(eDirection direction)
{
    POINT shootingPosition;

    switch (direction)
    {
        case UP:
        {
            shootingPosition.x = GetDrawingStart().x + m_patternWidth / 2 - 2;
            shootingPosition.y = GetDrawingStart().y;    
            break;
        } 
        case DOWN:
        {
            shootingPosition.x = GetDrawingStart().x + m_patternWidth / 2 - 2;
            shootingPosition.y = GetDrawingEnd().y - Utils::BULLET_PATTERN_HEIGHT;         
            break;
        }
        case LEFT:
        {
            shootingPosition.x = GetDrawingStart().x;  
            shootingPosition.y = GetDrawingStart().y + m_patternHeight / 2 - 2;
            break;
        }
        case RIGHT:
        {
            shootingPosition.x = GetDrawingEnd().x - Utils::BULLET_PATTERN_WIDTH;
            shootingPosition.y = GetDrawingEnd().y - m_patternHeight / 2 - 2;
            break;
        }
    }

    return shootingPosition;
}

void Tank::SetDirection(eDirection direction)
{
    if (m_currentDirection == LEFT || m_currentDirection == RIGHT)
    {
        if (direction == UP || direction == DOWN)
        {
            SwapDimensions();
        }
    }
    else
    {
        if (direction == LEFT || direction == RIGHT)
        {
            SwapDimensions();
        }
    }

    m_currentDirection = direction;
    SetCurrentPattern();    
}

eDirection Tank::GetDirection()
{
    return m_currentDirection;
}

void Tank::SetLastShootTime(int64_t time)
{
    m_lastShootTime = time;
}

void Tank::SetShootFlag(bool flag)
{
    m_shootFlag = flag;
}

int64_t Tank::GetLastShootTime()
{
    return m_lastShootTime;
}

bool Tank::GetShootFlag()
{
    return m_shootFlag;
}

void Tank::SetPathLength(int length)
{
    m_pathLength = length;
}

int Tank::GetPathLength()
{
    return m_pathLength;
}

void Tank::DecreasePath()
{
    if (m_pathLength > 0)
    {
        m_pathLength -= 1;
    }
    else
    {
        m_pathLength = 0;
    }
}

void Tank::SetLifesCount(int lifes)
{
    m_lifes = lifes;
    m_maxLifes = m_lifes;
}

int Tank::GetLifesCount()
{
    return m_lifes;
}

int Tank::GetMaxLifesCount()
{
    return m_maxLifes;
}

void Tank::TakeLife()
{
    m_isAttacked = true;

    if (m_hasArmour == false)
    {
        if (m_lifes > 0)
        {
            m_lifes -= 1;
        }
        else
        {
            m_lifes = 0;
        }
    }
}

void Tank::PickUpArmour()
{
    m_hasArmour = true;
    m_armourPickUpTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    SetBasePattern();
    SetCurrentPattern();
}

bool Tank::HasArmour()
{
    return m_hasArmour;
}

bool Tank::IsXAxisDirection()
{
    return m_isXAxisDirection;
}

void Tank::SetXAxisDirection(bool flag)
{
    m_isXAxisDirection = flag;
}

void Tank::SetEnemyObject(Box<TankStatusVO>* status_list)
{
    TankStatusVO* returnObject = NULL;
    Box<int> activeIndexes;

    // find active objects (status = 1) and store their indexes aside
    BoxItem<TankStatusVO>* p_item = status_list->GetHead();
    while (p_item != 0)
    {
        if (p_item->GetIndex() != m_index)
        {
            if ((p_item->GetCargo()->GetTag() == PLAYER || p_item->GetCargo()->GetTag() == NPC) && 
                 p_item->GetCargo()->GetStatus() == 1)
            {
                int* tempIndex = new int(0);
                *tempIndex = p_item->GetIndex();
                activeIndexes.Add(tempIndex);
            }
        }
        p_item = p_item->GetNext();
    }

    // check for active objects in the box and if there any, pick some random one
    if (activeIndexes.Size() != 0)
    {
        int randomNumber = Utils::GetRandomNumber(0, activeIndexes.Size() - 1);
        int* p_randomIndex = activeIndexes.GetElement(randomNumber);
        returnObject = status_list->GetElement(*p_randomIndex);
    }
    
    m_p_enemyObject = returnObject;
}

TankStatusVO* Tank::GetEnemyObject()
{
    return m_p_enemyObject;
}

void Tank::Animate()
{
    if (m_isAttacked)
    {
        switch (m_framesCount)
        {
            case 3:
            {
                --m_framesCount;
                m_tempColor = Utils::COLOR_ORANGE;
                SetBasePattern();
                SetCurrentPattern();
                break;
            }
            case 2:
            {
                --m_framesCount;
                m_tempColor = m_color;
                SetBasePattern();
                SetCurrentPattern();
                break;
            }
            case 1:
            {
                --m_framesCount;
                m_tempColor = Utils::COLOR_ORANGE;
                SetBasePattern();
                SetCurrentPattern();
                break;
            }
            case 0:
            {   
                m_isAttacked = false;
                m_framesCount = 3;
                m_tempColor = m_color;
                SetBasePattern();
                SetCurrentPattern();
                break;
            }
        }
    }

    if (m_hasArmour)
    {
        int64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        if (currentTime - m_armourPickUpTime >= ARMOUR_DURATION_TIME)
        {
            m_hasArmour = false;
            SetBasePattern();
            SetCurrentPattern();
        }
    }
}
