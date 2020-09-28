/*
Бобрович А.И.
гр. 044691
Лабораторная работа №1

13. Рассортировать отрицательные элементы каждого столбца матрицы
по возрастанию. Положительные элементы оставить на своих местах. Память
под матрицу выделять динамически. Необходимо освобождать память, 
выделенную под матрицу.
*/
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

void ColorDefault()
{
	SetColor(White, Black);
}

int RandGet(int min, int max)
{
	max = max + 1;
	return std::rand() % (max - min) + min;
}

int** MatrixNew(int h, int w)
{
	int** result = new int*[h];
	for (int i = 0; i < h; i++)
	{
		result[i] = new int[w];
		for (int j = 0; j < w; j++)
		{
			result[i][j] = 0;
		}
	}
	return result;
}

void MatrixFill(int** mas, int h, int w, int min, int max)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			mas[i][j] = RandGet(min, max);
		}
	}
}

void MatrixView(int** mas, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (mas[i][j] < 0)
				SetColor(White, Red);
			else if (mas[i][j] >= 0)
				SetColor(White, Green);
			cout << setw(4) << mas[i][j];
			ColorDefault();
			cout << "; ";
		}
		cout << endl;
	}
}


void MatrixSort(int** mas, int h, int w)
{
	for (int j = 0; j < w; j++)
	{
		for (int i = 0; i < h; i++)
		{
			int pred = -1;
			for (int k = 0; k < h - i; k++)
			{
				if (mas[k][j] < 0)
				{
					if (pred == -1)
					{
						pred = k;
					}
					else
					{
						if (mas[pred][j] > mas[k][j])
						{
							int buf = mas[pred][j];
							mas[pred][j] = mas[k][j];
							mas[k][j] = buf;
						}
						pred = k;
					}
				}
			}
		}
	}
}

void MatrixDelete(int** mass, int h) {
	for (int i = 0; i < h; i++) {
		delete[] mass[i];
	}
	delete[] mass;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	ColorDefault();

	int h = 0;
	int w = 0;

	cout << "Введите размеры массива:" << endl;
	cin >> h >> w;

	if (std::cin.fail() || w <= 0 || h <= 0)
	{
		cerr << "Ошибка, не верный ввод" << endl;
		system("pause");
		exit(0);
	}

	int** mas = MatrixNew(h, w);

	MatrixFill(mas, h, w, -10, 10);

	cout << "Исходный массив" << endl;
	MatrixView(mas, h, w);

	MatrixSort(mas, h, w);

	cout << "Сортированный массив" << endl;
	MatrixView(mas, h, w);

	MatrixDelete(mas, h);
	system("pause");
}
