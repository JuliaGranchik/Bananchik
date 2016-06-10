#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "mission.h"
#include "menu.h"
#include "timer.h"
#include <iostream>
#include <sstream>


using namespace sf;



//--------------------------------------------------------����� ������---------------------------------------------------
class Player { 
private: float x, y;//���������� ������ � � �
public:

float w, h, dx, dy, speed;
 int dir, playerScore, health;//����� ����������, �������� ����� ������
 bool life, hearts;//���������� �����, ����������
 String File;
 Image image;
 Texture texture;
 Sprite sprite;
 Player(String F, float X, float Y, float W, float H){
	 dir = 0; speed = 0; playerScore = 0; health = 5; hearts = false; // ���������������� ���������� ����� � ������������
 life = true;//���������������� ���������� ���������� �����
		File = F;
		w = W; h = H;
		image.loadFromFile(File);//�������� �����������
		texture.loadFromImage(image);//����������
		sprite.setTexture(texture);//���������
		x = X; y = Y;//���������� ��������� ������
		sprite.setTextureRect(IntRect(0, 0, w, h));  
	}



	void update(float time) //������� ���� �������� ������
	{
		switch (dir)//�������� �� �����������
		{
		case 0: dx = speed; dy = 0;   break;//����� ���� ������ ������
		case 1: dx = -speed; dy = 0;   break;//����� ���� ������ �����
		case 2: dx = 0; dy = speed;   break;//����� ���� ������ ����
		case 3: dx = 0; dy = -speed;   break;//����� ���� ������ �����
		}

		x += dx*time;//��������
		y += dy*time;

		speed = 0;//���������
		sprite.setPosition(x, y);
		interactionWithMap();//�������������� � ������
		if (health <= 0) { life = false; speed = 0; }//����� �������(((
		if (playerScore == 5) { hearts = true; speed = 0; life = false;}
	}
	float getplayercoordinateX() {	//����� �������� ���������� �	
		return x;
	}
	float getplayercoordinateY() {	//����� �������� ���������� Y 	
		return y;
	}

	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//������ �������, ������� ����� ��������� ���������
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's')//���� ��� ��������� ������������� ������� 0 (�����), �� ���������, ���� �� ���:
				{
					if (dy>0)//����
					{
						y = i * 32 - h;					}
					if (dy<0)//�����
					{
						y = i * 32 + 32;
					}
					if (dx>0)//������
					{
						x = j * 32 - w;
					}
					if (dx < 0)//�����
					{ 
						x = j * 32 + 32;
					}
				}
				if (TileMap[i][j] == 'h') {
					playerScore++;
					TileMap[i][j] = ' ';//������ ��������
					randomMapGenerate();
				}
				if (TileMap[i][j] == 'f') {
					health -= 1;//���� ����� ����������� � ���� ������,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ������
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
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.9f, 0.9f);//���� ��������� ��������, => ������ ���� ������

	Image map_image;//����������� ��� �����
	map_image.loadFromFile("map.png");//��������� ��������
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;
	s_map.setTexture(map);




	RenderWindow window(sf::VideoMode(700, 480), "Lonely banana searching for love");
	menu(window);//����� ����
	view.reset(sf::FloatRect(0, 0, 640, 480));//������ "����" ������ ��� �������� ������� ���� �
	view.reset(sf::FloatRect(0, 0, 1040, 1040)); 
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 25);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.

	Player p("banan.png", 45, 45, 50, 50);//�� = �����, ���������� �,�, ������, ������.

	const int size = 40;

	int hour = 2;
	int min = 60;
	int sec = 0;
	bool timeForPlaying = true;

	Text hourText("", font, size); Text minText("", font, size); Text secText("", font, size);//������ �� ����/������/�������
	Text text1(":", font, size); text1.setColor(Color::Yellow);//��������� ����� �������

	hourText.setColor(Color::Yellow); minText.setColor(Color::Yellow); secText.setColor(Color::Yellow);//���� ����
	hourText.setPosition(100, 200); minText.setPosition(200, 200); secText.setPosition(300, 200);//���������� ������� ����



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
			if (event.type == Event::KeyPressed)//������� ������� �������
				if ((event.key.code == Keyboard::Tab)) {//���� ������� ���


					switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

					case true: {
						std::ostringstream playerHealthString, gameTimeString, playerScoreString;    // �������� ���������� �������� � �������
						playerHealthString << p.health; gameTimeString << gameTime;
						playerScoreString << p.playerScore;
						std::ostringstream task;//������ ������ ������
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
						text.setString(task.str() + "\n���� �����: " + playerHealthString.str() + "\n������� �����:" + playerScoreString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str()
						text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
						s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����
						showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
						break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false: {
						text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
						showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
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
			//----------------------------------------���������� ����������-----------------------------------------------------
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
			text.setString("\n\n\n\n���� ��������. \n����� ������� ��� �����.");
			text.setPosition(view.getCenter().x - 200, view.getCenter().y - 100);//������ ������� ������, �������� �� ������ ������
			window.draw(text);//����� ���� �����
		}


		p.update(time);
		viewmap(time);//������� ���������� �����, �������� �� ����� 
		window.setView(view);//"��������" ������ � ���� sfml
		window.clear(Color(128, 106, 89));
		//----------------------------------------------------����� ���������----------------------------------------------------------------
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//� ��������
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//�������� ������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);//������ ������� �� ����������� ��� �������.

				window.draw(s_map);//������ ���������� �� �����
			}
		if (p.hearts)
		{
			text.setString("�� ����� ��� ������ ���������� �����!\n�� �������!");
			text.setPosition(view.getCenter().x-200, view.getCenter().y-100);//������ ������� ������, �������� �� ������ ������
			window.draw(text);//����� ���� �����


		}

		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����			
			window.draw(s_quest); window.draw(text); 
		}
		Sleep(10);// ���������� 
		if (event.key.code != Keyboard::Tab)
		{
			timer(hour, min, sec);//�������� �����
		}

		if (hour == 0 && min == 0)
		{
			p.life = false;

		}


		hourText.setString(intToString(hour)); minText.setString(intToString(min)); secText.setString(intToString(sec));// �� int � string �� string � Text

		text1.setPosition(100, 800); window.draw(text1);
		hourText.setPosition(70, 800);
		window.draw(hourText); 
		minText.setPosition(120, 800);
		window.draw(minText); 

		window.draw(p.sprite);//������ ����� 
		window.display();
	}

	return 0;
}