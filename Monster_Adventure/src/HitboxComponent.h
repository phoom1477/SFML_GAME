#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>


class HitboxComponent
{
private:
	//Variable
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	//Constrictor , Destructor
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, sf::Color linecolor);
	virtual ~HitboxComponent();

	//Accessor
	const sf::Vector2f& getPosition();
	const sf::FloatRect getGlobalBounds();
	const sf::Vector2f getSize();

	//Modifier
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Function
	bool checkIntersect(const sf::FloatRect& frect);

	void updateComponent();
	void renderComponent(sf::RenderTarget& target);
};

