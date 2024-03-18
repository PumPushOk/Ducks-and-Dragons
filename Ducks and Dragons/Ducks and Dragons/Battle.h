#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Location.h"
#include "Player.h"

using namespace std;

enum Options { Attack, Defence, Items, Leave };

class Battle
{
public:
	void startBattle(Player& player, Enemy* enemy) {
		printEnemy(enemy);

		short upperline = enemy->shape.size() - 1;
		printLine(upperline);
		short lowerLine = upperline + 2;
		printLine(lowerLine);

		printStats(enemy);
		printStats(player);

		while (player.health > 0 && enemy->health > 0) {
			int chosenOption = navigateMenu(lowerLine + 1);

			optionLogic(player, enemy, chosenOption);

			printStats(enemy);
			printStats(player);
		}

		Sleep(1000);

		endBattle(player, enemy);
	}


	Battle() {
		GetConsoleScreenBufferInfo(hConsole, &screenInfo);
	}

	bool isFriend() {
		return isDragonFriend;
	}

	bool isDead() {
		return isUncleDead;
	}
private:

#pragma region PrintMethods

	void printEnemy(Enemy* enemy) {
		int sideIndent = (screenInfo.srWindow.Right - enemy->shape[0].size()) / 2;

		for (size_t i = 0; i < enemy->shape.size(); ++i) {
			COORD pos;
			pos.Y = i;

			for (size_t j = 0; j < enemy->shape[i].size(); ++j) {
				char symbol = enemy->shape[i][j];

				pos.X = sideIndent + j;
				SetConsoleCursorPosition(hConsole, pos);

				if (symbol == '~') {
					cout << " ";
				}
				else if (symbol == '0') {
					SetConsoleTextAttribute(hConsole, 0x0);//чорний
					cout << (char)178;
				}
				else if (symbol == '1') {
					SetConsoleTextAttribute(hConsole, 0x0);//чорний 
					cout << (char)178;
				}
				else if (symbol == '2') {
					SetConsoleTextAttribute(hConsole, 0x2);//зелений
					cout << (char)178;
				}
				else if (symbol == '4') {
					SetConsoleTextAttribute(hConsole, 0x4);//рожевий
					cout << (char)178;
				}
				else if (symbol == '6') {
					SetConsoleTextAttribute(hConsole, 0x6);//жовтий колір
					cout << (char)178;
				}
				else if (symbol == '7') {
					SetConsoleTextAttribute(hConsole, 0x7);//білий
					cout << (char)178;
				}
				else if (symbol == '8') {
					SetConsoleTextAttribute(hConsole, 0x8);//сірий
					cout << (char)178;
				}
				else if (symbol == 'A') {

					SetConsoleTextAttribute(hConsole, 0xA); //світл зелений
					cout << (char)178;
				}
				else if (symbol == 'F') {
					SetConsoleTextAttribute(hConsole, 0xF);// світло білий
					cout << (char)178;
				}
				else if (symbol == 'D') {
					SetConsoleTextAttribute(hConsole, 0xD);//рожевий
					cout << (char)178;
				}
				else if (symbol == 'E') {
					SetConsoleTextAttribute(hConsole, 0xE);//світло жовтий
					cout << (char)178;
				}
				else if (symbol == 'B') {
					SetConsoleTextAttribute(hConsole, 0xB);//світло голуб 
					cout << (char)178;
				}
				else if (symbol == 'C') {
					SetConsoleTextAttribute(hConsole, 0xC);//світло червоний
					cout << (char)178;
				}
			}
		}

		SetConsoleTextAttribute(hConsole, 0x7);
	}

	void printStats(Enemy* enemy) {
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		cout << "\t\t" << "     " << endl <<
			"\tHealth: " << "     " << endl <<
			"Damage: " << "     " << endl;

		SetConsoleCursorPosition(hConsole, { 0, 0 });
		cout << "\t\t" << enemy->name << endl <<
			"\tHealth: " << enemy->health << endl <<
			"Damage: " << enemy->damage << endl;
	}

