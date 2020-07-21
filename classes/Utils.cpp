// Utils class implementation for Crazy Tanks utility objects and functions

#include <Utils.h>

std::mt19937 Utils::m_randomGenerator = std::mt19937{};
bool Utils::seeded = false;

std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT>
Utils::m_tankPatternArray = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                             1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};

std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT>
Utils::m_tankArmouredPatternArray = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,2,0,0,0,0,0,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,2,0,0,0,0,0,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,2,0,0,0,0,0,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,2,0,0,0,0,0,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,0,0,0,0,0,2,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,0,0,0,0,0,2,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,0,0,0,0,0,2,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,0,0,0,0,0,2,1,1,1,1,
                                     1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                                     1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};

std::array<int, Utils::BULLET_PATTERN_WIDTH * Utils::BULLET_PATTERN_HEIGHT>
Utils::m_bulletPatternArray = {1,1,1,1,
                               1,1,1,1,
                               1,1,1,1,
                               1,1,1,1};

std::array<int, Utils::ICON_PATTERN_WIDTH * Utils::ICON_PATTERN_HEIGHT> 
Utils::m_iconPatternArray = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0, 
                             0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0, 
                             0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0, 
                             0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                             0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
                             0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0};

std::array<int, Utils::BRICK_PATTERN_WIDTH * Utils::BRICK_PATTERN_HEIGHT>
Utils::m_brickPatternArray = {1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,0,0,0,0,0,0,1,1,
                              1,1,0,0,0,0,0,0,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,0,0,0,0,0,0,1,1,
                              1,1,0,0,0,0,0,0,1,1,
                              1,1,1,1,1,1,1,1,1,1,
                              1,1,1,1,1,1,1,1,1,1};

std::array<int, Utils::HEALTH_PATTERN_WIDTH * Utils::HEALTH_PATTERN_HEIGHT>
Utils::m_healthPatternArray = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
                               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

std::array<int, Utils::ARMOUR_PATTERN_WIDTH * Utils::ARMOUR_PATTERN_HEIGHT>
Utils::m_armourPatternArray = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
                               0,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,1,1,0,
                               0,0,0,1,1,2,2,2,2,2,3,3,3,3,3,1,1,0,0,0,
                               0,0,0,0,0,1,1,2,2,2,3,3,3,1,1,0,0,0,0,0,
                               0,0,0,0,0,0,0,1,1,2,3,1,1,0,0,0,0,0,0,0,
                               0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0};

COLORREF Utils::GetColor(int colorIndex)
{
    COLORREF color;
    switch (colorIndex)
    {
        case 4: color = COLOR_BLACK; break;        
        case 5: color = COLOR_GAINSBORO; break;  
        case 6: color = COLOR_RED; break;      
        case 7: color = COLOR_GREEN; break;      
        case 8: color = COLOR_BLUE; break;   
        case 9: color = COLOR_YELLOW; break; 
        case 10: color = COLOR_DARKGREY; break;
        case 11: color = COLOR_DIMGREY; break;
        case 12: color =  COLOR_DARKSLATEGREY; break;
        case 13: color =  COLOR_ORANGE; break;
        case 14: color =  COLOR_WHITE; break;
        default: color = COLOR_WHITE;        
    }

    return color;
}

int Utils::GetColorIndex(COLORREF color)
{
    if (color == COLOR_BLACK)
    {
        return 4;
    }
    if (color == COLOR_GAINSBORO)
    {
        return 5;
    }
    if (color == COLOR_RED)
    {
        return 6;
    }
    if (color == COLOR_GREEN)
    {
        return 7;
    }
    if (color == COLOR_BLUE)
    {
        return 8;
    }
    if (color == COLOR_YELLOW)
    {
        return 9;
    }
    if (color == COLOR_DARKGREY)
    {
        return 10;
    }
    if (color == COLOR_DIMGREY)
    {
        return 11;
    }
    if (color == COLOR_DARKSLATEGREY)
    {
        return 12;
    }
    if (color == COLOR_ORANGE)
    {
        return 13;
    }
    if (color == COLOR_WHITE)
    {
        return 14;
    }
    return 14;
}

bool Utils::GetRandomFlag()
{
    bool randomFlag = false;

    if (!seeded)
    {
        m_randomGenerator.seed(static_cast<unsigned int>(time(0)));
        seeded = true;
    }

    std::uniform_int_distribution<uint32_t> range(0, 1);
    int randomCheck = range(m_randomGenerator);
    if (randomCheck == 0)
    {
        randomFlag = false;
    }
    else
    {
        randomFlag = true;
    }

    return randomFlag;
}

int Utils::GetRandomNumber(int min, int max)
{
    if (!seeded)
    {
        m_randomGenerator.seed(static_cast<unsigned int>(time(0)));
        seeded = true;
    }

    std::uniform_int_distribution<uint32_t> range(min, max);
    return range(m_randomGenerator);
}

