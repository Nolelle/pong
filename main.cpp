#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <iostream>

// g++ -o pong main.cpp -lsfml-graphics -lsfml-window -lsfml-system ./sfml-test
// To do:
// Scoring System
// Menus
// Ball and Paddle Class

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
  window.setFramerateLimit(60);

  sf::RectangleShape leftPaddle(sf::Vector2f(25, 100));
  leftPaddle.setFillColor(sf::Color::White);
  leftPaddle.setPosition(50, 250);
  float paddleLeftSy = 5.0f;

  sf::RectangleShape rightPaddle(sf::Vector2f(25, 100));
  rightPaddle.setFillColor(sf::Color::White);
  rightPaddle.setPosition(725, 250);
  float paddleRightSy = 5.0f;

  sf::CircleShape ball(10);
  ball.setFillColor(sf::Color::White);
  ball.setPosition(375, 250);
  sf::Vector2f ballVelocity(200.0f, 200.0f);

  sf::FloatRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

  sf::Font font;

  if (!font.loadFromFile("Montserrat-Regular.otf")) {
    std::cout << "Error loading font\n";
  }

  int winningScore = 2;

  sf::Text score1Text;
  score1Text.setFont(font);
  score1Text.setCharacterSize(24);
  score1Text.setFillColor(sf::Color::White);
  int player1Score = 0;
  score1Text.setString(std::to_string(player1Score));
  score1Text.setPosition(200, 50);

  sf::Text score2Text;
  score2Text.setFont(font);
  score2Text.setCharacterSize(24);
  score2Text.setFillColor(sf::Color::White);
  int player2Score = 0;
  score2Text.setString(std::to_string(player2Score));
  score2Text.setPosition(window.getSize().x - 200, 50);

  bool gameOver = false;
  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(24);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setString("Game Over");
  gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2.0f,
                         gameOverText.getLocalBounds().height / 2.0f);
  gameOverText.setPosition(window.getSize().x / 2.0f,
                           window.getSize().y / 2.0f);

  sf::Event event;
  sf::Clock clock;
  bool isCollidingWithPaddle = false;

  while (window.isOpen()) {
    sf::Time dt = clock.restart();
    float dtAsSeconds = dt.asSeconds();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sf::FloatRect rightPaddleBounds = rightPaddle.getGlobalBounds();
    sf::FloatRect leftPaddleBounds = leftPaddle.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    // Paddle Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      leftPaddle.move(0, -paddleLeftSy);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      leftPaddle.move(0, paddleLeftSy);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      rightPaddle.move(0, -paddleRightSy);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      rightPaddle.move(0, paddleRightSy);
    }

    // Paddle to Top Window Collision Detection
    if (leftPaddle.getPosition().y < 0) {
      leftPaddle.setPosition(leftPaddle.getPosition().x, 0);
    }

    if (rightPaddle.getPosition().y < 0) {
      rightPaddle.setPosition(rightPaddle.getPosition().x, 0);
    }

    if (leftPaddle.getPosition().y >
        window.getSize().y - leftPaddle.getSize().y) {
      leftPaddle.setPosition(leftPaddle.getPosition().x,
                             window.getSize().y - rightPaddle.getSize().y);
    }

    if (rightPaddle.getPosition().y >
        window.getSize().y - rightPaddle.getSize().y) {
      rightPaddle.setPosition(rightPaddle.getPosition().x,
                              window.getSize().y - rightPaddle.getSize().y);
    }

    // Ball Movement
    ball.move(ballVelocity.x * dtAsSeconds, ballVelocity.y * dtAsSeconds);

    if (ball.getPosition().y < 0 ||
        ball.getPosition().y + (2 * ball.getRadius()) > window.getSize().y) {
      ballVelocity.y *= -1;
    }

    // Paddle  to Ball Collision Detection
    // ball is moving 200/60 = 3.33 pixles per frame the ball could be
    // intersecting the paddle more then in two frames, so we need to check if
    // the ball is colliding with the paddle
    if (ballBounds.intersects(leftPaddleBounds)) {
      if (!isCollidingWithPaddle) {
        ballVelocity.x *= -1;
        isCollidingWithPaddle = true;
      }
    } else if (ballBounds.intersects(rightPaddleBounds)) {
      if (!isCollidingWithPaddle) {
        ballVelocity.x *= -1;
        isCollidingWithPaddle = true;
      }
    } else {
      isCollidingWithPaddle = false;
    }

    if (player1Score == winningScore || player2Score == winningScore) {
      gameOver = true;
    }

    if (ball.getPosition().x < 0) {
      player2Score++;
      score2Text.setString(std::to_string(player2Score));
      if (!gameOver) {
        ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        leftPaddle.setPosition(50, 250);
        rightPaddle.setPosition(725, 250);
      }
    }

    if (ball.getPosition().x + (2 * ball.getRadius()) > window.getSize().x) {
      player1Score++;
      score1Text.setString(std::to_string(player1Score));
      if (!gameOver) {
        ball.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        leftPaddle.setPosition(50, 250);
        rightPaddle.setPosition(725, 250);
      }
    }

    if (gameOver) {
      window.clear();
      window.draw(gameOverText);
    } else {
      window.clear();
      window.draw(leftPaddle);
      window.draw(rightPaddle);
      window.draw(ball);
      window.draw(score1Text);
      window.draw(score2Text);
    }

    window.display();
  }
  return 0;
}
