// Class to hold Brick objects

#include <Brick.h>

Brick::Brick()
{}

Brick::~Brick()
{}

Brick::Brick(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    SetBasePattern();
    SetCurrentPattern();
}

void Brick::SetBasePattern() const
{
    std::array<int, Utils::BRICK_PATTERN_WIDTH * Utils::BRICK_PATTERN_HEIGHT> tempArray = Utils::GetBrickPattern(m_color);

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void Brick::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* Brick::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void Brick::SetColor(COLORREF color)
{
    m_color = color;
    SetBasePattern();
    SetCurrentPattern();
}
