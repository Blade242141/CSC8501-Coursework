#include <iostream>
#include <string>
#include "expression.h"
#include <cmath>

using namespace std;

void InsertCase();

void InsertTerm(int* a, int* b, string* txt);
void InsertBinomail(expression* exp, bool binomailCase);
void InsertTrinomial(expression* exp, bool trinomialCase);
void InsertQuadrinomial(expression* exp);
void InsertSymbol(char* symbol, string* str);
void InsertNextTerm(expression* exp, int* a, int* b, bool c);
void InsertConstant(int* constant, string* str);
bool IsConstant(bool b);

void FindOutputs(expression* exp);
string ForLoopRange(expression* exp, int start, int end, int* outputs);
int Section(char* symbol, int* co, int range, int* power, int* constant);
int XRangeStart();
int XRangeEnd(int start);

void ChooseOption();
int InsertMenu();
char CharInput();
int IntInput(int min, int max);
bool YesNo(string txt);

void SaveToFile(string fileName, string s);

#pragma region Input

void InsertCase() {
	expression expres;
	expression* exp = &expres;
	switch (InsertMenu()) {
	case 0: InsertTerm(&exp->a, &exp->b, &exp->txt); FindOutputs(exp); break;
	case 1: InsertBinomail(exp, true); FindOutputs(exp);  break;
	case 2: InsertTrinomial(exp, true); FindOutputs(exp); break;
	case 3: InsertQuadrinomial(exp); FindOutputs(exp); break;
	default: cout << "Invalid Option, please try again" << endl << endl; InsertCase(); break;
	}
}

void InsertTerm(int* a, int* b, string* txt) {
	cout << "Please enter an int value (a) for the coefficient part of the expression (ax^b)" << endl;
	*txt += to_string(*a = IntInput(1, 9));
	cout << "Please enter an int value (b) for the degree part of the expression (ax^b)" << endl;
	*txt += "x^" + to_string(*b = IntInput(2, 4));
}

void InsertBinomail(expression* exp, bool binomailCase) {
	InsertTerm(&exp->a, &exp->b, &exp->txt);
	InsertSymbol(&exp->symbolA, &exp->txt);
	InsertNextTerm(exp, &exp->c, &exp->d, binomailCase);
}

void InsertTrinomial(expression* exp, bool trinomialCase) {
	InsertBinomail(exp, false);
	InsertSymbol(&exp->symbolB, &exp->txt);
	InsertNextTerm(exp,&exp->e, &exp->f, trinomialCase);
}

void InsertQuadrinomial(expression* exp) {
	InsertTrinomial(exp, false);
	InsertSymbol(&exp->symbolC, &exp->txt);
	InsertNextTerm(exp, &exp->g, &exp->h, true);
}

void InsertNextTerm(expression* exp, int* a, int* b, bool c) {
	IsConstant(c) ? InsertConstant(&exp->constant, &exp->txt) : InsertTerm(a, b, &exp->txt);
}

void InsertConstant(int* constant, string* str) {
	cout << "Please enter a int between 0 and 1000" << endl;
	*constant = IntInput(0, 1000);
	*str = *str + to_string(*constant);
}

void InsertSymbol(char* symbol, string* str) {
	cout << "Please enter '+' or '-'" << endl;
	char ch = CharInput();
	if (ch == '+' || ch == '-') {
		*symbol = ch;
		*str += ch;
	} else {
		cout << "Invalid Option, please try again" << endl;
		InsertSymbol(symbol, str);
	}
}

bool IsConstant(bool b) {
	if (!b) return false;
	if (YesNo("Is the next part of the equation the constant?"))
		return true;
	else 
		return false;	
}

#pragma endregion

void FindOutputs(expression* exp) {
	int start = XRangeStart();
	int end = XRangeEnd(start);
	int* arr = new int [4];
	int size = ((end + 1) - start);
	int* outputs = new int[size];
	cout << endl << "Equation: " << exp->txt << endl;
	string str = ForLoopRange(exp, start, end, outputs);
	cout << str << endl;
	SaveToFile(exp->txt + " f(x) = " + to_string(start) + "-" + to_string(end), str);
}

string ForLoopRange(expression* exp, int start, int end, int* outputs) {
	string s;
	for (int i = start; i <= end; i++) {
		int combind = Section(nullptr, &exp->a, i, &exp->b, &exp->constant);
		combind += Section(&exp->symbolA, &exp->c, i, &exp->d, &exp->constant);
		combind += Section(&exp->symbolB, &exp->e, i, &exp->f, &exp->constant);
		combind += Section(&exp->symbolC, &exp->g, i, &exp->h, &exp->constant);
		s += to_string(combind) + (i == end ? "" : ", ");
	}
	return s;
}

int Section(char* symbol, int* co, int range, int* power, int* constant) {
	if (*co != -1) {
		if (symbol == nullptr || *symbol == '+') return (*co * (pow(range, *power)));
		else if (*symbol == '-') return -(*co * (pow(range, *power)));
	} else if (*constant != -1) {
		if (*symbol == '+') return *constant;
		else if (*symbol == '-') return -(*constant);
	}
	return 0;
}

int XRangeStart() {
	cout << "Please enter a start int for f(x) range" << endl;
	return IntInput(numeric_limits<int>::min(), numeric_limits<int>::max());
}

int XRangeEnd(int start){
	cout << "Please enter a end int for f(x) range" << endl;
	return IntInput(start, numeric_limits<int>::max());
}