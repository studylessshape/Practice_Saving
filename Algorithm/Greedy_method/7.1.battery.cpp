#include<iostream>
#include<iomanip>
using namespace std;

float calculate_longest_life(int sum, int max_life)
{
    if(max_life > sum)
        return sum;
    return (float)(sum + max_life) / 2.0;
}

int main()
{
    int ba, n;
    int sum = 0, max_life = 0;
    // 设置输出位数
    cout<<setiosflags(ios_base::fixed)<<setprecision(1);
    while(cin>>n)
    {
        while(n--)
        {
            cin>>ba;
            if(max_life < ba)
            {
                // 如果比当前值大，就把之前没有加的值加上，然后记录当前值
                sum += max_life;
                max_life = ba;
            }
            else
            {
                // 将比最大电池寿命小的电池加到总和
                sum += ba;
            }
        }
        cout<<calculate_longest_life(sum, max_life)<<endl;
        // 每计算完一次结果记得清零
        max_life = 0;
        sum = 0;
    }
}