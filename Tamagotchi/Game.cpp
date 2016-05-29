#include "stdafx.h"
#include "Game.h"

Game::~Game() {
	for (int i = 0; i < tamaVector.size(); i++) {
		delete tamaVector[i];
	}
	for (int i = 0; i < balls.size(); i++) {
		delete balls[i];
	}
}
Game::Game() {
	t1 = sf::seconds(5);
	t2 = sf::seconds(5);
	text_play.setFont(font.style);
	text_play.setString("PLAY");
	text_play.setCharacterSize(30);
	text_play.setColor(sf::Color::White);
	text_play.setPosition(320, 50);



}

Game::Game(bool loaded) {
	tamagotchiCount = 0;
	font_numb.style.loadFromFile("number.ttf");
	t1 = sf::seconds(10);
	t2 = sf::seconds(3);

	text_play.setFont(font.style);
	text_play.setString("1-PLAY");
	text_play.setCharacterSize(30);
	text_play.setColor(sf::Color::White);
	text_play.setPosition(20, 20);

	text_feed.setFont(font.style);
	text_feed.setString("2-FEED");
	text_feed.setCharacterSize(30);
	text_feed.setColor(sf::Color::White);
	text_feed.setPosition(400, 20);

	text_clean.setFont(font.style);
	text_clean.setString("3-CLEAN");
	text_clean.setCharacterSize(30);
	text_clean.setColor(sf::Color::White);
	text_clean.setPosition(20, 410);

	text_heal.setFont(font.style);
	text_heal.setString("4-HEAL");
	text_heal.setCharacterSize(30);
	text_heal.setColor(sf::Color::White);
	text_heal.setPosition(400, 410);

	title_health.setFont(font.style);
	title_health.setString("HEALTH");
	title_health.setCharacterSize(30);
	title_health.setColor(sf::Color::Green);
	title_health.setPosition(640, 20);

	text_health.setFont(font_numb.style);
	text_health.setCharacterSize(36);
	text_health.setColor(sf::Color::Green);
	text_health.setPosition(690, 60);

	title_energy.setFont(font.style);
	title_energy.setString("ENERGY");
	title_energy.setCharacterSize(30);
	title_energy.setColor(sf::Color::Green);
	title_energy.setPosition(640, 110);

	text_energy.setFont(font_numb.style);
	text_energy.setCharacterSize(36);
	text_energy.setColor(sf::Color::Green);
	text_energy.setPosition(690, 150);

	title_happiness.setFont(font.style);
	title_happiness.setString("HAPPY");
	title_happiness.setCharacterSize(30);
	title_happiness.setColor(sf::Color::Green);
	title_happiness.setPosition(640, 200);

	text_happiness.setFont(font_numb.style);
	text_happiness.setCharacterSize(36);
	text_happiness.setColor(sf::Color::Green);
	text_happiness.setPosition(690, 240);

	title_cleanliness.setFont(font.style);
	title_cleanliness.setString("CLEAN");
	title_cleanliness.setCharacterSize(30);
	title_cleanliness.setColor(sf::Color::Green);
	title_cleanliness.setPosition(640, 290);
	
	text_cleanliness.setFont(font_numb.style);
	text_cleanliness.setCharacterSize(36);
	text_cleanliness.setColor(sf::Color::Green);
	text_cleanliness.setPosition(690, 330);

	sf::Vector2f size;
	size.x = 580;
	size.y = 50;

	rectangle_up.setFillColor(sf::Color::Transparent);
	rectangle_up.setOutlineColor(sf::Color::White);
	rectangle_up.setOutlineThickness(1);
	rectangle_up.setPosition(10, 10);
	rectangle_up.setSize(size);

	rectangle_down.setFillColor(sf::Color::Transparent);
	rectangle_down.setOutlineColor(sf::Color::White);
	rectangle_down.setOutlineThickness(1);
	rectangle_down.setPosition(10, 400);
	rectangle_down.setSize(size);

	Tamagotchi *tamagotchi = new Egg("Ala");
	tamaVector.push_back(tamagotchi);
	tamagotchiCount++;


	
}

void Game::setUpBackground(sf::RenderWindow &window) {
	sf::Texture texture;
	try {
		texture.loadFromFile("background.jpg");
		background.setTexture(texture);
	}
	catch (exception e) {
		cout << "Error loading texture!" << endl;
	}

	window.draw(background);
}


