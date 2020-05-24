#include <stack>
#include "../include/GraphMatrix.h"

GraphMatrix::GraphMatrix()
{
    matrix = NULL;
    m_size = 0;
}

GraphMatrix::GraphMatrix(int Size)
{
    m_size = Size;
    matrix = new int*[m_size];
    for(int i = 0;i < m_size;i ++)
        matrix[i] = new int[m_size];
    for(int i = 0;i < m_size;i ++)
    {
        for(int j = 0;j < m_size;j ++)
        {
            if(i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }
    }
}

GraphMatrix::~GraphMatrix()
{
    for(int i = 0;i < m_size;i ++)
        delete[] matrix[i];
    delete[] matrix;
}

bool GraphMatrix::CombinePoint(int a, int b)
{
    bool isCombine = false;
    if(a<=0||a>m_size||b<=0||b>m_size||a==b)
    {
        std::cout<<"Error index!"<<std::endl;
        return isCombine;
    }

    if((matrix[a-1][b-1] != 0 || matrix[b-1][a-1] != 0) && (matrix[a-1][b-1] != INF || matrix[b-1][a-1] != INF))
    {
        std::cout<<"Have combined point "<<a<<","<<b<<"!"<<std::endl;
        return isCombine;
    }
    isCombine = true;
    matrix[a-1][b-1] = 1;
    matrix[b-1][a-1] = 1;
    return isCombine;
}

bool GraphMatrix::CombinePoint(int a, int b, int power)
{
    bool isCombine = false;
    if(a<=0||a>m_size||b<=0||b>m_size||a==b)
    {
        std::cout<<"Error index!"<<std::endl;
        return isCombine;
    }

    if(power==0)
    {
        std::cout<<"Power can't be zero!"<<std::endl;
        return isCombine;
    }

    if((matrix[a-1][b-1] != 0 || matrix[b-1][a-1] != 0) && (matrix[a-1][b-1] != INF || matrix[b-1][a-1] != INF))
    {
        std::cout<<"Have combined point "<<a<<","<<b<<"!"<<std::endl;
        return isCombine;
    }
    isCombine = true;
    matrix[a-1][b-1] = power;
    matrix[b-1][a-1] = power;
    return isCombine;
}

void GraphMatrix::PrintAll()
{
    /*for(int i = 0;i <= m_size;i ++)
    {
        std::cout<<i;
        if(i!=m_size)
            std::cout<<"|";
    }
    std::cout<<std::endl;
    for(int i = 0;i <= m_size;i ++)
    {
        std::cout<<"--";
    }
    std::cout<<std::endl;*/

    for(int i = 0;i < m_size;i ++)
    {
        //std::cout<<i+1<<"|";
        for(int j = 0;j < m_size;j ++)
        {
            /*if(matrix[i][j] == INF)
                std::cout<<"-1 ";
            else*/
                std::cout<<matrix[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }
}

void GraphMatrix::DFS(int start_index)
{
    if(start_index<=0 || start_index>m_size)
    {
        std::cout<<"Error index!Can't DFS!"<<std::endl;
        return;
    }
    std::stack<int> node;
    int visit[m_size] = {0};
    int current, i;
    int *go = NULL;

    std::cout<<"DFS Matrix: "<<start_index<<" ";
    visit[start_index-1]=1;
    node.push(start_index);
    while(!node.empty())
    {
        current = node.top();
        go = matrix[current-1];
        for(i = 0;i < m_size;i ++)
        {
            if(!visit[i] && i != current - 1 && (go[i] != 0 || go[i] != INF))
            {
                std::cout<<i+1<<" ";
                visit[i] = 1;
                node.push(i + 1);
                break;
            }
        }
        if(i==m_size)
        {
            node.pop();
        }
    }
    std::cout<<std::endl;
}

void GraphMatrix::Prim(int start_index)//在GraphMatrix类中的Prim函数
{
    if(start_index<0||start_index>=m_size)
    {
        std::cout<<"Error index!"<<std::endl;
        return;
    }
    int lowcost[m_size]; //储存相关顶点的最小路径
    int lowcostpoint;//记录最小权值对应顶点
    int min;//方便之后选择最小权值
    
    bool visit[m_size];//判断节点有没有被访问
    for(int i = 0;i < m_size;i ++)//初始化访问数组
        visit[i] = false;
    int cont = 0;//计数
    int adjvex[m_size];//储存相关顶点
    int V[m_size];//储存访问顺序
    

    V[cont] = start_index;//添加开始节点
    visit[start_index-1] = true;
    cont++;

    int sum = 0;//总权值
    for(int i = 0;i < m_size;i ++)
    {
        lowcost[i] = matrix[start_index-1][i];
        adjvex[i] = start_index - 1;
    }

    for(int i = 1;i < m_size;i ++)//因为第一个点已经访问，为了防止用cont访问V越界，所以把i=0改成了i=1
    {
        min = INF;
        for(int j = 0;j < m_size;j ++)//寻找lowcost的最小值和对应点
        {
            if(min > lowcost[j] && !visit[j] && lowcost[i] != 0)
            {
                min = lowcost[j];
                lowcostpoint = j;
            }
        }
        sum += lowcost[lowcostpoint];
        visit[lowcostpoint] = true;
        V[cont] = lowcostpoint + 1;
        cont++;
        for(int j = 0;j < m_size;j ++)
        {
            if(!visit[j])
            {
                min = INF;
                for(int k = 0;k < m_size;k ++)//对于未访问的单个节点，寻找与被访问的节点权值最小的节点
                {
                    if(min > matrix[j][k] && visit[k])//需要的是已经访问的节点
                    {
                        min = matrix[j][k];
                        adjvex[j] = k;//需要生成树的话这里很有必要
                    }
                }
                lowcost[j] = min;
            }
            else//已经访问的，lowcost置为INF
            {
                lowcost[j] = INF;
            }
        }
    }
    std::cout<<sum;
    std::cout<<std::endl;

    for(int i = 0;i < m_size;i ++)
    {
        std::cout<<V[i]<<" ";
    }
    std::cout<<std::endl;
}