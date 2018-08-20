#include<iostream>
#include<string>
#include<Windows.h>
#include<ctime>
#include<conio.h>
#include"package.h"
#include"item.h"
#include"player.h"
#include"monster.h"
#define MAP_X 88
#define MAP_Y 22
#define MONSTER_TOTAL 10
#define ITEM_TOTAL 15
using namespace std;

void help();
void Initialization();
void display();
void play();
void player_action(char);
void monster_action(int, int);
bool moveable(int, int, bool);
void battle(player&, monster&);
void end(bool);
void pick_up(int, int);
void use_medicine(int);
void skill(char);
void vision(int, int);

package pack;
player hero;
item items[ITEM_TOTAL];
int item_number = 0;
monster monsters[MONSTER_TOTAL];
int monster_number = 0;
int left_monster;
int run = 1;
bool win = 1;
char backups[MAP_Y][MAP_X] = {
	"XXXXXXXX",
	"X@..p..X         XXXXX      XXXXXXXXXXXXXXXX",
	"X....s.X        #o...X      X..............X                          XXXXX",
	"X.b....X      ###X.b.o####  X.S..b.........X                          X.T.X",
	"XoXXXXXX      #  X...X   #  X..........M...X                          X...X",
	" #######    ###  X...X   ###o.....b........X                          XoXXX",
	"       #    #    XXXXX     #XXXoXXXXXXXXXXXX                          ##",
	"       #  ###                 ####               XXXXXXXXXXXX         #",
	"       ## #                     #                X...M......X        ###",
	"     XXXoX#                     ###              X......b...X       XoXoX",
	"     X...X#                       #              X.{........X     ##oL..X",
	"     Xb..o#                       ###         ###o......b...o###### X...X",
	"     XXXXX#                         #         #  X.b........X       X...X",
	"       XXXoXXXXXXXX                 ####    #### XXXXXXXXXXXX       X...X",
	"       X.....S....X                   #     #                       X...X",
	"       X..b.......X                  XoXXXXX#                       XXXXX",
	"       X.S........X                  X..S..o#",
	"       X......b...o##################o.b...X",
	"       XXXXXXXXXXXX                  XXXXXXX",
};
char map_char[MAP_Y][MAP_X];
int map_int[MAP_Y][MAP_X] = { 0 };
int vision_record[MAP_Y][MAP_X] = { 0 };

int main()
{
	help();
	Initialization();
	while (run) {
		play();
	}
	end(win);
	return 0;
}

void Initialization() {
	for (int y = 0; y < MAP_Y; y++) {
		for (int x = 0; x < MAP_X; x++) {
			map_char[y][x] = backups[y][x];
			if (map_char[y][x] == '.' || map_char[y][x] == '#')
				map_int[y][x] = 3;
			else if (map_char[y][x] == 'X')
				map_int[y][x] = 1;
			else if (map_char[y][x] == 'o')
				map_int[y][x] = 2;
			//����item
			if (map_char[y][x] == 'p' || map_char[y][x] == 's' || map_char[y][x] == 'b' || map_char[y][x] == '{') {
				item tem(y, x, map_char[y][x]);
				items[item_number] = tem;
				item_number++;
				map_int[y][x] = tem.get_kind();
			}
			//����3�в�ͬ����Ĺ�
			else if (map_char[y][x] == 'S' || map_char[y][x] == 'L' || map_char[y][x] == 'M') {
				monster tem(y, x, map_char[y][x]);
				monsters[monster_number] = tem;
				monster_number++;
				map_int[y][x] = tem.get_kind();
				map_char[y][x] = '.';
			}
			//��������
			else if (map_char[y][x] == '@') {
				player tem(y, x);
				hero = tem;
				map_char[y][x] = '.';
			}
		}
	}
}

