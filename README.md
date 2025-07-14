# autonomy-mining
C++ implementation of an autonomous mining vehicle. Features self-driving logic, sensor integration, and real-time navigation for industrial mining environments.
# Autonomous Mining Vehicle (C++)

C++ implementation of an autonomous mining vehicle.  
Features self-driving logic, sensor integration, and real-time navigation for industrial mining environments.

## Features

- Real-time simulation of a self-driving mining vehicle
- Finite State Machine (FSM) for decision making
- Distance sensor simulation for obstacle detection
- Simple obstacle avoidance (currently only turns in one direction)
- Console visualization of vehicle position and environment

## Example Simulation Output

[AutonomyKit] Simulation system starting...
[AutonomyKit] Simulator initialized.

[Simulator] Step 1
. . . . . . .
. . . . . . X
A . . X . . .
. . . . . . .
. . . . . . .
[Sensor] DistanceSensor reading: 3 units
[FSM] Transitioning from IDLE to MOVE_FORWARD
[Simulator] Current state: MOVE_FORWARD

[Simulator] Step 2
. . . . . . .
. . . . . . X
. A . X . . .
...


## System Architecture

- **FSM States:** `IDLE`, `MOVE_FORWARD`, `OBSTACLE_DETECTED`, `TURN_LEFT`
- **Sensors:** Simulated distance sensor
- **Actuators:** Simulated motor commands (move forward, turn)

## How It Works

1. The vehicle starts in the `IDLE` state.
2. It reads distance data from the front sensor.
3. If the path is clear, it transitions to `MOVE_FORWARD`.
4. When an obstacle is detected, it transitions to `OBSTACLE_DETECTED` and then `TURN_LEFT`.
5. After turning, it attempts to move forward again.

## Current Limitations

- Obstacle avoidance only supports turning in a single direction.
- Only basic simulation and state transitions implemented.
- No real hardware integration yet.

## Roadmap / TODO

- [ ] Implement bidirectional or smarter obstacle avoidance
- [ ] Add support for additional sensors (e.g., LIDAR, IMU)
- [ ] Visualize path and state transitions with GUI or web interface
- [ ] Prepare for real-world hardware deployment

## How to Build & Run

1. Clone this repository.
2. Compile with CMake and your preferred C++ compiler.
3. Run the resulting executable:


## Contact

Created by [MUR_0612]  
For more information, please open an issue or contact me.
