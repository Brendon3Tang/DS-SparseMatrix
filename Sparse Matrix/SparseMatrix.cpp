#include "SparseMatrix.h"

//����
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
	//û���ڶ����������ݣ�����Ҫ����������
}

/*����item��triple���еı�׼��������item��matrix�������ڵ�row����С��������row��ͬʱ��column����
���²����item��row��column�Ѿ�������triple���У�������item�滻ԭitem*/
Status Matrix::setItem(int row, int col, int item)
{
	//���triple�����������޷���������
	if (itemNum == MAX)
		return ERROR;
	//�����������������matrix���������������޷��������ݵ�triple��
	if (row > rNum || col > cNum)
		return ERROR;
	int index = 0;//indexΪtriple����±�
	
	//ѭ������triple����triple���indexС��triple�����item��ʱ������ѭ��
	while (index < itemNum)
	{
		//Ѱ�Ҳ���item��λ�ã������item���ڵ��������ڸ�index��item������������������һ��index
		if (row > data[index].row)
		{
			index++;
		}
		//�����item���������ڸ�index��item����������������������������ڸ�index��item������������������һ��index
		else if (row == data[index].row && col > data[index].col)
			index++;
		//�������˵���Ѿ��ҵ�����item��λ�ã�ֹͣѭ����׼������
		else
			break;
	}

	//���triple�����Ѵ��ڸ�row��col,������item�滻ԭitem
	if (data[index].row == row && data[index].col == col)
	{
		data[index].item = item;
		itemNum--; //�ı�����λ���ϵ����ݣ���������������䡣���ں������itemNum+1���˴���ʹitemNum-1�Ա�֤������ȷ
	}
	//�����row��col������item�����ڸ�λ�ò���row,col��item������
	else
	{
		//��������֮ǰ�Ƚ�triple���и�index��ʼ�ĵ��������ݺ���һλ���Կճ���index����������
		for (int i = itemNum; i > index; i--)
		{
			//cout << "i�ǣ�" << i << endl;
			data[i].col = data[i-1].col;
			data[i].row = data[i-1].row;
			data[i].item = data[i-1].item;
		}
		//��������
		data[index].col = col;
		data[index].row = row;
		data[index].item = item;
	}
	//����item����
	itemNum++;
	return OK;
}

int Matrix::getItem(int row, int col)
{
	if (row > rNum || col > cNum)
		return 0;

	//ѭ��triple��
	for (int i = 0; i < itemNum; i++)
	{
		//�ҵ�����
		if (row == data[i].row && col == data[i].col)
			return data[i].item;
	}
	return 0;
}

void Matrix::printMatrix()
{
	int index = 0;

	cout << "The Matrix is: " << endl;

	/*ѭ��triple��ѭ���ܹ����� rNum*cNum�Σ�itemNum = rNum*cNum��index��0->itemNum���պ�ѭ���������triple��
	i��j��1��ʼ����Ϊ����������ʱ��1��ʼ��������row 0��column 0��*/
	for (int i = 1; i <= rNum; i++)
	{
		for (int j = 1; j <= cNum; j++)
		{
			//����ӡ��matrix���е�data[index].row�У�data[index].col��ʱ����ӡtriple���е����ݣ������ӡ0��
			if (data[index].row == i && data[index].col == j)
			{
				cout << data[index].item << "\t";
				index++;//ѭ���ܹ����� rNum*cNum�Σ�itemNum = rNum*cNum��index��0->itemNum���պ�ѭ���������triple��
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
		//cout << "paraItemNum�ǣ�" << paraItemNum << endl;
		cout << "Input row, column, and the item:" << endl;
		cin >> row >> col >> item;

		if (item != 0)
		{
			//set up data���items�������ڳ��ִ���ʱ����ERROR
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
	//cout << "itemNum��ֵ�ǣ�" << itemNum << endl;

	Matrix triple(row, col);
	inputMatrix(row, col, itemNum, triple);
	triple.printMatrix();
	triple.printTriple();

	return 0;
}