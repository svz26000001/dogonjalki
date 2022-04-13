#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "View.hpp"

using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
	/* это задел на следующие уроки,прошу не обращать внимания) //bbbb/ 
private: float w, h, dx, dy, x, y, speed;
		 int dir, playerScore, health;
		 bool life;
		 */

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect, onGround;//добавили переменные состояния движения и выбора объекта
	enum {left, right, up, down, jump, stay} state;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(0, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		x = X; y = Y;
		sprite.setTextureRect(IntRect(28, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.8; onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down; speed = 0.1;
		}
	}
	void update(float time)
	{
		control();
		switch (state)
		{
		case right: dx = speed; break;
		case left: dx = -speed; break;
		case up: break;
		case down: break;
		case jump: break;
		case stay: break;
		}
		x += dx * time;
		interactionWithMap(dx, 0);
		y += dy * time;
		interactionWithMap(0, dy);
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); 
		if (health <= 0) { life = false; }
		dy = dy + 0.0015 * time;
	}

	float getWidth() {//получить ширину объека
		return w;
	}
	void setWidth(float width) {//установить ширину объекта
		w = width;
	}

	float getHeight() {//взять ширину объекта
		return h;
	}
	void setHeight(float height) {//задать ширину объекта
		h = height;
	}

	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}

	void interactionWithMap(float Dx, float Dy)
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (Dy > 0) { y = i * 32 - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = i * 32 + 32;  dy = 0; }
					if (Dx > 0) { x = j * 32 - w; }
					if (Dx < 0) { x = j * 32 + 32; }
				}

				/*if (TileMap[i][j] == 's') {
					playerScore++;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'f') {
					health -= 40;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'h') {
					health += 20;
					TileMap[i][j] = ' ';
				}*/

			}
	}

};

class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(String File, String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


int main()
{


	RenderWindow window(VideoMode(640, 640), "Lesson 19. kychka-pc.ru");
	view.reset(FloatRect(0, 0, 640, 640));

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::Black);


	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	//SpriteManager playerSprite("hero.png", "Hero");//это задел на следующие уроки,прошу не обращать внимания)

	Player p("GreenHero.png", 250, 960-110, 40, 96);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	int tempY = 0;//коорд Y
	float distance = 0;//это расстояние от объекта до тыка курсора
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {//а именно левая
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						p.sprite.setColor(Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
						p.isSelect = true;
					}
				}


			if (p.isSelect)//если выбрали объект
				if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
					if (event.key.code == Mouse::Right) {//а именно правая
						p.isMove = true;//то начинаем движение
						p.isSelect = false;//объект уже не выбран
						p.sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
						tempX = pos.x;//забираем координату нажатия курсора Х
						tempY = pos.y;//и Y

					}
		}


		if (p.isMove) {
			distance = sqrt((tempX - p.x) * (tempX - p.x) + (tempY - p.y) * (tempY - p.y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора

			if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта

				p.x += 0.1 * time * (tempX - p.x) / distance;//идем по иксу с помощью вектора нормали
				p.y += 0.1 * time * (tempY - p.y) / distance;//идем по игреку так же
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}




		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (p.life) checkingCoord(p.getplayercoordinateX(), p.getplayercoordinateY());


		p.update(time);


		window.setView(view);
		window.clear();

		window.getSystemHandle();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}