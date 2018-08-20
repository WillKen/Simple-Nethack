#ifndef ITEM_H
#define ITEM_H

class item {
public:
	item() {};
	item(int y, int x, char sy);
	int get_kind();
	int get_x();
	int get_y();
	char get_symbol();
private:
	int kind, pos_x, pos_y;
	char symbol;
};
#endif