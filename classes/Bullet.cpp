// Class to hold Bullet objects

#include <Bullet.h>

Bullet::Bullet()
{}

Bullet::~Bullet()
{}

Bullet::Bullet(eTag tag, COLORREF color, eDirection direction, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    m_direction = direction;
    m_pathLength = Game::BULLET_FIRE_RANGE;
    SetBasePattern();
    SetCurrentPattern();
}

void Bullet::SetBasePattern() const
{
    std::array<int, Utils::BULLET_PATTERN_WIDTH * Utils::BULLET_PATTERN_HEIGHT> tempArray = Utils::GetBulletPattern(m_color);

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void Bullet::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* Bullet::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void Bullet::Move(eDirection direction)
{
    switch (direction)
    {
        case UP: 
        {
            SetDrawingStart(GetDrawingStart().x, GetDrawingStart().y - m_step);
            DecreasePath();
            break;
        }
        case DOWN:
        {
            SetDrawingStart(GetDrawingStart().x, GetDrawingStart().y + m_step);
            DecreasePath();
            break;
        } 
        case LEFT: 
        {
            SetDrawingStart(GetDrawingStart().x - m_step, GetDrawingStart().y);
            DecreasePath(); 
            break;
        }
        case RIGHT:
        {
            SetDrawingStart(GetDrawingStart().x + m_step, GetDrawingStart().y);
            DecreasePath(); 
            break;
        }
    }
}

eDirection Bullet::GetDirection()
{
    return m_direction;
}

int Bullet::GetPathLength()
{
    return m_pathLength;
}

void Bullet::DecreasePath()
{
    if (m_pathLength > 0)
    {
        m_pathLength -= m_step;
    }
    else
    {
        m_pathLength = 0;
    }
}

void Bullet::BelongTo(eTag tag)
{
    m_belongTo = tag;
}

eTag Bullet::ShotBy()
{
    return m_belongTo;
}

void Bullet::SetTankIndex(int index)
{
    m_tankIndex = index;
}

int Bullet::GetTankIndex()
{
    return m_tankIndex;
}