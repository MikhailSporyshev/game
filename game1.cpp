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

	void walk(int* steps, char**& field, int xSize, int ySize) {
		for(int i = 0; i < 2; i++) {
			switch(steps[i]) {
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
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

int main() {
	int x, y;
	char** field = new char*[y];

	cout << "insert x y:" << endl;
	cin >> x >> y;
	
	bool flag = false;

	cout << "insert field" << endl;
	for(int i = 0; i < y; i++) {
		field[i] = new char[x];
		for(int j = 0; j < x; j++) {
			cin >> field[i][j];
			if(field[i][j] = 'K') {
				Knight holyKnight(i, j);
				flag = true;
			}
		}
	}

	if(flag) {
		cout << "insert 2 steps: 1 - right, 2- left, 3 - down, 4 - up" << endl;
		int steps[2];
		for(int i = 0; i < 2; i++) {
			cin >> steps[i];
		}

	}


	for(int i = 0; i < y; i++) {
		for(int j = 0; j < x; j++) {
			cout << field[i][j];
			if(j == x - 1) {
				cout << endl;
			}
		}
	}

	return 0;
}
