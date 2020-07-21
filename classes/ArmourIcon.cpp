// Class to hold ArmourIcon objects

#include <ArmourIcon.h>

ArmourIcon::ArmourIcon()
{}

ArmourIcon::~ArmourIcon()
{}

ArmourIcon::ArmourIcon(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    SetBasePattern();
    SetCurrentPattern();
}

void ArmourIcon::SetBasePattern() const
{
    std::array<int, Utils::ARMOUR_PATTERN_WIDTH * Utils::ARMOUR_PATTERN_HEIGHT> tempArray = Utils::GetArmourPattern();

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void ArmourIcon::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* ArmourIcon::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void ArmourIcon::SetIndex(int index)
{
    m_index = index;
}

int ArmourIcon::GetIndex()
{
    return m_index;
}
