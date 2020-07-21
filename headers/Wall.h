// Header file for Wall class

#ifndef WALL_H
#define WALL_H

#include <GameObject.h>
#include <Brick.h>
#include <Utils.h>
#include <array>

class Wall : public GameObject
{
    public:
        Wall(eTag tag, Brick* firstBrick, Brick* secondBrick, eDirection direction);
        ~Wall();

        void SetLifesCount(int);
        int GetLifesCount();
        void TakeLife();
        void ChangeColor();
 
        virtual int* GetCurrentPattern() const;

    private:
        Brick* m_p_firstBrick;
        Brick* m_p_secondBrick; 
        eDirection m_direction;
        int m_lifes;             

    private:  
        Wall();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;
};

#endif