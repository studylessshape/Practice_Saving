#include <iostream>
#include <algorithm>
using namespace std;

int cross_river(int people[], int N)
{
    int total_time = 0;
    while(N >= 4)
    {
        total_time += min(
            // 最快的和次快的先过去，然后最快的把船送回来，即people[1] + people[0]
            // 然后最慢的两个人过去，次快的把船送回来，即people[N-1] + people[1]
            people[1] + people[0] + people[N-1] + people[1],

            // 最快的送最慢的人过去，然后最快把船送回来，即people[N-1] + people[0]
            // 最快的送次慢的人过去，然后最快把船送回来，即people[N-2] + people[0]
            people[N-1] + people[0] + people[N-2] + people[0]
        );
        // 每次循环送过去两个人，所以减二
        N-=2;
    }

    // 剩下的1-3个人，用最快的人送过去
    switch(N)
    {
        case 1:
            total_time += people[0];
            break;
        case 2:
            total_time += people[1];
            break;
        case 3:
            total_time += people[2] + people[0] + people[1];
            break;
    }
    return total_time;
}

int main()
{
    int T, N, people[1001];
    cin>>T;
    while(T--)
    {
        cin>>N;
        for(int i = 0;i < N;i ++)
        {
            cin>>people[i];
        }

        sort(people, people+N);

        cout<<cross_river(people, N)<<endl;
    }

    return 0;
}