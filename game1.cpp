#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
 
using namespace std;
 
ifstream input("map.txt");

struct Medkit;
struct Character;
 
struct Actor {
    bool isAlive;
    char sign;
    int x, y;

    Actor(int i, int j): y(i), x(j), isAlive(true) {}

    virtual void collide(Actor* a) {}
    virtual void collide(Medkit* m) {}
    virtual void collide(Character* c) {}
    virtual void Move(list<Actor*>& actors, vector<string>& field) {}
};
 
struct Medkit: Actor {
    int val = 100;
    
    Medkit(int i, int j):Actor(i,j) {
        sign = '+';
    }

    void collide(Actor* a) override {
        a->collide(this);
    }
 
    void collide(Character* c) override;
};
 
struct Character: Actor {   
    int hp = 100;
    int dmg = 20;

    Character(int i, int j):Actor(i, j) {
        sign = 'C';
    }

    void getHit(int getDamage) {
        this->hp -= getDamage;
        if(this->hp <= 0) {
            this->isAlive = false; 
        }
    }

    void collide(Actor* a) override {
        a->collide(this);
        a = this;
    }
 
    void collide(Medkit* m) override {
        hp += m->val;
        cout << "+" << m->val << endl;
        m->isAlive = false;
    }

    void collide(Character* c) override {
        while(c->isAlive && this->isAlive) {
            cout << " atacker deals: " << c->dmg;
            this->getHit(c->dmg);
            cout << " defenders health: " << this->hp << endl;
            if(this->isAlive) {
                cout << " defender deals: " << this->dmg;
                c->getHit(this->dmg);
                cout << " atackers health: " << c->hp << endl;    
            }        
        }
        if(this->isAlive) {
            cout << " atacker died" << endl;
        }
        else {
            cout << " defender died" << endl;
        }
    }
    virtual void Move(list<Actor*>& actors, vector<string>& field) {}
};

struct Knight: Character {
    Knight(int i, int j):Character(i, j) {
        sign = 'K';
    }

    char makeStep() {
        char step;
        cin >> step;
        return step;
    };

    void Move(list<Actor*>& actors, vector<string>& field) override {
        if(!this->isAlive) {
            return;
        }
        char step = makeStep();
        int nextY = this->y; 
        int nextX = this->x;
        if(step == 'w') {
            nextY--;
        }
        else if(step == 's') {
            nextY++;
        }
        else if(step == 'd') {
            nextX++;
        }
        else if(step == 'a') {
            nextX--;
        }
        else {
            return;
        }
        if((nextY < field.size() && nextY >= 0 )&&
         (nextX < field[0].length() && nextX >= 0) &&
          field[nextY][nextX] != '#') {
            if(field[nextY][nextX] != '.') {
                list<Actor*>::iterator iter = actors.begin(); 
                while(!((*iter)->y == nextY && (*iter)->x == nextX)) {
                    ++iter;
                }
                this->collide(*iter);
            }
            field[y][x] = '.';
            if(this->isAlive) {
                y = nextY;
                x = nextX;
                field[y][x] = this->sign;
            }
        }
    }
};

struct Zombie: Character {
    Zombie(int i, int j):Character(i, j) {
        sign = 'Z';
    }

    int makeStep() {
        int step = rand() % 4 + 1;
        return step;
    };

    void Move(list<Actor*>& actors, vector<string>& field) override {
        if(!this->isAlive) {
            return;
        }
        int step = makeStep();
        int nextY = this->y; 
        int nextX = this->x;
        if(step == 1) {
            nextY--;
        }
        else if(step == 2) {
            nextY++;
        }
        else if(step == 3) {
            nextX++;
        }
        else if(step == 4) {
            nextX--;
        }
        if((nextY < field.size() && nextY >= 0 )&&
         (nextX < field[0].length() && nextX >= 0) &&
          field[nextY][nextX] != '#' &&
          field[nextY][nextX] != 'Z') {      
            if(field[nextY][nextX] != '.') {
                list<Actor*>::iterator iter = actors.begin(); 
                
                while(!((*iter)->y == nextY && (*iter)->x == nextX)) {
                    ++iter;
                }
                
                this->collide(*iter);
            }
            field[y][x] = '.';
            
            if(this->isAlive) {
                y = nextY;
                x = nextX;
                field[y][x] = this->sign;
            }
        }
    }
};
 
void Medkit::collide(Character* c) {
    c->collide(this);
}

void getField(vector<string>& field);
void displayField(vector<string>& field);

int main() {
    vector<string> field;
    list<Actor*> actors;
    Knight* knightPtr;


    getField(field);
    cout << "here" <<                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    endl;
    displayField(field);
/*
    for(int i = 0; i < field.size(); i++) {
	    for(int j = 0; j < field[0].length(); j++) {
	        if(field[i][j] == 'Z') {
	            actors.push_back(new Zombie(i, j));
	        }
	        else if(field[i][j] == 'K') {
	            knightPtr = new Knight(i, j);
                actors.push_front(knightPtr);
	        }
            else if(field[i][j] == '+') {
                actors.push_back(new Medkit(i, j));
            }
	    }
    } 
    while((*actors.begin())->isAlive) {
        for(list<Actor*>:: iterator iter = actors.begin(); iter != actors.end(); ++iter) {
            (*iter)->Move(actors, field);
    	}
	    displayField(field);
    }*/
    return 0;
}

void getField(vector<string>& field) {
	string buffer;
	getline(input, buffer);
	while(!buffer.empty()) {
		field.push_back(buffer);
		getline(input, buffer);
	}
}
void displayField(vector<string>& field) {
	for(int i = 0; i < field.size(); i++) {
		cout << field[i] << endl;
	}
}