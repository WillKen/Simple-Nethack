#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>

class player
{
public:
	player() {};
	player(int y, int x);
	player operator=(player other);
	int get_x();
	int get_y();
	int get_kind();
	char get_symbol();
	int get_attack();
	int get_defense();
	int get_HP();
	int get_MP();
	void reduce_HP(int);
	void reduce_MP(int);
	void go_h();
	void go_l();
	void go_k();
	void go_j();
	void go_y();
	void go_b();
	void go_u();
	void go_n();
	void add_HP(int);
	void add_MP(int);
	void add_attack(int);
	void add_defense(int);
	friend std::ostream &operator<<(std::ostream &, const player&);
private:
	int HP, MP, attack, defense, kind, pos_x, pos_y;
	char symbol;
};
#endif