#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool server = false;

const Keyboard::Key controls[4] = {

	Keyboard::A,
	Keyboard::Z,
	Keyboard::Up,
	Keyboard::Down

};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
bool AIActive = true;
bool gameActive = false;
Font font;
Text text;
Text score;
int p1Score = 0;
int p2Score = 0;
Color darkblue(73, 109, 140);
Color lightgrey(199, 207, 217);
Color darkgrey(134, 154, 166);
Color lightblue(101, 136, 166);	
CircleShape ball;
RectangleShape paddles[2];

const float paddleDist = 10.f + paddleSize.x;

void Reset() {

	gameActive = false;

	// Update Score Text
	text.setString(std::to_string(p1Score) + " : " + std::to_string(p2Score));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

	score.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

	// Set Size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
		p.setFillColor(darkblue);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	ball.setFillColor(lightblue);
	//reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	ball.setPosition(gameWidth / 2, gameHeight / 2);

	cout << "paddle 1 pos: " << std::to_string(paddles[0].getPosition().x);
	cout << "paddle 1 pos: " << std::to_string(paddles[1].getPosition().x);
}

void Load() {
	
	/// Load font-face from res dir
	font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Fonts/mandalore.ttf");
	// Set text element to use font
	text.setFont(font);
	score.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(100);
	score.setCharacterSize(300);

	text.setColor(darkgrey);
	score.setColor(darkgrey);
	score.set
	score.setString("SCORE!");
	score.setPosition(gameWidth / 2, gameHeight / 2);
	
	Reset();

}

void Update(RenderWindow &window) {
	if (gameActive == false)
	{
		if (
			Keyboard::isKeyPressed(controls[0]) ||
			Keyboard::isKeyPressed(controls[1]) ||
			Keyboard::isKeyPressed(controls[2]) ||
			Keyboard::isKeyPressed(controls[3]))
		{
			gameActive = true;
		}
	}
	else if (gameActive == true)
	{

		// Reset clock, recalculate deltatime
		static Clock clock;
		float dt = clock.restart().asSeconds();
		//check and consume events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return;
			}
		}

		//quit via esc
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		//ball movement
		ball.move(ballVelocity * dt);

		//handle paddle movement
		float direction = 0.0f;
		if (Keyboard::isKeyPressed(controls[0])) {
			direction--;
		}
		if (Keyboard::isKeyPressed(controls[1])) {
			direction++;
		}
		paddles[0].move(0, direction * paddleSpeed * dt);

		if (AIActive == true)
		{
			if (Keyboard::isKeyPressed(controls[2])) {
				AIActive = false;
			}
			if (Keyboard::isKeyPressed(controls[3])) {
				AIActive = false;
			}
		}

		if (AIActive == true)
		{
			if (ball.getPosition().y > paddles[1].getPosition().y)
			{
				paddles[1].move(0, 1.0f * paddleSpeed * dt);
			}
			else
			{
				paddles[1].move(0, -1.0f * paddleSpeed * dt);
			}
		}
		else
		{
			//paddle 2 movement
			float direction2 = 0.0f;
			if (Keyboard::isKeyPressed(controls[2])) {
				direction2--;
			}
			if (Keyboard::isKeyPressed(controls[3])) {
				direction2++;
			}
			paddles[1].move(0, direction2 * paddleSpeed * dt);
		}

		//paddle collision in bounds
		if (paddles[0].getPosition().y > gameHeight - (paddleSize.y / 2))
		{
			paddles[0].setPosition(10 + (paddleSize.x / 2), gameHeight - (paddleSize.y / 2));
		}
		else if (paddles[0].getPosition().y < 0 + (paddleSize.y / 2))
		{
			paddles[0].setPosition(10 + (paddleSize.x / 2), 0 + (paddleSize.y / 2));
		}

		if (paddles[1].getPosition().y > gameHeight - (paddleSize.y / 2))
		{
			paddles[1].setPosition(paddles[1].getPosition().x, gameHeight - (paddleSize.y / 2));
		}
		else if (paddles[1].getPosition().y < 0 + (paddleSize.y / 2))
		{
			paddles[1].setPosition(paddles[1].getPosition().x, 0 + (paddleSize.y / 2));
		}

		//check ball collision
		const float bx = ball.getPosition().x;
		const float by = ball.getPosition().y;
		if (by > gameHeight - ballRadius) {
			//bottom wall
			ballVelocity.x *= 1.1f;
			ballVelocity.y *= -1.1f;
			ball.move(0, -ballRadius / 2);
		}
		else if (by < 0 + ballRadius) {
			//top wall
			ballVelocity.x *= 1.1f;
			ballVelocity.y *= -1.1f;
			ball.move(0, ballRadius / 2);
		}
		else if (bx > gameWidth) {
			//right wall
			p1Score++;
			Reset();
		}
		else if (bx < 0) {
			//left wall
			p2Score++;
			Reset();
		}
		else if (
			//ball is inline or behind paddle
			bx < paddleDist &&
			//AND ball is below top edge of paddle
			by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
			//AND ball is above bottom edge of paddle
			by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
			) {
			// bounce off left paddle

			cout << "collision at " << std::to_string(ball.getPosition().x);
			ball.move(ballRadius / 2, 0);
			ballVelocity.x *= -1.1f;
			ballVelocity.y *= 1.1f;
		}
		else if (
			//ball is inline or behind paddle
			bx > gameWidth - 10 - paddleDist &&
			//AND ball is below top edge of paddle
			by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
			//AND ball is above bottom edge of paddle
			by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
			) {
			// bounce off right paddle
			cout << "collision at " << std::to_string(ball.getPosition().x);
			ball.move(-ballRadius / 2, 0);
			ballVelocity.x *= -1.1f;
			ballVelocity.y *= 1.1f;
		}
	}
}

void Render(RenderWindow& window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
	window.draw(score);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear(lightgrey);
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}