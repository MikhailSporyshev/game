#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class  dot{ 
public:
	int y;
	int x;
	dot(int inputY, int inputX): y(inputY), x(inputX) {}
};

class Knight {
	int damage;
	int health;
	int speed;

	int x;
	int y;
public:
	Knight(dot YX):y(YX.y), x(YX.x) {
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
	Monster(dot YX): y(YX.y), x(YX.x) {
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

void getKnightAndMonsters(vector<string>& field, dot& YXknight, list<dot>& YX);

void createMonster(list<Monster>& monsters, list<dot>& YXmonsters);

void allMonstersWalk(list<Monster>& monsters, vector<string>& field);

void displayMonsters(list<Monster>& monsters);

int main() {
	vector<string> field;
	dot YXknight(0, 0);
	list<dot> YXmonsters;
	list<Monster> monsters;

	int step = 0;

	inputField(field);

	getKnightAndMonsters(field,YXknight, YXmonsters);

	createMonster(monsters, YXmonsters);

	Knight holyKnight(YXknight);	

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


void getKnightAndMonsters(vector<string>& field, dot& YXknight, list<dot>& YXmonsters) {
	for(int i = 0; i < field.size(); i++) {
		for(int j = 0; j < field[i].length(); j++) {
			if(field[i][j] == 'K') {
				YXknight.y = i;
				YXknight.x = j;
			}
			else if(field[i][j] == 'M') {
				dot YX(i, j);
				YXmonsters.push_back(YX);
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


void createMonster(list<Monster>& monsters, list<dot>& YXmonsters) {
	list<dot>::iterator iterYX = YXmonsters.begin();
	while(iterYX != YXmonsters.end()) {
		Monster newMonster(*iterYX);
		monsters.push_back(newMonster);
		++iterYX;
	}
}

