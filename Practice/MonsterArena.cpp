#include "MonsterArena.h"
#include <iostream>

using namespace std;

MonsterArena::MonsterArena(int maxMonsters)
	:maxMonsters(maxMonsters)
{
	cout << "몬스터 아레나가 열렸습니다!" << endl;
}

MonsterArena::~MonsterArena()
{
}

void MonsterArena::AddMonster(Monster* m)
{
	if (monsters.size() >= maxMonsters)
	{
		cout << "아레나의 몬스터 허용치를 초과하여 추가할 수 없습니다." << endl;
		return;
	}

	monsters.push_back(m);
	cout << "몬스터가 추가되었습니다" << endl;
}

void MonsterArena::PrintMonsters() const
{
	if (monsters.size() < 1)
	{
		cout << "아레나에 몬스터가 존재하지 않습니다." << endl;
		return;
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		monsters.at(i)->PrintMonster();
	}
}

bool MonsterArena::IsMonsterAreanaAvailable() const
{
	return monsters.size() > 1;
}

void MonsterArena::GoToRound()
{
	for (int i = 0; i < monsters.size() - 1; ++i)
	{
		Monster* attacker = monsters.at(i);
		Monster* target = monsters.at(i + 1);

		attacker->DoAttack(target);

		if (!target->CheckAlive())
		{
			monsters.erase(monsters.begin() + i + 1);
			--i;
		}
	}

	// 배열 마지막에 있는 몬스터는 맨 앞에 있는 몬스터를 때림
	Monster* lastMonster = monsters.back();
	Monster* firstMonster = monsters.front();

	lastMonster->DoAttack(firstMonster);

	if (!firstMonster->CheckAlive())
	{
		monsters.erase(monsters.begin());
	}
}

void MonsterArena::Play()
{
	if (monsters.empty())
	{
		cout << "아레나에 몬스터들이 준비되지 않았습니다!" << endl;
		return;
	}

	cout << "몬스터 아레나가 시작됩니다!" << endl;

	while (IsMonsterAreanaAvailable())
	{
		cout << endl;
		cout << "================================" << endl;
		GoToRound();
		PrintMonsters();
		cout << "================================" << endl;
	}

	cout << "몬스터 아레나가 종료됩니다!" << endl;
	cout << "승자 몬스터를 소개합니다!" << endl;
	monsters.front()->PrintMonster();
}