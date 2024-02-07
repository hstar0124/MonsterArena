#include "MonsterArena.h"
#include <iostream>
#include <string>

using namespace std;

MonsterArena::MonsterArena()
	:maxMonsters(0)
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

bool MonsterArena::IsMonsterArenaAvailable() const
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

void MonsterArena::Init()
{
	cout << "몬스터 아레나에 오신 것을 환영합니다!" << endl;

	int inputMaxMonster = -999;
	do {
		cout << "몬스터 아레나에 참가할 몬스터 숫자를 입력해주세요(ex : 1 ~ 10) >> ";
		cin >> inputMaxMonster;
	} while (inputMaxMonster < 1 || inputMaxMonster > 10);

	maxMonsters = inputMaxMonster;

	for (int i = 0; i < maxMonsters; i++)
	{
		string name;
		int health, attack, defense;
		string element;

		cout << "몬스터 " << i + 1 << "의 이름을 입력하세요: ";
		cin >> name;
		cout << "몬스터 " << i + 1 << "의 체력을 입력하세요: ";
		cin >> health;
		cout << "몬스터 " << i + 1 << "의 공격력을 입력하세요: ";
		cin >> attack;
		cout << "몬스터 " << i + 1 << "의 방어력을 입력하세요: ";
		cin >> defense;
		cout << "몬스터 " << i + 1 << "의 속성을 입력하세요(FIRE,WATER,EARTH,WIND): ";
		cin >> element;

		Monster* monster = new Monster(name, health, attack, defense, element);
		AddMonster(monster);
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

	while (IsMonsterArenaAvailable())
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