#include "Raycasting.hpp"


void rc::Raycasting::cast() {
    float rayAngle = observerRotation - HalfFOV;
    for (Ray& ray : rays) {
        ray.vertexArray[0].color = sf::Color::Red;
        ray.vertexArray[1].color = sf::Color::Red;
        ray.vertexArray[0].position = observerPosition;
        ray.vertexArray[1].position = ray.vertexArray[0].position;

        sf::Vector2f rayjump = calculateJump(rayAngle);

        for (short jumpI = 0; jumpI < RayJumps; jumpI++) {
            sf::Vector2f prevray = ray.vertexArray[1].position;
            ray.vertexArray[1].position += rayjump;
            short x = static_cast<short>(ray.vertexArray[1].position.x) / BlockSize;
            short y = static_cast<short>(ray.vertexArray[1].position.y) / BlockSize;
            if ((x >= 0 && y >= 0) && WorldMap[y][x] == 1) {
                ray.vertexArray[1].position = SetRayOnBorder(ray.vertexArray[1].position, prevray, sf::Vector2f(x, y));
                break;
            }
        }
        rayAngle += DeltaRayRadAngle;
    }
}

void rc::Raycasting::draw2d(sf::RenderWindow& app) {
    for (Ray& ray : rays) {
        app.draw(ray.vertexArray);
    }
}
void rc::Raycasting::draw3d(sf::RenderWindow& app)
{
    for (short i = 0; i < RayCounter; i++) {
        sf::Vector2f start = rays[i].vertexArray[0].position;
        sf::Vector2f end = rays[i].vertexArray[1].position;

        float dx = end.x - start.x;
        float dy = end.y - start.y;
        float rayLength = std::hypot(dx, dy);

        float rayAngle = std::atan2(dy, dx);
        float observerAngle = observerRotation - rayAngle;

        float maxrl = MaxRayLenght;
        float height = WindowSizeY - (rayLength / maxrl) * WindowSizeY * std::cos(observerAngle);

        float xPosition = i * DrawWidth;
        float yPosition = WindowSizeY / 2 - height /2;

        if (rayLength < 123) {
            sf::RectangleShape rect(sf::Vector2f(DrawWidth,  height));
            sf::Uint8 color = 255 - (rayLength / maxrl) * 255;
            rect.setFillColor(sf::Color(color, color, color));
            rect.setPosition(xPosition, yPosition);
            app.draw(rect);

        }
    }
}
sf::Vector2f rc::Raycasting::calculateJump(float& radAngle)
{
	float x = StandardJump * std::cos(radAngle);
	float y = StandardJump * std::sin(radAngle);

	return sf::Vector2f(x, y);
}

sf::Vector2f rc::Raycasting::SetRayOnBorder(sf::Vector2f& currentRay, sf::Vector2f& previousRay, sf::Vector2f mapIndex)
{
    sf::Vector2f blockposition = sf::Vector2f(BlockSize * mapIndex.x, BlockSize * mapIndex.y);
    sf::Vector2f blocklines[4][2];

    // Top line
    blocklines[0][0] = blockposition;
    blocklines[0][1] = blockposition + sf::Vector2f(BlockSize, 0);

    // Left line
    blocklines[1][0] = blockposition;
    blocklines[1][1] = blockposition + sf::Vector2f(0, BlockSize);

    // Right line
    blocklines[2][0] = blockposition + sf::Vector2f(BlockSize, 0);
    blocklines[2][1] = blockposition + sf::Vector2f(BlockSize, BlockSize);

    // Bottom line
    blocklines[3][0] = blockposition + sf::Vector2f(0, BlockSize);
    blocklines[3][1] = blockposition + sf::Vector2f(BlockSize, BlockSize);

    sf::Vector2f result = currentRay;
    for (short i = 0; i < 4; i++) {
        sf::Vector2f intersection = findIntersection(previousRay, currentRay, blocklines[i][0], blocklines[i][1]);

        if (intersection != sf::Vector2f(-1, -1)) {
            result = intersection;
            break;
        }
    }

	return result;
}
sf::Vector2f rc::Raycasting::findIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2)
{
    float dx1 = p2.x - p1.x;
    float dy1 = p2.y - p1.y;
    float dx2 = q2.x - q1.x;
    float dy2 = q2.y - q1.y;

    float denom = dx1 * dy2 - dy1 * dx2;

    if (denom == 0) {
        return sf::Vector2f(-1, -1);
    }

    float t = ((q1.x - p1.x) * dy2 - (q1.y - p1.y) * dx2) / denom;
    float u = ((q1.x - p1.x) * dy1 - (q1.y - p1.y) * dx1) / denom;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        return sf::Vector2f(p1.x + t * dx1, p1.y + t * dy1);
    }

    return sf::Vector2f(-1, -1);
}