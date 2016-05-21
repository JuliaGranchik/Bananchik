#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока


	view.setCenter(x + 100, y); //следим за игроком, передавая его координаты камере. +100 - сместили камеру по иксу вправо. эксперементируйте


}
void viewmap(float time) { //функция для перемещения камеры по карте


	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1*time, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1*time);
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1*time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1*time);
	}

}

