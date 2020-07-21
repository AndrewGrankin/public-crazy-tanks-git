// This is to test how to work with templates

#include <iostream>
#include <sstream>
#include <Box.h>
using namespace std;

class Tank
{
    public:
        Tank(int pos, string name)
        {               
            objectCount++;
            m_id = objectCount;

            m_p_position = new int(pos);
            m_name = name;
            // cout << "'Tank " << m_name << "' constructor. ID: " << m_id << endl;
        }

        ~Tank()
        {
            // cout << "'Tank "<< m_name << "' destructor. ID: " << m_id << endl;
            delete m_p_position;
            m_p_position = 0;
        }

        void SetName(string name)
        {
            m_name = name;
        }

        int GetID() const
        {
            return m_id;
        }

        int* GetPosition()
        {
            return m_p_position;
        }

        string GetName()
        {
            return m_name;
        }


    private:
        Tank();

        static int objectCount;
        int m_id;

        int* m_p_position;
        string m_name;
};

int Tank::objectCount = 0;

// template<typename T>
// class BoxItem
// {
//     public:
//         BoxItem();
//         ~BoxItem();
//         void SetCargo(T* cargo);
//         void SetNext(BoxItem<T>* next);
//         T* GetCargo() const;
//         BoxItem<T>* GetNext() const;

//     private:
//         T* m_p_cargo;
//         BoxItem<T>* m_p_next;
// };

// template<typename T>
// BoxItem<T>::BoxItem()
// {
//     // cout << "'BoxItem' constructor." << endl;
//     m_p_cargo = 0;
//     m_p_next = 0;
// }

// template<typename T>
// BoxItem<T>::~BoxItem()
// {
//     // cout << "'BoxItem' destructor. " << endl;
//     delete m_p_cargo;   // delete only cargo. We can't touch m_p_next
//     m_p_cargo = 0;
// }

// template<typename T>
// void BoxItem<T>::SetCargo(T* cargo)
// {
//     m_p_cargo = cargo;
// }

// template<typename T>
// void BoxItem<T>::SetNext(BoxItem<T>* next)
// {
//     m_p_next = next;
// }

// template<typename T>
// T* BoxItem<T>::GetCargo() const
// {
//     return m_p_cargo;
// }

// template<typename T>
// BoxItem<T>* BoxItem<T>::GetNext() const
// {
//     return m_p_next;
// }

// template<typename T>
// class Box
// {
//     public:
//         Box();
//         ~Box();

//         void Add(T* obj);
//         void Remove(T* obj);
//         void Clear();

//         BoxItem<T>* GetHead() const;
    
//     private:
//         BoxItem<T>* m_p_head;
//         BoxItem<T>* m_p_tail;

// };

// template<typename T>
// Box<T>::Box()
// {
//     m_p_head = 0;
//     m_p_tail = 0;
// }

// template<typename T>
// Box<T>::~Box()
// {
//     Clear();
// }

// template<typename T>
// void Box<T>::Add(T* obj)
// {
//     BoxItem<T>* boxItem = new BoxItem<T>();
//     boxItem->SetCargo(obj);
    
//     // if list is empty, make head and tail of list this new object
//     if (m_p_head == 0)
//     {
//         m_p_head = boxItem;
//         m_p_tail = boxItem; 
//     }
//     // otherwise find the end of the list and add the object there
//     else
//     {
//         m_p_tail->SetNext(boxItem);
//         m_p_tail = boxItem;
//     }
// }

// template<typename T>
// void Box<T>::Remove(T* obj)
// {
//     if (m_p_head != 0)
//     {        
//         BoxItem<T>* p_iter = m_p_head;
//         BoxItem<T>* p_temp = p_iter;
//         while (p_iter != 0)
//         {
//             if (p_iter->GetCargo() == obj)
//             {
//                 if (p_iter == m_p_head)
//                 {
//                     m_p_head = m_p_head->GetNext();
//                     delete p_temp;
//                     break;                    
//                 }
//                 else
//                 {
//                     p_temp->SetNext(p_iter->GetNext());
//                     if (p_iter == m_p_tail)
//                     {
//                         m_p_tail = p_temp;
//                     }
//                     delete p_iter;
//                     break;
//                 }  
//             }
//             p_temp = p_iter;
//             p_iter = p_iter->GetNext();
//         }

