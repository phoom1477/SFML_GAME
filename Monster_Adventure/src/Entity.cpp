#include "Entity.h"

//Initialization
void Entity::initVariable()
{
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

//Constructor , Destructor
Entity::Entity()
{
	this->initVariable();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
    delete this->movementComponent;
	delete this->animationComponent;
}

//Component Function
void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(const float offset_x, const float offset_y, const float width, const float height, sf::Color line_color)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height, line_color);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration, const float jumpForce, const float gravity)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration, jumpForce, gravity);
}

void Entity::createSoundComponent()
{
	this->soundComponent = new SoundComponent();
}

//Accessor
sf::FloatRect Entity::getGlobalBounds()
{
	if (this->hitboxComponent) {
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Entity::getPosition()
{
	if (this->hitboxComponent) {
		return this->hitboxComponent->getPosition();
	}
	return this->sprite.getPosition();
}

//Function
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent) {
		this->hitboxComponent->setPosition(x, y);
	}
	else {
		this->sprite.setPosition(x, y);
	}
}

void Entity::moveEntity(float direction_x, float direction_y, const float &dt)
{
	if (this->movementComponent) {
		this->movementComponent->move(direction_x, direction_y, dt);
	}
}

void Entity::stopEntityX()
{
	if (this->movementComponent) {
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopEntityY()
{
	if (this->movementComponent) {
		this->movementComponent->stopVelocityY();
	}
}

void Entity::updateCollisionFrame(sf::RenderWindow& window, int num_window)
{
	if (this->getPosition().x < 0.0f) {
		this->setPosition(
			0.0f,
			this->getPosition().y
		);

		this->stopEntityX();
	}
	else if (this->getPosition().x + this->getGlobalBounds().width > window.getSize().x * num_window) {
		this->setPosition(
			window.getSize().x * num_window - this->getGlobalBounds().width,
			this->getPosition().y
		);

		this->stopEntityX();
	}
	if (this->getPosition().y < 0.0f) {
		this->setPosition(
			this->getPosition().x,
			0.0f
		);

		this->stopEntityY();
	}
	else if (this->getPosition().y + this->getGlobalBounds().height > window.getSize().y) {
		this->setPosition(
			this->getPosition().x,
			window.getSize().y - this->getGlobalBounds().height
		);

		this->stopEntityY();
	}
}



