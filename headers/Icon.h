// Header file for Icon class

#ifndef ICON_H
#define ICON_H

#include <GameObject.h>
#include <Utils.h>
#include <array>

class Icon : public GameObject
{
    public:
        Icon(eTag tag, COLORREF color, int patWidth = Utils::ICON_PATTERN_WIDTH, int patHeight = Utils::ICON_PATTERN_HEIGHT);
        ~Icon();
   
        virtual int* GetCurrentPattern() const;                     

    private:  
        Icon();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;
};

#endif