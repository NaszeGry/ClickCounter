#include "GameLibrary.h"
#include <Windows.h>

#define wid 800
#define heig 600

int main() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(wid, 600),
						"ClickCounter", sf::Style::Titlebar);

	int testing = 0;

	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text textA = DrawFunctions::getText("Nacisnij LPM aby rozpoczac test",
		&font, 30, sf::Vector2f(wid / 2.f, heig / 2.f));
	textA.setOrigin(sf::Vector2f(textA.getLocalBounds().width / 2.f, 0.f));

	Math::Clock clock;

	sf::Text textB = DrawFunctions::getText("", &font, 30, sf::Vector2f(wid / 2.f, heig / 2.f));
	textB.setOrigin(sf::Vector2f(textB.getLocalBounds().width / 2.f, 0.f));

	sf::Text textC = DrawFunctions::getText("", &font, 30, sf::Vector2f(wid / 2.f, heig / 2.f));
	textC.setOrigin(sf::Vector2f(textC.getLocalBounds().width / 2.f, 0.f));

	float testTime;
	
	float clicksTime;

	int cps = 0;
	int totalclcks = 0;

	sf::Color clearColor = sf::Color::Black;

	while (true) {
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == e.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window->close();
			}
			else if (testing == 0) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					testing = 1;
					testTime = 0.f;
					clicksTime = 0.f;
					cps = 0;
					totalclcks = 0;
					newSeed();
				}
			}
			else if (testing == 2) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					testing = 0;
					Sleep(300);
				}
			}
			else {
				if (e.type == e.MouseButtonPressed) {
					if (e.mouseButton.button == sf::Mouse::Button::Left) {
						cps = int(1.f / clicksTime);
						totalclcks += 1;
						clicksTime = 0.f;

						if (totalclcks % 10 == 0) {
							clearColor = Math::randomColor();
						}
					}
				}
			}
		}

		if (!window->isOpen())
			break;


		window->clear(clearColor);

		if (testing == 1) {

			window->draw(textB);

			clock.Update();
			testTime += clock.deltaTime;
			if (testTime > 30.f) {
				testing = 2;
				// init 3rd 
				textC.setString("Wynik: " + std::to_string(totalclcks / testTime).substr(0, 3) + " CPS");
				textC.setOrigin(sf::Vector2f(textC.getLocalBounds().width / 2.f, 0.f));

				
				Sleep(1000);
			}
			clicksTime += clock.deltaTime;

			textB.setString(std::to_string(cps) + " CPS\n" +
					std::to_string(totalclcks) + " total clicks\n" +
					std::to_string(30.f - testTime).substr(0,4) + "s remaining time");
			textB.setOrigin(sf::Vector2f(textB.getLocalBounds().width / 2.f, 0.f));
		}
		else if (testing == 0) {
			window->draw(textA);
		}
		else {
			window->draw(textC);
		}

		window->display();
	}
	delete window;
	return 0;
}