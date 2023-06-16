#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

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
  sf::Vector2f ballVelocity(2.0f, 2.0f);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Paddle Input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      leftPaddle.move(0, -paddleLeftSy);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      leftPaddle.move(0, paddleLeftSy);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      rightPaddle.move(0, -paddleRightSy);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      rightPaddle.move(0, paddleRightSy);
    }

    // Paddle Collision Detection
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

    // ball movement
    ball.move(ballVelocity.x, ballVelocity.y);

    // ball collision detection
    // Circleshape origin is at top left of circle (0,0)
    if (ball.getPosition().x < 0 ||
        ball.getPosition().x + (2 * ball.getRadius()) > window.getSize().x) {
      ballVelocity.x *= -1;
    }
    if (ball.getPosition().y < 0 ||
        ball.getPosition().y + (2 * ball.getRadius()) > window.getSize().y) {
      ballVelocity.y *= -1;
    }

    // Ball to paddle collision detection

    if (ball.getPosition().x <
            leftPaddle.getPosition().x + leftPaddle.getSize().x ||
        ball.getPosition().x + (2 * ball.getRadius()) >
            rightPaddle.getPosition().x) {
      ballVelocity.x *= -1;
    }

    if (ball.getPosition().y + (2 * ball.getRadius()) >
            leftPaddle.getPosition().y ||
        ball.getPosition().y + (2 * ball.getRadius()) >
            rightPaddle.getPosition().y) {
      ballVelocity.y *= -1;
    }

    // To do: Scoring System and Menus, Ball is not smooth when moving in x
    // direction

    window.clear();
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
    window.display();
  }
  return 0;
}
