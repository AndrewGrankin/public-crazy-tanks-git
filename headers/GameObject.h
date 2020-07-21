// Header file for GameObject class

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <windows.h>
#include <Utils.h>

class GameObject        // abstract class
{
    public:
        GameObject();
        GameObject(eTag tag, COLORREF color, int patWidth, int patHeight);
        GameObject(const GameObject& gameObj);
        ~GameObject();

        void SetDrawingStart(int startX, int startY);
        int GetID();
        eTag GetTag();  
        int GetPatternWidth();
        int GetPatternHeight();   
        POINT GetDrawingStart();
        POINT GetDrawingEnd();
        RECT* GetBoxCollider();

        virtual int* GetCurrentPattern() const = 0;                         // pure virtual function 

    protected:
        static int objectCount;
        int m_id;
        eTag m_tag;
        COLORREF m_color;
        int m_patternWidth;
        int m_patternHeight;
        POINT m_drawingStart;
        POINT m_drawingEnd;
        int* m_p_basePattern;       // needs explicit copy constructor
        int* m_p_currentPattern;    // needs explicit copy constructor
        RECT* m_p_boxCollider;      // needs explicit copy constructor

    protected:
        void SwapDimensions();      // make patternWidh as patternHeight and vice versa

        virtual void SetBasePattern() const = 0;        // pure virtual function
        virtual void SetCurrentPattern() const = 0;     // pure virtual function
    
    private:
        void SetDrawingEnd(int startX, int startY);
        void SetBoxCollider(int startX, int startY, int endX, int endY);
};

#endif 