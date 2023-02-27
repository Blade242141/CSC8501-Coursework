#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "NumberArray.h"

using namespace std;

void MainMenu();
string StringInput();
bool YesNo(string txt);

void WriteToFile(string fileName, string s);
void DecodeFile(numberArray* na, string str);
void Split(string str, int* ptr);
void SaveToExp(string str);

const string txt = ".txt";
const string expName = "expressions.txt";

#pragma region File Output

void SaveToFile(string fileName, string s) {
	if (YesNo("Would you like to save to a file ?")) {
		try { WriteToFile(fileName, s); }
		catch (const char* msg) { YesNo(msg) ? SaveToFile(fileName, s) : MainMenu(); }
	}
	MainMenu();
}

void WriteToFile(string fileName, string s) {
	ofstream file(fileName + txt);
	if (file.is_open()) {
		file << s;
		file.close();
		cout << "File saved as '" << fileName << "'" << endl << endl;
	} else { throw "Unable to output file \n Would you like to try again"; }
}

#pragma endregion

#pragma region File Input

void GetFileStr(numberArray* na) {
	na->filename = StringInput();
	ifstream file(na->filename);
	if (file.is_open()) {
		string str;
		getline(file, str);
		file.close();
		DecodeFile(na, str);
	} else { throw "Unable to read file, would you like to try again ?"; }
}

void ReceiveFile(numberArray* na) {
	cout << "Please enter filename. (e.g. test.txt)" << endl;
	try {
		GetFileStr(na);
	} catch (const char* msg) {
		YesNo(msg) ? ReceiveFile(na) : MainMenu();
	}
}

void DecodeFile(numberArray* na, string str) {
	na->ptr = new int[sizeof(str)];
	Split(str, na->ptr);
	na->size = sizeof(str);
}

void Split(string str, int* ptr) {
	int count = 0; string s;
	for (auto x : str) {
		if (x == ',' && s != "") {
			ptr[count] = stoi(s);
			count++;
			s = "";
		}
		else {if (x != ' ' && x != ',') { s += x; }}
	}
}

void ExpOuput(string str) {
	if (YesNo("Would you like to save to the " + expName + " file?"))
		SaveToExp(str);
	else
		MainMenu();
}

	void SaveToExp(string str) {
		fstream appendFile;
		appendFile.open(expName, fstream::app);
		if (!appendFile)
			appendFile.open(expName, fstream::out);
		appendFile << str;
		appendFile.close();
		cout << "Saved to " + expName + " file." << endl << endl;
		MainMenu();
	}
#pragma endregion