#include "header.h"
char player;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	while (player != 'X' && player != 'O') {
		cout << "��������� ������ 'X' ��� 'O': " << endl;
		cin >> player;
	}

	Game game = initGame(player);
	if (game.isUserTurn) {
		while (true) {
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) break;
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) break;
		}
	}
	else {
		while (true) {
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) break;
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game)) break;
		}
	}
	switch (game.status) {
	case USER_WIN:
		cout << "�� ��������";
		break;
	case BOT_WIN:
		cout << "�� ���������";
		break;
	case NOT_WIN:
		cout << "�����";
		break;
	}
	cout << endl;
}