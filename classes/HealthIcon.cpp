// Class to hold HealthIcon objects

#include <HealthIcon.h>

HealthIcon::HealthIcon()
{}

HealthIcon::~HealthIcon()
{}

HealthIcon::HealthIcon(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    SetBasePattern();
    SetCurrentPattern();
}

void HealthIcon::SetBasePattern() const
{
    std::array<int, Utils::HEALTH_PATTERN_WIDTH * Utils::HEALTH_PATTERN_HEIGHT> tempArray = Utils::GetHealthPattern();

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void HealthIcon::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* HealthIcon::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void HealthIcon::SetIndex(int index)
{
    m_index = index;
}

int HealthIcon::GetIndex()
{
    return m_index;
}
