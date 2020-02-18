#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;


	enum Status {
		PLAY,            // Игра продолжается
		USER_WIN,        // Игрок победил
		BOT_WIN,         // Бот победил
		NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
	};

	struct Game {
		char bord[3][3];  // Игровое поле
		bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
		char userChar;    // Символ которым играет пользователь
		char botChar;     // Символ которым играет бот
		Status status;
	};

	Game initGame(char);

	void updateDisplay(const Game);

	void botTurn(Game*);

	void userTurn(Game*);

	bool updateGame(Game*);