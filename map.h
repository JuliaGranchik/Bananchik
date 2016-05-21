#pragma once
#include <SFML\Graphics.hpp>


int i, j;
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerate() {//рандомно расставляем камни

	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	

//--------------------------------------------
	for (i = 1; i < (HEIGHT_MAP-1); i += 3)
	{
		//присваивание каждой ячейке свое собсвтенное множество | все по 2, потому что по-другому банан не поместится :с
		for (j = 1; j < (WIDTH_MAP - 1); j += 2)
		{
			TileMap[i][j] = ('%d', j);
			TileMap[i][j + 1] = ('%d', j);
			TileMap[i][j + 2] = ('%d', j);


			TileMap[i+1][j] = ('%d', j);
			TileMap[i+1][j + 1] = ('%d', j);
			TileMap[i+1][j + 2] = ('%d', j);
		}

		for (j = 3; j < (WIDTH_MAP - 2); j += 3)// ???????????
		{
			//правые границы

			int random = 1 + rand() % 2;//рандомно решаем, добавлять границу или нет
			if (random == 1 && i==1)//если 1, то добавляем
			{
				TileMap[i][j] = '0';
				TileMap[i+1][j] = '0';
			}
			if (i != 1 && random==1)
			{
				if ((TileMap[i - 1][j] == '0' && TileMap[i - 2][j] == '0') || (TileMap[i - 1][j - 1] != '0' && TileMap[i - 1][j - 2] != '0' && TileMap[i - 1][j + 1] != '0' && TileMap[i - 1][j + 2]))
				{
					TileMap[i][j] = '0';
					TileMap[i + 1][j] = '0';
				}
			}
		}

		if (i != 22)
		{
			//объединение множеств
			for (j = 4; j < (WIDTH_MAP - 1); j++)
			{
				if (TileMap[i][j + 1] != TileMap[i][j] && TileMap[i][j] != '0' && TileMap[i][j + 1] != '0')
				{
					TileMap[i][j + 1] = TileMap[i][j];//объединяем ячейки в одно множество
					TileMap[i + 1][j + 1] = TileMap[i + 1][j];
				}
			}


			//Создание нижних границ
			//проверка на замкнутые области
			for (j = 1; j < (WIDTH_MAP - 1); j++)
			{
				int random = 1 + rand() % 2;//рандомно решаем, добавлять границу или нет
				if ((random == 1 && TileMap[i][j + 2] == TileMap[i][j]) || (random == 1 && TileMap[i][j] == '0') || (random == 1 && TileMap[i][j] != TileMap[i][j + 2] && TileMap[i][j + 1] == '0' && TileMap[i + 2][j - 1] != '0' && TileMap[i + 2][j - 2] != '0'))//если 1, то добавляем
				{
					TileMap[i + 2][j] = '0';
				}
				else
				{
					TileMap[i + 2][j] = ' ';
				}
			}

			//проверка на узкий прозод 
			for (j = 1; j < (WIDTH_MAP); j++)
			{
				if (TileMap[i + 2][j] != '0' && TileMap[i + 2][j - 1] == '0' && TileMap[i + 2][j + 1] == '0' && TileMap[i + 1][j - 1] != '0')//если условие соблюдается, то предыдущей нулевой ячейке присваивается значение текущей не нулевой
				{
					TileMap[i + 2][j - 1] = TileMap[i + 2][j];
				}
			}

			//копирование строки, там где правые границы, и их удаление 
			for (j = 1; j < (WIDTH_MAP - 1); j++)
			{
				TileMap[i + 3][j] = TileMap[i][j];//копирование всей первой строки, где правые границы
				TileMap[i + 4][j] = TileMap[i + 1][j];
				TileMap[i + 5][j] = TileMap[i + 2][j];//копирование всей второй строки, где нижние границы
			}

			for (j = 1; j < (WIDTH_MAP); j++)//удаление границ
			{
				if (TileMap[i + 3][j] == '0')
				{
					TileMap[i + 3][j] = TileMap[i + 3][j - 1];//удаление правых границ: если данная ячейка=0, то приравниваем ее к предыдущей
					TileMap[i + 4][j] = TileMap[i + 3][j - 1];
				}

				if (TileMap[i + 5][j] == '0')
				{
					TileMap[i + 5][j] = ' ';
				}
			}
		}
	}

		for (i = 0; i < HEIGHT_MAP; i++)
		{
			for (j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] != '0')
				{
					TileMap[i][j] =' ';
				}
			}
		}

		//создание правой и нижней границы
		for (i = 0; i < HEIGHT_MAP; i++)
		{
			TileMap[i][39] = '0';
		}
		for (j = 0; j < WIDTH_MAP; j++)
		{
			TileMap[24][j] = '0';
		}

		do {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 'h'; //то ставим туда камень.
		}
	} while (TileMap[randomElementY][randomElementX] == ' ');
	int count=0;//расставляем цветы
	while (count < 10) {
		do {
			randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
			randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

			if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
				TileMap[randomElementY][randomElementX] = 'f';
				count++;
			}
		} while ((TileMap[randomElementY][randomElementX] == ' '));
	}
	count = 0;//расставляем камни
	while (count < 10) {
		do {
			randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
			randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

			if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
				TileMap[randomElementY][randomElementX] = 's';
				count++;
			}
		} while ((TileMap[randomElementY][randomElementX] == ' '));
	}

}