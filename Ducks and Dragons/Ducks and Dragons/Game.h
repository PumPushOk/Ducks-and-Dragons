#pragma once
#include <conio.h>
#include "Anotation.h"
#include "Map.h"
#include "Battle.h"
#include "Location.h"

#include "Duck.h"
#include "Dragon.h"
#include "Shrek.h"
#include "Boss.h"

#define ENTER 13
enum Arrows { Arrow = 224, Up = 72, Down = 80, Left = 75, Right = 77 };

class Game
{
public:
	void run() {
		string titles = "DUCKS & DRAGONS";
		Annotation title(titles);
		title.printTitle();

		printAnnotation(annotationText);

		while (true) {
			printMap();

			//Ініціалізуємо локації
			createLocation();

			Location enteredLocation = mapPlayerMoving();

			system("cls");

			battle.startBattle(player, enteredLocation.enemy);

			_getch();

			if (battle.isFriend() && isPlayed == false) {
				printAnnotation(DragonF);
				isPlayed = true;
			}
			if (battle.isDead()) {
				if (battle.isFriend())
					printAnnotation(goodEnd);
				else
					printAnnotation(badEnd);
				return;
			}
		}
	}

	Game() {
		//Міняю назву вікна
		SetConsoleTitleA("Ducks & Dragons");

		//Не дозволяє змінювати розмір консолі
		HWND hwndConsole = GetConsoleWindow();
		LONG style = GetWindowLong(hwndConsole, GWL_STYLE);
		style &= ~WS_THICKFRAME; // Видалити WS_THICKFRAME
		SetWindowLong(hwndConsole, GWL_STYLE, style);

		//Невидимий курсор
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hConsole, &cursorInfo);

		//Записуємо далі про розмір консолі
		GetConsoleScreenBufferInfo(hConsole, &screenInfo);
	}

private:

#pragma region MapService

	void printMap() {
		vector<string> route = map.getRoute();

		for (size_t i = 0; i < route.size(); ++i) {
			COORD position = map.getIndents();
			position.Y += (short)i;

			for (size_t j = 0; j < route[0].size(); ++j) {
				position.X++;
				SetConsoleCursorPosition(hConsole, position);
				cout << route[i][j];
			}
		}
	}

	Location mapPlayerMoving() {
		vector<string> route = map.getRoute();

		//Координати появи гравця
		static COORD playerPos = map.getStartPos();

		//Відступи карти від верхньої і нижньої сторін
		COORD indents = map.getIndents();

		//Координати гравця враховуючи відступи
		COORD outputPos;
		outputPos.Y = indents.Y + playerPos.Y;
		outputPos.X = indents.X + playerPos.X + 1;

		const char player = '*';
		SetConsoleCursorPosition(hConsole, outputPos);
		cout << player;

		bool isAtLocation = false;
		while (true) {
			Location curLocation = getLocation(playerPos);
			if (!curLocation.name.empty()) {
				isAtLocation = true;
				showLocationName(curLocation.name);
			}

			if (_kbhit()) {
				unsigned char ch = _getch();

				if (ch == Arrow) {
					ch = _getch();

					SetConsoleCursorPosition(hConsole, outputPos);
					cout << route[playerPos.Y][playerPos.X];

					COORD previousPos = playerPos;
					if (ch == Up && route[playerPos.Y - 1][playerPos.X] != ' ') {
						playerPos.Y--;
						outputPos.Y--;
					}
					else if (ch == Down && route[playerPos.Y + 1][playerPos.X] != ' ') {
						playerPos.Y++;
						outputPos.Y++;
					}
					else if (ch == Left && route[playerPos.Y][playerPos.X - 1] != ' ') {
						playerPos.X--;
						outputPos.X--;
					}
					else if (ch == Right && route[playerPos.Y][playerPos.X + 1] != ' ') {
						playerPos.X++;
						outputPos.X++;
					}

					SetConsoleCursorPosition(hConsole, outputPos);
					cout << player;

					if (previousPos.Y != playerPos.Y || previousPos.X != playerPos.X) {
						isAtLocation = false;
						for (int i = 0; i < curLocation.name.size(); i++)
							curLocation.name[i] = ' ';
						showLocationName(curLocation.name);
					}
				}
				else if (ch == ENTER && isAtLocation) {
					return curLocation;
				}
			}
		}
	}

	const Location& getLocation(COORD pos) {
		//Виводимо назву локації, якщо стоїмо на ній
		for (auto i : locations)
			if (pos.X == i->coord.X && pos.Y == i->coord.Y) {
				pos.Y = 1;
				pos.X = (screenInfo.srWindow.Right - i->name.size()) / 2;
				return *i;
			}
		return Location(string(), COORD(), nullptr);
	}

	void showLocationName(const string& locName) {
		COORD namePos;
		namePos.Y = 1;
		namePos.X = (screenInfo.srWindow.Right - locName.size()) / 2;

		SetConsoleCursorPosition(hConsole, namePos);
		cout << locName;
	}

