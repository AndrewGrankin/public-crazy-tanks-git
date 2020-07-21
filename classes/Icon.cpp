// Class to hold Icon objects

#include <Icon.h>

Icon::Icon()
{}

Icon::~Icon()
{}

Icon::Icon(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    SetBasePattern();
    SetCurrentPattern();
}

void Icon::SetBasePattern() const
{
    std::array<int, Utils::ICON_PATTERN_WIDTH * Utils::ICON_PATTERN_HEIGHT> tempArray = Utils::GetIconPattern(m_color);

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void Icon::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* Icon::GetCurrentPattern() const
{
    return m_p_currentPattern;
}
