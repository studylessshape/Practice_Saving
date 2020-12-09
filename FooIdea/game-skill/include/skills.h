#include "skill_base.h"
class wind : public skill_base
{
public:
    wind(int damage, int id)
    {
        eff = effect(damage);
        skill_id = id;
        skill_name = "wind";
    }
};

class fire : public skill_base
{
public:
    fire(int damage, int id)
    {
        eff = effect(damage);
        skill_id = id;
        skill_name = "fire";
    }
};

class water : public skill_base
{
public:
    water(int damage, int id)
    {
        eff = effect(damage);
        skill_id = id;
        skill_name = "water";
    }
};

class thunder : public skill_base
{
public:
    thunder(int damage, int id)
    {
        eff = effect(damage);
        skill_id = id;
        skill_name = "thunder";
    }
};