#pragma endregion

#pragma region LocationService

	void createLocation() {
		vector<COORD> locationCoords = map.getLocationCoords();

		if (!locations.empty())
			locations.clear();

		locations.push_back(new Location("Castle", locationCoords[0], new Boss()));
		locations.push_back(new Location("Field", locationCoords[1], new Duck()));
		locations.push_back(new Location("Swamp", locationCoords[2], new Ogre()));
		if (battle.isFriend()) {
			locations.push_back(new Location("Mountain", locationCoords[3], new Ogre()));
		}
		else
			locations.push_back(new Location("Mountain", locationCoords[3], new Dragon()));
	}

	void printAnnotation(const string& text) {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		Annotation annotation(text);
		annotation.printStar();
		annotation.printAnnotation();

		SetConsoleCP(437);
		SetConsoleOutputCP(437);

		system("cls");
	}

#pragma endregion 

	bool isPlayed = false;

	vector<Location*> locations;

	Player player;

	Battle battle;

	Map map;

	string goodEnd = "Після довгих битв і важких випробувань Дакі разом зі своїм союзником завоював перемогу.~За допомогою знань, які він здобув у своїй подорожі, він зміг привести до миру між людьми~і драконами, врятувавши таким чином королівство від загибелі.Найважливіше, що він~розкрив таємницю свого походження, яка відкрила його справжнє покликання.Виявилося,~що він є справжнім спадкоємцем давніх правителів королівства, і його місце на троні було~відновлено.Завдяки мудрості і рішучості він став справедливим та мудрим правителем,~який забезпечив процвітання і благополуччя свого народу.~~~\t\t\t\t\tHAPPY END!";
	string badEnd = "Дакі з владою перлини, завдає рішучий удар своєму дядькові та його армії. Він використовує~магічну силу перлини, щоб перемогти ворогів і захистити королівство від знищення. Проте~ця перемога приходить із великою ціною. Королівство залишається без свого наймогутнішого~захисника - дракона, і Дакі відчуває тягар від свого вчинку. Його влада забруджена~кров'ю та зрадою.Дакі, відчуваючи вину та сором за свої дії, відправляється у самотню~подорож, спрямовану на пошук пробачення та відновлення миру в своєму королівстві.~Він покликає народ до спільної реконструкції та примирення,~намагаючись виправити свої помилки і створити краще майбутнє для всіх.~~~\t\t\t\t\tEND!";
	string annotationText = "Мій день розпочинався як завжди - раннім підйомом і рутинними обов'язками селянина.~Я, Дакі, молодий селянин, проживаю в самому серці середньовічного королівства.~Але моє життя змінилося, коли під час полювання я натрапив на дивну підвіску з вишукано~вишитим гербом королівства та моїм ім'ям.Ця знахідка здивувала мене, і я відчув,~що це не просто випадковість. Цікавість та бажання розкрити таємницю підштовхнули мене ~на небезпечну подорож, щоб з'ясувати, що сховано за цими загадковими знаками.~Так розпочалася моя подорож в невідоме, в пошуках власного минулого і таємниць,~що чекають на мене в королівстві.";
	string DragonF = "Дракон побачив підвіску.Дакі встановитив взаєморозуміння з драконом.";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	CONSOLE_CURSOR_INFO cursorInfo;
};

