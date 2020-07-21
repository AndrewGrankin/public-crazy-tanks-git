// Header file for Brick class

#ifndef BRICK_H
#define BRICK_H

#include <GameObject.h>
#include <Utils.h>
#include <array>

class Brick : public GameObject
{
    public:
        Brick(eTag tag, COLORREF color = Utils::COLOR_DARKGREY, int patWidth = Utils::BRICK_PATTERN_WIDTH, int patHeight = Utils::BRICK_PATTERN_HEIGHT);
        ~Brick();

        void SetColor(COLORREF color);
 
        virtual int* GetCurrentPattern() const;                     

    private:  
        Brick();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;  
};

#endif