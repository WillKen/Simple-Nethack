#include"monster.h"
#include<sstream>

monster::monster(int y, int x, char k) {
	pos_x = x;
	pos_y = y;
	kind = 4;
	switch (k)
	{
	case'S':
		HP = 100;
		attack = 15;
		defense = 10;
		battle = 0;
		break;
	case'M':
		HP = 100;
		attack = 20;
		defense = 12;
		battle = 0;
		break;
	case'L':
		HP = 100;
		attack = 25;
		defense = 10;
		battle = 0;
		break;
	default:
		break;
	}
	symbol = k;
}

int monster::get_x() {
	return pos_x;
}

int monster::get_y() {
	return pos_y;
}

int monster::get_kind() {
	return kind;
}

int monster::get_hp()
{
	return HP;
}

int monster::get_attack()
{
	return attack;
}

int monster::get_defense()
{
	return defense;
}

bool monster::if_battle()
{
	return battle;
}

void monster::reduce_HP(int x)
{
	if (x>0)
		HP -= x;
}

void monster::set_battle()
{
	battle = 1;
}

monster monster::operator=(monster other) {
	HP = other.HP;
	kind = 5;
	attack = other.attack;
	defense = other.defense;
	pos_x = other.pos_x;
	pos_y = other.pos_y;
	symbol = other.symbol;
	return *this;
}

char monster::get_symbol() {
	return symbol;
}

void monster::go_h() {
	pos_x--;
}

void monster::go_l() {
	pos_x++;
}

void monster::go_k() {
	pos_y--;
}

void monster::go_j() {
	pos_y++;
}

void monster::go_y() {
	pos_x--;
	pos_y--;
}

void monster::go_b() {
	pos_x--;
	pos_y++;
}

void monster::go_u() {
	pos_x++;
	pos_y--;
}

void monster::go_n() {
	pos_x++;
	pos_y++;
}

std::ostream & operator<<(std::ostream &os, const monster &obj)
{
	os << "monster:" << "	HP:" << obj.HP << "	attack:" << obj.attack << "	defense:" << obj.defense << std::endl;
	return os;
}