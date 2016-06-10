#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<Windows.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

string intToString(int a)// переобразовывает число в строку
{

	std::ostringstream ost;
	ost << a;
	std::string s_num = ost.str();

	return s_num;
}
void timer(int &hour, int &min, int &sec)// отнимает секунды/минуты/часы
{
	if (sec > 0)
	{
		sec--;
	}
	else  if (sec == 0 && min>0) {
		sec = 59;
		min--;
	}
	else if (sec == 0 && min == 0 && hour > 0)
	{
		sec = 59;
		min = 59;
		hour--;
	}
	else if (sec == 0 && min == 0 && hour == 0)
	{
		return;
	}
}
