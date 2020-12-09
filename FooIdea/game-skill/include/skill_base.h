#include <iostream>
#include <string>
#include <vector>

using namespace std;

class effect
{
private:
    int damage;

public:
    effect()
    {
        damage = 0;
    }
    effect(int set_damage) : damage(set_damage)
    {
    }
    int get_damage()
    {
        return damage;
    }
};

class skill_base
{
protected:
    int skill_id;
    string skill_name;
    effect eff;

public:
    virtual effect use_skill()
    {
        cout << "use skill " << skill_name << endl;
        return eff;
    }
    int get_id()
    {
        return skill_id;
    }
};

class skill_list
{
private:
    vector<skill_base> skills;

public:
    void add_skill(skill_base skill)
    {
        skills.push_back(skill);
    }

    void rm_skill(int skill_id)
    {
        for (auto i = skills.begin(); i != skills.end(); i++)
        {
            if (i->get_id() == skill_id)
            {
                skills.erase(i, i);
                break;
            }
        }
    }

    effect use_skill(int id)
    {
        effect e;
        for (auto i : skills)
        {
            if (i.get_id() == id)
            {
                e = i.use_skill();
            }
        }
        return e;
    }
};
