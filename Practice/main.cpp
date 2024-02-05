#include <iostream>
#include "Monster.h"
#include "MonsterArena.h"

int main()
{
    Monster m1("물", 100, 30, 10, "WATER");
    Monster m2("불", 100, 40, 20, "FIRE");
    Monster m3("바람", 100, 50, 30, "WIND");
    Monster m4("땅", 100, 60, 40, "EARTH");
    Monster m5("불", 100, 60, 40, "FIRE");

    MonsterArena monsterArena(4);
    monsterArena.AddMonster(&m1);
    monsterArena.AddMonster(&m2);
    monsterArena.AddMonster(&m3);
    monsterArena.AddMonster(&m4);
    monsterArena.AddMonster(&m5);
    monsterArena.Play();
}