int Utils::GetRandomRoundedNumber(int min, int max)
{
    if (!seeded)
    {
        m_randomGenerator.seed(static_cast<unsigned int>(time(0)));
        seeded = true;
    }

    std::uniform_int_distribution<uint32_t> range(min, max);
    int randomRoundedNumber;
    randomRoundedNumber = range(m_randomGenerator);
    randomRoundedNumber = randomRoundedNumber + (10 - (randomRoundedNumber % 10));
    return randomRoundedNumber;
}

eDirection Utils::GetRandomDirection()
{
    if (!seeded)
    {
        m_randomGenerator.seed(static_cast<unsigned int>(time(0)));
        seeded = true;
    }

    eDirection dir = STOP;
    std::uniform_int_distribution<uint32_t> range(0, 3);
    uint32_t randomNumber = range(m_randomGenerator);

    switch (randomNumber)
    {
        case 0: {dir = UP; break;}
        case 1: {dir = DOWN; break;}
        case 2: {dir = RIGHT; break;}
        case 3: {dir = LEFT; break;}
    }

    return dir;
}

std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT> Utils::GetTankPattern(COLORREF color)
{
    std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT> tempArray = m_tankPatternArray;
    for (unsigned int i = 0; i < tempArray.size(); ++i)
    {
        if (m_tankPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(color);
        }
        else if (m_tankPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
    }
    return tempArray;
}

std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT> Utils::GetTankArmouredPattern(COLORREF color)
{
    std::array<int, Utils::TANK_PATTERN_WIDTH * Utils::TANK_PATTERN_HEIGHT> tempArray = m_tankArmouredPatternArray;
    for (unsigned int i = 0; i < tempArray.size(); ++i)
    {
        if (m_tankArmouredPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(color);
        }
        else if (m_tankArmouredPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
        else if (m_tankArmouredPatternArray[i] == 2)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_ORANGE);
        }
    }
    return tempArray;
}

std::array<int, Utils::BULLET_PATTERN_WIDTH * Utils::BULLET_PATTERN_HEIGHT> Utils::GetBulletPattern(COLORREF color)
{
    std::array<int, Utils::BULLET_PATTERN_WIDTH * Utils::BULLET_PATTERN_HEIGHT> tempArray = m_bulletPatternArray;
    for (unsigned int i = 0; i < m_bulletPatternArray.size(); ++i)
    {
        if (m_bulletPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(color);
        }
        else if (m_bulletPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
    }
    return tempArray;
}

std::array<int, Utils::ICON_PATTERN_WIDTH * Utils::ICON_PATTERN_HEIGHT> Utils::GetIconPattern(COLORREF color)
{
    std::array<int, Utils::ICON_PATTERN_WIDTH * Utils::ICON_PATTERN_HEIGHT> tempArray = m_iconPatternArray;
    for (unsigned int i = 0; i < m_iconPatternArray.size(); ++i)
    {
        if (m_iconPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(color);
        }
        else if (m_iconPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_DARKGREY);
        }
    } 
    return tempArray;
}

std::array<int, Utils::BRICK_PATTERN_WIDTH * Utils::BRICK_PATTERN_HEIGHT> Utils::GetBrickPattern(COLORREF color)
{
    std::array<int, Utils::BRICK_PATTERN_WIDTH * Utils::BRICK_PATTERN_HEIGHT> tempArray = m_brickPatternArray;
    for (unsigned int i = 0; i < m_brickPatternArray.size(); ++i)
    {
        if (m_brickPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(color);
        }
        else if (m_brickPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
    }
    return tempArray;
}

std::array<int, Utils::HEALTH_PATTERN_WIDTH * Utils::HEALTH_PATTERN_HEIGHT> Utils::GetHealthPattern()
{
    std::array<int, Utils::HEALTH_PATTERN_WIDTH * Utils::HEALTH_PATTERN_HEIGHT> tempArray = m_healthPatternArray;
    for (unsigned int i = 0; i < m_healthPatternArray.size(); ++i)
    {
        if (m_healthPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_GREEN);
        }
        else if (m_healthPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_WHITE);
        }
    } 
    return tempArray;
}

std::array<int, Utils::ARMOUR_PATTERN_WIDTH * Utils::ARMOUR_PATTERN_HEIGHT> Utils::GetArmourPattern()
{
    std::array<int, Utils::ARMOUR_PATTERN_WIDTH * Utils::ARMOUR_PATTERN_HEIGHT> tempArray = m_armourPatternArray;
    for (unsigned int i = 0; i < m_armourPatternArray.size(); ++i)
    {
        if (m_armourPatternArray[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_ORANGE);
        }
        else if (m_armourPatternArray[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
        else if (m_armourPatternArray[i] == 2)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_ORANGE);
        }
        else if (m_armourPatternArray[i] == 3)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
    } 
    return tempArray;
}

