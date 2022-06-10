#include <Windows.h>

void gotoxy(int x, int y) {
	COORD Cur = {x * 2, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void setConsoleSize(int x, int y) {
	SMALL_RECT windowSize = {0, 0, x, y};
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

/*
0 = ������
1 = �Ķ���
2 = �ʷϻ�
3 = ����
4 = ������
5 = ���ֻ�
6 = �����
7 = ���
8 = ȸ��
9 = ���� �Ķ���
10 = ���� �ʷϻ�
11 = ���� ����
12 = ���� ������
13 = ���� ���ֻ�
14 = ���� �����
15 = ���� ���
*/
const struct {
	char BLACK, GREEN, RED, YELLOW, GREY, DARK_GREY, WHITE;
} COLOR = {0, 2, 4, 6, 7, 8, 15};

void setTextColor(int code) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}

void hideConsoleObjects() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);
}

void printString(int x, int y, char s[]) {
	gotoxy(x, y);
	printf("%s", s);
}

void printQuote(char* name, char* line) {
	gotoxy(0, 43);
	printf(" ��������������������������\n �� %s", name);
	gotoxy(6, 44);
	printf(" ��");
	gotoxy(0, 45);
	printf(" ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf(" ��                                                                                                  ��\n");
	printf(" ��                                                                                                  ��\n");
	printf(" ��                                                                                                  ��\n");
	printf(" ��                                                                                                  ��\n");
	printf(" ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	gotoxy(1, 46);
	printf(" %s", line);
	//_getch();

}

void printSequence(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		printf("%c", str[i]);
		Sleep(50);
	}
}

void cls() {
	system("cls");
}