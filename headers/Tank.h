// Header file for Tank class

#ifndef TANK_H
#define TANK_H

#include <stdint.h>
#include <ctime>
#include <chrono>

/* Custom types */
#include <GameObject.h>
#include <Utils.h>
#include <Box.h>
#include <TankStatusVO.h>

class Tank : public GameObject
{
    public:
        static const int ARMOUR_DURATION_TIME = 10;
        static const int STEP = 5;

    private:
        int m_index;
        COLORREF m_tempColor;
        eDirection m_currentDirection;
        int64_t m_lastShootTime;
        bool m_shootFlag;
        int m_pathLength;
        int m_lifes;
        int m_maxLifes;
        bool m_isAttacked;
        int m_framesCount = 3;
        bool m_hasArmour;
        int64_t m_armourPickUpTime;

        bool m_isXAxisDirection;
        TankStatusVO* m_p_enemyObject;

    public:
        Tank(eTag tag, COLORREF color, int patWidth = Utils::TANK_PATTERN_WIDTH, int patHeight = Utils::TANK_PATTERN_HEIGHT);
        Tank(const Tank& aTank);        // copy constructor to make a deep copy because of pointer members
        ~Tank();

        void SetIndex(int index);
        int GetIndex();
        void Move(eDirection direction, int step = STEP);
        POINT GetShootingPosition(eDirection direction);
        void SetDirection(eDirection direction);
        eDirection GetDirection();
        void SetLastShootTime(int64_t time);
        void SetShootFlag(bool);
        int64_t GetLastShootTime();
        bool GetShootFlag();
        void SetPathLength(int);
        int GetPathLength();
        void DecreasePath();
        void SetLifesCount(int);
        int GetLifesCount();
        int GetMaxLifesCount();
        void TakeLife();
        void PickUpArmour();
        bool HasArmour();

        bool IsXAxisDirection();
        void SetXAxisDirection(bool flag);
        void SetEnemyObject(Box<TankStatusVO>* status_list);
        TankStatusVO* GetEnemyObject();
        void Animate();     // animate something if any
        
        virtual int* GetCurrentPattern() const;
        
    private:
        Tank();
        virtual void SetBasePattern() const;
        virtual void SetCurrentPattern() const;
        
};

#endif