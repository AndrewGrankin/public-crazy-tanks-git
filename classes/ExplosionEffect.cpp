// Class to hold ExplosionEffect objects

#include <ExplosionEffect.h>

std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT>
ExplosionEffect::m_explosionEffectPatArray_0 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
                                                0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT>
ExplosionEffect::m_explosionEffectPatArray_1 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
                                                0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                                0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                                0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                                0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT>
ExplosionEffect::m_explosionEffectPatArray_2 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                                                0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
                                                0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT>
ExplosionEffect::m_explosionEffectPatArray_3 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,
                                                0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                                0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                                0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
                                                0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                                                                                               

ExplosionEffect::ExplosionEffect()
{}

ExplosionEffect::~ExplosionEffect()
{}

ExplosionEffect::ExplosionEffect(eTag tag, COLORREF color, int patWidth, int patHeight) : GameObject(tag, color, patWidth, patHeight)
{
    m_endLife = false;
    m_lastFrameChange = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    SetBasePattern(m_explosionEffectPatArray_0);
    SetCurrentPattern();
}

void ExplosionEffect::SetBasePattern() const
{}

void ExplosionEffect::SetBasePattern(std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> pattern)
{
    std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> tempArray = pattern;

    for (unsigned int i = 0; i < pattern.size(); ++i)
    {
        if (pattern[i] == 1)
        {
            tempArray[i] = Utils::GetColorIndex(m_color);
        }
        else if (pattern[i] == 0)
        {
            tempArray[i] = Utils::GetColorIndex(Utils::COLOR_BLACK);
        }
    }

    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_basePattern[y * m_patternWidth + x] = tempArray[y * m_patternWidth + x];
        }
    }
}

void ExplosionEffect::SetCurrentPattern() const
{
    for (int y = 0; y < m_patternHeight; ++y)
    {
        for (int x = 0; x < m_patternWidth; ++x)
        {
            m_p_currentPattern[y * m_patternWidth + x] = m_p_basePattern[y * m_patternWidth + x];
        }
    }
}

int* ExplosionEffect::GetCurrentPattern() const
{
    return m_p_currentPattern;
}

void ExplosionEffect::Animate()
{
    int64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    if (currentTime - m_lastFrameChange >= 100)
    {
        switch (m_framesCount)
        {
            case 4: 
            {
                SetBasePattern(m_explosionEffectPatArray_0);
                SetCurrentPattern();
                break;
            }
            case 3:
            {
                SetBasePattern(m_explosionEffectPatArray_1);
                SetCurrentPattern();
                break;
            }
            case 2:
            {
                SetBasePattern(m_explosionEffectPatArray_2);
                SetCurrentPattern();
                break;
            }
            case 1:
            {
                SetBasePattern(m_explosionEffectPatArray_3);
                SetCurrentPattern();
                break;
            }
            case 0:
            {
                m_endLife = true;
                break;
            }
        }

        m_lastFrameChange = currentTime;
        --m_framesCount;
    }
}

bool ExplosionEffect::IsLifeEnded()
{
    return m_endLife;
}