//         if (m_p_head == 0)
//         {            
//             m_p_tail = 0; 
//         }
//     }   
// }

// template<typename T>
// void Box<T>::Clear()
// {
//     while (m_p_head != 0)
//     {
//         BoxItem<T>* p_temp = m_p_head;
//         m_p_head = m_p_head->GetNext();
//         delete p_temp;

//         if (m_p_head == 0)
//         {
//             cout << "Tail to null..." << endl;
//             m_p_tail = 0; 
//         }      
//     }
// }

// template<typename T>
// BoxItem<T>* Box<T>::GetHead() const
// {
//     return m_p_head;
// }


int main()
{
    Box<Tank> box;
    int choice;

    do
    {
        // show box content
        BoxItem<Tank>* p_item = box.GetHead();
        cout << "====================\n";
        cout << "Box contains:\n";
        if (p_item == 0)
        {
            cout << "Nothing!\n";
        }
        else
        {
            int count = 0;
            while (p_item != 0)
            {
                cout << "index: " << p_item->GetIndex() << " ";
                cout << "ID: " << p_item->GetCargo()->GetID() << ". ";
                cout << p_item->GetCargo()->GetName() << " Pos: ";
                cout << *(p_item->GetCargo()->GetPosition());
                cout << endl;
                count++;

                p_item = p_item->GetNext();
            }
            cout << "There are " << count << " elements.\n";
        }
        cout << "====================\n";

        // menu
        cout << "Please select one of the following:\n";
        cout << "0 - Exit\n";
        cout << "1 - Add Item\n";
        cout << "2 - Remove Item\n";
        cout << "3 - Clear the box\n";
        cout << "4 - Make stress test\n";
        cout << "5 - Mark to remove\n";
        cout << "6 - Cleanup the box\n";
        cout << "7 - Get element by index\n";
        cout << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 0: break;
            case 1: 
            {
                Tank* p_newTank = new Tank(0, "tank");
                box.Add(p_newTank);
                break;
            }
            case 2:
            {
                cout << "Which ID to remove? ID: ";
                int id;
                cin >> id;
                Tank* p_tank_to_remove = 0;

                // find the Tank by id
                p_item = box.GetHead();
                while (p_item != 0)
                {
                    if (p_item->GetCargo()->GetID() == id)
                    {
                        p_tank_to_remove = p_item->GetCargo();
                        break;
                    }

                    p_item = p_item->GetNext();
                }

                if (p_tank_to_remove != 0)
                {
                    box.Remove(p_tank_to_remove);
                }
                else
                {
                    cout << "There is no such item!\n";
                }
                break;
            }
            case 3:
            {
                box.Clear(); 
                break;
            } 
            case 4:
            {
                cout << "Enter the volume: ";
                int volume;
                cin >> volume;
                
                for (int i = 0; i < volume; ++i)
                {
                    Tank* p_newTank = new Tank(4, "tank");
                    box.Add(p_newTank);
                }
                break;
            }
            case 5:
            {
                cout << "Which ID to mark? ID: ";
                int id;
                cin >> id;
                Tank* p_tank_to_mark = 0;

                // find the Tank by id
                p_item = box.GetHead();
                while (p_item != 0)
                {
                    if (p_item->GetCargo()->GetID() == id)
                    {
                        p_tank_to_mark = p_item->GetCargo();
                        break;
                    }

                    p_item = p_item->GetNext();
                }

                if (p_tank_to_mark != 0)
                {
                    box.MarkToRemove(p_tank_to_mark);
                }
                else
                {
                    cout << "There is no such item!\n";
                }
                break;  
            }
            case 6:
            {
                box.Cleanup();
                break;
            }
            case 7:
            {
                cout << "Which element to get? Index: ";
                int id;
                cin >> id;
                Tank* p_tank_to_get = 0;

                // find the Tank by id
                p_tank_to_get = box.GetElement(id);

                if (p_tank_to_get != 0)
                {
                    cout << "---------------------------\n";
                    cout << "You got the following Tank:\n";
                    cout << "ID: " << p_tank_to_get->GetID() << ". ";
                    cout << p_tank_to_get->GetName() << " Pos: ";
                    cout << *(p_tank_to_get->GetPosition());
                    cout << "\n-------------------------\n";
                }
                else
                {
                    cout << "There is no such object!\n";
                }
                break;
            }
        }

    } while (choice != 0);

    

    cin.ignore();
    return 0;
}