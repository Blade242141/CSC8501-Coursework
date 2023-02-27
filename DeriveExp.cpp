#include <iostream>
#include <string>
#include "expression.h"
#include "NumberArray.h"

using namespace std;

void ReceiveFile(numberArray* na);
void ExpOuput(string str);

void CheckTerm(expression* exp, int xRange, int* str);
int CalcB(int a, int x, int y);
bool CheckConstant(expression* exp, int x, int y);

void MainMenu();

const int xRange = 20;

void DeriveCase() {
	expression exp; numberArray yRange; ReceiveFile(&yRange);
	cout << endl << "expression: " << exp.txt << endl;
	CheckTerm(&exp, xRange, yRange.ptr);
	string str = ""; 
	str = to_string(exp.a) + "x^" + to_string(exp.b);
	exp.constant != NULL ? str += to_string(exp.constant) + '\n': str += '\n';
	cout << str;
	str = yRange.filename + ": " + str;
	ExpOuput(str);
	MainMenu();
}

void CheckTerm(expression* exp, int xRange, int* y) {
	for (int x = 0; x < xRange; x++) {
		if (x == 0 && CheckConstant(exp, x, y[x])) {
		} else if (x == 1) {
			exp->a = (y[x] + -(exp->constant));
		} else if (x == 2){
			exp->b = CalcB(exp->a, x, (y[x] + -(exp->constant)));
		}
	}
}

int CalcB(int a, int x, int y) {
	int d = log2(y/a);
	return d;
} 

bool CheckConstant(expression* exp, int x, int y) {
	if (y != 0 && x == 0) {
		exp->constant = y;
		return true;
	} else {
		return false;
	}
}