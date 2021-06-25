# The Competition
In the CoSpace Rescue Challenge, teams develop and program appropriate strategies for autonomous robots to navigate through a virtual environment, collecting objects and avoiding obstacles along the way.

# Project Layout
Refer to the TDP for more information.
## Main Program
Contains the C++ code for the robot.

## External Scripts
Contains a few helper scripts for converting the original bmp to an integer array representing the map (generate mapData.hpp).

# Setup
1. Download CoSpaceRobot Simulator (https://cospacerobot.org/download/cospace-rescue-download)
2. Download g++ Compiler Toolchain for Windows 32bit (https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-posix/dwarf/)
3. Obtain original map.bmp from CsBot application folder; use helper scripts to generate mapData.hpp
4. Copy mapData.hpp to Main Program folder 
5. Make a few more changes to the program based on the map
6. Run Build.bat
7. Select the dll for red/blue robot and run the Simulator 

# Videos
https://www.youtube.com/playlist?list=PLIiXUtD1ITQgM67tc36gdv7UKwYlbLlcg

# Future Development
The project can be further improved. Posible ideas are listed below.
- Replace A* with more advanced algorithms such as Any-Angle Path Finding (Theta*, Anya)
- Implementation of odometry in World 1
- Varying ultrasonic values based on wheel speeds
- Revamp the entire codebase to improve ease of reading

# Discord
You can join our [Discord Server](https://discord.gg/sagtrca) to discuss anything related to CoSpace Rescue.

# Disclaimer
The code was written under heavy time constraints during the competition and thus does not follow common coding standards and best practices.
