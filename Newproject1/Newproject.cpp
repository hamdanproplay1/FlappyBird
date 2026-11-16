#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
FloatRect getBirdHitbox(const Sprite& bird) {
	float padding_x = 69.0f;
	float padding_y = 69.0f;
	FloatRect bounds = bird.getGlobalBounds();
	return FloatRect(
		Vector2f(bounds.position.x + padding_x, bounds.position.y + padding_y),
		Vector2f(bounds.size.x - (padding_x * 2), bounds.size.y - (padding_y * 2))
	);
}

int main()
{
	const auto SPEED = 150;
	const float JUMPSTRENGTH = 300.f;
	const float GRAVITY = 900.f;
	float velocity = 0.f;
	bool pause = true;
	Clock _clock;
	Font font;

	auto window = RenderWindow(VideoMode({ 1050,600 }), "Flappy Bird");
	Texture birdTexture;
	if (!birdTexture.loadFromFile("Assets/FlappyBird.png")) {
		return -1;
	}
	if (!font.openFromFile("Assets/font.ttf"))
	{
		return -1;
	}
	Text objs(font);
	objs.setString("Game Over!");
	objs.setFillColor(Color::Red);
	objs.setCharacterSize(80);
	objs.setPosition({ 325.f, 230.f });
	Text restart(font);
	restart.setString("Press \"W\" to restart");
	restart.setFillColor(Color::Black);
	restart.setCharacterSize(50);
	restart.setPosition({ 285.f, 380.f });
	Sprite bird(birdTexture);
	bird.setPosition({ 75.f, 250.f });
	bird.setScale({ 0.2f,0.2f });

	Texture bottompipeTexture;
	if (!bottompipeTexture.loadFromFile("Assets/Bottom_pipe.png")) {
		cout << "Failed to load this asset:(";
		return -1;
	}
	Sprite Bottompipe(bottompipeTexture);
	Bottompipe.setPosition({ 350.f, 250.f });
	Bottompipe.setScale({ 0.75f,0.75f });
	Texture upperpipeTexture;
	if (!upperpipeTexture.loadFromFile("Assets/Upper_pipe.png")) {
		cout << "Failed to load this asset:(";
		return -1;
	}
	Sprite Upperpipe(upperpipeTexture);
	Upperpipe.setPosition({ 650.f,0.f });
	Upperpipe.setScale({ 0.75f,0.75f });
	Texture BackgroundTexture;
	if (!BackgroundTexture.loadFromFile("Assets/flappybirdwallpaper.jpg")) {
		cout << "Failed to load this asset:(";
		return -1;
	}
	Sprite Background(BackgroundTexture);
	Background.setPosition({ 0.f,0.f });
	Background.setScale({
	1050.f / BackgroundTexture.getSize().x,
	600.f / BackgroundTexture.getSize().y
		});

	Sprite Background2(BackgroundTexture);
	Background2.setPosition({ 1049.f,0.f });
	Background2.setScale({
	1050.f / BackgroundTexture.getSize().x,
	600.f / BackgroundTexture.getSize().y
		});

	while (window.isOpen())
	{

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (const auto* keypressed = event->getIf < Event::KeyPressed>()) {
				if (keypressed->code == Keyboard::Key::Space) {
					velocity = -JUMPSTRENGTH;

				}
				if (keypressed->code == Keyboard::Key::W) {
					pause = true;

				}
			}
		}
		float deltaTime = _clock.restart().asSeconds();
		if (Background.getPosition().x <= -1050) {
			Background.setPosition({ 1048.f,0.f });
		}
		if (Background2.getPosition().x <= -1050) {
			Background2.setPosition({ 1048.f,0.f });
		}
		Sprite Upperpipe2(upperpipeTexture);
		Upperpipe2.setPosition({ 650.f,0.f });
		Upperpipe2.setScale({ 0.75f,0.75f });
		Sprite Bottompipe2(bottompipeTexture);
		Bottompipe2.setPosition({ 350.f, 250.f });
		Bottompipe2.setScale({ 0.75f,0.75f });
		Sprite Upperpipe3(upperpipeTexture);
		Upperpipe3.setPosition({ 650.f,0.f });
		Upperpipe3.setScale({ 0.75f,0.75f });
		Sprite Bottompipe3(bottompipeTexture);
		Bottompipe3.setPosition({ 350.f, 250.f });
		Bottompipe3.setScale({ 0.75f,0.75f });
		Sprite Upperpipe4(upperpipeTexture);
		Upperpipe4.setPosition({ 650.f,0.f });
		Upperpipe4.setScale({ 0.75f,0.75f });
		Sprite Bottompipe4(bottompipeTexture);
		Bottompipe4.setPosition({ 350.f, 250.f });
		Bottompipe4.setScale({ 0.75f,0.75f });


		if (pause) {
			Background.move({ -SPEED * deltaTime, 0.f });
			Background2.move({ -SPEED * deltaTime, 0.f });
			Upperpipe.move({ -SPEED * deltaTime, 0.f });
			Bottompipe.move({ -SPEED * deltaTime, 0.f });

			Upperpipe2.move({ -SPEED * deltaTime, 0.f });
			Bottompipe2.move({ -SPEED * deltaTime, 0.f });

			Upperpipe3.move({ -SPEED * deltaTime, 0.f });
			Bottompipe3.move({ -SPEED * deltaTime, 0.f });

			Upperpipe4.move({ -SPEED * deltaTime, 0.f });
			Bottompipe4.move({ -SPEED * deltaTime, 0.f });
			bird.move({ 0.f,velocity * deltaTime });
		velocity += GRAVITY * deltaTime;
		}
		FloatRect very_eww = getBirdHitbox(Bottompipe);
		if (getBirdHitbox(bird).findIntersection(very_eww).has_value()) {
			pause = false;
			bird.setPosition({ 75.f, 250.f });
			velocity = 0.f;
			Upperpipe.setPosition({ 650.f, 0.f });
			Bottompipe.setPosition({ 350.f, 250.f });
		}
		FloatRect eww = getBirdHitbox(Upperpipe);
		if (getBirdHitbox(bird).findIntersection(eww).has_value()) {
			pause = false;
			bird.setPosition({ 75.f, 250.f });
			velocity = 0.f;
			Upperpipe.setPosition({ 650.f, 0.f });
			Bottompipe.setPosition({ 350.f, 250.f });
			window.draw(objs);
		}if (bird.getPosition().y > 650) {
			pause = false;
			bird.setPosition({ 75.f, 250.f });
			velocity = 0.f;
			Upperpipe.setPosition({ 650.f, 0.f });
			Bottompipe.setPosition({ 350.f, 250.f });
			window.draw(objs);
		}if (bird.getPosition().y < -50) {
			pause = false;
			bird.setPosition({ 75.f, 250.f });
			velocity = 0.f;
			Upperpipe.setPosition({ 650.f, 0.f });
			Bottompipe.setPosition({ 350.f, 250.f });
			window.draw(objs);
		}

		if (Upperpipe.getPosition().x <= -250) {
			Upperpipe.setPosition({ Upperpipe2.getPosition().x + 200.f, -100.f });
		}
		if (Bottompipe.getPosition().x <= -250) {
			Bottompipe.setPosition({ Bottompipe2.getPosition().x + 200.f, 450.f });
		}

		if (Upperpipe2.getPosition().x <= -250) {
			Upperpipe2.setPosition({ Upperpipe.getPosition().x + 200.f, 0.f });
		}
		if (Bottompipe2.getPosition().x <= -250) {
			Bottompipe2.setPosition({ Bottompipe.getPosition().x + 200.f, 380.f });
		}

		

		window.clear();
		window.draw(Background2);
		window.draw(Background);
		window.draw(bird);
		window.draw(Bottompipe);
		window.draw(Upperpipe);
		if (pause == false) {
			window.draw(objs);
			window.draw(restart);
		}

		window.display();
	}
}