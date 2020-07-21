// This is the header file for BoxItem of Box collection

#ifndef BOX_ITEM_H
#define BOX_ITEM_H

template<typename T>
class BoxItem
{
    public:
        BoxItem();
        ~BoxItem();
        void SetCargo(T* cargo);
        void SetNext(BoxItem<T>* next);
        T* GetCargo() const;
        BoxItem<T>* GetNext() const;
        void SetRemovalMark(bool);
        bool GetRemovalMark();
        void SetIndex(int index);
        int GetIndex();

    private:
        T* m_p_cargo;
        BoxItem<T>* m_p_next;
        bool m_removalMark;
        int m_index;
};

template<typename T>
BoxItem<T>::BoxItem()
{
    m_p_cargo = 0;
    m_p_next = 0;
    m_removalMark = false;
    m_index = 0;
}

template<typename T>
BoxItem<T>::~BoxItem()
{
    delete m_p_cargo;   // delete only cargo. We can't touch m_p_next
    m_p_cargo = 0;
}

template<typename T>
void BoxItem<T>::SetCargo(T* cargo)
{
    m_p_cargo = cargo;
}

template<typename T>
void BoxItem<T>::SetNext(BoxItem<T>* next)
{
    m_p_next = next;
}

template<typename T>
T* BoxItem<T>::GetCargo() const
{
    return m_p_cargo;
}

template<typename T>
BoxItem<T>* BoxItem<T>::GetNext() const
{
    return m_p_next;
}

template<typename T>
void BoxItem<T>::SetRemovalMark(bool flag)
{
    m_removalMark = flag;
}

template<typename T>
bool BoxItem<T>::GetRemovalMark()
{
    return m_removalMark;
}

template<typename T>
void BoxItem<T>::SetIndex(int index)
{
    m_index = index;
}

template<typename T>
int BoxItem<T>::GetIndex()
{
    return m_index;
}

#endif