void display() {
	int y, x, i, m_x, m_y;
	for (y = 0; y < MAP_Y; y++) {
		for (x = 0; x < MAP_X; x++) {
			//��map_int ��¼��ͬͼ��Ĳ�ͬ���࣬�����ò�ͬ��ɫ��ӡ
			switch (map_char[y][x])
			{
			case'X':
				map_int[y][x] = 1;
				break;
			case'o':
				map_int[y][x] = 2;
				break;
			case'.':
				map_int[y][x] = 3;
			case'#':
				map_int[y][x] = 3;
			default:
				break;
			}
		}
	}
	map_int[hero.get_y()][hero.get_x()] = 4;
	//�������Ѫ������0����ʾ
	for (i = 0; i <monster_number; i++) {
		if (monsters[i].get_hp() >= 0) {
			m_y = monsters[i].get_y();
			m_x = monsters[i].get_x();
			map_int[m_y][m_x] = 5;
		}
	}
	//������Ұ����
	vision(hero.get_y(), hero.get_x());
	for (y = 0; y < MAP_Y; y++) {
		for (x = 0; x < MAP_X; x++) {
			if (vision_record[y][x] == 0)
				cout << ' ';
			else {
				switch (map_int[y][x])
				{
				case 1://ǽ
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 1);
					cout << map_char[y][x];
					break;
				case 2://��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 10);
					cout << map_char[y][x];
					break;
				case 3://·
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << map_char[y][x];
					break;
				case 4://��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 14);
					cout << '@';
					break;
				case 5://��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 12);
					cout << 'M';
					break;
				case 6:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 11);
					cout << map_char[y][x];
					break;
				default:
					cout << map_char[y][x];
					break;
				}
			}
		}
		cout << endl;
	}
	int num;
	left_monster = 0;
	//ͳ��ʣ�����
	for (num = 0; num < monster_number; num++) {
		if (monsters[num].get_hp() > 0) {
			left_monster++;
		}
	}
	//��ͼ�·���ʾ����Ϣ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 15);
	cout << "Press ��x��to use your skill to reduce 10%HP of each monster!" << endl;
	cout << "Press ��z��to use your skill to have a vision of the whole map for 3sec!" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 14);
	cout << endl << hero;
	if (pack.get_necklace()) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 10);
		cout << "You've got the necklace,find the sacrificial altar and you will WIN!!!!" << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 12);
	cout << "There are " << left_monster << " monster(s) left!" << endl;
	for (i = 0; i < monster_number; i++) {
		if (monsters[i].get_hp() > 0 && monsters[i].if_battle()) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << monsters[i];
		}
	}
}

void play() {//�����û�ָ����в���
	char cmd;
	char p_cmd;
	int num;
	system("cls");
	display();
	if (_kbhit)
	{
		cmd = _getch();
		if (cmd == 'h' || cmd == 'j' || cmd == 'k' || cmd == 'l' || cmd == 'y' || cmd == 'u' || cmd == 'b' || cmd == 'n') {
			player_action(cmd);
		}
		else if (cmd == 'p') {
			system("cls");
			pack.print();
			if (pack.get_medicine() > 0) {
				if (_kbhit) {
					p_cmd = _getch();
					if (p_cmd == '1') {
						cout << endl << "HOW MANY BOTTLES OF MEDICINE DO YOU WANT TO USE?" << endl;
						cin >> num;
						if (num >= 0 && num <= pack.get_medicine()) {
							use_medicine(num);
						}
						else
							cout << endl << " illegal operation!!" << endl;
					}

				}
			}
			system("pause");
		}
		else if (cmd == 'q') {
			help();
		}
		else if (cmd == 'x') {
			skill(cmd);
		}
		else if (cmd == 'z') {
			skill(cmd);
		}
	}
}

