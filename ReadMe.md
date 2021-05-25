# Pac-Man++

![C++ Ver][1] ![OF Ver][2]

Pac-Man game written and coded in C++ using the _OpenFrameWorks_ library. The player controls Pac-Man and must attempt to eat all of the white dots on the screen while dodging the incoming ghosts. The base game has been enhanced with added ghosts and power ups.

![Gameplay][3]

## Controls
| Keys              | Actions                                                        |
|-------------------|----------------------------------------------------------------|
| `WASD`            | The four keys that move Pac-Man up, down, left, or right.      |  
| `Spacebar`        | Activates a Power Up based on what ghost Pac-Man has eaten.    |
| `P`               | Pauses the screen when in game.                                |

## Special Ghosts and Power Ups
| Ghosts  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;      | Description                                                    |
|-------------------|----------------------------------------------------------------|
| `Random Ghost`    | When Pac-Man reaches 500 points, a ghost is spawned on a random dot on the map. Eating this ghost spawns another random ghost on another dot on the map.|  
| `Peek A Boo Ghost`| Spawns when Pac-Man reaches 1000 points. This ghost is invisible until Pac-Man gets close to said ghost.|

| Power Ups &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;        | Effect                                                         |
|-------------------|----------------------------------------------------------------|
| ![RandomPowerUp][4] | When activated, teleports Pac-Man to a random dot on the map. Pac-Man gains this Power Up when a _Random Ghost_ is eaten.|  
| ![InvincinbilityPowerUp][5] | When activated, for a brief amount of steps, makes Pac-Man invincible and invisible so that he may dodge any incoming ghosts. Can't be activated if Pac-Man is too close to a ghost. Pac-Man gains this Power Up when a _Peek A Boo_ ghost is eaten.|

## Downloading and running
After downloading and extracting `bin.rar` from the [releases][4] page, double
click on the exectuable to run the program.

[1]: https://img.shields.io/badge/gcc-10.2.0-red
[2]: https://img.shields.io/badge/openframeworks-0.11.2-blue
[3]: https://i.imgur.com/2E5X6ZP.gif
[4]: https://i.imgur.com/M6DkuWr.png
[5]: https://i.imgur.com/Rmxd8nX.png
[6]: https://github.com/Mercrist/PacMan/releases/tag/v1.0
