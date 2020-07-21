// Class to hold Wall objects

#include <Wall.h>

Wall::Wall()
{}

Wall::~Wall()
{
    delete m_p_firstBrick;
    delete m_p_secondBrick;
}

Wall::Wall(eTag tag, Brick* firstBrick, Brick* secondBrick, eDirection direction)
{
    m_tag = tag;
    m_color = 0;
    m_lifes = 15;
    m_direction = direction;

    if (m_direction == LEFT || m_direction == RIGHT)
    {
        m_patternWidth = firstBrick->GetPatternWidth() + secondBrick->GetPatternWidth();
        m_patternHeight = firstBrick->GetPatternHeight();
    }
    else
    {
        m_patternWidth = firstBrick->GetPatternWidth();
        m_patternHeight = firstBrick->GetPatternHeight() + secondBrick->GetPatternHeight();
    }
    
    m_p_basePattern = new int[m_patternWidth * m_patternHeight];
    m_p_currentPattern = new int[m_patternWidth * m_patternHeight];
    m_p_boxCollider = new RECT();

    m_p_firstBrick = firstBrick;
    m_p_secondBrick = secondBrick;

    SetBasePattern();
    SetCurrentPattern();
}

void Wall::SetBasePattern() const
{
    GameObject* p_firstBrickGO = (GameObject*)m_p_firstBrick;
    GameObject* p_secondBrickGO = (GameObject*)m_p_secondBrick;

    // if direction is horizontal
    if (m_direction == LEFT || m_direction == RIGHT)
    {
        // then setup bricks in a row
        for (int y = 0; y < m_patternHeight; ++y)
        {
            for (int x = 0; x < m_patternWidth; ++x)
            {
                // dealing with the first brick in the wall
                if (x < p_firstBrickGO->GetPatternWidth())
                {
                    m_p_basePattern[y * m_patternWidth + x] = (m_p_firstBrick->GetCurrentPattern())[y * p_firstBrickGO->GetPatternWidth() + x];
                }
                // dealing with second brick in the wall
                else
                {
                    m_p_basePattern[y * m_patternWidth + x] = (m_p_secondBrick->GetCurrentPattern())[y * p_secondBrickGO->GetPatternWidth() + (x - p_secondBrickGO->GetPatternWidth())];
                }
            }
        }
    }
    // else direction is vertical
    else
    {
        // then setup bricks in a column
         for (int y = 0; y < m_patternHeight; ++y)
        {
            for (int x = 0; x < m_patternWidth; ++x)
            {
                // dealing with the first brick in the wall
                if (y < p_firstBrickGO->GetPatternHeight())
                {
                    m_p_basePattern[y * m_patternWidth + x] = (m_p_firstBrick->GetCurrentPattern())[y * p_firstBrickGO->GetPatternWidth() + x];
                }
                // dealing with the second brick in the wall
                else
                {
                    m_p_basePattern[y * m_patternWidth + x] = (m_p_secondBrick->GetCurrentPattern())[(y - p_secondBrickGO->GetPatternHeight()) * p_secondBrickGO->GetPatternWidth() + x];
                }
            }
        }  
    }

    
}

void Wall::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* Wall::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void Wall::SetLifesCount(int lifes)
{
    m_lifes = lifes;
}

int Wall::GetLifesCount()
{
    return m_lifes;
}

void Wall::TakeLife()
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

void Wall::ChangeColor()
{
    switch (m_lifes)
    {
        case 10: 
        {
            m_p_firstBrick->SetColor(Utils::COLOR_DIMGREY);
            m_p_secondBrick->SetColor(Utils::COLOR_DIMGREY);
            break;
        }
        case 5:
        {
            m_p_firstBrick->SetColor(Utils::COLOR_DARKSLATEGREY);
            m_p_secondBrick->SetColor(Utils::COLOR_DARKSLATEGREY);
            break;
        }
    }

    SetBasePattern();
    SetCurrentPattern();
}
