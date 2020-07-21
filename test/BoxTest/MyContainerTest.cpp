// This is to test the custom container (collection)

#include <iostream>
#include <sstream>
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
            cout << "'Tank " << m_name << "' constructor. ID: " << m_id << endl;
        }

        ~Tank()
        {
            cout << "'Tank "<< m_name << "' destructor. ID: " << m_id << endl;
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

class BoxItem
{
    public:
        BoxItem();
        ~BoxItem();
        void SetCargo(Tank* cargo);
        void SetNext(BoxItem* next);
        Tank* GetCargo() const;
        BoxItem* GetNext() const;

    private:
        Tank* m_p_cargo;
        BoxItem* m_p_next;
};

BoxItem::BoxItem()
{
    cout << "'BoxItem' constructor." << endl;
    m_p_cargo = 0;
    m_p_next = 0;
}

BoxItem::~BoxItem()
{
    cout << "'BoxItem' destructor. " << endl;
    delete m_p_cargo;   // delete only cargo. We can't touch m_p_next
    m_p_cargo = 0;
}

void BoxItem::SetCargo(Tank* cargo)
{
    m_p_cargo = cargo;
}

void BoxItem::SetNext(BoxItem* next)
{
    m_p_next = next;
}

Tank* BoxItem::GetCargo() const
{
    return m_p_cargo;
}

BoxItem* BoxItem::GetNext() const
{
    return m_p_next;
}


class Box
{
    public:
        Box();
        ~Box();

        void Add();
        void Add(Tank* tank);
        void Remove();
        void Remove(Tank* tank);
        void Clear();
        void Test();
        void Test(int volume);

        BoxItem* GetHead() const;
    
    private:
        BoxItem* m_p_head;
        BoxItem* m_p_tail;

};

Box::Box()
{
    m_p_head = 0;
    m_p_tail = 0;
}

Box::~Box()
{
    Clear();
}

void Box::Add()
{
    // // create a new Tank object
    // cout << "Please enter the name of the new Tank: ";
    // string name;
    // cin >> name;
    // cout << "\nPlease enter the position of the Tank: ";
    // int position;
    // cin >> position;

    Tank* p_newTank = new Tank(2, "npc_");
    stringstream ss;
    ss << p_newTank->GetName() << p_newTank->GetID();
    p_newTank->SetName(ss.str());
    Add(p_newTank);
}

void Box::Add(Tank* tank)
{
    BoxItem* boxItem = new BoxItem();
    boxItem->SetCargo(tank);
    
    // if list is empty, make head of list this new player
    if (m_p_head == 0)
    {
        m_p_head = boxItem;
        m_p_tail = boxItem; 
    }
    // otherwise find the end of the list and add the player there
    else
    {
        m_p_tail->SetNext(boxItem);
        m_p_tail = boxItem;
    }
}

void Box::Remove()
{
    if (m_p_head == 0)
    {
        cout << "There is nothing to remove!" << endl;
    }
    else
    {
        // find the tank based on id
        cout << "Please enter the Tank ID to remove: ";
        int id;
        cin >> id;
        BoxItem* p_iter = m_p_head;
        while (p_iter != 0)
        {
            if (p_iter->GetCargo()->GetID() == id)
            {
                Remove(p_iter->GetCargo());
                break;
            }
            p_iter = p_iter->GetNext();
        }
    }
}

void Box::Remove(Tank* tank)
{
    if (m_p_head != 0)
    {        
        BoxItem* p_iter = m_p_head;
        BoxItem* p_temp = p_iter;
        while (p_iter != 0)
        {
            if (p_iter->GetCargo() == tank)
            {
                if (p_iter == m_p_head)
                {
                    m_p_head = m_p_head->GetNext();
                    delete p_temp;
                    break;                    
                }
                else
                {
                    p_temp->SetNext(p_iter->GetNext());
                    if (p_iter == m_p_tail)
                    {
                        m_p_tail = p_temp;
                    }
                    delete p_iter;
                    break;
                }  
            }
            p_temp = p_iter;
            p_iter = p_iter->GetNext();
        }

        if (m_p_head == 0)
        {            
            m_p_tail = 0; 
        }
    }   
}

void Box::Clear()
{
    while (m_p_head != 0)
    {
        BoxItem* p_temp = m_p_head;
        m_p_head = m_p_head->GetNext();
        delete p_temp;

        if (m_p_head == 0)
        {
            cout << "Tail to null..." << endl;
            m_p_tail = 0; 
        }    
    }
}

void Box::Test()
{
    cout << "Please enter the volume: ";
    int vol;
    cin >> vol;
    Test(vol);
}

void Box::Test(int volume)
{
    for (int i = 0; i < volume; ++i)
    {
        Add();
    }
}

BoxItem* Box::GetHead() const
{
    return m_p_head;
}

void ShowBox(Box* box)
{
    cout << "Box contains:\n";
    BoxItem* p_iter = box->GetHead();
    if (p_iter == 0)
    {
        cout << "There is nothing in the box!\n";
    }
    else
    {
        while (p_iter != 0)
        {
            cout << p_iter->GetCargo()->GetID() << ". ";
            cout << p_iter->GetCargo()->GetName();
            cout << " Pos: " << *(p_iter->GetCargo()->GetPosition()) << endl;
            p_iter = p_iter->GetNext();
        }
    }
    
    
}


int main()
{
    Box* myBox = new Box();
    int choice;

    do
    {
        cout << "---------------------------\n";
        ShowBox(myBox);
        cout << "---------------------------\n";
        cout << "\n\t***** BOX TEST *****\n";
        cout << "0 = Exit the program.\n";
        cout << "1 = Add an item to the box.\n";
        cout << "2 = Remove an item from the box.\n";
        cout << "3 = Clear the box.\n";
        cout << "4 = Stress Test.\n";
        cout << endl << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 0: cout << "Good-bye.\n"; break;
            case 1: myBox->Add(); break;
            case 2: myBox->Remove(); break;
            case 3: myBox->Clear(); break;
            case 4: myBox->Test(); break;
            default: cout << "That was not a valid choice.\n";
        }
    } while (choice != 0);

    // Tank* player = new Tank(2, "player");
    // Tank* npc0 = new Tank(3, "NPC0");
    // Tank* npc1 = new Tank(1, "NPC1");

    // Box myBox;

    // myBox.Add(player);
    // myBox.Add(npc0);
    // myBox.Add(npc1);

    // BoxItem* p_iter = myBox.GetHead();
    // while (p_iter != 0)
    // {
    //     cout << p_iter->GetCargo()->GetName() << endl;
    //     p_iter = p_iter->GetNext();
    // }
    
    // myBox.Remove(npc0);

    // p_iter = myBox.GetHead();
    // while (p_iter != 0)
    // {
    //     cout << p_iter->GetCargo()->GetName() << endl;
    //     p_iter = p_iter->GetNext();
    // }

    cin.ignore();
    return 0;
}