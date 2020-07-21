// This is  to test dynamic memory allocation

#include <iostream>

using namespace std;

class A
{
    public:
        A();
        // A(const A& a);
        ~A();
        int* m_position;
        int m_start;
};

A::A()
{
    cout << "\n|Constructor|\n";
    m_position = new int;
}

// A::A(const A& a)
// {
//     cout << "\n|Copy Constructor|\n";
//     // m_position = new int(*(a.m_position));
//     // m_start = a.m_start;
// }

A::~A()
{
    cout << "\n|Destructor|\n";
    delete m_position;
    m_position = 0;
}

void Move(A a)
{
    int newPosition = 20;
    int newStart = 200;
    *(a.m_position) = newPosition;
    a.m_start = newStart;
    cout << "m_position = " << *(a.m_position) << endl;
    // cout << "m_start = " << a.m_start << endl;
}

int main()
{
    A* item = new A();
    cout << "Set position to 10 and start to 100\n";
    *(item->m_position) = 10;
    item->m_start = 100;
    cout << "m_position = " << *(item->m_position) << endl;
    // cout << "m_start = " << item->m_start << endl;
    cout << "Calling Move() function\n";
    Move(*item);
    cout << "Checking position and start\n";
    cout << "m_position = " << *(item->m_position) << endl;
    cout << "Trying to write something to dangling pointer...\n";
    *(item->m_position) = 30;
    cout << "m_position = " << *(item->m_position) << endl;
    // cout << "m_start = " << item->m_start << endl;
    delete item;

    // int size = 3;
    // int* p_array = new int[size];
    // for (int i = 0; i < size; ++i)
    // {
    //     p_array[i] = i;
    // } 

    // cout << p_array << endl;
    // for (int i = 0; i < size; ++i)
    // {
    //     cout << p_array[i] << " ";
    // }

    // int* p_newArray = new int[size];
    // for (int i = 0; i < size; ++i)
    // {
    //     p_newArray[i] = p_array[i];
    // }
    // cout << endl;
    // cout << p_newArray << endl;
    // for (int i = 0; i < size; ++i)
    // {
    //     cout << p_newArray[i] << " ";
    // }

    cin.ignore();
    return 0;
}