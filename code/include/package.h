#ifndef PACKAGE_H
#define PACKAGE_H

class package {
public:
	package();
	void print();
	void add_sword();
	void add_shield();
	void add_medicine();
	void add_necklace();
	void reduce_medicine(int);
	bool get_necklace();
	int  get_medicine();
	int get_sword();
	int get_shield();
private:
	int medicine, sword, shield;
	bool necklace;
};
#endif 
