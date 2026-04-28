# 433MHz RF Communication Project with ID Filtering & Servo Control

This project implements a wireless communication system between two Arduino boards using 433MHz Radio Frequency modules. It features a custom ID filtering system to ensure messages are processed only by the intended receiver, and allows for remote control of a servo motor.

---

## Hardware Configuration

### Components Required
* **Microcontrollers:** 2x Arduino Uno.
* **RF Kit:** 2x 433MHz Transmitter (FS1000A), 1x 433MHz Receiver (XY-MX-5V).
* **Actuator:** 1x Servo Motor (e.g., SG90, MG996R).
* **Antennas:** 4x 17.3 cm copper wires (Required for range beyond 10cm).

### RF Wiring Diagram

| RF Module | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Transmitter DATA** | D12 | Data Input |
| **Transmitter VCC** | 5V | Power (Up to 12V for range) |
| **Transmitter GND** | GND | Ground |
| **Receiver DATA** | D11 | Data Output |
| **Receiver VCC** | 5V | Power (Must be stable 5V) |
| **Receiver GND** | GND | Ground |

![Pinout](/asset/fs1000a-pinout.jpg)

### Servo Wiring Diagram

| Servo | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Signal (Orange/Yellow)**| D2 | PWM Control Signal |
| **VCC (Red)** | 5V | Power (External power recommended for larger servos) |
| **GND (Brown/Black)** | GND | Ground |

---

## Technical Implementation & Dependencies

The system relies on specific libraries to manage the communication and motor control without hardware timer conflicts:

* **RadioHead (RH_ASK):** Handles the physical layer bit-streaming, preamble, and CRC error checking for the RF modules. It inherently relies on Arduino's Timer 1.
* **ServoTimer2:** Manages the PWM signals for the servo motor. Using this library instead of the standard Arduino `Servo.h` is necessary to prevent Timer 1 conflicts, ensuring both RF communication and servo movements work seamlessly together.

---

## Features

* **Targeted Messaging:** Uses custom ID prefixes to ensure that only the designated receiver acts on a broadcasted message, ignoring irrelevant data.
* **Remote Actuation:** Wirelessly controls a servo motor, interpreting text strings to execute specific physical movements.
* **Dynamic Pulse Mapping:** Automatically maps standard angle values (0-180 degrees) to microsecond pulse widths for accurate servo positioning.

---

## Command Protocol

The transmitter must format strings with a specific structure for the receiver to validate and act upon them. The structure is: 

`[RECEIVER_ID] [COMMAND]`

### Example Usage:
In this project, the Receiver's ID is set to `100`. Through the Serial Monitor, you can send the following commands:

* **`100 OPEN`**: The receiver parses the ID, confirms a match, and moves the servo to the 90-degree position.
* **`100 CLOSE`**: The receiver parses the ID, confirms a match, and returns the servo to the 0-degree position.

Any message received with an incorrect ID (e.g., `300 OPEN` or just `OPEN`) will be completely ignored by the receiving node.

---

## Important Notes
* **Power Supply:** If the Arduino resets or the RF receiver stops working when the servo moves, it is highly recommended to power the servo with a separate 5V power supply. Remember to connect the ground (GND) of the external power supply to the Arduino's GND.

---

![Schematic Overview](/asset/Scheme-it-export-New-Project-2026-04-21-10-42.png)

The uploaded image illustrates the specific wiring connections for two separate microcontroller nodes capable of two-way RF communication.

**Node 1** (Top Section)
    This node acts as the primary controller equipped with actuation capabilities.

* Microcontroller: Arduino Uno (U1).

* RF Transmitter (U2 - FS1000A): The Data pin is wired to digital pin D12 (blue wire).

* RF Receiver (U3 - XY-MK-5V): The Data pin is wired to digital pin D11 (green wire).

* Servo Motor (U4): The PWM signal pin is wired to digital pin D2 (orange wire).

Power: All three peripherals (U2, U3, U4) share common 5V (red wires) and Ground (black wires) connections drawn directly from the Arduino Uno.

**Node 2** (Bottom Section)
    This node acts as the secondary transceiver.

* Microcontroller: A compact Arduino board, such as a Nano or Micro (U5).

* RF Transmitter (U6 - FS1000A): The Data pin is wired to digital pin D12 (blue wire).

* RF Receiver (U7 - XY-MK-5V): The Data pin is wired to digital pin D11 (green wire).

Power: Both RF modules draw 5V (red wires) and Ground (black wires) from the compact Arduino board.
