#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

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

  sf::CircleShape ball(50.f);
  ball.setFillColor(sf::Color::White);
  ball.setPosition(375, 250);
  float ballSx = 2.0f;
  float ballSy = 2.0f;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
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

    window.clear();
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
    window.display();
  }
  return 0;
}
