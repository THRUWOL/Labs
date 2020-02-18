#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;


	enum Status {
		PLAY,            // ���� ������������
		USER_WIN,        // ����� �������
		BOT_WIN,         // ��� �������
		NOT_WIN          // �����. ���������� ���, �� � �� ���� ��� ��������� ������
	};

	struct Game {
		char bord[3][3];  // ������� ����
		bool isUserTurn;  // ��� ���. ���� ������������, �� isUserTurn = true
		char userChar;    // ������ ������� ������ ������������
		char botChar;     // ������ ������� ������ ���
		Status status;
	};

	Game initGame(char);

	void updateDisplay(const Game);

	void botTurn(Game*);

	void userTurn(Game*);

	bool updateGame(Game*);