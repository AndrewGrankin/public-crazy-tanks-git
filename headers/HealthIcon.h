// Header file for HealthIcon class

#ifndef HEALTH_ICON_H
#define HEALTH_ICON_H

#include <GameObject.h>
#include <Utils.h>
#include <array>

class HealthIcon : public GameObject
{
    public:
        HealthIcon(eTag tag, COLORREF color = 0, int patWidth = Utils::HEALTH_PATTERN_WIDTH, int patHeight = Utils::HEALTH_PATTERN_HEIGHT);
        ~HealthIcon();
   
        virtual int* GetCurrentPattern() const;  

        void SetIndex(int index);
        int GetIndex();

    private:
        int m_index;                 

    private:  
        HealthIcon();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;
};

#endif