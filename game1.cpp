#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

ifstream input("map.txt");

class  dot{ 
public:
	int y;
	int x;
	dot(int inputY, int inputX): y(inputY), x(inputX) {}
};


class Character {
protected:
	bool isAlive;

	int damage;
	int health;
	int speed;

	int x;
	int y;
public:

	virtual int HitPoints() {
		return health;
	}

	virtual int Damage() {
		return damage;
	}

	virtual void Move(int step, vector<string>& field) {}

	bool alive() {
		return isAlive;
	}

	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}

	void getHit(int getDamage) {	
		health -= getDamage;
		if(health <= 0) {
			isAlive = false;
			cout << "dead" << endl;
		}
	}
	
	void fight(Character& atacker, Character& defender) {
		defender.getHit(atacker.Damage());
		cout << "atacker deals: " << atacker.Damage() << endl;
		cout << "defender's health: " << defender.HitPoints() << endl;
	}
};

class Monster: public Character{
public:
	Monster(dot YX) {
		isAlive = true;
		y = YX.y;
		x = YX.x;
		damage = 2;
		health = 2;
		speed = 1;
	}

	void Move(vector<string>& field, Character& holyKnight) {
		if(!isAlive) {
			return;
		}
		int step = rand() % 4 + 1;
		int nextX = x;
		int nextY = y;
		if(step == 1) {
			nextX++;
		}
		else if(step == 2) {
			nextX--;
		}
		else if(step == 3) {
			nextY++;
		}
		else if(step == 4) {
			nextY--;
		}

		if(nextY < field.size() && nextY >= 0 &&
		 nextX < field[nextY].length() && nextX >= 0 &&
		  field[nextY][nextX] != '#') {
		  	if(field[nextY][nextX] != 'K') {
				field[y][x] = '.';
				x = nextX;
				y = nextY;
				field[y][x] = 'M';
		  	}
		  	else {
		  		fight(*this, holyKnight);
		  	}
		}
	}
};

class Knight: public Character {
public:
	Knight(dot YX) {
		isAlive = true;
		y = YX.y;
		x = YX.x;
		damage = 10;
		health = 10;
		speed = 1;
	}


	void Move(int step, vector<string>& field, list<Monster>& monsters) {
		int nextX = x;
		int nextY = y;
		if(step == 1) {
			nextX++;
		}
		else if(step == 2) {
			nextX--;
		}
		else if(step == 3) {
			nextY++;
		}
		else if(step == 4) {
			nextY--;
		}

		if(nextY < field.size() && nextY >= 0 &&
		 nextX < field[nextY].length() && nextX >= 0 &&
		  field[nextY][nextX] != '#') {
		  	if(field[nextY][nextX] != 'M') {
				field[y][x] = '.';
				x = nextX;
				y = nextY;
				field[y][x] = 'K';
		  	}
		  	else {
		  		list<Monster>::iterator iter = monsters.begin();
		  		while(nextY != iter->getY() && nextX != iter->getX()) {
		  			iter++;
		  		}
		  		fight(*this, *iter);
		  		if(!iter->alive()) {
		  			field[iter->getY()][iter->getX()] = '.';
		  			monsters.erase(iter);
		  		}
		  	}
		}
	}
};

void inputField(vector<string>& field);
void outputField(vector<string>& field);

void getKnightAndMonsters(vector<string>& field, dot& YXknight, list<dot>& YX);

void createMonsters(list<Monster>& monsters, list<dot>& YXmonsters);

void allMonstersMove(list<Monster>& monsters, vector<string>& field, Character& holyKnight);

void displayMonsters(list<Monster>& monsters);

int main() {
	vector<string> field;
	dot YXknight(0, 0);
	list<dot> YXmonsters;
	list<Monster> monsters;

	int step = 0;

	inputField(field);
	outputField(field);

	getKnightAndMonsters(field,YXknight, YXmonsters);

	createMonsters(monsters, YXmonsters);

	Knight holyKnight(YXknight);	

	cout << "insert step: 1,2,3,4" << endl;
	while(holyKnight.alive() && monsters.size() > 0) {
		cin >> step;
		holyKnight.Move(step, field, monsters);
		allMonstersMove(monsters, field, holyKnight);
		cout << endl;
		cout << "=======" << endl;
		outputField(field);
	}
	if(!holyKnight.alive()) {
		cout << "You Failed" << endl;
	}
	else {
		cout << "You Won" << endl;
	}

	return 0;
}

void inputField(vector<string>& field) {
	string buffer;
	getline(input, buffer);
	while(! buffer.empty()) {
		field.push_back(buffer);
		getline(input, buffer);
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


void allMonstersMove(list<Monster>& monsters, vector<string>& field, Character& holyKnight) {
	list<Monster>::iterator iter = monsters.begin();
	while(iter != monsters.end()){
		iter->Move(field, holyKnight);
		if(!iter->alive()) {
			field[iter->getY()][iter->getX()] = '.';
			monsters.erase(iter);
		}
		else {
			++iter;
		}
	}
}


void createMonsters(list<Monster>& monsters, list<dot>& YXmonsters) {
	list<dot>::iterator iterYX = YXmonsters.begin();
	while(iterYX != YXmonsters.end()) {
		Monster newMonster(*iterYX);
		monsters.push_back(newMonster);
		++iterYX;
	}
}

