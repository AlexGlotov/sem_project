#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <windows.h>
#include <string>

using namespace sf;
using namespace std;

int mode;
int w = 50; //клетка

struct miner
{
	int x = 1, y = 1, mine_dec = 0, healh = 0;
	bool key_dec = 0, red = 0, green = 0, blue = 0;
};

int rand_uns(int min, int max)
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

int** create_pole() {
	int m = 1000, n = 1000;
	switch (mode)
	{
	case 1:
		m = 32;
		n = 32;
		break;
	case 2:
		m = 52;
		n = 52;
		break;
	case 3:
		m = 52;
		n = 102;
		break;
	}
	int** pole = new int* [m];
	for (int i = 0; i < m; i++) {
		pole[i] = new int[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((i == 0) || (j == 0) || (i == (m - 1)) || (j == (n - 1))) {
				pole[i][j] = 1000;
			}
			else {
				pole[i][j] = 0;
			}
		}
	}
	pole[1][1] = -1;
	for (int i = 0; i < m * n / 5; i++) {
		int i_rand = rand_uns(1, m - 1);
		int j_rand = rand_uns(1, n - 1);
		if (pole[i_rand][j_rand] == 0) {
			pole[i_rand][j_rand] = 15;
		}
		else {
			i--;
		}

	}
	for (int i = 0; i < 3; i++) {
		int i_rand = rand_uns(1, m - 1);
		int j_rand = rand_uns(1, n - 1);
		if (pole[i_rand][j_rand] == 0) {
			pole[i_rand][j_rand] = i * 100 + 700;
		}
		else {
			i--;
		}
	}
	for (int i = 0; i < 3; i++) {
		int i_rand = rand_uns(1, m - 1);
		int j_rand = rand_uns(1, n - 1);
		if (pole[i_rand][j_rand] == 0) {
			pole[i_rand][j_rand] = 20;
		}
		else {
			i--;
		}
	}
	for (int i = 0; i < 1; i++) {
		int i_rand = rand_uns(1, m - 1);
		int j_rand = rand_uns(n - 4, n - 1);
		if (pole[i_rand][j_rand] == 0) {
			pole[i_rand][j_rand] = -1000;
		}
		else {
			i--;
		}
	}
	for (int i = 1; i < m - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			pole[i][j]++;
		}
	}
	pole[1][2] = 1;
	pole[2][1] = 1;
	return pole;
}

void init_menu() {
	/*while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			// Была нажата кнопка мыши…?
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left) {
					if (() && ()) {
						mode = 1;
						return;
					}
					if (() && ()) {
						mode = 2;
						return;
					}
					if (() && ()) {
						mode = 3;
						return;
					}
				}
		}
		app.clear(Color::Black);
		app.display();
	}*/
	while (true) {
		cout << "Выберете размер карты" << endl;
		cout << "Press '1' to change map 30*30" << endl;
		cout << "Press '2' to change map 50*50" << endl;
		cout << "Press '3' to change map 50*100" << endl;
		cout << ">>";
		cin >> mode; cout << endl;
		if (mode == 1 || mode == 2 || mode == 3) return;
	}

}

int** main_menu() {
	/*while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			// Была нажата кнопка мыши…?
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left) {
					if (() && ()) {
						settings_menu();
					}
					if (() && ()) {
						init_menu();

						int** point = create_pole();
						return point;

					}
				}
		}
		app.clear(Color::Black);
		app.display();
	}*/
	cout << "Print Enter to begin" << endl;
	init_menu();
	int** point = create_pole();
	return point;
}

void settings_menu() {

	return;
}

void destructor(int** pole) {
	int m;
	switch (mode)
	{
	case 1:
		m = 30;
		break;
	case 2:
		m = 50;
		break;
	case 3:
		m = 50;
		break;
	}
	for (int i = 0; i < m; i++)
	{
		delete[] pole[i];
	}
	delete[] pole;

}

int mine_detector(int** pole, int x, int y, int mode) {
	int m, n;
	switch (mode)
	{
	case 1:
		m = 30;
		n = 30;
		break;
	case 2:
		m = 50;
		n = 50;
		break;
	case 3:
		m = 50;
		n = 100;
		break;
	default:
		break;
	}
	int sum = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((pole[x + i][y + j] - 1) == 15 || ((pole[x + i][y + j] - 2) == 15)) {
				sum++;
			}
		}
	}
	return sum;
}

