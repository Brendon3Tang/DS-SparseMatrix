#include "SparseMatrix.h"

//æÿ’Û
TripleMatrix::TripleMatrix(int rParaNum, int cParaNum)
{
	rNum = rParaNum;
	cNum = cParaNum;
	itemNum = 0;
	//for (int i = 0; i < itemNum; i++)
	//{
	//	data[i].col = 0;
	//	data[i].row = 0;
	//	data[i].item = 0;
	//}
}

TripleMatrix::~TripleMatrix()
{

}

Status TripleMatrix::setItem(int row, int col, int item)
{
	if (itemNum == MAX)
		return ERROR;
	if (row > rNum || col > cNum)
		return ERROR;
	int index = 0;

	while (index < itemNum)
	{
		if (row > data[index].row)
		{
			index++;
		}
		else if (row == data[index].row && col > data[index].col)
			index++;
		else
			break;
	}

	if (data[index].row == row && data[index].col == col)
		data[index].item = item;
	else
	{
		for (int i = itemNum; i > index; i--)
		{
			data[i + 1].col = data[i].col;
			data[i + 1].row = data[i].row;
			data[i + 1].item = data[i].item;
		}
		data[index].col = col;
		data[index].row = row;
		data[index].item = item;
	}
	itemNum++;
	return OK;
}

int TripleMatrix::getItem(int row, int col)
{
	if (row > rNum || col > cNum)
		return 0;

	for (int i = 0; i < itemNum; i++)
	{
		if (row == data[i].row && col == data[i].col)
			return data[i].item;
	}
	return 0;
}

void TripleMatrix::printMatrix()
{
	int index = 0;

	cout << "The Matrix is: " << endl;

	for (int i = 1; i < rNum; i++)
	{
		for (int j = 1; j < cNum; j++)
		{
			if (data[index].row == rNum && data[index].col == cNum)
			{
				cout << data[index].item << "\t";
				index++;
			}
			else
				cout << 0 << "\t";
		}
		cout << endl;
		
	}
	cout << "The matrix has " << rNum << "row(s), " << cNum << "column(s) and " << itemNum << "item(s)" << endl;
}

void TripleMatrix::printTriple()
{
	cout << "The triple table is: " << endl;
	cout << "row\t" << "column\t" << "item\t" << endl;
	for (int i = 0; i < itemNum; i++)
	{
		cout << data[i].row << "\t" << data[i].col << "\t" << data[i].item << "\t" << endl;
	}
}

void inputMatrix(int paraRow, int paraCol, int paraItemNum, TripleMatrix& matrix)
{
	int row, col, item;
	for (int i = 1; i < paraItemNum; i++)
	{
		cout << "Input row, column, and the item:" << endl;
		cin >> row >> col >> item;

		if (item != 0)
		{
			if (matrix.setItem(row, col, item) == ERROR)
			{
				cout << "Input is illegal or the matrix has been full." << endl;
				break;
			}
			else
				matrix.setItem(row, col, item);
		}
	}
}

int main()
{
	int row, col, itemNum;
	cout << "Input the row, column, and item Number: " << endl;
	cin >> row >> col >> itemNum;
	TripleMatrix triple(row, col);
	inputMatrix(row, col, itemNum, triple);
	triple.printMatrix();
	triple.printTriple();

	return 0;
}