#include"package.h"
#include<iostream>
#include<Windows.h>

package::package() {
	medicine = 0;
	sword = 0;
	shield = 0;
	necklace = 0;
}

void package::print() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 15);
	if (medicine + sword + shield) {
		if (medicine) {
			std::cout << "You have " << medicine << " bottle(s) of ¡¾medicine¡¿." << std::endl << "Each bottle of medicine will add 15HP for your hero." << std::endl;
		}
		if (sword)
			std::cout << std::endl << "You have " << sword << " ¡¾swords¡¿;  hero's attack +" << sword * 10 << std::endl;
		if (shield)
			std::cout << std::endl << "You have " << shield << " ¡¾shields¡¿;  hero's defense +" << shield * 10 << std::endl;
		if (medicine) {
			std::cout << std::endl << "PRESS [1] TO USE MEDICINE!";
		}
	}
	else
		std::cout << "You have nothing,adventure is out there!" << std::endl;

}

void package::add_sword()
{
	sword++;
}

void package::add_shield()
{
	shield++;
}

void package::add_medicine()
{
	medicine++;
}

void package::add_necklace()
{
	necklace = true;
}

void package::reduce_medicine(int x)
{
	medicine -= x;
}

bool package::get_necklace()
{
	return necklace;
}

int package::get_medicine()
{
	return medicine;
}

int package::get_sword()
{
	return sword;
}

int package::get_shield()
{
	return shield;
}
