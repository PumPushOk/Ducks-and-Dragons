#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

class Map
{
public:
	Map() {
		//Записуємо далі про розмір консолі
		GetConsoleScreenBufferInfo(hConsole, &screenInfo);

		//Відстань від верху, щоб помістити назву локації
		indents.Y = 2;
		//Симетричний відступ від боків екрану
		indents.X = (screenInfo.srWindow.Right - route[0].size()) / 2;

		//Переробляємо карту з нулів і одиниць в потрібний вигляд
		adaptRoute();
	}

	COORD getStartPos() {
		COORD startPos;
		//Шукаємо координати першої дороги від низу карти
		for (int i = route.size() - 1; i > 0; i--)
			for (int j = 0; j < route[i].size(); j++)
				if (route[i][j] != GRASS && route[i][j] != BORDER) {
					startPos.X = j;
					startPos.Y = i;
					return startPos;
				}
	}

	COORD getIndents() {
		return indents;
	}

	const vector<string>& getRoute() {
		return route;
	}

	const vector<COORD> getLocationCoords() {
		return locations;
	}

private:
	void adaptRoute() {
		//vector<string> newRoute = route;

		////Замінюємо всі 0, які оточені нулями, на символ трави
		//for (int i = 1; i < newRoute.size() - 1; ++i) {
		//	for (int j = 1; j < newRoute[i].size() - 1; ++j) {
		//		bool top = route[i - 1][j] == '0';
		//		bool bottom = route[i + 1][j] == '0';
		//		bool left = route[i][j - 1] == '0';
		//		bool right = route[i][j + 1] == '0';

		//		bool topLeft = route[i - 1][j - 1] == '0';
		//		bool topRight = route[i - 1][j + 1] == '0';
		//		bool bottomLeft = route[i + 1][j - 1] == '0';
		//		bool bottomRight = route[i + 1][j + 1] == '0';

		//		if (top && bottom && left && right && topLeft && topRight && bottomLeft && bottomRight)
		//			newRoute[i][j] = GRASS;
		//	}
		//}

		////Замінюємо всі 0, які залишились, на пробіл
		//for (int i = 0; i < newRoute.size(); ++i) {
		//	for (int j = 0; j < newRoute[i].size(); ++j) {
		//		if (newRoute[i][j] == '0')
		//			newRoute[i][j] = ' ';
		//	}
		//}

		////Малюємо дорогу
		//for (size_t i = 1; i < newRoute.size() - 1; ++i) {
		//	for (size_t j = 1; j < newRoute[i].size() - 1; ++j) {
		//		const char symbol = newRoute[i][j];

		//		if (symbol == '1') {
		//			bool top = route[i - 1][j] == '1';
		//			bool bottom = route[i + 1][j] == '1';
		//			bool left = route[i][j - 1] == '1';
		//			bool right = route[i][j + 1] == '1';

		//			//Цю частину можна оптимізувати, але це якщо буде час
		//			if (top && bottom && left && right)
		//				newRoute[i][j] = char(197);
		//			else if (top && bottom && left)
		//				newRoute[i][j] = char(180);
		//			else if (top && bottom && right)
		//				newRoute[i][j] = char(195);
		//			else if (top && left && right)
		//				newRoute[i][j] = char(193);
		//			else if (bottom && left && right)
		//				newRoute[i][j] = char(194);
		//			else if (top && left)
		//				newRoute[i][j] = char(217);
		//			else if (top && right)
		//				newRoute[i][j] = char(192);
		//			else if (bottom && left)
		//				newRoute[i][j] = char(191);
		//			else if (bottom && right)
		//				newRoute[i][j] = char(218);
		//			else if (top || bottom)
		//				newRoute[i][j] = char(179);
		//			else if (left || right)
		//				newRoute[i][j] = char(196);
		//		}
		//		else if (symbol != GRASS && symbol != BORDER) {
		//			newRoute[i][j] = '@';

		//			COORD coord;
		//			coord.Y = (short)i;
		//			coord.X = (short)j;

		//			locations.push_back(coord);
		//		}
		//	}
		//}

		//route = newRoute;
	}

	COORD indents;
	vector<COORD> locations;

	const char GRASS = '\'';
	const char BORDER = ' ';

	//Кожна стрічка має бути однакового розміру!
	vector<string> route = {
	   "00000000000000000000000000000000000000000000000",
	   "00000000000000000000000000000000000000000000000",
	   "00000000000000000000000000000000000000000000000",
	   "00000000000000000511111111111100000000000000000",
	   "00000000000100000000000000000100000000000000000",
	   "00000000000100000000000000000111111111111110000",
	   "00000000000100000000000000000100000000000000000",
	   "00000000000100000000000000000100000000000000000",
	   "00001111111100000000000000000100000000000000000",
	   "00001000000000000000000011111111111111111111000",
	   "00001000000000000000000010000000000000000001000",
	   "00001000000000000000000010000001111111300001000",
	   "00001111111111111111111110000001000000000001000",
	   "00000000000100000000000010000001000000000001000",
	   "00000000000100000411111110000001000000000001000",
	   "00000000000100000000000000000001111111111111000",
	   "00000000000100000000000000000001000000000000000",
	   "00000000000100000000000000000001000000000000000",
	   "00000000000100000111111111111111111111111000000",
	   "00000000000100000100000000000001000000001000000",
	   "00000000000100000100000000000001000000001000000",
	   "00002111111111111111111000000000000000001000000",
	   "00000000000000000000001000000000000000001000000",
	   "00000000000000000000001111111111111111111000000",
	   "00000000000000000000001000000000000000000000000",
	   "00000000000000000000001000000000000000000000000",
	   "00000000000000000000000000000000000000000000000",
	};

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
};

