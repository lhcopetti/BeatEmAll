#include "SFMLDebugDraw.h"

#include "DebugBoxDraw\WorldConstants.h"

SFMLDebugDraw::SFMLDebugDraw()
{
//	_window = &window;
}

SFMLDebugDraw::~SFMLDebugDraw()
{

}

/* convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range) */
sf::Color SFMLDebugDraw::boxToSfColor(const b2Color &color, sf::Uint8 alpha)
{
	sf::Uint8 r = color.r * 255;
	sf::Uint8 g = color.g * 255;
	sf::Uint8 b = color.b * 255;
	return sf::Color(r, g, b, alpha);
}


void SFMLDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	sf::Vector2f center;

	for (int i = 0; i < vertexCount; ++i)
	{
		sf::Vector2f transformVec = WorldConstants::physicsToSFML(vertices[i]);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformVec.x), std::floor(transformVec.y)));
	}
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(SFMLDebugDraw::boxToSfColor(color));

	_window->draw(polygon);
}

void SFMLDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);

	for (int i = 0; i < vertexCount; ++i)
	{
		b2Vec2 vec = vertices[i];
		if (vec.Length() > 0)
			polygon.setPoint(i, WorldConstants::physicsToSFML(vec));
	}

	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(SFMLDebugDraw::boxToSfColor(color, 60));
	polygon.setOutlineColor(SFMLDebugDraw::boxToSfColor(color));
	_window->draw(polygon);
}

void SFMLDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius * WorldConstants::SCALE);

	circle.setOrigin(radius * WorldConstants::SCALE, radius * WorldConstants::SCALE);
	circle.setPosition(WorldConstants::physicsToSFML(center));

	circle.setFillColor(SFMLDebugDraw::boxToSfColor(color, 60));
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(SFMLDebugDraw::boxToSfColor(color));

	_window->draw(circle);
}

void SFMLDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius * WorldConstants::SCALE);
	circle.setOrigin(radius * WorldConstants::SCALE, radius * WorldConstants::SCALE);
	circle.setPosition(WorldConstants::physicsToSFML(center));

	circle.setFillColor(SFMLDebugDraw::boxToSfColor(color, 60));
	circle.setOutlineThickness(-1.f);
	circle.setOutlineColor(SFMLDebugDraw::boxToSfColor(color));

	b2Vec2 endPoint = center + radius * axis;
	sf::Vertex line[2] =
	{
		sf::Vertex(WorldConstants::physicsToSFML(center), SFMLDebugDraw::boxToSfColor(color)),
		sf::Vertex(WorldConstants::physicsToSFML(endPoint), SFMLDebugDraw::boxToSfColor(color))
	};


	_window->draw(circle);
	_window->draw(line, 2, sf::Lines);
}

void SFMLDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex lines[] = 
	{
		sf::Vertex(WorldConstants::physicsToSFML(p1), SFMLDebugDraw::boxToSfColor(color)),
		sf::Vertex(WorldConstants::physicsToSFML(p2), SFMLDebugDraw::boxToSfColor(color))
	};

	_window->draw(lines, 2, sf::Lines);
}

void SFMLDebugDraw::DrawTransform(const b2Transform& xf)
{
	float lineLength = 0.4;

	/*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
	b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
	sf::Vertex redLine[] =
	{
		sf::Vertex(WorldConstants::physicsToSFML(xf.p), sf::Color::Red),
		sf::Vertex(WorldConstants::physicsToSFML(xAxis), sf::Color::Red)
	};

	// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
	// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
	/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
	b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
	sf::Vertex greenLine[] =
	{
		sf::Vertex(WorldConstants::physicsToSFML(xf.p), sf::Color::Green),
		sf::Vertex(WorldConstants::physicsToSFML(yAxis), sf::Color::Green)
	};

	_window->draw(redLine, 2, sf::Lines);
	_window->draw(greenLine, 2, sf::Lines);
}