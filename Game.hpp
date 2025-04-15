#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include <vector>
#include <string>
#include "GameState.hpp"
#include "Bike.hpp"
#include "Track.hpp"
#include "PowerUp.hpp"

class ParticleSystem;
class SoundManager;
class UIManager;
class NetworkManager;
class PhysicsWorld;
class Camera;

class Game {
public:
    Game();
    ~Game();
    
    bool Initialize();
    void Run();
    void Cleanup();
    
    // Subsystem access
    ParticleSystem* GetParticleSystem() { return particleSystem.get(); }
    SoundManager* GetSoundManager() { return soundManager.get(); }
    UIManager* GetUIManager() { return uiManager.get(); }
    NetworkManager* GetNetworkManager() { return networkManager.get(); }
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld.get(); }
    Camera* GetCamera() { return camera.get(); }

private:
    // Core game loop
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void LoadResources();
    
    // Game systems
    std::unique_ptr<ParticleSystem> particleSystem;
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<UIManager> uiManager;
    std::unique_ptr<NetworkManager> networkManager;
    std::unique_ptr<PhysicsWorld> physicsWorld;
    std::unique_ptr<Camera> camera;
    
    // Performance monitoring
    float frameTime;
    float fps;
    float physicsUpdateTime;
    float renderTime;
    
    void UpdatePerformanceMetrics();
    void RenderDebugInfo();
    
    // Scene management
    void LoadScene(const std::string& sceneName);
    void UnloadScene();
    void TransitionToScene(const std::string& sceneName);
    
    // Resource management
    struct ResourceManager {
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, Mix_Chunk*> sounds;
        std::map<std::string, Mix_Music*> music;
        std::map<std::string, TTF_Font*> fonts;
        void UnloadAll();
    } resources;
    
    // Input handling
    struct InputState {
        std::map<SDL_Keycode, bool> keyStates;
        std::map<Uint8, bool> mouseStates;
        int mouseX, mouseY;
        void Update();
    } input;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    GameState currentState;
    
    std::vector<std::unique_ptr<Bike>> bikes;
    std::unique_ptr<Track> currentTrack;
    std::vector<PowerUp> powerUps;
    
    // Audio
    Mix_Music* backgroundMusic;
    std::vector<Mix_Chunk*> soundEffects;
    
    // Resources
    std::vector<SDL_Texture*> bikeTextures;
    std::vector<SDL_Texture*> trackTextures;
    std::vector<SDL_Texture*> powerUpTextures;
    TTF_Font* gameFont;
    
    // Configuration
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const std::string WINDOW_TITLE = "Advanced Bike Racing";
    const int TARGET_FPS = 60;
    const float FIXED_TIMESTEP = 1.0f / 60.0f;
    const int MAX_FRAME_SKIP = 5;
    
    // Debug flags
    struct DebugFlags {
        bool showFPS = false;
        bool showColliders = false;
        bool showParticles = false;
        bool showPhysicsDebug = false;
        bool enableCheats = false;
    } debug;
};
