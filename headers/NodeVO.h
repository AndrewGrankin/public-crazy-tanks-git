// header file for node value object class

#ifndef NODE_VO_H
#define NODE_VO_H

#include <windows.h>
#include <stdint.h>

class NodeVO
{
    private:
        uint16_t m_nodeNumber;
        uint16_t m_coordX;
        uint16_t m_coordY;
        bool m_isAccessible;
        uint32_t m_color;

    public:
        NodeVO(){};
        ~NodeVO(){};

        // setters functions
        void SetNodeNumber(uint16_t number) { m_nodeNumber = number; }
        void SetNodeCoords(uint16_t x, uint16_t y) { m_coordX = x; m_coordY = y; }
        void SetAccess(bool flag) { m_isAccessible = flag; }
        void SetColor(uint32_t color) { m_color = color; }

        // getters functions
        uint16_t GetNodeNumber() { return m_nodeNumber; }
        uint16_t GetNodeCoordX() { return m_coordX; }
        uint16_t GetNodeCoordY() { return m_coordY; }
        bool IsAccessible() { return m_isAccessible; }
        uint32_t GetColor() { return m_color; }

};

#endif