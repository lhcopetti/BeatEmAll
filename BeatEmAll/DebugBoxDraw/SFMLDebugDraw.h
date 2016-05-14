#pragma once

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

class SFMLDebugDraw : public b2Draw
{
private:
	/*
	* https://github.com/MrPlow442/Box2D-SFML2-Debug-Draw
	* https://github.com/slok/Box2D-and-SFML-demo
	* https://bitbucket.org/GuigasGit/highorderninja
	*/

	sf::RenderWindow* _window;

public:
	SFMLDebugDraw();
	virtual ~SFMLDebugDraw();

	void setRenderWindow(sf::RenderWindow& window) { _window = &window; };

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);

	/* Default alpha value: opaque */
	sf::Color boxToSfColor(const b2Color &color, sf::Uint8 alpha = 255);
};