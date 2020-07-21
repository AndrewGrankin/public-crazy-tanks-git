// Header file for Bullet class

#ifndef BULLET_H
#define BULLET_H

#include <GameObject.h>
#include <Utils.h>
#include <Game.h>

class Bullet : public GameObject
{
    public:
        Bullet(eTag tag, COLORREF color, eDirection direction, int patWidth = Utils::BULLET_PATTERN_WIDTH, int patHeight = Utils::BULLET_PATTERN_HEIGHT);
        ~Bullet();
   
        virtual int* GetCurrentPattern() const;

        void Move(eDirection direction);
        eDirection GetDirection();
        int GetPathLength(); 
        void BelongTo(eTag);
        eTag ShotBy();      
        void SetTankIndex(int index);
        int GetTankIndex();                 

    private:
        eTag m_belongTo = EMPTY;
        int m_tankIndex = -1;
        int m_step = 10;
        int m_pathLength;
        eDirection m_direction;

    private:  
        Bullet();

        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;

        void DecreasePath();       
};

#endif