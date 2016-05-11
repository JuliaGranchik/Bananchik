#pragma once
#include <SFML\Graphics.hpp>
#include <iostream> 
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>

const int h = 25;//размер карты высота
const int w = 40;//размер карты ширина 
int r = rand();
char a[h][w];
int count = 0;
bool check = true;
int i, j;

/* sf::String a[h] = {
	"0000000000000000000000000000000000000000",
	"0  0                                   0",
	"0  0    000000                         0",
	"0  00000     0                         0",
	"0            0                         0",
	"0            0                         0",
	"0   00000    000000                    0",
	"0   0   0          0                   0",
	"0   0   0    h     0                   0",
	"0   0   0          0         h         0",
	"0   0   0       0000                   0",
	"0   0   0                              0",
	"0   0   0                              0",
	"0       0000000                        0",
	"0             0      0                 0",
	"0             0      0                 0",
	"0             0      0                 0",
	"0             0      0                 0",
	"0      000000                          0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
}; */


void MapGenerate()
{
	srand(time(NULL));//рандом	
		//установка рамки из границ
	for (j = 0; j < w; j++)
	{
		a[0][j] = '0';
		a[h-1][j] = '0';
	}
	for (i = 0; i < h; i++)
	{
		a[i][0] = '0';
		a[i][w-1] = '0';
	}

	//присваивание каждой ячейке свое собсвтенное множество
	for (j = 1; j <(w - 1); j++)
	{
		a[1][j] = '%d',j;
	}


	//цикл ляляля
	for (i = 1; i < (h - 1); (i + 2))
	{
		for (j = 2; j < (w - 2); (j+2))
		{
			int random = 1 + rand() % 2;//рандомно решаем, добавлять границу или нет
			if (random == 1)//если 1, то добавляем
			{
				a[i][j] = '0';
			}
		}

		//объединение множеств
		for (j = 2; j < (w - 1); j++)
		{
/*			if (a[i][j] == 0 && a[i][j + 1] == 0)//на случай, если вышло так, что две ячейки под ряд одинаковые
			{
				a[i][j] = a[i][j - 1];
			} */
			if ((a[i][j - 1] == '0' && a[i][j+1]!='0') || (a[i][j-1]==a[i][j] && a[i][j+1]!='0') )//если предыдущая ячейка=0, то мы объединяем множетсва
			{	
				a[i][j+1] = a[i][j];//объединяем ячейки в одно множество
			}
		}

		//Создание нижних границ
		//проверка на замкнутые области
		for (j = 1; j < (w - 1); j++)
		{
			int random = 1 + rand() % 2;//рандомно решаем, добавлять границу или нет
			if ((random == 1) && (a[i][j+1]==a[i][j]))//если 1, то добавляем
			{
				a[i+1][j] = '0';
			}
			else
			{
				a[i + 1][j] = a[i][j];//копирование множества
			}
		}

		//копирование строки, там где правые границы, и их удаление 
		for (j = 1; j < (w - 1); i++)
		{	
			a[i + 2][j] = a[i][j];//копирование всей первой строки, где правые границы
			a[i + 3][j] = a[i + 1][j];//копирование всей второй строки, где нижние границы
		}

		for (j = 1; j < (w - 2); j++)//удаление границ
		{
			if (a[i][j] == '0')
			{
				a[i][j] = a[i][j-1];//удаление правых границ: если данная ячейка=0, то приравниваем ее к предыдущей
			}

			if (a[i + 3][j] == '0')
			{
				a[i + 2][j] = (a[i+2][j-1]+1);//удаляем нижние границы: если она есть, то присваеваем свое число для ячейки
			}
		}



	}

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			if (a[i][j] != '0')
			{
				a[i][j] = ' ';
			}
		}
	}
	//рандомно ставим сердечко
	do
	{
		i = 1 + rand() %(h-1);
		j= 1 + rand() % (w-1);
		if (a[i][j] != '0')
		{
			a[i][j] = 'h';
		}

	} while (a[i][j] == '0');

		
}