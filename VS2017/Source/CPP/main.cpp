#include <SFML/Graphics.hpp>


int main() {
	sf::RenderWindow window({ 1024, 768 }, "Hello World");
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);

	window.setFramerateLimit(30);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		window.clear();

		window.draw(shape);

		window.display();


	}

	return 0;

}

//IT WORKS!!