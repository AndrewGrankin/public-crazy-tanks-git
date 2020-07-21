// Test programm to calculate nodes and routes with graphics

#define NOMINMAX

#include <windows.h>
#include <iostream>
#include <array>
#include <limits>
#include <cmath>
#include <random>

#include <NodeVO.h>

typedef unsigned char uint8;
typedef unsigned int uint32;
static const int MATRIX_WIDTH = 150;
static const int MATRIX_HEIGHT = 150;
static const int TANK_SIZE = 20;
static const uint16_t STEP = 5;
// static const int MAX_INT = std::numeric_limits<int>::max();
static const uint16_t MAX_NUMBER = 65535;
static const int NODES_WIDTH = (MATRIX_WIDTH - TANK_SIZE + STEP) / STEP;
static const int NODES_HEIGHT = (MATRIX_HEIGHT - TANK_SIZE + STEP) / STEP;
static const int NODES_NUMBER = NODES_WIDTH * NODES_HEIGHT;

std::array<NodeVO*, NODES_NUMBER> nodesArray;
std::array<int, NODES_NUMBER * NODES_NUMBER> nodesAdjacencyMatrix;
std::array<int, NODES_NUMBER * NODES_NUMBER> nodesWeightMatrix;
std::array<int, NODES_NUMBER * NODES_NUMBER> nodesPathMatrix;


BITMAPINFO BitmapInfo;

struct DrawBuffer
{
   HBITMAP DIBBitmap;
   void* Memory;
   int Width;
   int Height;
   uint32 BytesPerPixel;
   uint32 Pitch;
};

void FillBuffer(DrawBuffer* Buffer, uint32 Color)
{
   uint8* Row = (uint8*)Buffer->Memory;
   for(int y = 0; y < Buffer->Height; ++y)
   {
      uint32 *Pixel = (uint32*)Row;
      for(int x = 0; x < Buffer->Width; ++x)
      {
         *Pixel++ = Color;
      }
      Row += Buffer->Pitch;
   }
}

void DrawLine(DrawBuffer* Buffer, int startX, int startY, int endX, int endY, uint32 lineColor)
{
      int lengthX = abs(endX - startX);
      int lengthY = abs(endY - startY);

      uint8* p_row;
      uint32* p_pixel;

       // draw start line point
      p_row = (uint8*)Buffer->Memory;
      p_pixel = (uint32*)p_row;
      p_pixel += startY * Buffer->Width + startX;
      *p_pixel = lineColor;   

      if (lengthX > lengthY)
      {
            // find coords for each X
            
            int trueStartX = startX;
            int trueEndX = endX;
            if (startX > endX)
            {
                  trueStartX = endX;
                  trueEndX = startX;
            }
                                                           
            for (int x = trueStartX + 1; x < trueEndX; ++x)
            {
                  int y = startY + (x - startX) * (endY - startY) / (endX - startX);

                  // draw line point
                  p_row = (uint8*)Buffer->Memory;
                  p_pixel = (uint32*)p_row;
                  p_pixel += y * Buffer->Width + x;
                  *p_pixel = lineColor; 
            }     
      }
      else
      {
            // find coords for each Y

            int trueStartY = startY;
            int trueEndY = endY;
            if (startY > endY)
            {
                  trueStartY = endY;
                  trueEndY = startY;
            }

            for (int y = trueStartY + 1; y < trueEndY; ++y)
            {
                  int x = startX + (endX - startX) * (y - startY) / (endY - startY);

                  // draw line point
                  p_row = (uint8*)Buffer->Memory;
                  p_pixel = (uint32*)p_row;
                  p_pixel += y * Buffer->Width + x;
                  *p_pixel = lineColor; 
            }
      }

      // draw end line point
      p_row = (uint8*)Buffer->Memory;
      p_pixel = (uint32*)p_row;
      p_pixel += endY * Buffer->Width + endX;
      *p_pixel = lineColor; 
}

void DrawRectangle(DrawBuffer* Buffer, int rect_x, int rect_y, int rect_width, int rect_height, uint32 rect_color)
{
	uint8* p_row = (uint8*)Buffer->Memory;
	p_row += (Buffer->Pitch * rect_y);
	for (int y = rect_y; y < rect_height + rect_y; ++y)
	{
		uint32* p_pixel = (uint32*)p_row;
		p_pixel += rect_x;
		for (int x = rect_x; x < rect_width + rect_x; ++x)
		{	
			*p_pixel = rect_color;
			++p_pixel;
		}
		p_row += Buffer->Pitch;
	}
}

