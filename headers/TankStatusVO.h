// Header file for TankStatusVO class

#ifndef TANK_STATUS_VO_H
#define TANK_STATUS_VO_H

#include <stdint.h>
#include <sstream>

class TankStatusVO
{
    private:
        eTag m_tag;
        POINT m_location;
        int m_status;
        int m_score;
        int64_t m_deathTime;
        std::string m_statusInfo;

    public:
        TankStatusVO(){};
        ~TankStatusVO(){};

        // Setter functions
        void SetTag(eTag tag) { m_tag = tag; }
        void SetLocation(int posX, int posY) { m_location.x = posX; m_location.y = posY; }
        void SetStatus(int status) { m_status = status; }
        void SetScore(int score) { m_score = score; }
        void SetDeathTime(int64_t time) { m_deathTime = time; }
        void IncreaseScore(int score) { m_score += score; }

        // Getter functions
        eTag GetTag() { return m_tag; }
        POINT GetLocation() { return m_location; }
        int GetStatus() { return m_status; }
        int GetScore() { return m_score; }
        int64_t GetDeathTime() { return m_deathTime; }
        std::string GetStatusInfo(int index)
        { 
            std::stringstream ss;

            switch (m_tag)
            {
                case PLAYER: { ss << "  PLAYER" << "   - - - - - - - - - - - - - - - - - - - - - - - - "; break; }
                case NPC: { ss << "   TANK_" << index << " - - - - - - - - - - - - - - - - - - - - - - - - "; break; }
            }

            // ss << "X: " << m_location.x << " Y: " << m_location.y << "   " << m_score << "  ";  // for test purposes
            ss << m_score << "  ";
            m_statusInfo = ss.str();
            return m_statusInfo;
        }
};

#endif