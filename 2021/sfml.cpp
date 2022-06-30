#include <SFML/Graphics.hpp>	

using namespace sf;

bool transf = false;

int main() {
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(500, 400), "SFML Works!", Style::Default, settings);

	CircleShape triangle(50.f, 3);
	triangle.setPosition(200, 180);
	triangle.setFillColor(Color::Blue);

	while (window.isOpen())	{
		Event event;
		while (window.pollEvent(event))	{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Right) transf = true;
				if (event.key.code == Keyboard::Left) transf = false;
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left)
					transf = true;
				if (event.key.code == Mouse::Right)
					transf = false;
			}
		}
		window.clear(Color::Cyan);

		if (transf)
			triangle.rotate(0.1);

		window.draw(triangle);

		window.display();
	}

	return 0;
}
