// This is  to test dynamic memory allocation with inheritance

#include <iostream>

using namespace std;

class B
{
    public:
        
        B(int start);
        B(const B& b);
        ~B();

        int* m_p_oldPosition;
        int m_oldStart;
    
    private:
        B();
};

class A : public B
{
    public:
        A();
        A(int start);
        A(const A& a);
        ~A();
    
        int* m_p_position;
        int m_start;
    
    private:
        // A();
};

B::B()
{
    cout << "\n|'B' Constructor|\n";
    m_p_oldPosition = new int;
}

B::B(int start)
{
    cout << "\n|'B(int)' Constructor|\n";
    m_oldStart = start;
}

B::B(const B& b)
{
    cout << "\n|'B' Copy Constructor|\n";
    m_p_oldPosition = new int(*(b.m_p_oldPosition));
    m_oldStart = b.m_oldStart;
}

B::~B()
{
    cout << "\n|'B' Destructor|\n";
    delete m_p_oldPosition;
    m_p_oldPosition = 0;
}

A::A()
{
    cout << "\n|'A' Constructor|\n";
    m_p_position = new int;
}

A::A(int start) : B(start)
{
    cout << "\n|'A(int) Constructor|\n";
    m_start = start;
    m_p_position = new int;
}

A::A(const A& a)
{
    cout << "\n|'A' Copy Constructor|\n";
    *m_p_oldPosition = *(a.m_p_oldPosition);
    m_oldStart = a.m_oldStart;
    m_p_position = new int(*(a.m_p_position));
    m_start = a.m_start;
}

A::~A()
{
    cout << "\n|'A' Destructor|\n";
    delete m_p_position;
    m_p_position = 0;
}

Move(A a)
{
    int newPosition = 20;
    int newStart = 200;
    // *(a.m_p_position) = newPosition;
    // a.m_start = newStart;
    // *(a.m_p_oldPosition) = newPosition;
    // a.m_oldStart = newStart;
    cout << "m_p_position = " << *(a.m_p_position) << endl;
    cout << "&m_p_position = " << a.m_p_position << endl;
    cout << "m_p_oldPosition = " << *(a.m_p_oldPosition) << endl;
    cout << "&m_p_oldPosition = " << a.m_p_oldPosition << endl;
    cout << "m_start = " << a.m_start << endl;
    cout << "m_oldStart = " << a.m_oldStart << endl;
}

int main()
{
    A* item = new A(230);

    cout << "\nSet position to 10 and start to 100\n";
    *(item->m_p_position) = 10;
    *(item->m_p_oldPosition) = 10;
    item->m_start = 100;
    item->m_oldStart = 100;

    cout << "m_p_position = " << *(item->m_p_position) << endl;
    cout << "&m_p_position = " << item->m_p_position << endl;
    cout << "m_p_oldPosition = " << *(item->m_p_oldPosition) << endl;
    cout << "&m_p_oldPosition = " << item->m_p_oldPosition << endl;
    cout << "m_start = " << item->m_start << endl;
    cout << "m_oldStart = " << item->m_oldStart << endl;

    cout << "\nCalling Move() function\n";
    Move(*item);

    cout << "\nChecking position and start\n";
    cout << "m_p_position = " << *(item->m_p_position) << endl;
    cout << "&m_p_position = " << item->m_p_position << endl;
    cout << "m_p_oldPosition = " << *(item->m_p_oldPosition) << endl;
    cout << "&m_p_oldPosition = " << item->m_p_oldPosition << endl;
    cout << "m_start = " << item->m_start << endl;
    cout << "m_oldStart = " << item->m_oldStart << endl;

    delete item;

    cin.ignore();
}