// This is to test Abstract class and copy constructor

#include <iostream>

using namespace std;

class GameObject    // abstract class
{
    public:
        // GameObject();
        GameObject(int size = 20);
        GameObject(const GameObject& aGameObject);      // copy constructor
        virtual int GetSize() const = 0;
        virtual int* GetPosition() const = 0;
    
    protected:
        int m_size;
        int* m_p_position;
};

// GameObject::GameObject()
// {
//     cout << "\n|'GameObject()' constructor|\n"; 
// }

GameObject::GameObject(int size)
{
    cout << "\n|'GameObject(int)' consturctor|\n";
    m_size = size;
    m_p_position = new int();
}

GameObject::GameObject(const GameObject& aGameObject)
{
    cout << "\n|'GameObject(GameObject&)' copy constructor called|\n";
}

class Tank : public GameObject
{
    public:
        Tank(int size);
        Tank(const Tank& aTank);            // copy constructor
        virtual int GetSize() const;
        virtual int* GetPosition() const;

    private:
        Tank();
};

Tank::Tank(int size) : GameObject(size)
{
    cout << "\n|'Tank(int)' constructor|\n";
}

Tank::Tank(const Tank& aTank)
{
    cout << "\n|'Tank(Tank&)' copy constructor called|\n";
}

int Tank::GetSize() const
{
    return m_size;
}

int* Tank::GetPosition() const
{
    return m_p_position;
}

void Move(Tank aTank)
{
    cout << "\nMove() function called\n";
}



int main()
{
    GameObject* tank = new Tank(30);

    Tank* newTank = (Tank*)tank;
    Move(*newTank);

    cin.ignore();
    return 0;
}