void player_action(char deriction) {
	//����ƶ�
	switch (deriction) {
	case'h':
		if (moveable(hero.get_y(), hero.get_x() - 1, 1))
			hero.go_h();
		break;
	case'j':
		if (moveable(hero.get_y() + 1, hero.get_x(), 1))
			hero.go_j();
		break;
	case'k':
		if (moveable(hero.get_y() - 1, hero.get_x(), 1))
			hero.go_k();
		break;
	case'l':
		if (moveable(hero.get_y(), hero.get_x() + 1, 1))
			hero.go_l();
		break;
	case'y':
		if (moveable(hero.get_y() - 1, hero.get_x() - 1, 1))
			hero.go_y();
		break;
	case'u':
		if (moveable(hero.get_y() - 1, hero.get_x() + 1, 1))
			hero.go_u();
		break;
	case'b':
		if (moveable(hero.get_y() + 1, hero.get_x() - 1, 1))
			hero.go_b();
		break;
	case'n':
		if (moveable(hero.get_y() + 1, hero.get_x() + 1, 1))
			hero.go_n();
		break;
	}
	monster_action(hero.get_y(), hero.get_x());
}

void monster_action(int player_y, int player_x) {
	enum direction { y, u, h, j, k, l, b, n }dir;
	int distance[8];//8��int�ֱ������yuhjklbn�˸������ƶ�����player�ľ��� 
	int num = 0;
	int i = 0;
	for (num = 0; num < monster_number; num++) {
		//�����һ�������ߣ���moveable�� �ͽ������Ϊ999  ����ͼ�����ʵ����
		if (monsters[num].get_hp() > 0 && !monsters[num].if_battle()) {//monster Ѫ������0 �Ҳ���battle ״̬ ������
			if (!moveable(monsters[num].get_y() - 1, monsters[num].get_x() - 1, 0))
				distance[0] = 999;
			else
				distance[0] = abs(player_y - (monsters[num].get_y() - 1)) + abs(player_x - (monsters[num].get_x() - 1));
			if (!moveable(monsters[num].get_y() - 1, monsters[num].get_x() + 1, 0))
				distance[1] = 999;
			else
				distance[1] = abs(player_y - (monsters[num].get_y() - 1)) + abs(player_x - (monsters[num].get_x() + 1));
			if (!moveable(monsters[num].get_y(), monsters[num].get_x() - 1, 0))
				distance[2] = 999;
			else
				distance[2] = abs(player_y - (monsters[num].get_y())) + abs(player_x - (monsters[num].get_x() - 1));
			if (!moveable(monsters[num].get_y() + 1, monsters[num].get_x(), 0))
				distance[3] = 999;
			else
				distance[3] = abs(player_y - (monsters[num].get_y() + 1)) + abs(player_x - (monsters[num].get_x()));
			if (!moveable(monsters[num].get_y() - 1, monsters[num].get_x(), 0))
				distance[4] = 999;
			else
				distance[4] = abs(player_y - (monsters[num].get_y() - 1)) + abs(player_x - (monsters[num].get_x()));
			if (!moveable(monsters[num].get_y(), monsters[num].get_x() + 1, 0))
				distance[5] = 999;
			else
				distance[5] = abs(player_y - (monsters[num].get_y())) + abs(player_x - (monsters[num].get_x() + 1));
			if (!moveable(monsters[num].get_y() + 1, monsters[num].get_x() - 1, 0))
				distance[6] = 999;
			else
				distance[6] = abs(player_y - (monsters[num].get_y() + 1)) + abs(player_x - (monsters[num].get_x() - 1));
			if (!moveable(monsters[num].get_y() + 1, monsters[num].get_x() + 1, 0))
				distance[7] = 999;
			else
				distance[7] = abs(player_y - (monsters[num].get_y() + 1)) + abs(player_x - (monsters[num].get_x() + 1));
			int  record;
			int min_distance = distance[0];
			record = 0;
			for (i = 1; i < 8; i++) {
				if (distance[i] == 0) {
					distance[i] = 999;
				}
				if (distance[i] < min_distance) {
					min_distance = distance[i];
					record = i;
				}
			}
			dir = (enum direction)record;//�����ƶ�����
			switch (dir) {
			case k:
				if (map_char[monsters[num].get_y() - 1][monsters[num].get_x()] == '.' || map_char[monsters[num].get_y() - 1][monsters[num].get_x()] == '#' || map_char[monsters[num].get_y() - 1][monsters[num].get_x()] == 'o')
					monsters[num].go_k();
				break;
			case h:
				if (map_char[monsters[num].get_y()][monsters[num].get_x() - 1] == '.' || map_char[monsters[num].get_y()][monsters[num].get_x() - 1] == '#' || map_char[monsters[num].get_y()][monsters[num].get_x() - 1] == 'o')
					monsters[num].go_h();
				break;
			case j:
				if (map_char[monsters[num].get_y() + 1][monsters[num].get_x()] == '.' || map_char[monsters[num].get_y() + 1][monsters[num].get_x()] == '#' || map_char[monsters[num].get_y() + 1][monsters[num].get_x()] == 'o')
					monsters[num].go_j();
				break;
			case l:
				if (map_char[monsters[num].get_y()][monsters[num].get_x() + 1] == '.' || map_char[monsters[num].get_y()][monsters[num].get_x() + 1] == '#' || map_char[monsters[num].get_y()][monsters[num].get_x() + 1] == 'o')
					monsters[num].go_l();
				break;
			case y:
				if (map_char[monsters[num].get_y() - 1][monsters[num].get_x() - 1] == '.' || map_char[monsters[num].get_y() - 1][monsters[num].get_x() - 1] == '#' || map_char[monsters[num].get_y() - 1][monsters[num].get_x() - 1] == 'o') {
					monsters[num].go_y();
				}
				break;
			case u:
				if (map_char[monsters[num].get_y() - 1][monsters[num].get_x() + 1] == '.' || map_char[monsters[num].get_y() - 1][monsters[num].get_x() + 1] == '#' || map_char[monsters[num].get_y() - 1][monsters[num].get_x() + 1] == 'o') {
					monsters[num].go_u();
				}
				break;
			case b:
				if (map_char[monsters[num].get_y() + 1][monsters[num].get_x() - 1] == '.' || map_char[monsters[num].get_y() + 1][monsters[num].get_x() - 1] == '#' || map_char[monsters[num].get_y() + 1][monsters[num].get_x() - 1] == 'o') {
					monsters[num].go_b();
				}
				break;
			case n:
				if (map_char[monsters[num].get_y() + 1][monsters[num].get_x() + 1] == '.' || map_char[monsters[num].get_y() + 1][monsters[num].get_x() + 1] == '#' || map_char[monsters[num].get_y() + 1][monsters[num].get_x() + 1] == 'o') {
					monsters[num].go_n();
				}
				break;
			default:
				break;
			}
		}
	}
}

