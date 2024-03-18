#pragma once
#pragma comment (lib, "winmm.lib")
#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <sstream> 
#include <vector> 

using namespace std;

class Annotation {
public:

	Annotation(const string& text) :text_(text), ss(text_) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		textCoord = { 0, 0 };
	}

	void printAnnotation() {
		printTextAtPosition(20, 3);
		SetConsoleTextAttribute(h, 0x7);

		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(h, &screen);

		PlaySound(TEXT("soundd.wav"), NULL, SND_FILENAME | SND_ASYNC);
		string line;
		for (char c : text_) {
			if (c == '~') {
				textCoord.X = max(20, (screen.srWindow.Right - line.length()) / 6);
				textCoord.Y++;
				SetConsoleCursorPosition(h, textCoord);
				c = ' ';
			}
			cout << c << flush;
			Sleep(100);
		}
		cout << endl;
	}

	void printStar() {
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(h, &screen);
		CONSOLE_CURSOR_INFO curs;
		GetConsoleCursorInfo(h, &curs);
		curs.bVisible = false;
		SetConsoleCursorInfo(h, &curs);

		srand(time(NULL));
		int starColor = 15;
		int activeStarColor = 0;
		srand(time(NULL));
		COORD coord;
		PlaySound(TEXT("Forestt.wav"), NULL, SND_FILENAME | SND_ASYNC);
		clock_t startTime = clock();
		const clock_t duration = 5 * CLOCKS_PER_SEC;
		while ((clock() - startTime) < duration) {
			activeStarColor = (rand() % 10 > 8) ? starColor : 0;
			coord.X = rand() % screen.srWindow.Right;
			coord.Y = rand() % screen.srWindow.Bottom;
			SetConsoleTextAttribute(h, activeStarColor);
			SetConsoleCursorPosition(h, coord);
			cout << '.';
		}
	}




	void printTitle() {
		PlaySound(TEXT("DUCK&DRAGONS.wav"), NULL, SND_FILENAME | SND_ASYNC);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		vector<int> colors = { FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE, FOREGROUND_INTENSITY };
		printTextAtPosition(47, 2);
		int colorIndex = 0;
		for (char c : text_) {
			SetConsoleTextAttribute(hConsole, colors[colorIndex]);
			cout << c << flush;
			colorIndex = (colorIndex + 1) % colors.size();
			Sleep(120);
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << endl;
	}

	void printTextAtPosition(int a, int b) {
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(h, &screen);
		int annotationLength = text_.length();
		textCoord.X = max(a, (screen.srWindow.Right - annotationLength) / 4);
		textCoord.Y = screen.srWindow.Bottom / b;
		SetConsoleCursorPosition(h, textCoord);
	}


private:
	string text_;
	stringstream ss;
	HANDLE h;
	COORD textCoord;

};

