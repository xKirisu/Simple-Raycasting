#include "Observer.hpp"

void rc::Observer::take_event(sf::Event& e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::W) moveUp = true;
		if (e.key.code == sf::Keyboard::S) moveDown = true;
		if (e.key.code == sf::Keyboard::A) moveLeft = true;
		if (e.key.code == sf::Keyboard::D) moveRight = true;
		if (e.key.code == sf::Keyboard::Q) rotateLeft = true;
		if (e.key.code == sf::Keyboard::E) rotateRight = true;

	}
	if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W) moveUp = false;
		if (e.key.code == sf::Keyboard::S) moveDown = false;
		if (e.key.code == sf::Keyboard::A) moveLeft = false;
		if (e.key.code == sf::Keyboard::D) moveRight = false;
		if (e.key.code == sf::Keyboard::Q) rotateLeft = false;
		if (e.key.code == sf::Keyboard::E) rotateRight = false;
	}

}
void rc::Observer::update(float& tickrate) {
	if (moveUp) {
		shape.move(
			moveSpeed * tickrate * std::cos(radianAngle),
			moveSpeed * tickrate * std::sin(radianAngle)
		);
	}
	if (moveDown) {
		shape.move(
			-moveSpeed * tickrate * std::cos(radianAngle),
			-moveSpeed * tickrate * std::sin(radianAngle)
		);
	}
	if (moveLeft) {
		float radLeft = radianAngle - PI / 2;
		shape.move(
			moveSpeed * tickrate * std::cos(radLeft),
			moveSpeed * tickrate * std::sin(radLeft)
		);
	}
	if (moveRight) {
		float radRight = radianAngle + PI / 2;
		shape.move(
			moveSpeed * tickrate * std::cos(radRight),
			moveSpeed * tickrate * std::sin(radRight)
		);
	}
	if (rotateLeft) {
		radianAngle -= rotateSpeed;
	}
	if (rotateRight) {
		radianAngle += rotateSpeed;
	}
	
	position = shape.getPosition() + sf::Vector2f(12, 12);
}
void rc::Observer::draw(sf::RenderWindow& app) {
	app.draw(shape);
}

sf::Vector2f& rc::Observer::getPosition()
{
	return position;
}

float& rc::Observer::getRotation()
{
	return radianAngle;
}