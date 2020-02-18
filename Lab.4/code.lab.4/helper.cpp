#include "header.h"
	Game initGame(char userChar) {
		Game gm;

			//заполнение поля пробелами
			for (int width = 0; width < 3; width++) {
				for (int height = 0; height < 3; height++) gm.bord[width][height] = ' ';
			}
		//случайное распределение хода
		for (int width = 0; width < 3; width++) {
			for (int height = 0; height < 3; height++) {
				gm.bord[width][height] = ' ';
			}
		}
		srand(time(NULL));
		gm.isUserTurn = bool(rand() % 3);

		gm.userChar = userChar;
		switch (gm.userChar) {
		case 'O':
			gm.botChar = 'X';
			break;
		case 'X':
			gm.botChar = '0';
			break;
		}

		return gm;
	}

	void updateDisplay(const Game game) {
		system("cls");										

		for (int width = 0; width < 3; width++) {			
			cout << width << " : ";							
			for (int height = 0; height < 3; height++) {	
				cout << game.bord[width][height] << " : ";	
			}							 
			cout << endl << "  ............." << endl;		
		}												
		cout << "    0   1   2 " << endl;
	}

	void botTurn(Game* game) {
		bool is_clear = true;
		for (int width = 0; width < 3; width++) {
			for (int height = 0; height < 3; height++) {
				if (game->bord[width][height] != ' ') {
					is_clear = false;
					break;
				}
			}
		}
		if (is_clear) game->bord[1][1] = game->botChar;

		else {
			for (auto& width : game->bord) {
				int val = 0;
				int len = 0;
				bool flag = false;
				for (int height = 0; height < 3; height++) {
					if (width[height] == game->userChar) {
						len++;
					}
					else if (width[height] != game->botChar) {
						val = height;
						flag = true;
					}
				}
				if ((len == 2) && flag) {
					width[val] = game->botChar;
					return;
				}
			}

			for (int width = 0; width < 3; width++) {
				int val = 0;
				int len = 0;
				bool flag = false;
				for (int height = 0; height < 3; height++) {
					if (game->bord[height][width] == game->userChar) {
						len++;
					}
					else if (game->bord[height][width] != game->botChar) {
						val = height;
						flag = true;
					}
				}
				if ((len == 2) && flag) {
					game->bord[val][width] = game->botChar;
					return;
				}
			}

			{
				int val = 0;
				int len = 0;
				bool flag = false;
				for (int width = 0; width < 3; width++) {
					if (game->bord[width][width] == game->userChar) {
						len++;
					}
					else if (game->bord[width][width] != game->botChar) {
						val = width;
						flag = true;
					}
				}
				if ((len == 2) && flag) {
					game->bord[val][val] = game->botChar;
					return;
				}
			}
			
			{
				int val = 0;
				int len = 0;
				bool flag = false;
				for (int width = 0; width < 3; width++) {
					if (game->bord[width][2 - width] == game->userChar) {
						len++;
					}
					else  if (game->bord[width][2 - width] != game->botChar) {
						val = width;
						flag = true;
					}
				}
				if ((len == 2) && flag) {
					game->bord[val][2 - val] = game->botChar;
					return;
				}
			}

			int width = 0;
			int height = 0;
			while (game->bord[width][height] != ' ') {
				width = rand() % 3;
				height = rand() % 3;
			}
			game->bord[width][height] = game->botChar;
		}
	}

	void userTurn(Game* game) {
		int width = 0, height;
		bool flag_wd = true, flag_hg = true, flag_all = true;
		while (flag_all) {
			while (flag_wd) {
				cout << endl << "Y:  ";
				cin >> width;
				if ((width < 0) || (width > 2)) {
					cout << "Выход за пределы поля­" << endl;
				}
				else {
					flag_wd = false;
				}
			}
			while (flag_hg) {
				cout << endl << "X:  ";
				cin >>height;
				if ((height < 0) || (height > 2)) {
					cout << "Выход за пределы поля" << endl;
				}
				else {
					flag_hg = false;
				}
			}
			if (game->bord[width][height] == ' ') {
				flag_all = false;
			}
			else {
				cout << "Позиция занята" << endl;
				flag_wd = true;
				flag_hg = true;
			}
		}
		game->bord[width][height] = game->userChar;
	}
	bool updateGame(Game* game) {
		for (int width = 0; width < 3; width++) {
			int len2 = 0;
			int len1 = 0;
			for (int height = 0; height < 3; height++) {
				if (game->bord[width][height] == game->userChar) {
					len1++;
				}
				else if (game->bord[width][height] == game->botChar) {
					len2++;
				}
			}
			if ((len1 == 3) || (len2 == 3)) {
				game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
				return true;
			}
		}

 		for (int width = 0; width < 3; width++) {
			int len2 = 0;
			int len1 = 0;
			for (int height = 0; height < 3; height++) {
				if (game->bord[height][width] == game->userChar) {
					len1++;
				}
				else if (game->bord[height][width] == game->botChar) {
					len2++;
				}
			}
			if ((len1 == 3) || (len2 == 3)) {
				game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
				return true;
			}
		}

		{
			int len2 = 0;
			int len1 = 0;
			for (int width = 0; width < 3; width++) {
				if (game->bord[width][width] == game->userChar) {
					len1++;
				}
				else if (game->bord[width][width] == game->botChar) {
					len2++;
				}
			}
			if ((len1 == 3) || (len2 == 3)) {
				game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
				return true;
			}
		}

		{
			int len2 = 0;
			int len1 = 0;
			for (int width = 0; width < 3; width++) {
				if (game->bord[width][2 - width] == game->userChar) {
					len1++;
				}
				else if (game->bord[width][2 - width] == game->botChar) {
					len2++;
				}
			}
			if ((len1 == 3) || (len2 == 3)) {
				game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
				return true;
			}
		}
		int len = 0;
		for (int width = 0; width < 3; width++) {
			for (int height = 0; height < 3; height++) {
				if (game->bord[width][height] != ' ') {
					len++;
				}
			}
		}
		if (len == 9) {
			game->status = NOT_WIN;
			return true;
		}
		game->status = PLAY;
		return false;
	}
