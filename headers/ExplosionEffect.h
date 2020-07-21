// Header file for ExplosionEffect class

#ifndef EXPLOSION_EFFECT_H
#define EXPLOSION_EFFECT_H

#include <GameObject.h>
#include <Utils.h>
#include <array>
#include <ctime>
#include <chrono> 

class ExplosionEffect : public GameObject
{
    public:
        ExplosionEffect(eTag tag, COLORREF color = Utils::COLOR_YELLOW, int patWidth = Utils::EXPLOSION_EFFECT_PAT_WIDTH, int patHeight = Utils::EXPLOSION_EFFECT_PAT_HEIGHT);
        ~ExplosionEffect();
        void Animate();
        bool IsLifeEnded();
        virtual int* GetCurrentPattern() const;                     

    private:
        int m_framesCount = 4;
        bool m_endLife;
        int64_t m_lastFrameChange;
        static std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> m_explosionEffectPatArray_0;
        static std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> m_explosionEffectPatArray_1;
        static std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> m_explosionEffectPatArray_2;
        static std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> m_explosionEffectPatArray_3;

    private:  
        ExplosionEffect();
        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const; 
        void SetBasePattern(std::array<int, Utils::EXPLOSION_EFFECT_PAT_WIDTH * Utils::EXPLOSION_EFFECT_PAT_HEIGHT> pattern); 
};

#endif