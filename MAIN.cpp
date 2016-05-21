#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "mission.h"
#include "menu.h"
#include <iostream>
#include <sstream>


using namespace sf;



//--------------------------------------------------------КЛАСС ИГРОКА---------------------------------------------------
class Player { 
private: float x, y;//координаты игрока х и у
public:

float w, h, dx, dy, speed;
 int dir, playerScore, health;//новая переменная, хранящая жизни игрока
 bool life, hearts;//переменная жизнь, логическая
 String File;
 Image image;
 Texture texture;
 Sprite sprite;
 Player(String F, float X, float Y, float W, float H){
	 dir = 0; speed = 0; playerScore = 0; health = 5; hearts = false; // инициализировали переменную жизни в конструкторе
 life = true;//инициализировали логическую переменную жизни
		File = F;
		w = W; h = H;
		image.loadFromFile(File);//загрузка изображения
		texture.loadFromImage(image);//текстурина
		sprite.setTexture(texture);//заливочка
		x = X; y = Y;//координата появления банана
		sprite.setTextureRect(IntRect(0, 0, w, h));  
	}



	void update(float time) //функция дает движение банану
	{
		switch (dir)//движение по направлению
		{
		case 0: dx = speed; dy = 0;   break;//банан идет только вправо
		case 1: dx = -speed; dy = 0;   break;//банан идет только влево
		case 2: dx = 0; dy = speed;   break;//банан идет только вниз
		case 3: dx = 0; dy = -speed;   break;//банан идет только вверх
		}

		x += dx*time;//движение
		y += dy*time;

		speed = 0;//остановка
		sprite.setPosition(x, y);
		interactionWithMap();//взаимодействие с картой
		if (health <= 0) { life = false; speed = 0; }//банан умерает(((
		if (playerScore == 5) { hearts = true; speed = 0; life = false;}
	}
	float getplayercoordinateX() {	//будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY() {	//будем забирать координату Y 	
		return y;
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//задаем квадрат, который будет проверять местность
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's')//если наш квадратик соответствует символу 0 (стена), то проверяем, куда мы шли:
				{
					if (dy>0)//вниз
					{
						y = i * 32 - h;					}
					if (dy<0)//вверх
					{
						y = i * 32 + 32;
					}
					if (dx>0)//вправо
					{
						x = j * 32 - w;
					}
					if (dx < 0)//влево
					{ 
						x = j * 32 + 32;
					}
				}
				if (TileMap[i][j] == 'h') {
					playerScore++;
					TileMap[i][j] = ' ';//убрали сердечко
					randomMapGenerate();
				}
				if (TileMap[i][j] == 'f') {
					health -= 1;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
					TileMap[i][j] = ' ';//убрали цветок
				}
			}
	}
};


int main()
{ 
	Image quest_image;
	quest_image.loadFromFile("svitok.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.9f, 0.9f);//чуть уменьшили картинку, => размер стал меньше

	Image map_image;//изображение для карты
	map_image.loadFromFile("map.png");//загружаем картинку
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;
	s_map.setTexture(map);




	RenderWindow window(sf::VideoMode(700, 480), "Lonely banana searching for love");
	menu(window);//вызов меню
	view.reset(sf::FloatRect(0, 0, 640, 480));//размер "вида" камеры при создании объекта вида к
	view.reset(sf::FloatRect(0, 0, 1040, 1040)); 
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 25);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	Player p("banan.png", 45, 45, 50, 50);//гг = банан, координата Х,У, ширина, высота.


	bool showMissionText = true;
	randomMapGenerate();
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); 
		clock.restart();
		time = time / 800;


		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
						std::ostringstream playerHealthString, gameTimeString, playerScoreString;    // объявили переменную здоровья и времени
						playerHealthString << p.health; gameTimeString << gameTime;
						playerScoreString << p.playerScore;
						std::ostringstream task;//строка текста миссии
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
						text.setString(task.str() + "\nВаши жизни: " + playerHealthString.str() + "\nНайдено любви:" + playerScoreString.str() + "\nВремя игры: " + gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
						text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
						s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
						showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
						break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
						text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
						showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
						break;
					}
					}
				}
			if ((event.key.code == Keyboard::Space)) {
				randomMapGenerate();
				p.health--;
			}
		}


		if (p.life) {
			//----------------------------------------Управление персонажем-----------------------------------------------------
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				p.dir = 1; p.speed = 0.1;
				p.sprite.setTextureRect(IntRect(0, 0, 50, 50));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				p.dir = 0; p.speed = 0.1;
				p.sprite.setTextureRect(IntRect(0, 0, 50, 50));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				p.dir = 3; p.speed = 0.1;
				p.sprite.setTextureRect(IntRect(0, 0, 50, 50));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				p.dir = 2; p.speed = 0.1;
				p.sprite.setTextureRect(IntRect(0, 0, 50, 50));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			}
		}
		if (!p.life)
		{
			text.setString("\n\n\n\nВы умерли.\nТак и не нашли \nлюбовь для банана.\nТеперь он будет \nгрустить:с");
			text.setPosition(view.getCenter().x - 200, view.getCenter().y - 100);//задаем позицию текста, отступая от центра камеры
			window.draw(text);//рисую этот текст
		}


		p.update(time);//оживляем объект p класса Player с помощью времени, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		viewmap(time);//функция скроллинга карты, передаем ей время 
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear(Color(128, 106, 89));
		//----------------------------------------------------карта лабиринта----------------------------------------------------------------
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//и сердечко
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//добавили цветок
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);//задает каждому из квадратиков них позицию.

				window.draw(s_map);//рисуем квадратики на экран
			}
		/*
		std::ostringstream playerHealthString, gameTimeString, playerScoreString;    // объявили переменную здоровья и времени
		playerHealthString << p.health; gameTimeString << gameTime;
		playerScoreString << p.playerScore;	
		text.setString("Ваши жизни: " + playerHealthString.str() + "\nНайдено любви:" + playerScoreString.str() + "\nВремя игры: " + gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()

		text.setPosition(view.getCenter().x + 300, view.getCenter().y + 350);//задаем позицию текста, отступая от центра камеры
		window.draw(text);//рисую этот текст
		*/

		if (p.hearts)
		{
			text.setString("ВЫ НАШЛИ ДЛЯ БАНАНА ДОСТАТОЧНО ЛЮБВИ!\nВЫ МОЛОДЕЦ!");
			text.setPosition(view.getCenter().x-200, view.getCenter().y-100);//задаем позицию текста, отступая от центра камеры
			window.draw(text);//рисую этот текст


		}

		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока			
			window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		}

		window.draw(p.sprite);//рисуем банан 
		window.display();
	}

	return 0;
}