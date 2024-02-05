#ifndef MONSTER_ARENA_H
#define MONSTER_ARENA_H

#include "Monster.h"
#include <vector>

using namespace std;

class MonsterArena
{
private:
	int maxMonsters;
	vector<Monster*> monsters;

public:
	MonsterArena(int maxMonsters);
	~MonsterArena();
	void AddMonster(Monster* m);
	void PrintMonsters() const;
	void GoToRound();
	void Play();

private:
	bool IsMonsterAreanaAvailable() const;
};

#endif