	void printStats(Player player) {
		COORD pos;
		pos.Y = 0;
		pos.X = screenInfo.srWindow.Right - 25;

		SetConsoleCursorPosition(hConsole, pos);
		cout << "Player";

		pos.Y++;
		pos.X += 6;
		SetConsoleCursorPosition(hConsole, pos);
		cout << "Health: " << "            ";
		SetConsoleCursorPosition(hConsole, pos);
		cout << "Health: " << player.health << '/' << player.maxHealth;

		pos.Y++;
		pos.X += 7;
		SetConsoleCursorPosition(hConsole, pos);
		cout << "Damage: " << "        ";
		SetConsoleCursorPosition(hConsole, pos);
		cout << "Damage: " << player.damage;
	}

	void printLine(short lineY) {
		SetConsoleCursorPosition(hConsole, { 0, lineY });
		for (int i = 0; i < screenInfo.srWindow.Right; i++)
			cout << '-';
	}

#pragma endregion 

#pragma region BattleLogic

	void printOptions(short lineY, int selectedOptionIndex) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int totalOptionsLength = 0;
		for (const auto& option : options) {
			totalOptionsLength += option.length() + 2; // Adding 2 for the space and the selector symbols
		}
		int spaceBetween = (columns - totalOptionsLength) / (options.size() + 1);
		int currentPosition = spaceBetween;

		for (int i = 0; i < options.size(); i++) {
			SetConsoleCursorPosition(hConsole, { (short)(currentPosition), lineY });
			cout << (i == selectedOptionIndex ? ">" : " ") << options[i] << (i == selectedOptionIndex ? "<" : " ");
			currentPosition += options[i].length() + spaceBetween + 2; // Adjusting for the selector symbols
		}
		cout << endl;
	}

	int navigateMenu(int lineY) {
		int selectedOptionIndex = 0;

		while (true) {
			printOptions(lineY, selectedOptionIndex);
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == 75 && selectedOptionIndex > 0) {
					selectedOptionIndex--;
				}
				else if (key == 77 && selectedOptionIndex < options.size() - 1) {
					selectedOptionIndex++;
				}
			}
			else if (key == 13) {
				return selectedOptionIndex;
				break;
			}
		}
	}

	void optionLogic(Player& player, Enemy* enemy, int option) {
		switch (option) {
		case Attack:
			player.attack(enemy);
			break;
		case Defence:
			if (enemy->name == "Toothless") {
				isDragonFriend = true;
				player.health = 0;

			}
			else {
				player.health += enemy->damage / 2;
			}
			break;
		case Items:
			break;
		case Leave:
			player.health = 0;
			break;
		}

		enemy->attack(&player);
	}

	void endBattle(Player& player, Enemy* enemy) {
		system("cls");

		string winText("YOU WON!");
		string looseText("YOU LOST!");
		COORD coord;

		coord.Y = screenInfo.srWindow.Bottom / 2 - 2;


		if (enemy->name == "Toothless" && isDragonFriend) {
			player.damage += 20;

		}
		else if (enemy->health <= 0) {
			if (enemy->name == "Uncle") {
				isUncleDead = true;
				return;
			}

			coord.X = (screenInfo.srWindow.Right - winText.size()) / 2;
			SetConsoleCursorPosition(hConsole, coord);
			cout << winText;

			string earned("You earned:");
			coord.X = (screenInfo.srWindow.Right - earned.size()) / 2;
			coord.Y += 2;
			SetConsoleCursorPosition(hConsole, coord);
			cout << earned;

			string coins = to_string(enemy->coins) + " coins";
			coord.X = (screenInfo.srWindow.Right - coins.size()) / 2;
			coord.Y++;
			SetConsoleCursorPosition(hConsole, coord);
			cout << coins;

			string experience = to_string(enemy->exp) + " experience";
			coord.X = (screenInfo.srWindow.Right - experience.size()) / 2;
			coord.Y++;
			SetConsoleCursorPosition(hConsole, coord);
			cout << experience;

			player.coins += enemy->coins;
			player.maxHealth += enemy->exp;
			player.damage += enemy->exp / 5;
		}
		else {
			coord.X = (screenInfo.srWindow.Right - looseText.size()) / 2;
			SetConsoleCursorPosition(hConsole, coord);
			cout << looseText;
		}

		player.health = player.maxHealth;
		enemy->health = enemy->maxHealth;
	}

#pragma endregion 
	bool isDragonFriend = false;
	bool isUncleDead = false;

	vector<string> options = { "Attack", "Defence", "Items", "Leave" };

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
};

