#include <iostream>
#include <string>

using namespace std;

int IntInput(int min, int max);
void ChooseOption();
void userChoice(int i);

void InsertCase();
void DeriveCase();

#pragma region MainMenu

void MainMenu() {
	cout << "XXXXXXXXXXXXX" << endl << "X MAIN MENU X" << endl << "XXXXXXXXXXXXX" << endl;
	ChooseOption();
}

void ChooseOption() {
	cout << "Please enter a number based on the following options:" << endl;
	cout << " 0:Insert Algebraic Expression" << endl << " 1:Derive Algebraic Expression" << endl;
	userChoice(IntInput(0, 1));
}

void userChoice(int i) {
	switch (i) {
	case 0: InsertCase(); break;
	case 1: DeriveCase(); break;
	default:
		cout << "Invalid Option, please try again" << endl << endl;
		ChooseOption();
		break;
	}
}

int InsertMenu() {
	cout << "Please enter a number based on the following options:" << endl;
	cout <<" 0:Monomial" << endl << " 1:Binomial" << endl << " 2:Trinomial" << endl << " 3:Quadrinomial" << endl;
	return IntInput(0, 3);
}

string StringInput() {
	string input = "";
	cin >> input;
	return input;
}

char CharInput() {
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	char input = NULL;
	cin >> input;
	if (cin.fail()) {
		cout << "Invalid Option, please try again" << endl;
		return CharInput();
	}
	return input;
}

int IntInput(int min, int max) {
	int input = NULL;
	cin >> input;
	if (cin.fail() || input < min || input > max) {
		cout << "Invalid Option, please try again" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return IntInput(min, max);
	}
	return input;
}

bool YesNo(string txt) {
	cout << txt << " (Y/N)" << endl;
	char c = CharInput();
	if (c == 'Y' || c == 'y')
		return true;
	else if (c == 'N' || c == 'n')
		return false;
	cout << "Invaild character given, please try again"  << endl;
	return YesNo(txt);
}