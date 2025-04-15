#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Vector2D.hpp"

enum class TerrainType {
    ASPHALT,
    DIRT,
    GRASS,
    SAND,
    ICE,
    MUD,
    WATER,
    GRAVEL,
    SNOW
};

enum class WeatherEffect {
    CLEAR,
    RAIN,
    SNOW,
    FOG,
    STORM
};

struct Obstacle {
    Vector2D position;
    float rotation;
    SDL_Rect bounds;
    bool destructible;
    float health;
    std::string type;
};

struct TrackSegment {
    std::vector<Vector2D> points;
    TerrainType terrain;
    float friction;
};

class Track {
public:
    Track(const std::string& trackName);
    ~Track();

    void Load(const std::string& filename);
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(const SDL_Rect& bikeRect) const;
    TerrainType GetTerrainAt(const Vector2D& position) const;
    float GetFrictionAt(const Vector2D& position) const;
    
    // Checkpoints and race progress
    bool IsCheckpointReached(int checkpointIndex, const SDL_Rect& bikeRect) const;
    float GetProgress(const Vector2D& position) const;
    Vector2D GetStartPosition(int playerIndex) const;

private:
    std::string name;
    std::vector<TrackSegment> segments;
    std::vector<SDL_Rect> checkpoints;
    SDL_Texture* trackTexture;
    SDL_Texture* backgroundTexture;
    
    // Track properties
    int trackWidth;
    int trackLength;
    std::vector<Vector2D> startPositions;
    
    // Track generation
    void GenerateCollisionMap();
    void GenerateCheckpoints();
    
    // Weather and environment
    WeatherEffect currentWeather;
    float weatherIntensity;
    float timeOfDay; // 0.0 to 24.0
    bool isDynamic; // Whether weather/time changes during race
    
    void UpdateWeather(float deltaTime);
    void UpdateLighting();
    void ApplyWeatherEffects();
    
    // Obstacles and hazards
    std::vector<Obstacle> obstacles;
    std::vector<Vector2D> powerUpSpawnPoints;
    std::vector<SDL_Rect> dangerZones;
    
    void SpawnObstacles();
    void UpdateObstacles(float deltaTime);
    void HandleObstacleCollision(const SDL_Rect& bikeRect);
    
    // Track deformation
    std::vector<Vector2D> deformationPoints;
    void ApplyDeformation(const Vector2D& point, float radius, float intensity);
    void UpdateDeformation(float deltaTime);
    
    // Helper functions
    bool IsPointInTrack(const Vector2D& point) const;
    Vector2D GetNearestTrackPoint(const Vector2D& point) const;
    float GetElevationAt(const Vector2D& point) const;
    Vector2D GetTrackNormalAt(const Vector2D& point) const;
    
    // Track records
    struct LapRecord {
        std::string playerName;
        float time;
        std::string date;
    };
    std::vector<LapRecord> bestLaps;
    void UpdateRecords(const std::string& player, float time);
};
