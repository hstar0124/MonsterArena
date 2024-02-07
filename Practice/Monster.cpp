#include "Monster.h"
#include <iostream>
#include <string>

using namespace std;

const double ADVANTAGE_MULTIPLIER = 2.0;
const double NORMAL_MULTIPLIER = 1.0;
const double WEAKNESS_MULTIPLIER = 0.5;

Monster::Monster(string name, int hp, int attack, int defense, ElementalProperties elemental)
	:name(name), hp(hp), attack(attack), defense(defense), elemental(elemental)
{
	if (hp < 0 || attack < 0 || defense < 0)
	{
		cout << "몬스터 초기화 값이 잘못되었습니다." << endl;
		// TODO : 에러제어
	}
}

Monster::Monster(string name, int hp, int attack, int defense, const string& elementalStr)
	:name(name), hp(hp), attack(attack), defense(defense), elemental(StringToElemental(elementalStr)) 
{
	if (hp < 0 || attack < 0 || defense < 0)
	{
		cout << "몬스터 초기화 값이 잘못되었습니다." << endl;
		// TODO : 에러제어
	}
}

Monster::~Monster()
{
}

void Monster::TakeDamage(int demage)
{
	if (demage < 0)
	{
		cout << "데미지 값이 잘못되었습니다." << endl;
		return;
	}

	hp -= demage;
}

bool Monster::CheckAlive() const
{
	return hp > 0;
}

void Monster::DoAttack(Monster* m) 
{
	// 최소 데미지는 1, (공격력 - 방어력) * 속성 보정치
	int demage = (this->attack - m->defense) * CheckAdvantage(this, m);
	if (demage < 1)
	{
		demage = 1;
	}
	cout << this->name << " 이(가) " << m->name << " 에게 " << demage << "의 데미지를 입힙니다!" << endl;
	m->TakeDamage(demage);
}

void Monster::PrintMonster() const
{
	cout << "================================" << endl;
	cout << "몬스터 상태" << endl;
	cout << "NAME : " << name << endl;
	cout << "HP : " << hp << endl;
	cout << "ATK : " << attack << endl;
	cout << "DEF : " << defense << endl;
	cout << "ELEM : " << ElemToString() << endl;
	cout << "================================" << endl;
}

string Monster::ElemToString() const
{
	switch (elemental)
	{
	case FIRE:
		return "FIRE";
	case WATER:
		return "WATER";
	case WIND:
		return "WIND";
	case EARTH:
		return "EARTH";
	default:
		return "UNKNOWN";
	}
}

double Monster::CheckAdvantage(Monster* attacker, Monster* defender) const
{
	ElementalProperties attackerElem = attacker->elemental;
	ElementalProperties defenderElem = defender->elemental;

	// 공격자와 방어자의 속성에 따라 강점 계산
	if ((attackerElem == FIRE && defenderElem == EARTH) ||
		(attackerElem == EARTH && defenderElem == WIND) ||
		(attackerElem == WIND && defenderElem == WATER) ||
		(attackerElem == WATER && defenderElem == FIRE))
	{
		// 공격자의 속성이 방어자에게 강함
		cout << "공격이 효과적입니다!" << endl;
		return ADVANTAGE_MULTIPLIER;
	}
	else if ((attackerElem == FIRE && defenderElem == WATER) ||
		(attackerElem == EARTH && defenderElem == FIRE) ||
		(attackerElem == WIND && defenderElem == EARTH) ||
		(attackerElem == WATER && defenderElem == WIND))
	{
		// 공격자의 속성이 방어자에게 약함
		cout << "공격이 약하게 들어갑니다!" << endl;
		return WEAKNESS_MULTIPLIER;
	}
	else
	{
		// 속성이 동일하거나 강약관계가 아니면 보통의 공격
		cout << "공격이 평범하게 들어갑니다!" << endl;
		return NORMAL_MULTIPLIER;
	}
}

ElementalProperties Monster::StringToElemental(const string& elementalStr) const
{
	if (elementalStr == "FIRE")
	{
		return FIRE;
	}
	else if (elementalStr == "WATER")
	{
		return WATER;
	}
	else if (elementalStr == "WIND")
	{
		return WIND;
	}
	else if (elementalStr == "EARTH")
	{
		return EARTH;
	}
	else
	{
		cout << "잘못된 몬스터 속성 문자열입니다." << endl;
		// TODO 에러제어
	}
}