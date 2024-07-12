#ifndef _RCObserver
#define _RCObserver
#include <SFML/Graphics.hpp>
#include "Settings.hpp"
namespace rc{
	class Observer {
	private:
		bool
			moveLeft = false,
			moveRight = false,
			moveUp = false,
			moveDown = false,
			rotateLeft = false,
			rotateRight = false;

		float moveSpeed = 150;
		float rotateSpeed = 0.015;

		sf::Vector2f position;
		sf::CircleShape shape;
	public:
		float radianAngle = 270 * PI / 180;

		Observer(sf::Vector2f startPosition = sf::Vector2f(0,0)) {
			shape.setRadius(BlockSize / 4);
			shape.setFillColor(sf::Color::Blue);
			shape.setPosition(startPosition);
		}
		void take_event(sf::Event& e);
		void update(float& tickrate);
		void draw(sf::RenderWindow& app);
		sf::Vector2f& getPosition();
		float& getRotation();
	};
}
#endif // !_Observer
