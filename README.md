# Tetris
## Arduino code for the project which showcases the fusion of hardware and software to recreate the classic game of Tetris in a physical form using LEDs.  Through meticulous planning and utilization of various materials and  components, the aim was to construct a tangible gaming experience that pays homage to the beloved retro game.

  <div align="center">
    <img src="https://github.com/Projects23-24/Tetris/assets/98465500/c68feacb-83da-4cea-bdd5-8c8fab294656" alt="WhatsApp Image 2024-04-19 at 15 49 19" width="250" />
</div>


## The game operates through a combination of user input and programmed  logic. Players control the falling Tetromino blocks using the Thumb  Joystick, moving them and rotating them to  fit into the LED matrix grid. The game's mechanics, including block  movement and collision detection, were programmed to mimic  the gameplay of the original Tetris. Features like pause screens have been integrated into the gameplay loop.

### Description of Tetris Game Implementation

1. **FastLED Library Integration**: LEDs controlled using FastLED library. Linear array used to track LED colors.

2. **Time Control**: Utilizing the `EVERY_N_MILLIS` function instead of `millis` due to interrupt issues. Executes code at fixed intervals.

3. **Matrix Mapping**: 20x10 2D array utilized, mapped to a linear array for LED matrix representation.

4. **Tetromino Representation**: Blocks defined by 4x4x4 3D arrays representing four orientations. Seven blocks available: I, L, J, O, S, Z, and T.

<div align="center">
    <img src="https://github.com/Projects23-24/Tetris/assets/98465500/c656e85b-1bcd-4921-85c9-825c3a8182db" alt="images" />
</div>




5. **Random Block Selection**: Random function generates a number (0-6) each frame. Analog noise used to seed Random Number Generator for variety.

6. **Player Input Handling**: Thumb joystick powered by Arduino's 3.3V pin. Input range adjusted (0-675). EasyButton library used for button clicks.

7. **Block Movement**: Horizontal movement controlled by joystick input. Rotation triggered by upward joystick movement. Block descends periodically. Collision detection with static blocks.

8. **Speed Increase**: Downward joystick input reduces delay, accelerating block descent and increasing points per interval.

9. **Line Clearance**: Upon block becoming static, each row in the grid checked for clearance. Score incremented accordingly.

10. **Game End Condition**: Check for filled top row; if found, game ends. High score updated if current score surpasses previous high score. High score stored in EEPROM.

11. **Pause Functionality**: Button click triggers pause, displaying options on LEDs and LCD. Vertical joystick movement selects option.

12. **Finite State Machines (FSM)**: Four game states implemented - Title screen, Loading, In-game, and Game Over. Transitions between states managed by FSM.

<div align="center">
    <img src="https://github.com/Projects23-24/Tetris/assets/98465500/77dc4b0c-b0b9-4f0b-8a94-71f0f17cafd0" alt="WhatsApp Image 2024-04-19 at 15 49 19 (1)" />
</div>

