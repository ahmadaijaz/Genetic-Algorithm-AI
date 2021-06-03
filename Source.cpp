#include<iostream>
#include<fstream>
#include<conio.h>
#include"help.h"
#include<windows.h>
using namespace std;
int evaluation_function(int*image, int*arr, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = sum + abs(image[i] - arr[i]);
	}
	return sum;
}

void GE_swap(int*arr1, int*arr2, int size)
{
	int*temp = new int[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr2[i];
	}
	for (int i = 0; i < size; i++)
	{
		arr2[i] = arr1[i];
	}
	for (int i = 0; i < size; i++)
	{
		arr1[i] = temp[i];
	}
	delete[] temp;
}

void sort(int**arr, int*image, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		int E_i = evaluation_function(image, arr[i], col);
		for (int j = i + 1; j < row; j++)
		{
			int E_j = evaluation_function(image, arr[j], col);
			if (E_i > E_j)
			{
				GE_swap(arr[i], arr[j], col);
			}
		}
	}
}

void crossover(int*arr, int*arr2, int size)
{
	int mid = (rand() % size) + 1;
	int*temp = new int[mid];
	for (int i = 0; i < mid; i++)
	{
		temp[i] = arr[i];
	}
	for (int i = 0; i < mid; i++)
	{
		arr[i] = arr2[i];
	}
	for (int i = 0; i < mid; i++)
	{
		arr2[i] = temp[i];
	}
	delete[] temp;
}

void mutation(int*temp, int**arr)
{
	int a = (rand() % 20) + 1;
	int b = (rand() % 8470) + 1;
	int c = (rand() % 8470) + 1;
	temp[c] = arr[a][b];
}

void printimage(int*arr)
{
	int x1 = 400, x2 = 402, y1 = 40, y2 = 42;
	int count = 0;
	for (int i = 0; i < 8470; i++)
	{
		myRect(x1, y1, x2, y2, arr[i], arr[i], arr[i], arr[i], arr[i], arr[i]);
		x1 = x1 + 2;
		x2 = x2 + 2;
		count++;
		if (count == 77)
		{
			count = 0;
			y1 = y1 + 2;
			y2 = y2 + 2;
			x1 = 400;
			x2 = 402;
		}
	}
}
int main()
{
	ifstream fin;
	fin.open("pixels.txt");
	int*image = new int[8470];
	int count = 0;
	for (int i = 0; i < 8470; i++)
	{
		fin >> image[i];
	}
	cout << "Target Image" << endl;
	printimage(image);
	Sleep(1000);
	system("cls");
	int ** arr = new int*[100];       //creating random number arrays
	for (int i = 0; i < 100; i++)
	{
		arr[i] = new int[8470];
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 8470; j++)
		{
			arr[i][j] = (rand() % 255) + 1;
		}
	}

	int i = 0;
	while (i < 50000)
	{
		int ** pop = new int*[100];        // new population
		for (int i = 0; i < 100; i++)
		{
			pop[i] = new int[8470];
		}
		sort(arr, image, 100, 8470);		//sorting the population
		cout << "Generation : " << i << " Difference : " << evaluation_function(image, arr[0], 8470) << endl;
		if (i % 100 == 0)				//for printing image after 100 generations
		{
			printimage(arr[0]);
			Sleep(2000);
			system("cls");
		}
		if ((evaluation_function(image, arr[0], 8470) == 0))
		{
			break;
		}
		for (int i = 0; i < 20; i++)       //Selecting 20% of population
		{
			for (int j = 0; j < 8470; j++)
			{
				pop[i][j] = arr[i][j];
			}
		}
		for (int i = 20; i < 60; i++)      //selecting 40% from crossover
		{
			int a = (rand() % 20) + 1;
			crossover(arr[i], arr[a], 8470);
			for (int j = 0; j < 8470; j++)
			{
				pop[i][j] = arr[a][j];
			}
		}
											//mutation 40% 
		for (int i = 60; i < 100; i++)
		{
			int a = (rand() % 20) + 1;
			mutation(arr[a], arr);
			for (int j = 0; j < 8470; j++)
			{
				pop[i][j] = arr[a][j];
			}
		}

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 8470; j++)
			{
				arr[i][j] = pop[i][j];
			}
		}
		for (int i = 0; i < 100; i++)
		{
			delete[] pop[i];
		}
		delete[]pop;
		i++;
	}
}