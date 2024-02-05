#ifndef MONSTER_H
#define MONSTER_H

#include <string>
using namespace std;

enum ElementalProperties
{
	FIRE,
	WATER,
	WIND,
	EARTH
};

class Monster
{
private:
	string name;
	int hp;
	int attack;
	int defense;
	ElementalProperties elemental;

public:
	Monster(string name, int hp, int attack, int defense, ElementalProperties elemental);
	Monster(string name, int hp, int attack, int defense, const string& elementalStr);
	~Monster();
	void TakeDamage(int demage);
	bool CheckAlive() const;
	void DoAttack(Monster* monster);
	void PrintMonster() const;

private:
	double CheckAdvantage(Monster*, Monster*) const;
	ElementalProperties StringToElemental(const string& elementalStr) const;
	string ElemToString() const;
};

#endif