void UpdateWindow(HDC DeviceContext, DrawBuffer* Buffer)
{

   StretchDIBits(DeviceContext, 250, 50, Buffer->Width, Buffer->Height,
                 0, 0, Buffer->Width, Buffer->Height, Buffer->Memory,
                 &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

int main()
{
    HWND consoleWindow = GetConsoleWindow();
    HDC deviceContext = GetDC(consoleWindow);
    DrawBuffer Buffer;

    Buffer.Width = MATRIX_WIDTH;
    Buffer.Height = MATRIX_HEIGHT;
    Buffer.BytesPerPixel = sizeof(uint32);
    Buffer.Pitch = Buffer.Width * Buffer.BytesPerPixel;

    uint32 BufferSize = Buffer.Width * Buffer.Height * Buffer.BytesPerPixel;
    Buffer.Memory = VirtualAlloc(0, BufferSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);

    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = Buffer.Width;
    BitmapInfo.bmiHeader.biHeight = -Buffer.Height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    //======================================================

    std::cout << "NODES: " << NODES_NUMBER;
    std::cout << std::endl;
    std::cout << "MAX: " << RAND_MAX;
    std::cout << std::endl;
    std::cout << "SizeOf(int): " << sizeof(int);
    std::cout << std::endl;
    std::cout << "SizeOf(POINT): " << sizeof(POINT);
    std::cout << std::endl;
    std::cout << "SizeOf(bool): " << sizeof(bool);
    std::cout << std::endl;
    std::cout << "SizeOf(uint32_t): " << sizeof(uint32_t);
    std::cout << std::endl << std::endl;
    

    //NOTE: 0x00RRGGBB - RR - red byte, GG - green byte, BB - blue byte
    uint32 ColorBlue = 0x000000ff;
    uint32 ColorAmber = 0x00ffbf00;
    uint32 ColorLight = 0x0000c0ff;
    uint32 ColorRed = 0x00ff0000;

    FillBuffer(&Buffer, ColorBlue);

    // fill nodes array with nodeVO objects
    uint16_t coordX = 0;
    uint16_t coordY = 0;
    NodeVO* p_nodeVO;

    for (uint16_t y = 0; y < NODES_HEIGHT; ++y)
    {
        for (uint16_t x = 0; x < NODES_WIDTH; ++x)
        {
            p_nodeVO = new NodeVO();
            p_nodeVO->SetNodeNumber((y * NODES_WIDTH + x) + 1);   // we start nodes count from 1 for valid path building
            p_nodeVO->SetNodeCoords(coordX, coordY);
            p_nodeVO->SetAccess(true);
            p_nodeVO->SetColor(ColorAmber);
            nodesArray[y * NODES_WIDTH + x] = p_nodeVO;

            // for test
            // std::cout << (y * NODES_WIDTH + x) << " ";

            coordX += STEP;
        }

        // for test
        // std::cout << std::endl;

        coordX = 0;
        coordY += STEP;
    } 

    NodeVO* p_falseAccessNode = nodesArray[5];
    p_falseAccessNode->SetAccess(false);
    p_falseAccessNode = nodesArray[6];
    p_falseAccessNode->SetAccess(false);
    p_falseAccessNode = nodesArray[12];
    p_falseAccessNode->SetAccess(false);
    p_falseAccessNode = nodesArray[13];
    p_falseAccessNode->SetAccess(false);
    p_falseAccessNode = nodesArray[14];
    p_falseAccessNode->SetAccess(false);
    p_falseAccessNode = nodesArray[15];
    p_falseAccessNode->SetAccess(false);
    // p_falseAccessNode = nodesArray[38];
    // p_falseAccessNode->SetAccess(false);

    std::cout << std::endl;  

    // draw each nodeVO on the screen
    for (uint16_t y = 0; y < NODES_HEIGHT; ++y)
    {
        for (uint16_t x = 0; x < NODES_WIDTH; ++x)
        {
            NodeVO* p_checkNode = nodesArray[y * NODES_WIDTH + x];
            DrawRectangle(&Buffer, p_checkNode->GetNodeCoordX(), p_checkNode->GetNodeCoordY(), 2, 2, p_checkNode->GetColor());
            // std::cout << p_checkNode->GetNodeNumber() << "(" << p_checkNode->GetNodeCoords().x << ";" << p_checkNode->GetNodeCoords().y << ") ";
        }
        // std::cout << std::endl;
    } 


    // constructing the nodes adjacency matrix
    for (uint16_t i = 0; i < NODES_NUMBER; ++i)
    {
        for (uint16_t j = 0; j < NODES_NUMBER; ++j)
        {
            if (i == j)
            {
                nodesAdjacencyMatrix[i * NODES_NUMBER + j] = 0;
            }
            else
            {
                NodeVO* p_i_Node = nodesArray[i];
                NodeVO* p_j_Node = nodesArray[j];
                if (p_i_Node->IsAccessible() && p_j_Node->IsAccessible())
                {
                    
                    uint16_t node_i_x = p_i_Node->GetNodeCoordX();
                    uint16_t node_i_y = p_i_Node->GetNodeCoordY();
                    uint16_t node_j_x = p_j_Node->GetNodeCoordX();
                    uint16_t node_j_y = p_j_Node->GetNodeCoordY();

                    if ( (abs(node_j_x - node_i_x) == STEP && node_j_y - node_i_y == 0) 
                      || (abs(node_j_y - node_i_y) == STEP && node_j_x - node_i_x == 0) )
                    {
                        nodesAdjacencyMatrix[i * NODES_NUMBER + j] = 1;
                    }
                    else
                    {
                        nodesAdjacencyMatrix[i * NODES_NUMBER + j] = MAX_NUMBER;    
                    }
                }
                else
                {
                    nodesAdjacencyMatrix[i * NODES_NUMBER + j] = MAX_NUMBER;
                }
            }
        }
    }

    std::cout << std::endl;


    // // display nodes adjacency matrix
    // std::cout << "   ";
    // for (int i = 0; i < NODES_NUMBER; ++i)
    // {
    //     if (i + 1 >= 10)
    //     {
    //         std::cout << i + 1 << " ";
    //     }
    //     else
    //     {
    //         std::cout << i + 1 << "  ";
    //     }
    // }
    // std::cout << std::endl;
    // for (int i = 0; i < NODES_NUMBER; ++i)
    // {
    //     if (i + 1 < 10)
    //     {
    //         std::cout << " " << i + 1 << " ";
    //     }
    //     else
    //     {
    //         std::cout << i + 1 << " ";
    //     }
    //     for (int j = 0; j < NODES_NUMBER; ++j)
    //     {   
    //         if (nodesAdjacencyMatrix[i * NODES_NUMBER + j] == MAX_NUMBER)
    //         {
    //             std::cout << "9" << "  ";
    //         }
    //         else
    //         {
    //             std::cout << nodesAdjacencyMatrix[i * NODES_NUMBER + j] << "  ";
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    
    // draw lines for connected nodes
    for (uint16_t i = 0; i < NODES_NUMBER; ++i)
    {
        for (uint16_t j = 0; j < NODES_NUMBER; ++j)
        {   
            if (nodesAdjacencyMatrix[i * NODES_NUMBER + j] == 1)
            {
                NodeVO* p_i_Node = nodesArray[i];
                NodeVO* p_j_Node = nodesArray[j];
                uint16_t node_i_x = p_i_Node->GetNodeCoordX();
                uint16_t node_i_y = p_i_Node->GetNodeCoordY();
                uint16_t node_j_x = p_j_Node->GetNodeCoordX();
                uint16_t node_j_y = p_j_Node->GetNodeCoordY();
                DrawLine(&Buffer, node_i_x, node_i_y, node_j_x, node_j_y, 0x00ff0000);
            }
        }
    }

    // action Floyd algorithm
    for (uint16_t k = 0; k < NODES_NUMBER; ++k)
    {
        for (uint16_t y = 0; y < NODES_NUMBER; ++y)
        {
            for (uint16_t x = 0; x < NODES_NUMBER; ++x)
            {
                uint16_t value_0 = nodesAdjacencyMatrix[y * NODES_NUMBER + x];
                uint16_t value_1 = nodesAdjacencyMatrix[y * NODES_NUMBER + k];
                uint16_t value_2 = nodesAdjacencyMatrix[k * NODES_NUMBER + x];

                if (value_1 + value_2 < value_0)
                {  
                    nodesWeightMatrix[y * NODES_NUMBER + x] = value_1 + value_2;
                    nodesPathMatrix[y * NODES_NUMBER + x] = k + 1;
                }
                else
                {
                    nodesWeightMatrix[y * NODES_NUMBER + x] = value_0;
                }
            }
        }

        // // new line
        // std::cout << std::endl;

        // // draw result matrix
        // std::cout << "  ";
        // for (uint16_t i = 0; i < NODES_NUMBER; ++i)
        // {
        //     std::cout << i + 1 << "  ";
        // }
        // std::cout << std::endl;
        // for (uint16_t y = 0; y < NODES_NUMBER; ++y)
        // {
        //     std::cout << y + 1 << " ";
        //     for (uint16_t x = 0; x < NODES_NUMBER; ++x)
        //     {
        //         uint16_t value = nodesWeightMatrix[y * NODES_NUMBER + x];
        //         if (value < 10)
        //         {
        //             std::cout << " " << value << " ";
        //         }
        //         else
        //         {
        //             std::cout << value << " ";
        //         }
        //     }
        //     std::cout << std::endl;
        // }

        // copy result matrix to source matrix
        for (uint16_t y = 0; y < NODES_NUMBER; ++y)
        {
            for (uint16_t x = 0; x < NODES_NUMBER; ++x)
            {
                nodesAdjacencyMatrix[y * NODES_NUMBER + x] = nodesWeightMatrix[y * NODES_NUMBER + x];
            }
        }
    }
    
    UpdateWindow(deviceContext, &Buffer);

    


    std::cin.ignore();
    return 0;
}