int Game::play(sf::RenderWindow &window) {
	Tamagotchi *tamagotchi;
	while (window.isOpen())
	{
		sf::Event event;
 		while (window.pollEvent(event))
		{
			//jezeli zamknieto okno
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				//jezeli nacisnieta zostala spacja, generowana jest nowa kula
				if (event.key.code == sf::Keyboard::Space)
				{
					sf::CircleShape shape(50);
					shape.setFillColor(sf::Color::Blue);
					window.draw(shape);
				
				}
			//nacisnieto 1 - bawimy sie
			if (event.key.code == sf::Keyboard::Num1) {
				//tamaVector[tamagotchiCount-1]->play();
				
			}

			if (event.key.code == sf::Keyboard::Num2) {
				tamaVector[tamagotchiCount - 1]->feed();
			}

			if (event.key.code == sf::Keyboard::Num3) {
				tamaVector[tamagotchiCount - 1]->clean();
			}
			if (event.key.code == sf::Keyboard::Num4) {
				tamaVector[tamagotchiCount - 1]->cure();
			}

			//jezeli nacisniety zostal klawisz escape, przechodzimy do trybu pauzy
			if (event.key.code == sf::Keyboard::Escape)
			{
				Pause pause;
				if (pause.pause_menu(window, tamaVector[tamagotchiCount-1]) == 0)
					window.close();
			}
		}

		//poruszanie sie graczem za pomoca strzalek
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			tamagotchi = tamaVector[tamagotchiCount - 1];
			try {
				Egg &egg = dynamic_cast<Egg &>(*tamagotchi);
				cout << egg.returnx();
				if (egg.returnx() > 0)
					egg.move(-14);
			}
			catch (bad_cast&) {
				try {
					Chicken &chicken = dynamic_cast<Chicken &>(*tamagotchi);
					if (chicken.returnx() > 0)
						chicken.move(-14);
				}
				catch (bad_cast&) {
					cout << "Bad cast" << endl;
				}
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			tamagotchi = tamaVector[tamagotchiCount - 1];
			try {
				Egg &egg = dynamic_cast<Egg &>(*tamagotchi);
				if (egg.returnx() <500)
					egg.move(14);
			}
			catch (bad_cast&) {
				try {
					Chicken &chicken = dynamic_cast<Chicken &>(*tamagotchi);
					if (chicken.returnx() < 500)
						chicken.move(14);
				}
				catch (bad_cast&) {
					cout << "Bad cast" << endl;
				}
			}

		}
		
		time = clock.getElapsedTime();
		//jezeli zmierzony czas jest wiekszy od zmiennej t1 (2 sek) generowany jest nowy wrog
		if (time > t1)
		{
			Tamagotchi *tamagotchi;
		
			if (typeid(Egg) == typeid(*tamaVector[tamagotchiCount - 1])) {
				Egg &egg = dynamic_cast<Egg &>(*tamaVector[tamagotchiCount - 1]);
			tamagotchi = new Chicken(egg);
			tamaVector.push_back(tamagotchi);
			tamagotchiCount++;
			clock.restart();
			}
			else {
				//if (typeid(Chicken) == typeid(*tamaVector[tamagotchiCount - 1])) 
				//tamagotchi = new Chicken(tamaVector[tamagotchiCount - 1]);
			}
			
		}

		time = clock_PU.getElapsedTime();
		//jezeli zmierzony czas jest wiekszy od zmiennej t1 (5 sek) generowany jest nowy bonus
		if (time>t2)
		{
			
				Ball *tmp = new Ball(125,0);
				balls.push_back(tmp);
				clock_PU.restart();
		}

		//obsluga rysowania i ruchu wrogow
	
		for (int i = 0; i<balls.size(); i++)
		{
			if (balls[i]->returny()<300)
			{
				//jezeli wrog miesci sie na polu gry, porusza sie w dol i jest rysowany na ekranie
				balls[i]->move();
				balls[i]->draw(window);
			}
			//else
			//{
			//	//jezeli nie miesci sie, graczowi odejmowana jest liczba punktow jaka zostala niezabitemu wrogowi w polu Damage
			////	player -= enemies[i]->returnDamage();
			//	//wrog jest usuwany z wektora i z pamieci
			//	tamaVector[tamagotchiCount - 1]->feed();
			//	delete balls[i];
			//	balls.erase(balls.begin() + i, balls.begin() + i + 1);
			//}
			Egg *egg = (dynamic_cast<Egg*>(tamaVector[tamagotchiCount - 1]));
			if (balls[i]->returny() +20 > egg->returny() && balls[i]->returny() < egg->returny()
				&& (balls[i]->returnx() < egg->returnx()+100) && balls[i]->returnx() > egg->returnx()) {
					tamaVector[tamagotchiCount - 1]->feed();
					delete balls[i];
					balls.erase(balls.begin() + i, balls.begin() + i + 1);
			}
		}
		

	

	


		//przejscie do funkcji wyswietlajacej na ekranie pole do gry, wynik, poziom
		show_info(window);
		window.display();
		window.clear();

	}
	return 0;
}

void Game::show_info(sf::RenderWindow &window)
{


	int tamaHealth = tamaVector[tamagotchiCount - 1]->getHealth();
	int tamaHappiness = tamaVector[tamagotchiCount - 1]->getHappiness();
	int tamaCleanless = tamaVector[tamagotchiCount - 1]->getCleanless();
	int tamaEnergy = tamaVector[tamagotchiCount - 1]->getEnergy();

	text_health.setString(int2str(tamaHealth));
	text_happiness.setString(int2str(tamaHappiness));
	text_cleanliness.setString(int2str(tamaCleanless));
	text_energy.setString(int2str(tamaEnergy));

	window.draw(title_health);
	window.draw(title_happiness);
	window.draw(title_cleanliness);
	window.draw(title_energy);
	
	window.draw(text_health);
	window.draw(text_happiness);
	window.draw(text_cleanliness);
	window.draw(text_energy);
	window.draw(text_play);
	window.draw(text_feed);
	window.draw(text_clean);
	window.draw(text_heal);

	//setUpBackground(window);

	window.draw(rectangle_up);
	window.draw(rectangle_down);

	tamaVector[tamagotchiCount - 1]->draw(window);
}