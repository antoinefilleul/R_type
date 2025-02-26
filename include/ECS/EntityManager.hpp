#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <queue>
#include <array>
#include "IComponent.hpp"
#include "ComponentManager.hpp"
#include "../graphic/graphic.hpp"
using ComponentType = uint8_t;
struct PositionComponent {
    sf::Vector2<int> pos;
};

struct SpeedComponent {
    sf::Vector2<int> Speed;
};

struct InputComponent {
    sf::Keyboard::Key direction;
};

struct FightComponent {
    int hp;
    int damage;
    int player;
    sf::Clock lastHitClock;
};

struct DisplayComponent {
	sf::Clock animationClock;
	Graphic *graphic;
    int animation;
    int spriteIndex;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i frameSize;
};

using Entity = uint32_t;
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
	EntityManager()
	{
		// Initialize the queue with all possible entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		mSignatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		mSignatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return mSignatures[entity];
	}

private:
	// Queue of unused entity IDs
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t mLivingEntityCount{};
};