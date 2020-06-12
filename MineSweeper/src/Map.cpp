#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Map.h"
Map::Map() : map_size(9)
{
    //��ʼ����ͼ
    for (int i = 0; i < map_size; i++)
        for (int j = 0; j < map_size; j++)
            map[i][j] = 0;
    //��ʼ����ӡ�о�
    for (int i = 0; i < map_size; i++)
        for (int j = 0; j < map_size; j++)
            is_open[i][j] = false;

    srand((unsigned int)time(NULL));
    int count = 0;
    while(count < 10)
    {
        //�������һ����������
        int x = rand() % 9;
        int y = rand() % 9;
        if (map[x][y] == 0)//�����Ա�8���㣬���ǵ��׵���Ҫ�����ּ�1
        {
            count++;
            map[x][y] = BOOM;

        }
    }
    for(int x = 0; x < map_size; x ++)
    {
        for(int y = 0; y < map_size; y ++)
        {
            if(map[x][y] == BOOM)//�����Ա�8���㣬���ǵ��׵���Ҫ�����ּ�1
            {
                if (x != 0)
                {
                    map[x - 1][y] = map[x - 1][y] == BOOM ? BOOM : map[x - 1][y] + 1;
                }

                if (y != 0)
                {
                    map[x][y - 1] = map[x][y - 1] == BOOM ? BOOM : map[x][y - 1] + 1;
                }

                if (x != map_size - 1)
                {
                    map[x + 1][y] = map[x + 1][y] == BOOM ? BOOM : map[x + 1][y] + 1;
                }

                if (y != map_size - 1)
                {
                    map[x][y + 1] = map[x][y + 1] == BOOM ? BOOM : map[x][y + 1] + 1;
                }

                if (x != 0 && y != 0)
                {
                    map[x - 1][y - 1] = map[x - 1][y - 1] == BOOM ? BOOM : map[x - 1][y - 1] + 1;
                }

                if (x != 0 && y != map_size - 1)
                {
                    map[x - 1][y + 1] = map[x - 1][y +1] == BOOM ? BOOM : map[x - 1][y + 1] + 1;
                }

                if (x != map_size - 1 && y != 0)
                {
                    map[x + 1][y - 1] = map[x + 1][y - 1] == BOOM ? BOOM : map[x + 1][y - 1] + 1;
                }

                if (x != map_size - 1 && y != map_size - 1)
                {
                    map[x + 1][y + 1] = map[x + 1][y + 1] == BOOM ? BOOM : map[x + 1][y + 1] + 1;
                }
            }
        }
    }
    open_number = 9 * 9;
}

void Map::PrintMap()
{
    //��ӡ������
    std::cout << "  |";
    for (int i = 1; i <= 9; i++)
        std::cout << " " << i << " ";
    std::cout << std::endl;
    for (int i = 1; i <= 30; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < map_size; i++)
    {
        //��ӡ������
        std::cout << " " << i + 1<< "|";
        for (int j = 0; j < map_size; j++)
        {
            //��ӡ��ͼ
            if (map[i][j] == BOOM)
            {
                std::cout << " "<<HIDE<<" ";
            }
            else
            {
                if (is_open[i][j])
                {
                    if (map[i][j] < 10)
                        std::cout << " ";
                    std::cout << map[i][j] << " ";
                }
                else
                {
                    std::cout << " " << HIDE << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void Map::PrintMap(OpenPointType res)
{
    if (res == Number)
    {
        PrintMap();
        return;
    }

    //��ӡ������
    std::cout << "  |";
    for (int i = 1; i <= 9; i++)
        std::cout << " " << i << " ";
    std::cout << std::endl;
    for (int i = 1; i <= 30; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < map_size; i++)
    {
        //��ӡ������
        std::cout << " " << i + 1 << "|";
        for (int j = 0; j < map_size; j++)
        {
            //��ӡ��ͼ
            if (map[i][j] == BOOM)
            {
                std::cout << " * ";
            }
            else
            {
                if (map[i][j] < 10)
                    std::cout << " ";
                std::cout << map[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int Map::length()
{
    return map_size;
}

OpenPointType Map::OpenPoint(int x, int y)
{
    if (open_number == 10)
    {
        return win;
    }
    if (x < 0 || x >= map_size)
        return Error;
    if (y < 0 || y >= map_size)
        return Error;
    if (is_open[x][y])
        return Error;

    if (map[x][y] == BOOM)
    {
        return Boom;
    }
    is_open[x][y] = true;
    open_number--;
    if (map[x][y] == 0)
    {
        OpenPoint(x - 1, y);
        OpenPoint(x, y - 1);
        OpenPoint(x + 1, y);
        OpenPoint(x, y + 1);
        OpenPoint(x - 1, y - 1);
        OpenPoint(x - 1, y + 1);
        OpenPoint(x + 1, y - 1);
        OpenPoint(x + 1, y + 1);
    }
    if (open_number == 10)
    {
        return win;
    }
    else
    {
        return Number;
    }
}
