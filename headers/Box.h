// This is the header file for Box collection

#ifndef BOX_H
#define BOX_H

#include <BoxItem.h>

template<typename T>
class Box
{
    public:
        Box();
        ~Box();

        void Add(T* obj);           // add element to the collection
        void Remove(T* obj);        // remove element
        void MarkToRemove(T* obj);  // mark element to be removed during the cleanup (void Cleanup())
        void Clear();               // remove all elements in the collection
        void Cleanup();             // to remove all elements that marked to remove
        int Size();                 // get total elements count
        T* GetElement(int index);   // get element by index
        int GetElementIndex(T* obj);   // get id of element if element exists. Returns "-1" if nothig there
        
        BoxItem<T>* GetHead() const;
    
    private:
        BoxItem<T>* m_p_head;
        BoxItem<T>* m_p_tail;
        int m_itemsCount;
};

template<typename T>
Box<T>::Box()
{
    m_p_head = 0;
    m_p_tail = 0;
    m_itemsCount = 0;
}

template<typename T>
Box<T>::~Box()
{
    Clear();
}

template<typename T>
void Box<T>::Add(T* obj)
{
    BoxItem<T>* boxItem = new BoxItem<T>();
    boxItem->SetCargo(obj);
    
    // if list is empty, make head and tail of list this new object
    if (m_p_head == 0)
    {
        m_p_head = boxItem;
        m_p_tail = boxItem; 
    }
    // otherwise find the end of the list and add the object there
    else
    {
        m_p_tail->SetNext(boxItem);
        m_p_tail = boxItem;
    }

    boxItem->SetIndex(m_itemsCount);
    m_itemsCount++;
}

template<typename T>
void Box<T>::Remove(T* obj)
{
    if (m_p_head != 0)
    {    
        bool removed = false;    
        BoxItem<T>* p_iter = m_p_head;
        BoxItem<T>* p_temp = p_iter;
        while (p_iter != 0)
        {
            if (p_iter->GetCargo() == obj)
            {
                if (p_iter == m_p_head)
                {
                    m_p_head = m_p_head->GetNext();
                    delete p_temp;  
                    removed = true;
                    p_iter = m_p_head;
                    continue;             
                }
                else
                {
                    p_temp->SetNext(p_iter->GetNext());     // "p_temp" is a previous element in this case
                   
                    // if tested element is tail, then set previous element as a tail
                    if (p_iter == m_p_tail)
                    {
                        m_p_tail = p_temp;
                    }

                    // remove the tested element
                    delete p_iter;      
                    removed = true;
                    p_iter = p_temp->GetNext();
                    continue;
                }  
            }
            
            // if element was already removed, then reset index for every next element
            if (removed && p_iter != 0)
            {
                p_iter->SetIndex(p_iter->GetIndex() - 1);
            }
            
            p_temp = p_iter;
            p_iter = p_iter->GetNext();
        }

        if (m_p_head == 0)
        {            
            m_p_tail = 0; 
        }
    }
    m_itemsCount--;   
}

template<typename T>
void Box<T>::MarkToRemove(T* obj)
{
    if (m_p_head != 0)
    {        
        BoxItem<T>* p_iter = m_p_head;
        while (p_iter != 0)
        {
            if (p_iter->GetCargo() == obj)
            {
                p_iter->SetRemovalMark(true);
                break;
            }
            p_iter = p_iter->GetNext();
        }
    }  
}

template<typename T>
void Box<T>::Clear()
{
    while (m_p_head != 0)
    {
        BoxItem<T>* p_temp = m_p_head;
        m_p_head = m_p_head->GetNext();
        delete p_temp;

        if (m_p_head == 0)
        {
            m_p_tail = 0; 
        }      
    }
    m_itemsCount = 0;
}

template<typename T>
void Box<T>::Cleanup()
{
    if (m_p_head != 0)
    {        
        int delta = 0;
        BoxItem<T>* p_current = m_p_head;
        BoxItem<T>* p_previous = m_p_head;
        while (p_current != 0)
        {
            if (p_current->GetRemovalMark() == true)
            {
                if (p_current == m_p_head)
                {
                    BoxItem<T>* p_temp;
                    p_temp = p_current;
                    if (m_p_tail == m_p_head)
                    {
                        m_p_tail = 0;
                    }
                    m_p_head = p_current->GetNext();
                    p_previous = p_current->GetNext();
                    p_current = m_p_head;
                    delete p_temp;
                    m_itemsCount--;
                    delta++;
                    continue;                  
                }
                else
                {
                    BoxItem<T>* p_temp;
                    p_temp = p_current;
                    p_previous->SetNext(p_current->GetNext());
                    if (p_current == m_p_tail)
                    {
                        m_p_tail = p_previous;
                    }
                    p_current = p_previous->GetNext();
                    delete p_temp;
                    m_itemsCount--;
                    delta++;
                    continue;
                }  
            }
            else
            {
                p_current->SetIndex(p_current->GetIndex() - delta);
            }
            p_previous = p_current;
            p_current = p_current->GetNext();
        }
    }  
}

template<typename T>
int Box<T>::Size()
{
    return m_itemsCount;
}

template<typename T>
T* Box<T>::GetElement(int index)
{
    T* p_element = 0;       // return "0" if there is no element with such id
    BoxItem<T>* p_current = m_p_head;       
    while (p_current != 0)
    {
        if (p_current->GetIndex() == index)
        {
            p_element = p_current->GetCargo();
            break;
        }
        p_current = p_current->GetNext();
    }

    return p_element;
}

template<typename T>
int Box<T>::GetElementIndex(T* obj)
{
    int index = -1;    // return "-1" if no such object
    BoxItem<T>* p_current = m_p_head;
    while (p_current != 0)
    {
        if (p_current->GetCargo() == obj)
        {
            index = p_current->GetIndex();
            break;
        }
        p_current = p_current->GetNext();
    }

    return index;
}

template<typename T>
BoxItem<T>* Box<T>::GetHead() const
{
    return m_p_head;
}

#endif