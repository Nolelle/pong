#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
  window.setFramerateLimit(60);

  sf::RectangleShape leftPaddle(sf::Vector2f(25, 100));
  sf::RectangleShape rightPaddle(sf::Vector2f(25, 100));
  leftPaddle.setFillColor(sf::Color::White);
  rightPaddle.setFillColor(sf::Color::White);
  leftPaddle.setPosition(50, 250);
  rightPaddle.setPosition(700, 250);
  float paddleLeftSy = 5.0f;
  float paddleRightSy = 5.0f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up) {
        leftPaddle.move(0, -paddleLeftSy);
      }
      if (event.key.code == sf::Keyboard::Down) {
        leftPaddle.move(0, paddleLeftSy);
      }

      if (event.key.code == sf::Keyboard::W) {
        rightPaddle.move(0, -paddleRightSy);
      }

      if (event.key.code == sf::Keyboard::S) {
        rightPaddle.move(0, paddleRightSy);
      }
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
    window.display();
  }

  return 0;
}
