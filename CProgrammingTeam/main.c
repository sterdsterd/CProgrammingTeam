#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "common.h"
#include "console.h"

Object** map = NULL;
int difficulty;
const Difficulty difficultyCons[3] = {{51, 11, 20, 50}, {101, 21, 30, 100}, {151, 31, 50, 150}};
int charX, charY, mapSize, sightSize, bombAmount, moveCount;
int consoleX = 100, consoleY = 50;
int score = 0;

int main() {
	hideConsoleCursor();
	setConsoleSize(consoleX, consoleY);
	if (initLobby()) return 0;
	for (;;) {
		initGame();
		if (playGame() == 1) {
			gameOver();
			if (initLobby()) break;
		}
		else {
			difficulty++;
			for (int i = 0; i < mapSize; i++) {
				free(map[i]);
			}
			free(map);
		}
	}

	return 0;
}

int initLobby() {
	char ch;
	system("cls");
	printString(10, 9, "���̵��� �����ϼ���");
	printString(10, 11, "+-------------------------+");
	printString(10, 12, "| 0. EASY                 |");
	printString(10, 13, "+-------------------------+");
	printString(10, 15, "+-------------------------+");
	printString(10, 16, "| 1. NORMAL               |");
	printString(10, 17, "+-------------------------+");
	printString(10, 19, "+-------------------------+");
	printString(10, 20, "| 2. HARD                 |");
	printString(10, 21, "+-------------------------+");
	printString(10, 23, "+-------------------------+");
	printString(10, 24, "| 3. ����                 |");
	printString(10, 25, "+-------------------------+");
	while (1) {
		ch = _getch();
		if (ch >= '0' && ch <= '2') {
			difficulty = ch - '0';
			return 0;
		} else if (ch == '3') return 1;
	}
}

void initGame() {

	mapSize = difficultyCons[difficulty].mapSize;
	sightSize = difficultyCons[difficulty].sightSize;
	bombAmount = difficultyCons[difficulty].bombAmount;
	moveCount = difficultyCons[difficulty].moveCount;

	// ĳ������ x, y�� -> �� ���߾�
	charX = mapSize / 2;
	charY = mapSize / 2;

	// difficulty�� �°� map �迭 mapSize * mapSize ũ��� ���� �Ҵ�
	map = (Object**)malloc(sizeof(Object*) * mapSize);
	for (int i = 0; i < mapSize; i++) {
		map[i] = (Object*)malloc(sizeof(Object) * mapSize);
	}
	// map �迭 �ʱ�ȭ
	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			if (x == 0 || x == mapSize - 1 || y == 0 || y == mapSize - 1) {
				map[x][y].category = 'W';
			} else {
				map[x][y].category = '.';
			}
		}
	}

	// ���� ����
	int x = rand() % (mapSize - 2) + 1;
	int y = rand() % (mapSize - 2) + 1;
	map[x][y].category = 'T';
	map[x][y].isActive = 1;

	// ��ź ����
	for (int i = 0; i < bombAmount; i++) {
		int x = rand() % (mapSize - 2) + 1;
		int y = rand() % (mapSize - 2) + 1;
		map[x][y].category = 'B';
		map[x][y].isActive = 1;
	}

	// �þ� ����
	for (int i = 0; i < 10; i++) {
		int x = rand() % (mapSize - 2) + 1;
		int y = rand() % (mapSize - 2) + 1;
		map[x][y].category = 'S';
		map[x][y].isActive = 1;
	}

	// �þ� ����
	for (int i = 0; i < 10; i++) {
		int x = rand() % (mapSize - 2) + 1;
		int y = rand() % (mapSize - 2) + 1;
		map[x][y].category = 's';
		map[x][y].isActive = 1;
	}

	// �̵� Ƚ�� ����
	for (int i = 0; i < 10; i++) {
		int x = rand() % (mapSize - 2) + 1;
		int y = rand() % (mapSize - 2) + 1;
		map[x][y].category = 'M';
		map[x][y].isActive = 1;
	}

	// �̵� Ƚ�� ����
	for (int i = 0; i < 10; i++) {
		int x = rand() % (mapSize - 2) + 1;
		int y = rand() % (mapSize - 2) + 1;
		map[x][y].category = 'm';
		map[x][y].isActive = 1;
	}

}

