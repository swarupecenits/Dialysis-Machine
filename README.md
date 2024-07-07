# Dialysis Machine Using Arduino

<img src="https://www.mdpi.com/healthcare/healthcare-10-00564/article_deploy/html/images/healthcare-10-00564-g007-550.jpg"/>

## Project Description

This project develops a prototype of a dialysis machine using an Arduino microcontroller. The machine automates fluid control, monitors flow rates and volumes in real-time, and provides essential information on an LCD display to simulate kidney function.

## Features

- **Automated Fluid Control**: Solenoid valves and pumps controlled by Arduino.
- **Real-Time Monitoring**: Sensors for continuous monitoring of flow rates and volumes.
- **User Interface**: LCD display showing real-time information.

## Components

- Arduino microcontroller
- Solenoid valves
- Pumps
- Flow rate sensors
- LCD display
- Tubing and connectors
- Power supply

## Installation

1. **Clone this repository**:
    ```sh
    git clone https://github.com/your-username/dialysis-machine-arduino.git
    cd dialysis-machine-arduino
    ```

2. **Install Arduino IDE**: Download and install from [Arduino website](https://www.arduino.cc/en/software).

3. **Connect the components**:
    - Follow the schematic provided in the repository to connect the solenoid valves, pumps, sensors, and LCD display to the Arduino.

4. **Upload the code**:
    - Open the Arduino IDE.
    - Open the `dialysis_machine.ino` file from the cloned repository.
    - Select your Arduino board and port from the Tools menu.
    - Click on the Upload button to upload the code to your Arduino.

Usage

    Start the system:
        Connect the Arduino to the power supply.
        The LCD display will show the initial message and start monitoring.

    Monitor the process:
        The LCD display will update with the flow rate and total fluid volume in real-time.

    Control the fluid flow:
        The solenoid valves and pumps will operate in a controlled manner to simulate the dialysis process.

This project is licensed under the terms and conditions of the National Institute of Technology Silchar. Unauthorized copying, sharing, or distribution is strictly prohibited without prior permission from NIT Silchar.
