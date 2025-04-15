#pragma once
#include <SDL2/SDL.h>
#include "Vector2D.hpp"

enum class PowerUpType {
    NITRO_BOOST,
    SHIELD,
    SPEED_BURST,
    JUMP_BOOST,
    MISSILE,
    OIL_SLICK
};

class PowerUp {
public:
    PowerUp(PowerUpType type, const Vector2D& position);
    ~PowerUp();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    bool IsCollected() const { return collected; }
    void Collect() { collected = true; }
    
    PowerUpType GetType() const { return type; }
    Vector2D GetPosition() const { return position; }
    SDL_Rect GetCollisionBox() const;

    // Power-up effects
    void ApplyEffect(class Bike* bike);
    void RemoveEffect(class Bike* bike);
    bool IsEffectActive() const { return effectActive; }
    float GetRemainingDuration() const { return remainingDuration; }

private:
    PowerUpType type;
    Vector2D position;
    bool collected;
    bool effectActive;
    float remainingDuration;
    float rotationAngle;
    
    // Animation
    void UpdateAnimation(float deltaTime);
    SDL_Texture* texture;
    float bobHeight;
    float bobSpeed;
    float baseY;
    
    // Effect properties
    const float NITRO_BOOST_DURATION = 3.0f;
    const float SHIELD_DURATION = 5.0f;
    const float SPEED_BURST_DURATION = 2.0f;
    const float JUMP_BOOST_POWER = 15.0f;
    const float OIL_SLICK_DURATION = 4.0f;
};
