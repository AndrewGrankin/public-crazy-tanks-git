// Class to hold GameObject objects

#include <GameObject.h>

int GameObject::objectCount = 0;

GameObject::GameObject()
{
    objectCount++;
    m_id = objectCount;
}

GameObject::GameObject(eTag tag, COLORREF color, int patWidth, int patHeight)
{
    objectCount++;
    m_id = objectCount;
    m_tag = tag;
    m_color = color;
    m_patternWidth = patWidth;
    m_patternHeight = patHeight;
    m_p_basePattern = new int[m_patternWidth * m_patternHeight];
    m_p_currentPattern = new int[m_patternWidth * m_patternHeight];
    m_p_boxCollider = new RECT();
}

GameObject::GameObject(const GameObject& gameObj)
{

}

GameObject::~GameObject()
{
    delete m_p_basePattern;
    delete m_p_currentPattern;
    delete m_p_boxCollider;
    m_p_basePattern = 0;
    m_p_currentPattern = 0;
    m_p_boxCollider = 0;
}

eTag GameObject::GetTag()
{
    return m_tag;
}

int GameObject::GetID()
{
    return m_id;
}

int GameObject::GetPatternWidth()
{
    return m_patternWidth;
}

int GameObject::GetPatternHeight()
{
    return m_patternHeight;
}

void GameObject::SwapDimensions()
{
    int newPatternWidth = m_patternHeight;
    int newPatternHeight = m_patternWidth;
    m_patternWidth = newPatternWidth;
    m_patternHeight = newPatternHeight;
}

void GameObject::SetDrawingStart(int startX, int startY)
{
    m_drawingStart.x = startX;
    m_drawingStart.y = startY;
    SetDrawingEnd(m_drawingStart.x, m_drawingStart.y);
}

POINT GameObject::GetDrawingStart()
{
    return m_drawingStart;
}

void GameObject::SetDrawingEnd(int startX, int startY)
{
    m_drawingEnd.x = startX + (m_patternWidth - 1);    // "-1" - because startX already takes one pixel
    m_drawingEnd.y = startY + (m_patternHeight - 1);    // "-1" - because startY already takes one pixel
    SetBoxCollider(startX, startY, m_drawingEnd.x, m_drawingEnd.y);
}

POINT GameObject::GetDrawingEnd()
{
    return m_drawingEnd;
}

void GameObject::SetBoxCollider(int startX, int startY, int endX, int endY)
{
    m_p_boxCollider->left = startX;
    m_p_boxCollider->top = startY;
    m_p_boxCollider->right = endX;
    m_p_boxCollider->bottom = endY;
}

RECT* GameObject::GetBoxCollider()
{
    return m_p_boxCollider;
}

