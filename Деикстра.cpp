﻿#include <iostream>
using namespace std;
int main()
{

	int MasVer[4]; // минимальное расстояние
	int v[4]; // посещенные вершины
	int temp, minindex, min;
	int begin_index = 0;

	int mas[4][4] =
	{
		{ 0, 5, 0, 6, }, // матрица смежности
		{ 5, 0, 8, 7, },
		{ 0, 8, 0, 9, },
		{ 6, 7, 9, 0, },
	};

	// Вывод матрицы связей
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << mas[i][j];
		printf("\n");
	}
	//Инициализация вершин и расстояний
	for (int i = 0; i < 4; i++)
	{
		MasVer[i] = 10000;
		v[i] = 1;
	}
	MasVer[begin_index] = 0;
	// Шаг алгоритма
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < 4; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((v[i] == 1) && (MasVer[i] < min))
			{ // Переприсваиваем значения
				min = MasVer[i];
				minindex = i;
			}
		}
		// Добавляем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minindex != 10000)
		{
			for (int i = 0; i < 4; i++)
			{
				if (mas[minindex][i] > 0)
				{
					temp = min + mas[minindex][i];
					if (temp < MasVer[i])
					{
						MasVer[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);
	// Вывод кратчайших расстояний до вершин
	printf("\nКратчайшие расстояния до вершин: \n");
	for (int i = 0; i < 4; i++)
		printf("%5d ", MasVer[i]);

	/* Восстановление пути
	int ver[SIZE]; // массив посещенных вершин
	int end = 4; // индекс конечной вершины = 5 - 1
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = d[end]; // вес конечной вершины

	while (end != begin_index) // пока не дошли до начальной вершины
	{
	  for (int i = 0; i<SIZE; i++) // просматриваем все вершины
		if (a[end][i] != 0)   // если связь есть
		{
		  int temp = weight - a[end][i]; // определяем вес пути из предыдущей вершины
		  if (temp == d[i]) // если вес совпал с рассчитанным
		  {                 // значит из этой вершины и был переход
			weight = temp; // сохраняем новый вес
			end = i;       // сохраняем предыдущую вершину
			ver[k] = i + 1; // и записываем ее в массив
			k++;
		  }
		}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	printf("\nВывод кратчайшего пути\n");
	for (int i = k - 1; i >= 0; i--)
	  printf("%3d ", ver[i]);
	getchar(); getchar();*/
	return 0;
}
