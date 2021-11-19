#include "SparseMatrix.h"

//矩阵
Matrix::Matrix(int rParaNum, int cParaNum)
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

Matrix::~Matrix()
{
	//没有在堆区创建数据，不需要析构函数。
}

/*插入item到triple表中的标准：首先以item在matrix中所存在的row来从小到大排序，row相同时以column排序。
若新插入的item的row与column已经存在于triple表中，则用新item替换原item*/
Status Matrix::setItem(int row, int col, int item)
{
	//如果triple表已满，则无法插入数据
	if (itemNum == MAX)
		return ERROR;
	//如果行数或列数大于matrix的行数与列数，无法插入数据到triple表
	if (row > rNum || col > cNum)
		return ERROR;
	int index = 0;//index为triple表的下标
	
	//循环整个triple表：当triple表的index小于triple表里的item数时，保持循环
	while (index < itemNum)
	{
		//寻找插入item的位置：如果新item所在的行数大于该index下item的行数，则继续检查下一个index
		if (row > data[index].row)
		{
			index++;
		}
		//如果新item的行数等于该index下item的行数，则检查列数，如果列数大于该index下item的列数，则继续检查下一个index
		else if (row == data[index].row && col > data[index].col)
			index++;
		//其他情况说明已经找到插入item的位置，停止循环，准备插入
		else
			break;
	}

	//如果triple表中已存在该row于col,则用新item替换原item
	if (data[index].row == row && data[index].col == col)
	{
		data[index].item = item;
		itemNum--; //改变已有位置上的数据，因此数据总数不变。由于函数最后itemNum+1，此处先使itemNum-1以保证数量正确
	}
	//如果该row于col不存在item，则在该位置插入row,col与item的数据
	else
	{
		//插入数据之前先将triple表中该index开始的的所有数据后移一位，以空出该index接收新数据
		for (int i = itemNum; i > index; i--)
		{
			//cout << "i是：" << i << endl;
			data[i].col = data[i-1].col;
			data[i].row = data[i-1].row;
			data[i].item = data[i-1].item;
		}
		//插入数据
		data[index].col = col;
		data[index].row = row;
		data[index].item = item;
	}
	//更新item数量
	itemNum++;
	return OK;
}

int Matrix::getItem(int row, int col)
{
	if (row > rNum || col > cNum)
		return 0;

	//循环triple表
	for (int i = 0; i < itemNum; i++)
	{
		//找到数据
		if (row == data[i].row && col == data[i].col)
			return data[i].item;
	}
	return 0;
}

void Matrix::printMatrix()
{
	int index = 0;

	cout << "The Matrix is: " << endl;

	/*循环triple表：循环总共进行 rNum*cNum次，itemNum = rNum*cNum。index从0->itemNum。刚好循环完毕整个triple表。
	i与j从1开始，因为行数与列数时从1开始（不存在row 0或column 0）*/
	for (int i = 1; i <= rNum; i++)
	{
		for (int j = 1; j <= cNum; j++)
		{
			//当打印的matrix进行到data[index].row行，data[index].col列时，打印triple表中的数据，否则打印0。
			if (data[index].row == i && data[index].col == j)
			{
				cout << data[index].item << "\t";
				index++;//循环总共进行 rNum*cNum次，itemNum = rNum*cNum。index从0->itemNum。刚好循环完毕整个triple表。
			}
			else
				cout << 0 << "\t";
		}
		cout << endl;
		
	}
	cout << "The matrix has " << rNum << "row(s), " << cNum << "column(s) and " << itemNum << "item(s)" << endl;
}

void Matrix::printTriple()
{
	cout << "The triple table is: " << endl;
	cout << "row\t" << "column\t" << "item\t" << endl;
	for (int i = 0; i < itemNum; i++)
	{
		cout << data[i].row << "\t" << data[i].col << "\t" << data[i].item << "\t" << endl;
	}
}

void inputMatrix(int paraRow, int paraCol, int paraItemNum, Matrix& matrix)
{
	int row, col, item;
	for (int i = 0; i < paraItemNum; i++)
	{
		//cout << "paraItemNum是：" << paraItemNum << endl;
		cout << "Input row, column, and the item:" << endl;
		cin >> row >> col >> item;

		if (item != 0)
		{
			//set up data里的items，并且在出现错误时返回ERROR
			if (matrix.setItem(row, col, item) == ERROR)
			{
				cout << "Input is illegal or the matrix has been full." << endl;
				break;
			}
		}
	}
}

int main()
{
	int row, col, itemNum;
	cout << "Input the row, column, and item Number: " << endl;
	cin >> row >> col >> itemNum;
	//cout << "itemNum的值是：" << itemNum << endl;

	Matrix triple(row, col);
	inputMatrix(row, col, itemNum, triple);
	triple.printMatrix();
	triple.printTriple();

	return 0;
}