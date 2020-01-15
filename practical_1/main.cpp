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
Font font;
Text text;
int p1Score = 0;
int p2Score = 0;

CircleShape ball;
RectangleShape paddles[2];

void Reset() {

	// Update Score Text
	text.setString(p1Score + " : " + p2Score);
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

	// Set Size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	//reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	ball.setPosition(gameWidth / 2, gameHeight / 2);
}

void Load() {
	
	/// Load font-face from res dir
	font.loadFromFile("res/Fonts/mandalore.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
	
	Reset();

}

void Update(RenderWindow &window) {
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
		paddles[1].setPosition(gameWidth - 10 - (paddleSize.x / 2), gameHeight - (paddleSize.y / 2));
	}
	else if (paddles[1].getPosition().y < 0 + (paddleSize.y / 2))
	{
		paddles[1].setPosition(gameWidth - 10 - (paddleSize.x / 2), 0 + (paddleSize.y / 2));
	}

	//check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
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
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// bounce off left paddle
		ball.move(10, 0);
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	}
	else if (
		//ball is inline or behind paddle
		bx > gameWidth - paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		)  {
		// bounce off right paddle
		ball.move(-10, 0);
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	}

}

void Render(RenderWindow& window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}