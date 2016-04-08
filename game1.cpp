#include <iostream>

using namespace std;

class Knight{
	int damage;
	int health;
	int speed;

	int x;
	int y;
public:
	Knight(int inputX, int inputY):x(inputX), y(inputY) {
		damage = 2;
		health = 2;
		speed = 2;
	}

	void walk(int step, char**& field, int xSize, int ySize) {
		switch(step) {
			case 1: if(field[x + 1][y] != '#' && xSize - 1 - x > 1) {
				field[x][y] = '.';
				x++;
				field[x][y] = 'K';
			}
			case 2: if(field[x - 1][y] != '#' &&  x > 0) {
				field[x][y] = '.';
				x--;
				field[x][y] = 'K';
			}
			case 3: if(field[x][y + 1] != '#' && ySize - 1 - y > 1) {
				field[x][y] = '.';
				y++;
				field[x][y] = 'K';
			}
			case 4: if(field[x][y - 1] != '#' &&  y > 0) {
				field[x][y] = '.';
				y--;
				field[x][y] = 'K';
			}
		}
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

void getFieldAndKnight(char** field,int& x, int& y, int& xKnight, int& yKnight);
void displayField(char** field,int& x, int& y);

int main() {
	int x, y;
	char** field = new char*[y];
	int xKingt = 0, yKnight = 0;

	int step = 0;

	cout << "insert x y:" << endl;
	cin >> x >> y;
	
	getFieldAndKnight(field, x, y, xKingt, yKnight);


	Knight holyKnight(xKingt, yKnight);	


	cout << "insert step: 1,2,3,4" << endl;
	cin >> step;
	while(step > 0) {
		holyKnight.walk(step, field, x, y);
		displayField(field, x, y);
		cin >> step;
	}

	return 0;
}

void getFieldAndKnight(char** field, int& x, int& y, int& xKnight, int& yKnight) {
	cout << "insert field" << endl;
	for(int i = 0; i < y; i++) {
		field[i] = new char[x];
		for(int j = 0; j < x; j++) {
			cin >> field[i][j];
			if(field[i][j] == 'K') {
				xKnight = i;
				yKnight = j;
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