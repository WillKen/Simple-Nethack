#ifndef MONSTER_H
#define MONSTER_H
#include<iostream>

class monster
{
public:
	monster() {};
	monster(int y, int x, char k);
	int get_x();
	int get_y();
	int get_kind();
	int get_hp();
	int get_attack();
	int get_defense();
	bool if_battle();
	void reduce_HP(int);
	void set_battle();
	monster operator=(monster other);
	char get_symbol();
	void go_h();
	void go_l();
	void go_k();
	void go_j();
	void go_y();
	void go_b();
	void go_u();
	void go_n();
	friend std::ostream & operator<<(std::ostream &, const monster&);
private:
private:
	int HP, attack, defense, kind, pos_x, pos_y;
	char symbol;
	bool battle;
};
#endif