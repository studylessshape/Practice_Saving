#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H
#include <cstddef>
#include <iostream>
#include "GraphDefine.h"

class GraphMatrix
{
    public:
        GraphMatrix();
        GraphMatrix(int Size);
        virtual ~GraphMatrix();

        bool CombinePoint(int a, int b);
        bool CombinePoint(int a, int b, int power);

        void PrintAll();
        void DFS(int start_index);

        void Prim(int start_index);
    private:
        int **matrix;
        int m_size;

};

#endif // GRAPHMATRIX_H
