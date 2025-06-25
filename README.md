# cub3D

## 🎮 Project Overview

cub3D is a 3D raycasting engine inspired by the legendary **Wolfenstein 3D**, which was one of the first true First-Person Shooters in video game history. This project implements a raycasting algorithm to create a dynamic 3D view inside a maze where the player must navigate through the environment.

The project is built using the **miniLibX** graphics library (MLX42) and follows the 42 School coding standards (The Norm).

## ✨ Features

### Mandatory Features
- **3D Raycasting Engine**: Real-time 3D rendering using raycasting principles
- **Wall Textures**: Different textures for walls facing North, South, East, and West
- **Floor and Ceiling Colors**: Customizable solid colors for floor and ceiling
- **Player Movement**: WASD keys for movement, arrow keys for rotation
- **Map Parsing**: Support for `.cub` map files with validation
- **Window Management**: Smooth window operations (minimize, maximize, close)

### Bonus Features
- **Wall Collision Detection**: Realistic collision system
- **Minimap System**: Real-time minimap showing player position and view rays
- **Interactive Doors**: Doors that can be opened and closed with spacebar
- **Animated Sprites**: Support for multi-frame animated sprites
- **Mouse Look**: Mouse movement for camera rotation

## 🛠 Installation

### Prerequisites
- **Operating System**: macOS or Linux
- **Compiler**: `cc` with flags `-Wall -Wextra -Werror`
- **Graphics Libraries**: 
  - libglfw3
  - OpenGL libraries
  - X11 development libraries (Linux)

### Build Instructions

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd cub3D
   ```

2. **Build the project**:
   ```bash
   make
   ```

3. **Clean build files** (optional):
   ```bash
   make clean    # Remove object files
   make fclean   # Remove object files and executable
   make re       # Clean and rebuild
   ```

## 🚀 Usage

### Basic Usage
```bash
./cub3D <map_file.cub>
```

### Example
```bash
./cub3D map/good/test.cub
```

## 🗺 Map Configuration

### Map File Format (`.cub`)

The map file must contain the following elements:

#### Texture Definitions
```
NO ./textures/north_texture.png     # North wall texture
SO ./textures/south_texture.png     # South wall texture  
WE ./textures/west_texture.png      # West wall texture
EA ./textures/east_texture.png      # East wall texture
DOOR ./textures/door_texture.png    # Door texture (bonus)
```

#### Animated Sprites (Bonus)
```
ANIMATED ./textures/tree/tree00.png
ANIMATED ./textures/tree/tree01.png
ANIMATED ./textures/tree/tree02.png
ANIMATED ./textures/tree/tree03.png
ANIMATED ./textures/tree/tree04.png
ANIMATED ./textures/tree/tree05.png
```

#### Colors
```
F 220,100,0      # Floor color (RGB: 0-255)
C 225,30,0       # Ceiling color (RGB: 0-255)
```

#### Map Grid
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
110000011101010111110111100N111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

#### Map Characters
- `1`: Wall
- `0`: Empty space (floor)
- ` ` (space): Empty area outside the map
- `N/S/E/W`: Player starting position and orientation
- `A`: Animated sprite position (bonus)
- `D`: Door position (bonus)

### Map Rules
- Map must be surrounded by walls (`1`) or spaces (` `)
- Must contain exactly one player starting position
- All walkable areas must be properly enclosed
- Spaces cannot be adjacent to walkable areas

## 🎮 Controls

### Movement
- **W**: Move forward
- **S**: Move backward  
- **A**: Strafe left
- **D**: Strafe right

### Camera
- **Left Arrow**: Turn left
- **Right Arrow**: Turn right
- **Mouse Movement**: Look around (bonus)

### Interaction
- **Space**: Open/Close doors (bonus)
- **ESC**: Exit game
- **Red X**: Close window

## 🎁 Bonus Features

### Wall Collision
- Realistic collision detection prevents walking through walls
- Sliding movement along walls when collision occurs

### Minimap System
- Real-time minimap in the top-left corner
- Shows player position, orientation, and view rays
- Displays walls, floors, doors, and sprites with different colors

### Interactive Doors
- Doors can be opened and closed using the spacebar
- Smooth door opening/closing animations
- Collision detection works with door states

### Animated Sprites  
- Support for multi-frame sprite animations
- Configurable frame count (2-10 frames)
- Automatic frame cycling with timing control

### Mouse Look
- Mouse movement controls camera rotation
- Smooth rotation response

## 📁 Project Structure

```
cub3D/
├── include/           # Header files
│   ├── common.h      # Common structures and definitions
│   ├── parser.h      # Parsing functionality
│   ├── render.h      # Rendering functionality  
│   └── control.h     # Input and movement controls
├── src/              # Source files
│   ├── common/       # Core functionality
│   ├── parser/       # Map and file parsing
│   ├── render/       # 3D rendering and graphics
│   └── control/      # Input handling and movement
├── lib/              # External libraries
│   ├── MLX42/        # Graphics library
│   └── libft/        # Utility library
├── map/              # Example maps
│   ├── good/         # Valid test maps
│   └── bad/          # Invalid maps for testing
├── textures/         # Texture files
└── Makefile          # Build configuration
```

## 🔧 Technical Implementation

### Raycasting Algorithm
- **DDA (Digital Differential Analyzer)**: Efficient grid traversal
- **Fish-eye Correction**: Perpendicular distance calculation to remove distortion
- **Wall Height Calculation**: Distance-based perspective projection

### Texture Mapping
- **Wall Texture Mapping**: UV coordinate calculation for wall textures
- **Texture Selection**: Automatic texture selection based on wall orientation
- **Pixel Perfect Rendering**: Accurate texture coordinate mapping

### Sprite Rendering
- **Distance Sorting**: Back-to-front rendering for proper depth
- **Screen Space Projection**: 3D to 2D coordinate transformation
- **Alpha Blending**: Transparent pixel handling for sprite textures

### Performance Optimizations
- **Efficient Ray Casting**: Optimized DDA implementation
- **Memory Management**: Proper allocation and deallocation
- **Real-time Rendering**: 60 FPS target with smooth gameplay

### Testing
The project includes comprehensive test maps:
- **Valid maps** (`map/good/`): Test various valid configurations
- **Invalid maps** (`map/bad/`): Test error handling and validation

Run the norminette to check code compliance:
```bash
norminette src include
```

## 👥 Team

This project was developed in collaboration with **[Jiani](https://github.com/lanfeitiao)**.

## 📝 Notes

- This project is inspired by Wolfenstein 3D and serves as an educational implementation of raycasting
- All textures and assets should be in PNG format
- The project uses MLX42, a modern version of the miniLibX graphics library
- Memory management is critical - all allocated memory must be properly freed

---

**Enjoy exploring the world of 3D graphics and raycasting! 🎮**
