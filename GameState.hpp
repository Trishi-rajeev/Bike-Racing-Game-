#pragma once
#include <vector>
#include <string>

enum class State {
    MENU,
    BIKE_SELECTION,
    TRACK_SELECTION,
    RACE,
    PAUSE,
    RESULTS,
    CHAMPIONSHIP,
    TIME_TRIAL,
    TUTORIAL,
    GARAGE,
    TOURNAMENT,
    ONLINE_LOBBY,
    SETTINGS,
    PROFILE,
    ACHIEVEMENTS
};

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD,
    EXTREME
};

struct Achievement {
    std::string id;
    std::string name;
    std::string description;
    bool unlocked;
    float progress;
    std::string unlockDate;
};

struct BikeCustomization {
    std::string paintJob;
    std::string decals;
    std::vector<std::string> upgrades;
    float performance;
};

struct PlayerStats {
    int points;
    float bestTime;
    int wins;
    std::string name;
};

class GameState {
public:
    GameState();
    ~GameState();

    void ChangeState(State newState);
    void UpdateStats();
    void SaveProgress();
    void LoadProgress();
    
    // Getters
    State GetCurrentState() const { return currentState; }
    int GetPlayerCount() const { return playerCount; }
    const std::vector<PlayerStats>& GetPlayerStats() const { return playerStats; }
    
    // Setters
    void SetPlayerCount(int count) { playerCount = count; }
    void AddPlayerStats(const PlayerStats& stats) { playerStats.push_back(stats); }

private:
    State currentState;
    int playerCount;
    std::vector<PlayerStats> playerStats;
    
    // Championship data
    int currentRace;
    int totalRaces;
    std::vector<std::string> trackOrder;
    
    // Player progression
    struct PlayerProgress {
        int level;
        int experience;
        int coins;
        std::vector<std::string> unlockedBikes;
        std::vector<std::string> unlockedTracks;
        std::vector<Achievement> achievements;
        std::map<std::string, BikeCustomization> bikeCustomizations;
    };
    std::vector<PlayerProgress> playersProgress;

    // Tournament system
    struct Tournament {
        std::string name;
        std::vector<std::string> tracks;
        int minLevel;
        Difficulty difficulty;
        std::vector<std::string> rewards;
        bool isActive;
    };
    std::vector<Tournament> tournaments;

    // Online features
    struct LeaderboardEntry {
        std::string playerName;
        float time;
        std::string trackName;
        std::string bikeType;
        std::string date;
    };
    std::vector<LeaderboardEntry> globalLeaderboard;

    // Settings
    struct GameSettings {
        bool fullscreen;
        int resolution[2];
        float musicVolume;
        float sfxVolume;
        std::map<std::string, int> controls;
        bool vsync;
        int graphicsQuality;
    } settings;

    // Methods
    void UpdatePlayerProgress(int playerId, int exp);
    void UnlockAchievement(int playerId, const std::string& achievementId);
    void SaveSettings();
    void LoadSettings();
    void UpdateLeaderboard(const LeaderboardEntry& entry);
    bool IsContentUnlocked(int playerId, const std::string& contentId);
    void StartTournament(const std::string& tournamentName);

    // Save/Load helpers
    void SerializeData();
    void DeserializeData();
    const std::string SAVE_FILE = "game_progress.sav";
    const std::string SETTINGS_FILE = "game_settings.cfg";
    const std::string LEADERBOARD_FILE = "leaderboard.dat";
};
