#ifndef _rcRaycasting
#define _rcRaycasting
#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include <iostream>
namespace rc {
	struct Ray {
		sf::VertexArray vertexArray;

		Ray() {
			vertexArray = sf::VertexArray(sf::Lines, 2);
		}
	};
	class Raycasting {
		Ray rays[RayCounter];

		sf::Vector2f& observerPosition;
		float& observerRotation;

		float lenghts[RayCounter] = { 0 };
	public:
		Raycasting(sf::Vector2f& observerPosition, float& observerRotation) : observerPosition(observerPosition), observerRotation(observerRotation) {
		
		}

		void cast();
		void draw2d(sf::RenderWindow& app);

		void draw3d(sf::RenderWindow& app);

		static sf::Vector2f calculateJump(float& radAngle);
		static sf::Vector2f SetRayOnBorder(sf::Vector2f& currentRay, sf::Vector2f& previousRay, sf::Vector2f mapIndex);
		static sf::Vector2f findIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2);
	};
}

#endif // !_rcRaycasting