bool key_detector(int** pole, int x, int y, int mode) {
	int m, n;
	switch (mode)
	{
	case 1:
		m = 32;
		n = 32;
		break;
	case 2:
		m = 52;
		n = 52;
		break;
	case 3:
		m = 52;
		n = 102;
		break;
	default:
		break;
	}
	for (int i = -3; i < 4; i++) {
		for (int j = -3; j < 4; j++) {
			if((x + i > 0) && (x + i < m) && (y + j > 0) && (y + j < n))
			if ((pole[x + i][y + j] / 1000 == 0) && (pole[x + i][y + j] / 100 > 0)) {
				return true;
			}
		}
	}
	return false;
}

void game_over(int** pole) {
	destructor(pole);
	exit(0);
}

int main() {

	miner data;
	int end = 0;
	// Загрузка текстур и создание спрайтов
	Texture trail, stone, dirt, exit, dig_left, dig_up, dig_right, lose_game, green_pole, bomb;
	Texture dig_down, flag, background, heart, green, red, blue, win_game, red_pole, blue_pole;
	trail.loadFromFile("images/trail.jpg");
	stone.loadFromFile("images/stone.jpg");
	dirt.loadFromFile("images/dirt.jpg");
	exit.loadFromFile("images/exit.jpg");
	dig_left.loadFromFile("images/dig_left.jpg");
	dig_right.loadFromFile("images/dig_right.jpg");
	dig_up.loadFromFile("images/dig_up.jpg");
	dig_down.loadFromFile("images/dig_down.jpg");
	flag.loadFromFile("images/flag.jpg");
	background.loadFromFile("images/background.jpg");
	heart.loadFromFile("images/heart.jpg");
	green.loadFromFile("images/green.png");
	red.loadFromFile("images/red.png");
	blue.loadFromFile("images/blue.png");
	win_game.loadFromFile("images/win.jpg");
	lose_game.loadFromFile("images/lose.jpg");
	red_pole.loadFromFile("images/red_pole.png");
	green_pole.loadFromFile("images/green_pole.png");
	blue_pole.loadFromFile("images/blue_pole.png");
	bomb.loadFromFile("images/bomb.png");
	Sprite t(trail), s(stone), d(dirt), ex(exit), left(dig_left), h(heart), gk(green), rk(red), lose(lose_game), gkp(green_pole), b(bomb);
	Sprite right(dig_right), up(dig_up), down(dig_down), f(flag), bg(background), bk(blue), win(win_game), rkp(red_pole), bkp(blue_pole);
	
	Font font;//шрифт 
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
	Text text("", font, 40);
	text.setStyle(sf::Text::Bold);
	
	int** pole = main_menu();

	int x0 = 35, y0 = 115, m, n, x_point = 0, y_point = 0, x_mem = 0, y_mem = 0;
	
	RenderWindow app(VideoMode(800, 800), "Miner");
	switch (mode)
	{
	case 1:
		m = 32;
		n = 32;
		break;
	case 2:
		m = 52;
		n = 52;
		break;
	case 3:
		m = 52;
		n = 102;
		break;
	default:
		break;
	}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = (pos.x - x0) / w + x_point;
		int y = (pos.y - y0) / w + y_point;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed) {
				int num = pole[x][y];
				if (e.key.code == Mouse::Left) {
					if (((abs(x - data.x) + abs(y - data.y)) == 1) && (pole[x][y] % 5 != 2)) {
						x_mem = data.x;
						y_mem = data.y;
						data.x = x;
						data.y = y;
						data.key_dec = key_detector(pole, x, y, mode);
						data.mine_dec = mine_detector(pole, x, y, mode);
						if ((num - 1) == 700) {
							data.red = true;
							pole[x][y] = 0;
							rkp.setPosition((x - x_point) * w + x0, (y - y_point) * w + y0);
							app.draw(rkp);
							app.display();
							Sleep(1000);
						}
						if ((num - 1) == 800) {
							data.green = true;
							pole[x][y] = 0;
							gkp.setPosition((x - x_point) * w + x0, (y - y_point) * w + y0);
							app.draw(gkp);
							app.display();
							Sleep(1000);
						}
						if ((num - 1) == 900) {
							data.blue = true;
							pole[x][y] = 0;
							bkp.setPosition((x - x_point) * w + x0, (y - y_point) * w + y0);
							app.draw(bkp);
							app.display();
							Sleep(1000);
						}
						if ((num - 1) == 20) {
							data.healh++;
							h.setPosition((x - x_point) * w + x0, (y - y_point) * w + y0);
							app.draw(h);
							app.display();
							Sleep(1000);
							pole[x][y] = 0;
						}
						if (((num - 1) == -1000)) {
							if ((data.blue + data.green + data.red) == 3) {
								end = 2;
							}
							else {
								data.x = x_mem;
								data.y = y_mem;
							}
						}
						if ((num - 1) == 15) {
							b.setPosition((x - x_point) * w + x0, (y - y_point) * w + y0);
							app.draw(b);
							app.display();
							Sleep(500);
							if (data.healh == 0) {
								end = 1;
							}
							else {
								data.healh--;
							}
						}
						if (num % 5 == 1) {
							pole[x][y] = 0;
						}
					}
				}
				if (e.key.code == Mouse::Right) {
					if (num < 1000) {
						if ((num % 5) == 1) {
							pole[x][y]++;
						}
						if ((num % 5) == 2) {
							pole[x][y]--;
						}
					}
				}
			}
			// 1000 - стена, 15 - бомба, 700, 800, 900 - ключи, -1000 - выход, 20 - хп, ост.1 - закрытая, ост.2 - флаг, 0 - открытая
			app.clear();
			if (end == 2) {
				win.setPosition(0, 0);
				app.draw(win);
				app.display();
				Sleep(1000);
				game_over(pole);
			}
			if (end == 1) {
				lose.setPosition(0, 0);
				app.draw(lose);
				app.display();
				Sleep(1000);
				game_over(pole);
			}
			bg.setPosition(0, 0);
			app.draw(bg);
			int start_draw = 11;
			for (int i = x_point; i < max(min(data.x + 6, m), start_draw); i++) {
				for (int j = y_point; j < max(min(data.y + 6, n), start_draw); j++) {
					if (pole[i][j] == 1000) {
						s.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(s);
					}
					if (pole[i][j] == 0) {
						t.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(t);
					}
					if (pole[i][j] % 5 == 1) {
						d.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(d);
					}
					if (pole[i][j] == 2000) {
						ex.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(ex);
					}
					if (pole[i][j] % 5 == 2) {
						f.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(f);
					}
					if (i == data.x && j == data.y) {
						if (data.y - y_mem == - 1) {
							up.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
							app.draw(up);
						}
						if (data.y - y_mem == 1) {
							down.setPosition((i - x_point)* w + x0, (j - y_point)* w + y0);
							app.draw(down);
						}
						if (data.x - x_mem == - 1) {
							left.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
							app.draw(left);
						}
						if (data.x - x_mem == 1) {
							right.setPosition((i - x_point)* w + x0, (j - y_point)* w + y0);
							app.draw(right);
						}

					}
					if ((pole[i][j] - 1) == -1000) {
						ex.setPosition((i - x_point) * w + x0, (j - y_point) * w + y0);
						app.draw(ex);
					}
					if (data.healh) {
						switch (data.healh)
						{
						case 1:
							h.setPosition(660, 70);
							app.draw(h);
							break;
						case 2:
							h.setPosition(660, 70);
							app.draw(h);
							h.setPosition(720, 70);
							app.draw(h);
							break;
						case 3:
							h.setPosition(660, 70);
							app.draw(h);
							h.setPosition(720, 70);
							app.draw(h);
							h.setPosition(690, 130);
							app.draw(h);
							break;
						}
					}
					if (data.key_dec) {
						CircleShape circle(20.f); 
						circle.setFillColor(Color::Green);
						circle.move(650, 300);
						app.draw(circle);
					}
					else {
						CircleShape circle(20.f);
						circle.setFillColor(Color::Red);
						circle.move(650, 300);
						app.draw(circle);
					}
					text.setString(std::to_string(data.mine_dec));
					text.setPosition(710, 300);
					app.draw(text);
					if (data.blue) {
						bk.setPosition(690, 400);
						app.draw(bk);
					}
					if (data.green) {
						gk.setPosition(690, 500);
						app.draw(gk);
					}
					if (data.red) {
						rk.setPosition(690, 600);
						app.draw(rk);
					}
				}
			}
			app.display();
			start_draw--;
			x_point = min(max(0, data.x - 5), m - 11);
			y_point = min(max(0, data.y - 5), n - 11);
		}
	}
	return 0;
}