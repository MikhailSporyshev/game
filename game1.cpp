#include <iostream>
#include <algorithm>

using namespace std;

class Knight{
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

	void walk(int step, char** field, int xSize, int ySize) {
		if(step == 1 && x < xSize - 1 && field[y][x + 1] != '#') {
			field[y][x] = '.';
			x++;
			field[y][x] = 'K';
		}
		else if(step == 2 &&  x > 0 && field[y][x - 1] != '#') {
			field[y][x] = '.';
			x--;
			field[y][x] = 'K';
		}
		else if(step == 3 && y < ySize - 1 && field[y + 1][x] != '#') {
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
	Monster(int inputY, int inputX):y(inputY), x(inputX) {
		damage = 2;
		health = 2;
		speed = 2;
	}

	void walk(char** field, int xSize, int ySize) {
		int step = rand() % 4;
		if(step == 0 && x < xSize - 1 && field[y][x + 1] != '#') {
			field[y][x] = '.';
			x++;
			field[y][x] = 'M';
		}
		else if(step == 1 &&  x > 0 && field[y][x - 1] != '#') {
			field[y][x] = '.';
			x--;
			field[y][x] = 'M';
		}
		else if(step == 2 && y < ySize - 1 && field[y + 1][x] != '#') {
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



void getFieldAndKnightAndMonster(char** field,int& x, int& y, int& xKnight, int& yKnight, int& xMonster, int& yMonster);
void displayField(char** field,int& x, int& y);

int main() {
	int x, y;
	char** field = new char*[y];
	int xKingt = 0, yKnight = 0;
	int xMonster = 0, yMonster = 0;

	int step = 0;

	cout << "insert x y:" << endl;
	cin >> x >> y;
	
	getFieldAndKnightAndMonster(field, x, y, xKingt, yKnight, xMonster, yMonster);


	Knight holyKnight(yKnight, xKingt);	
	Monster unholyMonster(yMonster, xMonster);

	cout << holyKnight.getY() << " " << holyKnight.getX() << endl;


	cout << "insert step: 1,2,3,4" << endl;
	cin >> step;
	while(step > 0) {
		holyKnight.walk(step, field, x, y);
		unholyMonster.walk(field, x, y);
		displayField(field, x, y);
		cin >> step;
	}

	return 0;
}

void getFieldAndKnightAndMonster(char** field, int& x, int& y, int& xKnight, int& yKnight, int& xMonster, int& yMonster) {
	cout << "insert field" << endl;
	for(int i = 0; i < y; i++) {
		field[i] = new char[x];
		for(int j = 0; j < x; j++) {
			cin >> field[i][j];
			if(field[i][j] == 'K') {
				yKnight = i;
				xKnight = j;
			}
			else if(field[i][j] == 'M') {
				yMonster = i;
				xMonster = j;
			}
		}
	}
}
void displayField(char** field,int& x, int& y) {	
	for(int i = 0; i < y; i++) {
		for(int j = 0; j < x; j++) {
			cout << field[i][j];
			if(j == x - 1) {
				cout << endl;
			}
		}
	}
}