void help() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 15);
	cout << "���¡�y��,��u��,��h��,��j��,��k��,��l��,��b��,��n��,���а����ƶ�" << endl << endl;
	cout << "���¡�q���򿪰���ҳ" << endl << endl;
	cout << "���¡�p���򿪱���ҳ" << endl << endl;
	cout << "��z������һ������30MP" << endl << endl;
	cout << "��x������һ������20MP" << endl << endl;
	cout << "ҩƿ��b�� ��ȥ��ɽ��뱳��ҳ���С��ֶ�ʹ�á�" << endl << endl;
	cout << "������s�� & ���ơ�p�� ʰȡ���Զ����ӡ��������ԡ�" << endl << endl;
	cout << "���Ŀ����ʰȡ������{�����������ŵ���̨��T���ϣ�" << endl << endl;
	system("pause");
	system("cls");
}

bool moveable(int y, int x, bool human) {
	//�ж���һ���Ƿ�����
	int i;
	if ((map_char[y][x] == '.' || map_char[y][x] == '#' || map_char[y][x] == 'o') && map_int[y][x] != 5)
		return true;
	else {
		if (human) {//������� �ж���һ���Ƿ�Ϊmonster �ǵĻ�����battle ״̬
			for (i = 0; i < monster_number; i++) {
				if (y == monsters[i].get_y() && x == monsters[i].get_x()) {
					monsters[i].set_battle();
					battle(hero, monsters[i]);
					break;
				}
			}
		}
		if (human)//������˻������ж���һ���ܷ����Ʒ
			pick_up(y, x);
		if (human&&map_char[y][x] == 'T'&&pack.get_necklace()) {
			run = 0;
			win = 1;
		}
		return false;
	}
}

