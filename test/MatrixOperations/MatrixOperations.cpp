// Test file to test different operations on matrix

#include <iostream>
#include <array>
#include <sstream>

using namespace std;

// brick check
static const int BRICK_WIDTH = 3;
static const int BRICK_HEIGHT = 3;

// path algorithm check
static const int PATH_MATRIX_SIZE = 5; 

void BrickFormationCheck()
{
    array<int, BRICK_WIDTH * BRICK_HEIGHT> b1 = {2,2,2,
                                               3,3,3,
                                               4,4,4};
                                               

    array<int, BRICK_WIDTH * BRICK_HEIGHT> b2 = {1,1,1,
                                               5,5,5,
                                               6,6,6};
                                               

    array<int, 18> wall;

    int wallWidth = BRICK_WIDTH + BRICK_WIDTH;
    int wallHeight = BRICK_HEIGHT;

    cout << "--array b1:\n";
    for (int y = 0; y < BRICK_HEIGHT; ++y)
    {
        for (int x = 0; x < BRICK_WIDTH; ++x)
        {
            cout << b1[y * BRICK_WIDTH + x] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "--array b2:\n";
    for (int y = 0; y < BRICK_HEIGHT; ++y)
    {
        for (int x = 0; x < BRICK_WIDTH; ++x)
        {
            cout << b2[y * BRICK_WIDTH + x] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "--array Wall:\n";
    for (int y = 0; y < wallHeight; ++y)
    {
        for (int x = 0; x < wallWidth; ++x)
        {
            if (x < BRICK_WIDTH)
            {
                wall[y * wallWidth + x] = b1[y * BRICK_WIDTH + x];
                cout << wall[y * wallWidth + x] << " ";
            }
            else
            {
                wall[y * wallWidth + x] = b2[y * BRICK_WIDTH + (x - BRICK_WIDTH)];
                cout << wall[y * wallWidth + x] << " ";
            }
        }
        cout << endl;
    }

    wallWidth = BRICK_WIDTH;
    wallHeight = BRICK_HEIGHT + BRICK_HEIGHT;

    cout << endl;
    cout << "changed dimension\n";
    cout << endl;

    cout << "--array Wall:\n";
    for (int y = 0; y < wallHeight; ++y)
    {
        for (int x = 0; x < wallWidth; ++x)
        {
            if (y < BRICK_HEIGHT)
            {
                wall[y * wallWidth + x] = b1[y * BRICK_WIDTH + x];
                cout << wall[y * wallWidth + x] << " ";
            }
            else
            {
                wall[y * wallWidth + x] = b2[(y - BRICK_HEIGHT) * BRICK_WIDTH + x];
                cout << wall[y * wallWidth + x] << " ";
            }
        }
        cout << endl;
    }
}

int GetMIN(int a, int b)
{
    int min = a;
    if (b < min)
    {
        min = b;
    }

    return min;
}

void FloydAlgorithmCheck()
{
    array<int, PATH_MATRIX_SIZE * PATH_MATRIX_SIZE> sourceMatrix;
    array<int, PATH_MATRIX_SIZE * PATH_MATRIX_SIZE> resultMatrix;
    array<int, PATH_MATRIX_SIZE * PATH_MATRIX_SIZE> pathMatrix;

    // set source matrix
    for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
    {
        for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
        {
            if (y == x)
            {
                sourceMatrix[y * PATH_MATRIX_SIZE + x] = 0;
                pathMatrix[y * PATH_MATRIX_SIZE + x] = 0;
            }
            else
            {
                sourceMatrix[y * PATH_MATRIX_SIZE + x] = 99;
                pathMatrix[y * PATH_MATRIX_SIZE + x] = 0;
            }
        }
    }

    // sourceMatrix[0 * PATH_MATRIX_SIZE + 1] = 1;
    // sourceMatrix[0 * PATH_MATRIX_SIZE + 2] = 2;
    // sourceMatrix[1 * PATH_MATRIX_SIZE + 0] = 1;
    // sourceMatrix[1 * PATH_MATRIX_SIZE + 3] = 4;
    // sourceMatrix[2 * PATH_MATRIX_SIZE + 0] = 2;
    // sourceMatrix[2 * PATH_MATRIX_SIZE + 3] = 3;
    // sourceMatrix[2 * PATH_MATRIX_SIZE + 4] = 5;
    // sourceMatrix[3 * PATH_MATRIX_SIZE + 1] = 4;
    // sourceMatrix[3 * PATH_MATRIX_SIZE + 2] = 3;
    // sourceMatrix[4 * PATH_MATRIX_SIZE + 2] = 5;

    sourceMatrix[0 * PATH_MATRIX_SIZE + 1] = 1;
    sourceMatrix[0 * PATH_MATRIX_SIZE + 2] = 1;
    sourceMatrix[1 * PATH_MATRIX_SIZE + 0] = 1;
    sourceMatrix[1 * PATH_MATRIX_SIZE + 3] = 1;
    sourceMatrix[2 * PATH_MATRIX_SIZE + 0] = 1;
    sourceMatrix[2 * PATH_MATRIX_SIZE + 3] = 1;
    sourceMatrix[2 * PATH_MATRIX_SIZE + 4] = 1;
    sourceMatrix[3 * PATH_MATRIX_SIZE + 1] = 1;
    sourceMatrix[3 * PATH_MATRIX_SIZE + 2] = 1;
    sourceMatrix[4 * PATH_MATRIX_SIZE + 2] = 1;

    // draw source matrix
    cout << "  ";
    for (int i = 0; i < PATH_MATRIX_SIZE; ++i)
    {
        cout << i + 1 << "  ";
    }
    cout << endl;

    for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
    {
        cout << y + 1 << " ";
        for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
        {
            int value = sourceMatrix[y * PATH_MATRIX_SIZE + x];
            if (value < 10)
            {
                cout << "0" << value << " ";
            }
            else
            {
                cout << value << " ";
            }
        }
        cout << endl;
    }

    // action Floyd algorithm
    for (int k = 0; k < PATH_MATRIX_SIZE; ++k)
    {
        for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
        {
            for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
            {
                int value_0 = sourceMatrix[y * PATH_MATRIX_SIZE + x];
                int value_1 = sourceMatrix[y * PATH_MATRIX_SIZE + k];
                int value_2 = sourceMatrix[k * PATH_MATRIX_SIZE + x];

                if (value_1 + value_2 < value_0)
                {  
                    resultMatrix[y * PATH_MATRIX_SIZE + x] = value_1 + value_2;
                    pathMatrix[y * PATH_MATRIX_SIZE + x] = k + 1;
                }
                else
                {
                    resultMatrix[y * PATH_MATRIX_SIZE + x] = value_0;
                }
            }
        }

        // new line
        cout << endl;

        // draw result matrix
        cout << "  ";
        for (int i = 0; i < PATH_MATRIX_SIZE; ++i)
        {
            cout << i + 1 << "  ";
        }
        cout << endl;
        for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
        {
            cout << y + 1 << " ";
            for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
            {
                int value = resultMatrix[y * PATH_MATRIX_SIZE + x];
                if (value < 10)
                {
                    cout << " " << value << " ";
                }
                else
                {
                    cout << value << " ";
                }
            }
            cout << endl;
        }

        // copy result matrix to source matrix
        for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
        {
            for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
            {
                sourceMatrix[y * PATH_MATRIX_SIZE + x] = resultMatrix[y * PATH_MATRIX_SIZE + x];
            }
        }
    }

    // new line
    cout << endl;

    // draw path matrix
    cout << "  ";
    for (int i = 0; i < PATH_MATRIX_SIZE; ++i)
    {
        cout << i + 1 << "  ";
    }
    cout << endl;
    for (int y = 0; y < PATH_MATRIX_SIZE; ++y)
    {
        cout << y + 1 << " ";
        for (int x = 0; x < PATH_MATRIX_SIZE; ++x)
        {
            int value = pathMatrix[y * PATH_MATRIX_SIZE + x];
            if (value < 10)
            {
                cout << " " << value << " ";
            }
            else
            {
                cout << value << " ";
            }
        }
        cout << endl;
    }

    // new line
    cout << endl;

    // draw optimal path
    int a = 2;
    int b = 5;

    if (resultMatrix[(a - 1) * PATH_MATRIX_SIZE + (b - 1)] == 99)
    {
        cout << a << " -> " << b << " no path";
    }
    else if (pathMatrix[(a - 1) * PATH_MATRIX_SIZE + (b - 1)] == 0)
        {
            cout << "path: " << a << " -> " << b << " = 0";
        }
        else
        {
            int k = pathMatrix[(a - 1) * PATH_MATRIX_SIZE + (b - 1)];
            std::stringstream ss;
            ss << k << " -> ";
            std::string path_string = ss.str();
            while (pathMatrix[(a - 1) * PATH_MATRIX_SIZE + (k - 1)] != 0)
            {
                ss.str("");
                ss << pathMatrix[(a - 1) * PATH_MATRIX_SIZE + (k - 1)] << " -> ";
                path_string.insert(0, ss.str());
                k = pathMatrix[(a - 1) * PATH_MATRIX_SIZE + (k - 1)];
            }
            cout << "path: " << a << " -> " << path_string << b << " = " << resultMatrix[(a - 1) * PATH_MATRIX_SIZE + (b - 1)];
        }



}

int main()
{
    
    // BrickFormationCheck();
    
    FloydAlgorithmCheck();




    cin.ignore();
    return 0;
}