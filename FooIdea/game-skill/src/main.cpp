#include <iostream>
#include "../include/skills.h"
using namespace std;
int main()
{
    //init
    wind wi(10, 1);
    fire fi(15, 2);
    water wa(8, 3);
    thunder th(18, 4);
    skill_list list;
    list.add_skill(wi);
    list.add_skill(fi);
    list.add_skill(wa);
    list.add_skill(th);

    //input
    int id;
    cout << "input number to use skill:" << endl;
    cin >> id;

    auto e = list.use_skill(id);
    cout<<"get "<<e.get_damage()<<" damage!"<<endl;

    return 0;
}
