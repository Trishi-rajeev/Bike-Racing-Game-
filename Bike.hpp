#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Vector2D.hpp"

enum class BikeType {
    SPEED,
    ALL_ROUNDER,
    OFF_ROAD
};

class Bike {
public:
    Bike(BikeType type, const std::string& name);
    ~Bike();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void HandleInput(const Uint8* keystate);
    void ApplyForce(const Vector2D& force);
    void UsePowerUp();
    
    // Getters
    Vector2D GetPosition() const { return position; }
    Vector2D GetVelocity() const { return velocity; }
    float GetRotation() const { return rotation; }
    bool HasPowerUp() const { return hasPowerUp; }
    
    // Setters
    void SetPosition(const Vector2D& pos) { position = pos; }
    void SetVelocity(const Vector2D& vel) { velocity = vel; }
    void SetRotation(float rot) { rotation = rot; }

private:
    BikeType type;
    std::string name;
    Vector2D position;
    Vector2D velocity;
    float rotation;
    float acceleration;
    float maxSpeed;
    float handling;
    float grip;
    bool hasPowerUp;
    
    // Bike characteristics based on type
    void InitializeBikeStats();
    
    // Physics
    void ApplyPhysics(float deltaTime);
    void HandleCollisions();
    
    // Bike state
    bool isGrounded;
    bool isStunned;
    float stunDuration;
    float health;
    int currentLap;
    int checkpointsPassed;
    
    // Power-up effects
    bool hasShield;
    bool hasNitro;
    float nitroFuel;
    float powerUpDuration;
    
    // Physics properties
    float mass;
    float wheelBase;
    float suspensionTravel;
    float suspensionStiffness;
    float damping;
    float engineForce;
    float brakeForce;
    
    // Constants
    const float GRAVITY = 9.81f;
    const float DRAG_COEFFICIENT = 0.3f;
    const float MAX_HEALTH = 100.0f;
    const float MAX_NITRO = 100.0f;
    const float NITRO_CONSUMPTION_RATE = 25.0f;
    const float STUN_RECOVERY_RATE = 1.0f;
    const float HEALTH_RECOVERY_RATE = 5.0f;
    
    // Particle system
    void EmitParticles(const std::string& type);
    void UpdateParticles(float deltaTime);
    
    // Sound effects
    void PlayEngineSound();
    void PlayCollisionSound();
    void PlayPowerUpSound();
};
