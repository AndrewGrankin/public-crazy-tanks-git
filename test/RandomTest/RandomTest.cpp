// This is to test random number generation

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main()
{
    mt19937 generator;
    uniform_int_distribution<uint32_t> range(0, 100);

    // seed random number generator
    generator.seed(time(0));

    int randomNumber;
    for (int i = 0; i < 100; ++i)
    {
        randomNumber = range(generator);
        // cout << randomNumber << " | ";
        // cout << randomNumber % 10 << " | ";
        // cout << 10 - (randomNumber % 10) << " = ";
        // randomNumber = randomNumber + (10 - (randomNumber % 10));
        cout <<  randomNumber << endl;
    }




    cin.ignore();
    return 0;
}