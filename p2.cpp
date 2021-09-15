// p2.cpp

#include <iostream>
#include <ctime>
#include <cmath>
#include <conio.h>

#define GAME_WIDTH 10
#define GAME_HEIGHT 10

using namespace std;

class Tile {
	int number;
	int x;
	int y;
	bool isMine;
	bool isOpen;
public:
	int getNumber() {
		return number;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	bool getMine() {
		return isMine;
	}
	bool getOpen() {
		return isOpen;
	}
	void setNumber(int number) {
		this->number = number;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setMine(bool isMine) {
		this->isMine = isMine;
	}
	void setOpen(bool isOpen) {
		this->isOpen = isOpen;
	}
};

class Cursor {
	int x = 0;
	int y = 0;
public:
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
};

int main()
{
	srand((unsigned int)time(NULL));

	Tile map[GAME_HEIGHT][GAME_WIDTH];

	Cursor cur;

	bool isGameover = false;

	// ¸Ê »ý¼º
	for (int i = 0; i < GAME_HEIGHT; i++) {
		for (int j = 0; j < GAME_WIDTH; j++) {
			map[i][j].setX(j);
			map[i][j].setY(i);
			map[i][j].setOpen(false);
			map[i][j].setMine(rand() % 10 == 0);
		}
	}

	// Áö·Ú °¨Áö
	for (int i = 0; i < GAME_HEIGHT; i++) {
		for (int j = 0; j < GAME_WIDTH; j++) {
			if (!map[i][j].getMine()) {
				int mineCount = 0;

				if (i > 0) {
					if (map[i - 1][j].getMine()) {
						mineCount++;
					}
				}

				if (i > 0 && j > 0) {
					if (map[i - 1][j - 1].getMine()) {
						mineCount++;
					}
				}

				if (j > 0) {
					if (map[i][j - 1].getMine()) {
						mineCount++;
					}
				}

				if (i < GAME_HEIGHT - 1 && j > 0) {
					if (map[i + 1][j - 1].getMine()) {
						mineCount++;
					}
				}

				if (i < GAME_HEIGHT - 1) {
					if (map[i + 1][j].getMine()) {
						mineCount++;
					}
				}

				if (i < GAME_HEIGHT - 1 && j < GAME_WIDTH - 1) {
					if (map[i + 1][j + 1].getMine()) {
						mineCount++;
					}
				}

				if (j < GAME_WIDTH - 1) {
					if (map[i][j + 1].getMine()) {
						mineCount++;
					}
				}

				if (i > 0 && j < GAME_WIDTH - 1) {
					if (map[i - 1][j + 1].getMine()) {
						mineCount++;
					}
				}

				map[i][j].setNumber(mineCount);
			}
		}
	}

	do {
		// ¸Ê ·»´õ¸µ
		system("cls");
		for (int i = 0; i < GAME_HEIGHT; i++) {
			for (int j = 0; j < GAME_WIDTH; j++) {
				if (map[i][j].getX() == cur.getX() && map[i][j].getY() == cur.getY()) {
					cout << "@";
				}
				else {
					//if (!map[i][j].getOpen()) {
					//	cout << "?";
					//}
					//else {
						if (map[i][j].getMine()) {
							cout << "*";
						}
						else {
							cout << map[i][j].getNumber();
						}
					//}
				}
			}
			cout << endl;
		}

		// Å° ÀÔ·Â
		int op = _getch();
		switch (op) {
		case 75:
			// left
			if (cur.getX() > 0) {
				cur.setX(cur.getX() - 1);
			}
			break;
		case 77:
			// right
			if (cur.getX() < GAME_WIDTH -1 ) {
				cur.setX(cur.getX() + 1);
			}
			break;
		case 72:
			// up
			if (cur.getY() > 0) {
				cur.setY(cur.getY() - 1);
			}
			break;
		case 80:
			// down
			if (cur.getY() < GAME_HEIGHT - 1) {
				cur.setY(cur.getY() + 1);
			}
			break;
		case 20:
			// detect
			map[cur.getX()][cur.getY()].setOpen(true);
			if (map[cur.getX()][cur.getY()].getMine()) {
				isGameover = true;
			}
			break;
		}
	} while (!isGameover);
}