int playGame() {
	system("cls");
	printSight();

	char ch;
	for (;;) {
		ch = _getch();
		int dx = 0, dy = 0;

		if (ch == 'w') dy--;
		else if (ch == 'a') dx--;
		else if (ch == 's') dy++;
		else if (ch == 'd') dx++;

		// �� ������ ����� ���ϰ�
		if (charX + dx <= 0 || charX + dx >= mapSize - 1 || charY + dy <= 0 || charY + dy >= mapSize - 1)
			continue;

		// �浹 üũ
		int c = collisionCheck(map, dx, dy);
		if (c) return c;

		printSight();
	}
}

int collisionCheck(Object** map, int dx, int dy) {
	switch (map[charX + dx][charY + dy].category) {
	case 'T':
		printQuote("�˸�", "������ ã�ҽ��ϴ�.");
		return 2;

	case 'B':
		printQuote("�˸�", "��ź�� ��ҽ��ϴ�.");
		return 1;

	case 'S':
		printQuote("�˸�", "�þ߰� �����Ǿ����ϴ�.");
		sightSize += 10;
		map[charX + dx][charY + dy].category = '.';
		break;

	case 's':
		printQuote("�˸�", "�þ߰� ���ҵǾ����ϴ�.");
		map[charX + dx][charY + dy].category = '.';
		sightSize -= 10;
		break;

	case 'M':
		printQuote("�˸�", "�̵� Ƚ���� �����Ǿ����ϴ�.");
		map[charX + dx][charY + dy].category = '.';
		moveCount += 15;
		break;

	case 'm':
		printQuote("�˸�", "�̵� Ƚ���� ���ҵǾ����ϴ�.");
		map[charX + dx][charY + dy].category = '.';
		moveCount -= 15;
		break;

	}

	charX += dx;
	charY += dy;
	score++;
	// �̵�Ƚ�� ���� �� ������ ���� ����
	if (--moveCount < 0) return 1;

	return 0;
}

void printSight() {

	gotoxy(0, 0);
	printf("���� �̵� Ƚ��: %d  ", moveCount);

	// startX, startY = �� ����Ʈ ���� ��ġ
	int startX = (consoleX / 2 - sightSize) / 2, startY = (consoleY - sightSize) / 2;
	gotoxy(startX - 1, startY - 1);
	for (int y = charY - sightSize / 2 - 1, i = 0; y <= charY + sightSize / 2 + 1; y++, i++) {
		for (int x = charX - sightSize / 2 - 1; x <= charX + sightSize / 2 + 1; x++) {
			// �þ� �׵θ� ǥ��
			if (x == charX - sightSize / 2 - 1 || x == charX + sightSize / 2 + 1 || y == charY - sightSize / 2 - 1 || y == charY + sightSize / 2 + 1)
				printf("* ");
			// �� �� ǥ��
			else if (x < 0 || x > mapSize - 1 || y < 0 || y > mapSize - 1)
				printf("  ");
			// �÷��̾� ǥ��
			else if (x == charX && y == charY) printf("P ");
			// �� �� ������Ʈ ǥ��
			else printf("%c ", categoryToChar(map[x][y].category));
		}
		gotoxy(startX - 1, startY + i);
	}

	// DEBUG
	// gotoxy(0, 0);
	// printf("x: %d; y: %d        ", charX, charY);
}

void gameOver() {

	// �����Ҵ� ����
	for (int i = 0; i < mapSize; i++) {
		free(map[i]);
	}
	free(map);

	system("cls");
	printString(10, 10, "GAME OVER");
	gotoxy(10, 12);
	printf("SCORE: %d", score);
	printString(10, 14, "Press any key to continue");

	score = 0;
	_getch();
}
