// Header file for ArmourIcon class

#ifndef ARMOUR_ICON_H
#define ARMOUR_ICON_H

#include <GameObject.h>
#include <Utils.h>
#include <array>

class ArmourIcon : public GameObject
{
    public:
        ArmourIcon(eTag tag, COLORREF color = 0, int patWidth = Utils::ARMOUR_PATTERN_WIDTH, int patHeight = Utils::ARMOUR_PATTERN_HEIGHT);
        ~ArmourIcon();
   
        virtual int* GetCurrentPattern() const;  

        void SetIndex(int index);
        int GetIndex();

    private:
        int m_index;                  

    private:  
        ArmourIcon();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;
};

#endif