# Door Lock System

## Overview
A secure and reliable door lock system implemented to control access via PIN code entry. This project leverages [ATmega32] to handle user inputs and control locking mechanisms efficiently. 

## Features
- **PIN Authentication**: Users enter a PIN to lock or unlock the door.
- **User Management**: Add, remove, or change user PINs.
- **Security Alert**: Triggers an alarm after multiple incorrect attempts.
- **Display Feedback**: Shows messages or status on an LCD or LED display.
- **Power Failure Handling**: Securely retains lock state even during power loss.

## Components
- Microcontroller (ATmega32)
- External EEPROM
- Keypad (4x4 matrix keypad recommended)
- LCD Display (16x2)
- DC-motor as lock
- Buzzer (for alert signaling)
- Power Supply (5V DC)
- Resistors, Wires, and Breadboard (for prototyping)

## Installation

1. **Hardware Setup**:
   - Connect the keypad to the microcontroller for user input.
   - Connect the LCD display to show status messages.
   - Attach the lock mechanism DC-motor to the microcontroller for control.
   - (Optional) Connect the buzzer to signal incorrect PIN attempts.

2. **Software Setup**:
   - Install required libraries for [Atmega 32].

3. **Compile and Upload**:
   - Use your preferred IDE (Eclipse or Atmel Studio) to compile and upload the code to the microcontroller.

## Usage
1. **Enter PIN**: Use the keypad to enter your assigned PIN code.
2. **Lock/Unlock**: The system will lock or unlock based on correct PIN entry.
3. **Manage Users**: Access the settings to change PINs (details in the code comments).
4. **Security Alert**: After 3 incorrect attempts, the system will activate the buzzer to alert for 1 min.

## Project Structure
- `src/`: Contains source code for the door lock system.
- `README.md`: Project documentation.


> **Note**: This project is intended for educational purposes only. Ensure secure implementation practices for real-world use.