void battle(player &pl, monster &mt) {
	float hit_rate;//�˺�����
	srand((unsigned)time(NULL));
	float player_damage, monster_damage;
	hit_rate = (rand() % 10 + 1)*0.1;//��������˺�����
	player_damage = (mt.get_attack() - pl.get_defense())*hit_rate;
	hit_rate = (rand() % 10 + 1)*0.1;//��������˺�����
	monster_damage = (pl.get_attack() - mt.get_defense())*hit_rate;
	pl.reduce_HP(player_damage);
	mt.reduce_HP(monster_damage);
	if (pl.get_HP() <= 0) {//����˵�Ѫ��С�ڵ���0  �ͽ������У�run�� ��ʤ��win) Ϊ��
		run = 0;
		win = 0;
	}
}

void end(bool win)//�ж���Ϸ����ʱ�Ľ��
{
	system("cls");
	if (win) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 10);
		cout << "YOU WIN!!!!!!" << endl;
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 12);
		cout << "GAME OVER!!!!" << endl;
	}
	system("pause");
}

void pick_up(int y, int x)
{
	if (map_char[y][x] == 'b') {
		pack.add_medicine();
		map_char[y][x] = '.';
		map_int[y][x] = 3;
	}
	if (map_char[y][x] == 's') {
		pack.add_sword();
		hero.add_attack(10);
		map_char[y][x] = '.';
		map_int[y][x] = 3;
	}
	if (map_char[y][x] == 'p') {
		pack.add_shield();
		hero.add_defense(10);
		map_char[y][x] = '.';
		map_int[y][x] = 3;
	}
	if (map_char[y][x] == '{') {
		pack.add_necklace();
		map_char[y][x] = '.';
		map_int[y][x] = 3;
	}
}

void use_medicine(int bottle)
{
	hero.add_HP(10 * bottle);
	hero.add_MP(10 * bottle);
	pack.reduce_medicine(bottle);
	cout << "successfully used!!!" << endl;
}

void skill(char mark)
{
	int x, y;
	int num;
	if (mark == 'x') {
		if (hero.get_MP() >= 20) {
			hero.reduce_MP(20);
			for (num = 0; num < monster_number; num++) {
				monsters[num].reduce_HP(0.1*monsters[num].get_hp());
			}
		}
		else {
			system("cls");
			cout << "Your magic power is too low to use the skill!!!!" << endl;
			system("pause");
		}
	}
	if (mark == 'z') {
		if (hero.get_MP() >= 30) {
			hero.reduce_MP(30);
			for (y = 0; y < MAP_Y; y++) {
				for (x = 0; x < MAP_X; x++) {
					vision_record[y][x] += 1;
				}
			}
			system("cls");
			display();
			Sleep(3000);
			for (y = 0; y < MAP_Y; y++) {
				for (x = 0; x < MAP_X; x++) {
					vision_record[y][x] -= 1;
				}
			}
		}
		else {
			system("cls");
			cout << "Your magic power is too low to use the skill!!!!" << endl;
			system("pause");
		}
	}
}

void vision(int y, int x)
{
	vision_record[y - 1][x - 1] = 1;
	vision_record[y - 1][x] = 1;
	vision_record[y - 1][x + 1] = 1;
	vision_record[y][x - 1] = 1;
	vision_record[y][x] = 1;
	vision_record[y][x + 1] = 1;
	vision_record[y + 1][x - 1] = 1;
	vision_record[y + 1][x] = 1;
	vision_record[y + 1][x + 1] = 1;
}