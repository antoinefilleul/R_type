// #include "../include/App.hpp" // Include the header file for the App class
#include "../include/ECS/Coordinator.hpp" 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../include/ECS/System.hpp"
Coordinator gCoordinator;

class PhysicsSystem : public System
{
	public:
	void Update(float dt) override {
		std::cout << "PhysicsSystem" << std::endl;
		for (auto const& entity : mEntities)
	    {
		    auto& Position = gCoordinator.GetComponent<PositionComponent>(entity);
		    auto& Speed = gCoordinator.GetComponent<SpeedComponent>(entity);
            Position.pos.x += Speed.Speed.x * dt;
            Position.pos.y += Speed.Speed.y * dt;
			std::cout << Position.pos.x << std::endl;
			std::cout << Position.pos.y << std::endl;
			std::cout << dt << std::endl;
	    }
    }
};

class CollisionSystem : public System
{
	public:
    void Update(float dt) override {
		std::cout << "CollisionSystem" << std::endl;
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
		for (auto const& entity : mEntities) {
		    auto& fight = gCoordinator.GetComponent<FightComponent>(entity);
			if (fight.hp <= 0) {
				gCoordinator.DestroyEntity(entity);
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
			std::cout << "DisplaySystem" << std::endl;
			std::cout << Position.pos.x << std::endl;
			std::cout << Position.pos.y << std::endl;
			display.graphic->drawSprite(display.sprite);
		}
	}
};

class InputSystem : public System
{
	public:
	InputSystem(Graphic& graphic) : graphic(graphic) {}
	void Update(float dt) override {
		std::cout << "InputSystem" << std::endl;
		for (auto const& entity : mEntities) {
			std::cout << "test" << std::endl;
		    auto& input = gCoordinator.GetComponent<InputComponent>(entity);
			auto& display = gCoordinator.GetComponent<DisplayComponent>(entity);
			input.direction = display.graphic->getDirection();
			if (input.direction == sf::Keyboard::Left) {
				auto& speed = gCoordinator.GetComponent<SpeedComponent>(entity);
				speed.Speed.x = -500;
				speed.Speed.y = 0;
			}
			if (input.direction == sf::Keyboard::Right) {
				auto& speed = gCoordinator.GetComponent<SpeedComponent>(entity);
				speed.Speed.x = 500;
				speed.Speed.y = 0;
			}
			if (input.direction == sf::Keyboard::Up) {
				auto& speed = gCoordinator.GetComponent<SpeedComponent>(entity);
				speed.Speed.x = 0;
				speed.Speed.y = -500;
			}
			if (input.direction == sf::Keyboard::Down) {
				auto& speed = gCoordinator.GetComponent<SpeedComponent>(entity);
				speed.Speed.x = 0;
				speed.Speed.y = 500;
			}
			if (input.direction == sf::Keyboard::Space) {
			
			}
			std::cout << input.direction << std::endl;
		}
	}
	private:
	Graphic& graphic;
	void createProjectile(Entity playerEntity) {
		auto& playerPosition = gCoordinator.GetComponent<PositionComponent>(playerEntity);
		Entity projectile = gCoordinator.CreateEntity();
		PositionComponent position = {playerPosition.pos};
		SpeedComponent speed = {sf::Vector2<int>(0, -500)};
		FightComponent fight = {1, 10, 0, sf::Clock()};
		sf::Clock animationClock;
		sf::Texture texture;

	}
};

class AnimationSystem : public System
{
	public:
	void Update(float dt) override {
		for (auto const& entity : mEntities) {
		    auto& display = gCoordinator.GetComponent<DisplayComponent>(entity);
			if (display.animationClock.getElapsedTime().asSeconds() >= 0.1f) {
		    	display.animationClock.restart();
		    	if (display.spriteIndex >= display.animation) {
		        	display.spriteIndex = 0;
			
				}
		    	display.spriteIndex++;
		    	if (display.spriteIndex >= display.animation) {
		        	display.spriteIndex = 0;
		    	}
			}
			updateSprite(display);
		}
	}
	private:
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
	gCoordinator.RegisterComponent<InputComponent>();

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
	
	auto inputSystem = gCoordinator.RegisterSystem<InputSystem>();
	Signature signature5;
	signature5.set(gCoordinator.GetComponentType<DisplayComponent>());
	signature5.set(gCoordinator.GetComponentType<InputComponent>());
	signature5.set(gCoordinator.GetComponentType<SpeedComponent>());
	signature5.set(gCoordinator.GetComponentType<PositionComponent>());
	gCoordinator.SetSystemSignature<InputSystem>(signature5);

	Entity player = gCoordinator.CreateEntity();
	PositionComponent position = {sf::Vector2<int>(0, 0)};
	SpeedComponent speed = {sf::Vector2<int>(1000, 1000)};
	sf::Clock animationClock;
	sf::Texture texture;
	graphic.loadTexture("../assets/pigeot.png", texture);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	sprite.setTextureRect(sf::IntRect(0, 0, 110, 110));
	DisplayComponent display = {animationClock, &graphic, 4, 0, texture, sprite, sf::Vector2i(110, 110)};
	FightComponent fight = {100, 10, 1, sf::Clock()};
	InputComponent input = {sf::Keyboard::Key::Left};
	gCoordinator.AddComponents(player, position, speed, display, fight, input);
	while (graphic.isWindowOpen()) {
		graphic.pollEvents();
		sf::Time elapsed = clock.restart();
		inputSystem->Update(elapsed.asSeconds());
		physicsSystem->Update(elapsed.asSeconds());
		collisionSystem->Update(elapsed.asSeconds());
		animationSystem->Update(elapsed.asSeconds());
		graphic.clearWindow();
		displaySystem->Update(elapsed.asSeconds());
		graphic.pollEvents();
		graphic.displayWindow();
	}
    return 0;
}