#include"item.h"

item::item(int y, int x, char sy) {
	pos_x = x;
	pos_y = y;
	symbol = sy;
	kind = 6;
}

int item::get_kind() {
	return kind;
}

int item::get_x() {
	return pos_x;
}

int item::get_y() {
	return pos_y;
}

char item::get_symbol() {
	return symbol;
}
