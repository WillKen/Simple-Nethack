#include"player.h"
#include<iostream>
#include<Windows.h>

player::player(int y, int x) {
	HP = 100;
	MP = 100;
	pos_x = x;
	pos_y = y;
	attack = 50;
	defense = 0;
	kind = 4;
	symbol = '@';
}

player player::operator=(player other) {
	HP = other.HP;
	MP = other.MP;
	pos_x = other.pos_x;
	pos_y = other.pos_y;
	attack = other.attack;
	defense = other.defense;
	kind = 4;
	symbol = other.symbol;
	return *this;
}

int player::get_x() {
	return pos_x;
}

int player::get_y() {
	return pos_y;
}

int player::get_kind() {
	return kind;
}

char player::get_symbol() {
	return symbol;
}

int player::get_attack()
{
	return attack;
}

int player::get_defense()
{
	return defense;
}

int player::get_HP()
{
	return HP;
}

int player::get_MP()
{
	return MP;
}

void player::reduce_HP(int x)
{
	if (x>0)
		HP -= x;
}

void player::reduce_MP(int x)
{
	MP -= x;
}

void player::go_h() {
	pos_x--;
}

void player::go_l() {
	pos_x++;
}

void player::go_k() {
	pos_y--;
}

void player::go_j() {
	pos_y++;
}

void player::go_y() {
	pos_x--;
	pos_y--;
}

void player::go_b() {
	pos_x--;
	pos_y++;
}

void player::go_u() {
	pos_x++;
	pos_y--;
}

void player::go_n() {
	pos_x++;
	pos_y++;
}

void player::add_HP(int x)
{
	HP += x;
}

void player::add_MP(int x)
{
	MP += x;
}

void player::add_attack(int x)
{
	attack += x;
}

void player::add_defense(int x)
{
	defense += x;
}

std::ostream & operator<<(std::ostream &os, const player &obj)
{
	os << "PLAYER:	HP:" << obj.HP << "	MP:" << obj.MP << "	attack:" << obj.attack << "	defense:" << obj.defense << std::endl;
	return os;
}
