// #include "../include/App.hpp" // Include the header file for the App class
#include "../include/ECS/Coordinator.hpp" 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include "../include/ECS/System.hpp"
Coordinator gCoordinator;

class PhysicsSystem : public System
{
	public:
	void Update(float dt) override {
	for (auto const& entity : mEntities)
	    {
		    auto& Position = gCoordinator.GetComponent<PositionComponent>(entity);
		    auto& Speed = gCoordinator.GetComponent<SpeedComponent>(entity);
            Position.pos.x += Speed.Speed.x * dt;
            Position.pos.y += Speed.Speed.y * dt;
	    }
    }
};

class CollisionSystem : public System
{
	public:
    void Update(float dt) override {
		for (auto const& entity : mEntities) {
		    auto& Position = gCoordinator.GetComponent<PositionComponent>(entity);
		    	auto& fight = gCoordinator.GetComponent<FightComponent>(entity);

			for (auto const& other_entity : mEntities) {
		    	auto& fight2 = gCoordinator.GetComponent<FightComponent>(other_entity);
		    	auto& other_Position = gCoordinator.GetComponent<PositionComponent>(other_entity);
            	if (&entity != &other_entity) {
					if (Position.pos == other_Position.pos) {
						if (fight.lastHitClock.getElapsedTime().asSeconds() >= 1.0f) {
							fight.hp -= fight2.damage;
							fight.lastHitClock.restart();
						}
						if (fight2.lastHitClock.getElapsedTime().asSeconds() >= 1.0f) {
							fight2.hp -= fight.damage;
							fight2.lastHitClock.restart();
						}
					}
				
				}
			}
	    }
    }
};

class DisplaySystem : public System
{
	public:
	void Update(float dt) override {
		for (auto const& entity : mEntities) {
		    auto& Position = gCoordinator.GetComponent<PositionComponent>(entity);
		    auto& display = gCoordinator.GetComponent<DisplayComponent>(entity);
			display.sprite.setTexture(display.texture);
		    display.sprite.setPosition(Position.pos.x, Position.pos.y);
			display.graphic->drawSprite(display.sprite);
		}
	}
};

class AnimationSystem : public System
{
	public:
	void Update(float dt) override {
		for (auto const& entity : mEntities) {
		    auto& display = gCoordinator.GetComponent<DisplayComponent>(entity);
		    display.spriteIndex++;
		    if (display.spriteIndex >= display.animation) {
		        display.spriteIndex = 0;
		    }
		    updateSprite(display);
		}
	}
	void updateSprite(DisplayComponent& display) {
		int left = display.spriteIndex * display.frameSize.x;
		display.sprite.setTextureRect(sf::IntRect(left, 0, display.frameSize.x, display.frameSize.y));
	}
};

int main() {
    // App app;
    // app.run();
    gCoordinator.Init();
    gCoordinator.RegisterComponent<PositionComponent>();
    gCoordinator.RegisterComponent<FightComponent>();
	gCoordinator.RegisterComponent<SpeedComponent>();
	gCoordinator.RegisterComponent<DisplayComponent>();

	auto physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();
	Signature signature;
	signature.set(gCoordinator.GetComponentType<PositionComponent>());
	signature.set(gCoordinator.GetComponentType<SpeedComponent>());
	gCoordinator.SetSystemSignature<PhysicsSystem>(signature);

	Graphic graphic;
	graphic.createWindow(800, 600, "SFML window");

	sf::Clock clock;
	auto displaySystem = gCoordinator.RegisterSystem<DisplaySystem>();
	Signature signature2;
	signature2.set(gCoordinator.GetComponentType<PositionComponent>());
	signature2.set(gCoordinator.GetComponentType<DisplayComponent>());
	gCoordinator.SetSystemSignature<DisplaySystem>(signature2);

	auto collisionSystem = gCoordinator.RegisterSystem<CollisionSystem>();
	Signature signature3;
	signature3.set(gCoordinator.GetComponentType<PositionComponent>());
	signature3.set(gCoordinator.GetComponentType<FightComponent>());
	gCoordinator.SetSystemSignature<CollisionSystem>(signature3);

	auto animationSystem = gCoordinator.RegisterSystem<AnimationSystem>();
	Signature signature4;
	signature4.set(gCoordinator.GetComponentType<DisplayComponent>());
	gCoordinator.SetSystemSignature<AnimationSystem>(signature4);

	Entity player = gCoordinator.CreateEntity();
	PositionComponent position = {sf::Vector2<int>(0, 0)};
	SpeedComponent speed = {sf::Vector2<int>(1, 1)};
	sf::Texture texture;
	graphic.loadTexture("../assets/pigeot.png", texture);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	DisplayComponent display = {&graphic, 4, 0, texture, sprite, sf::Vector2i(100, 100)};
	FightComponent fight = {100, 10, 1, sf::Clock()};
	gCoordinator.AddComponents(player, position, speed, display, fight);
	while (graphic.isWindowOpen()) {
		graphic.pollEvents();
		sf::Time elapsed = clock.restart();
		physicsSystem->Update(elapsed.asSeconds());
		collisionSystem->Update(elapsed.asSeconds());
		animationSystem->Update(elapsed.asSeconds());
		graphic.clearWindow();
		displaySystem->Update(elapsed.asSeconds());
		graphic.displayWindow();
	}
    return 0;
}