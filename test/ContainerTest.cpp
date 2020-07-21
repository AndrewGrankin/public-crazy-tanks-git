// This is to try containers

#include <iostream>
#include <vector>

using namespace std;

class SimpleClass
{
    private:
        string m_name;
        int m_position;

    public:
        SimpleClass();
        SimpleClass(string name);
        ~SimpleClass();

        void SetName(string name);
        void SetPosition(int pos);
        string GetName();
        int GetPosition();
};

SimpleClass::SimpleClass()
{
    cout << "==/Default Constractor/ " << m_name << " created." << endl;
}

SimpleClass::SimpleClass(string name) : m_name(name)
{
    cout << "==/Custom Constructor/ " << m_name << " created." << endl;
}

SimpleClass::~SimpleClass()
{
    cout << "\n==/Destructor/ " << m_name << " deleted." << endl;
}

void SimpleClass::SetName(string name)
{
    m_name = name;
}

void SimpleClass::SetPosition(int pos)
{
    m_position = pos;
}

string SimpleClass::GetName()
{
    return m_name;
}

int SimpleClass::GetPosition()
{
    return m_position;
}

void Move(SimpleClass sc)
{
    sc.SetPosition(200);
    cout << sc.GetName() << " position: " << sc.GetPosition() << endl;
}

int main()
{

    SimpleClass* simClass0 = new SimpleClass("sClass0");
    simClass0->SetPosition(100);

    cout << endl;
    cout << simClass0->GetName() << " position: " << simClass0->GetPosition() << endl;
    cout << endl;
    Move(*simClass0);
    cout << endl;
    cout << simClass0->GetName() << " position: " << simClass0->GetPosition() << endl;

    // // vector<SimpleClass> simpleClassList(10);
    // vector<SimpleClass*> simpleClassList;
    // simpleClassList.reserve(10);
    // simpleClassList.push_back(sClass0);
    // cout << endl;
    // cout << "simpleClassList contains " << simpleClassList.size() << " elements." << endl;
    // cout << endl;
    // for (unsigned int i = 0; i < simpleClassList.size(); ++i)
    // {
    //     cout << "simpleClassList[" << i << "] = " <<  simpleClassList[i]->GetName() << endl;
    // }
    // cout << endl;
    // vector<SimpleClass*>::const_iterator iter;
    // for (iter = simpleClassList.begin(); iter != simpleClassList.end(); ++iter)
    // {
    //     cout << (*iter)->GetName() << endl;
    // }
    // cout << endl;




    delete simClass0;


    cin.ignore();
}