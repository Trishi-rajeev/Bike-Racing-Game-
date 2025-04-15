# 🏍️ Advanced Bike Racing Game

A high-performance multiplayer bike racing game created in modern C++ with advanced physics, stunning graphics, and extensive gameplay features. Experience the thrill of racing with up to 4 players locally, customize your bikes, and compete in various game modes across dynamic tracks.

## ✨ Key Features

### 🎮 Gameplay
- **Multiple Game Modes**:
  - Quick Race: Jump straight into the action
  - Championship: Compete in a series of races
  - Time Trial: Beat your best times
  - Tournament: Join organized competitions
  - Practice Mode: Learn tracks without pressure

### 🏍️ Bikes & Customization
- **Three Distinct Bike Classes**:
  - Speed Bike: High top speed, lower stability
  - All-Rounder: Balanced performance
  - Off-Road: Superior handling on rough terrain
- **Deep Customization**:
  - Custom paint jobs and decals
  - Performance upgrades
  - Unique bike parts

### 🌍 Tracks & Environment
- **Dynamic Track System**:
  - Multiple terrain types (Asphalt, Dirt, Ice, etc.)
  - Real-time track deformation
  - Interactive obstacles
  - Destructible elements
- **Weather System**:
  - Dynamic weather changes
  - Day/night cycle
  - Weather affects gameplay

### 🎯 Technical Features
- **Advanced Physics**:
  - Realistic suspension system
  - Terrain-based traction
  - Accurate collision detection
  - Particle effects
- **Modern Graphics**:
  - High-quality textures
  - Dynamic lighting
  - Particle effects
  - Smooth animations
- **Rich Audio**:
  - Dynamic engine sounds
  - Environmental effects
  - Adaptive music system

### 🏆 Progression System
- Player levels and experience
- Unlockable content
- Achievements
- Global leaderboards
- Statistics tracking

## 🛠️ Development Setup

### System Requirements
- **OS**: Windows 10/11 64-bit
- **CPU**: Intel Core i3/AMD Ryzen 3 or better
- **RAM**: 4GB minimum, 8GB recommended
- **GPU**: DirectX 11 compatible graphics card
- **Storage**: 2GB available space

### Required Software
1. **Development Tools**:
   - MinGW-w64 (GCC 11.0 or later)
   - CMake 3.15 or later
   - Git
   - Visual Studio Code (recommended)

2. **Libraries**:
   - SDL2 (2.28.5 or later)
   - SDL2_image (2.6.3 or later)
   - SDL2_ttf (2.20.2 or later)
   - SDL2_mixer (2.6.3 or later)

### Installation Steps

1. **Install Development Tools**:
   ```powershell
   # Using Chocolatey (Windows package manager)
   choco install mingw cmake git vscode -y
   ```

2. **Set Up SDL2**:
   ```powershell
   # Create development libraries directory
   mkdir C:\Dev\Libraries
   cd C:\Dev\Libraries

   # Download SDL2 libraries
   # Extract them to C:\Dev\Libraries\SDL2
   ```

3. **Clone and Build**:
   ```powershell
   # Clone repository
   git clone https://github.com/yourusername/bike-racing-game.git
   cd bike-racing-game

   # Create build directory
   mkdir build
   cd build

   # Configure with CMake
   cmake -G "MinGW Makefiles" \
         -DCMAKE_PREFIX_PATH=C:\Dev\Libraries\SDL2 \
         -DCMAKE_BUILD_TYPE=Release ..

   # Build
   cmake --build . --config Release
   ```

4. **Run the Game**:
   ```powershell
   .\bin\bike_race.exe
   ```

## Building
```bash
mkdir build && cd build
cmake ..
make
```

## 🎮 Gameplay Guide

### Controls

#### Player 1 Controls
```
Movement:                Combat & Special:
-----------------        ------------------
W     - Accelerate      SPACE  - Use Power-up
S     - Brake           Q      - Look Behind
A     - Lean Left       E      - Change Camera
D     - Lean Right      TAB    - Show Standings
SHIFT - Boost           R      - Reset Position
```

#### Player 2 Controls
```
Movement:                Combat & Special:
-----------------        ------------------
↑     - Accelerate      RCTRL  - Use Power-up
↓     - Brake           RSHIFT - Look Behind
←     - Lean Left       RETURN - Change Camera
→     - Lean Right      P      - Show Standings
RCTRL - Boost           BACK   - Reset Position
```

### Advanced Techniques

1. **Boosting**
   - Hold boost while accelerating for maximum speed
   - Use on straightaways for best effect
   - Watch your boost meter!

2. **Cornering**
   - Lean into turns early
   - Release acceleration slightly before turns
   - Use brake and lean for tight corners

3. **Jumping**
   - Approach ramps at optimal speed
   - Pull back to gain height
   - Push forward to land faster

4. **Power-up Usage**
   - 🚀 Nitro: 3-second speed boost
   - 🛡️ Shield: 5-second protection
   - ⚡ Speed Burst: Instant acceleration
   - 🦘 Jump Boost: Enhanced jump height
   - 🎯 Missile: Targets nearest opponent
   - 🛢️ Oil Slick: Creates hazard zone

## 🏗️ Project Structure

```
bikerace/
├── src/                 # Source files
│   ├── core/           # Core game systems
│   │   ├── Game.cpp
│   │   ├── GameState.cpp
│   │   └── Config.cpp
│   ├── physics/        # Physics engine
│   │   ├── Physics.cpp
│   │   └── Collision.cpp
│   ├── entities/       # Game entities
│   │   ├── Bike.cpp
│   │   ├── Track.cpp
│   │   └── PowerUp.cpp
│   ├── graphics/       # Rendering system
│   │   ├── Renderer.cpp
│   │   └── Particles.cpp
│   └── audio/          # Sound system
│       ├── SoundMgr.cpp
│       └── Music.cpp
├── include/            # Header files
│   ├── core/
│   ├── physics/
│   ├── entities/
│   ├── graphics/
│   └── audio/
├── assets/            # Game resources
│   ├── textures/      # Images and sprites
│   ├── sounds/        # Audio files
│   ├── tracks/        # Track definitions
│   └── shaders/       # Graphics shaders
├── docs/              # Documentation
└── tests/             # Unit tests

## 🔧 Configuration

The game can be configured through `config.json` in the game directory:

```json
{
  "graphics": {
    "resolution": [1280, 720],
    "fullscreen": false,
    "vsync": true,
    "quality": "high",
    "particles": true
  },
  "audio": {
    "music_volume": 0.8,
    "sfx_volume": 1.0,
    "engine_sounds": true
  },
  "gameplay": {
    "difficulty": "medium",
    "ai_opponents": 2,
    "laps": 3,
    "power_ups": true
  },
  "debug": {
    "show_fps": false,
    "show_colliders": false,
    "enable_cheats": false
  }
}
```

## 📖 Documentation

### Building Documentation
```bash
# Install Doxygen
choco install doxygen.install -y

# Generate documentation
doxygen Doxyfile
```

Documentation will be generated in `docs/html/`.

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Code Style
- Follow the provided `.clang-format` configuration
- Use meaningful variable and function names
- Document your code using Doxygen-style comments
- Write unit tests for new features

### Bug Reports
- Use the issue tracker
- Include steps to reproduce
- Attach relevant logs and screenshots
- Specify your system configuration
