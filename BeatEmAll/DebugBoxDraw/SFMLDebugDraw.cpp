#include "SFMLDebugDraw.h"

#include "DebugBoxDraw\WorldConstants.h"

SFMLDebugDraw::SFMLDebugDraw()
{
//	_window = &window;
}

SFMLDebugDraw::~SFMLDebugDraw()
{

}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
//sf::Color SFMLDebugDraw::makeColor(, int alpha = 255)
//{
//	sf::Color result((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255), (sf::Uint8) alpha);
//	return result;
//}

void SFMLDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

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

	polygon.setFillColor(sf::Color(255, 0, 0));
	polygon.setOutlineColor(sf::Color(0, 255, 0));
	polygon.setOutlineThickness(1.0f);
	_window->draw(polygon);

	//sf::Shape polygon;
	//for (int32 i = 0; i<vertexCount; i++)
	//{
	//	b2Vec2 vertex = vertices[i];
	//	polygon.AddPoint(vertex.x*RATIO, vertex.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
	//}
	//polygon.SetOutlineWidth(1.0f);
	//this->window->Draw(polygon);
}

void SFMLDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}

void SFMLDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}

void SFMLDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}

void SFMLDebugDraw::DrawTransform(const b2Transform& xf)
{

}

//void SFMLDebugDraw::drawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
//{
//	sf::Shape polygon;
//	sf::Shape polygon2;
//	float p1x = p1.x * RATIO;
//	float p1y = p1.y * RATIO;
//	float p2x = p2.x * RATIO;
//	float p2y = p2.y * RATIO;
//	float size = 4.0f;
//
//	sf::Color boxClr = this->B2SFColor(boxColor);
//	sf::Color lineClr = this->B2SFColor(lineColor);
//
//	//first green box for the joint
//	polygon.AddPoint(p1x - size / 2, p1y - size / 2, boxClr);
//	polygon.AddPoint(p1x + size / 2, p1y - size / 2, boxClr);
//	polygon.AddPoint(p1x + size / 2, p1y + size / 2, boxClr);
//	polygon.AddPoint(p1x - size / 2, p1y + size / 2, boxClr);
//
//	//second green box for the joint
//	polygon2.AddPoint(p2x - size / 2, p2y - size / 2, boxClr);
//	polygon2.AddPoint(p2x + size / 2, p2y - size / 2, boxClr);
//	polygon2.AddPoint(p2x + size / 2, p2y + size / 2, boxClr);
//	polygon2.AddPoint(p2x - size / 2, p2y + size / 2, boxClr);
//
//	sf::Shape line = sf::Shape::Line(p1x, p1y, p2x, p2y, 1, lineClr);
//	line.EnableFill(true);
//
//	this->window->Draw(polygon);
//	this->window->Draw(polygon2);
//	this->window->Draw(line);
//}