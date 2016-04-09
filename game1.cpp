#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Knight {
	int damage;
	int health;
	int speed;

	int x;
	int y;
public:
	Knight(int inputY, int inputX):y(inputY), x(inputX) {
		damage = 2;
		health = 2;
		speed = 2;
	}

	void walk(int step, vector<string>& field) {
		if(step == 1 && x < field[y].length() - 1 && field[y][x + 1] != '#') {
			field[y][x] = '.';
			x++;
			field[y][x] = 'K';
		}
		else if(step == 2 &&  x > 0 && field[y][x - 1] != '#') {
			field[y][x] = '.';
			x--;
			field[y][x] = 'K';
		}
		else if(step == 3 && y < field.size() - 1 && field[y + 1][x] != '#') {
			field[y][x] = '.';
			y++;
			field[y][x] = 'K';
		}
		else if(step == 4 &&  y > 0 && field[y - 1][x] != '#') {
			field[y][x] = '.';
			y--;
			field[y][x] = 'K';
		}
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};


class Monster{
	int damage;
	int health;
	int speed;

	int x;
	int y;
public:
	Monster() {
		damage = 2;
		health = 2;
		speed = 2;
	}
	Monster(int inputY, int inputX):y(inputY), x(inputX) {
		damage = 2;
		health = 2;
		speed = 2;
	}

	void walk(vector<string>& field) {
		int step = rand() % 4;
		if(step == 0 && x < field[y].length() - 1 && field[y][x + 1] != '#') {
			field[y][x] = '.';
			x++;
			field[y][x] = 'M';
		}
		else if(step == 1 &&  x > 0 && field[y][x - 1] != '#') {
			field[y][x] = '.';
			x--;
			field[y][x] = 'M';
		}
		else if(step == 2 && y < field.size() - 1 && field[y + 1][x] != '#') {
			field[y][x] = '.';
			y++;
			field[y][x] = 'M';
		}
		else if(step == 3 &&  y > 0 && field[y - 1][x] != '#') {
			field[y][x] = '.';
			y--;
			field[y][x] = 'M';
		}
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

void inputField(vector<string>& field);
void outputField(vector<string>& field);

void getKnightAndMonsters(vector<string>& field, int& xKnight, int& yKnight,
 list<int>& xMonster, list<int>& yMonster);

void createMonster(list<Monster>& monsters, list<int>& xMonster, list<int>& yMonster);

void allMonstersWalk(list<Monster>& monsters, vector<string>& field);

void displayMonsters(list<Monster>& monsters);

int main() {
	vector<string> field;
	int xKingt = 0, yKnight = 0;
	list<int> xMonster, yMonster;
	list<Monster> monsters;

	int step = 0;

	inputField(field);

	getKnightAndMonsters(field, xKingt, yKnight, xMonster, yMonster);

	createMonster(monsters, xMonster, yMonster);

	Knight holyKnight(yKnight, xKingt);	

	cout << "insert step: 1,2,3,4" << endl;
	cin >> step;
	while(step > 0) {
		holyKnight.walk(step, field);
		allMonstersWalk(monsters, field);
		cout << endl;
		cout << "=======" << endl;
		outputField(field);
		cin >> step;
	}

	return 0;
}

void inputField(vector<string>& field) {
	string buffer;
	getline(cin, buffer);
	while(! buffer.empty()) {
		field.push_back(buffer);
		getline(cin, buffer);
	}
}

void outputField(vector<string>& field) {
	for(vector<string>::iterator iter = field.begin(); iter != field.end(); ++iter) {
		cout << *iter << endl;
	}
}


void getKnightAndMonsters(vector<string>& field, int& xKnight, int& yKnight,
 list<int>& xMonster, list<int>& yMonster) {
	for(int i = 0; i < field.size(); i++) {
		for(int j = 0; j < field[i].length(); j++) {
			if(field[i][j] == 'K') {
				yKnight = i;
				xKnight = j;
			}
			else if(field[i][j] == 'M') {
				yMonster.push_back(i);
				xMonster.push_back(j);
			}	
		}
	}	
}


void allMonstersWalk(list<Monster>& monsters, vector<string>& field) {
	list<Monster>::iterator iter = monsters.begin();
	while( iter != monsters.end()){
		iter->walk(field);
		++iter;
	}
}


void createMonster(list<Monster>& monsters, list<int>& xMonster, list<int>& yMonster) {
	list<int>::iterator iterX = xMonster.begin();
	list<int>::iterator iterY = yMonster.begin();
	while(iterX != xMonster.end() && iterY != yMonster.end()) {
		Monster newMonster(*iterY, *iterX);
		monsters.push_back(newMonster);
		++iterX;
		++iterY;
	}
}

