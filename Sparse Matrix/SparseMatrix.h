#pragma once
#include <iostream>
using namespace std;

#define MAX	100
#define ERROR 0
#define OK 1

typedef int Status;

typedef struct
{
	int row, col;
	int item;
} Triple;

class Matrix
{
private:
	Triple data[MAX];
	int rNum, cNum, itemNum;
public:
	Matrix(int rParaNum,int cParaNum);

	~Matrix();

	Status setItem(int row, int col, int item);

	int getItem(int row, int col);

	void printMatrix();

	void printTriple();

};
