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

	virtual void getHit(int getDamage) {}

	void fight(Character& atacker, Character& defender) {
		cout << "fight" << endl;
		while(atacker.alive() && defender.alive()) {
			cout << "atacker deals:" << atacker.Damage() << endl;
			defender.getHit(atacker.Damage());
			cout << "defenders health:" << defender.HitPoints() << endl;
			if(defender.alive()) {
				cout << "defender alive" << endl;
			}
			else cout << "defender dead" << endl;	

			if(defender.alive()){
				cout << "defender deals:" << defender.Damage() << endl;
				atacker.getHit(defender.Damage());
				cout << "atacker health:" << atacker.HitPoints() << endl;
				if(atacker.alive()) {
					cout << "atacker alive" << endl;
			 	}
			 	else cout << "atacker dead" << endl;
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


	void Move(int step, vector<string>& field) {
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
		  field[nextY][nextX] != '#' && field[nextY][nextX] != 'M') {
			field[y][x] = '.';
			x = nextX;
			y = nextY;
			field[y][x] = 'K';
		}
	}

	void getHit(int getDamage) {	
		health -= getDamage;
		if(!health > 0) {
			isAlive = false;
		}
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
	void getHit(int getDamage) {	
		health -= getDamage;
		if(!health > 0) {
			isAlive = false;
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

	getKnightAndMonsters(field,YXknight, YXmonsters);

	createMonsters(monsters, YXmonsters);

	Knight holyKnight(YXknight);	

	cout << "insert step: 1,2,3,4" << endl;
	cin >> step;
	while(holyKnight.alive() && monsters.size() > 0) {
		holyKnight.Move(step, field);
		allMonstersMove(monsters, field, holyKnight);
		cout << endl;
		cout << "=======" << endl;
		outputField(field);
		cin >> step;
	}
	cout << "You Failed" << endl;

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

