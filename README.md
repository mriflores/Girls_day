# 433MHz RF Communication Project with ID Filtering

This project implements a wireless communication system between two Arduino boards (Nano and Uno) using 433MHz Radio Frequency modules. It features a custom ID filtering system to ensure messages are processed only by the intended receiver.

---

## Hardware Configuration

### Components Required
* **Microcontrollers:** 1x Arduino Uno, 1x Arduino Nano.
* **RF Kit:** 1x 433MHz Transmitter (FS-01P), 1x 433MHz Receiver (MX-05V).
* **Antennas:** 2x 17.3 cm copper wires (Required for range beyond 10cm).

### Wiring Diagram

| RF Module | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Transmitter DATA** | D12 | Data Input |
| **Transmitter VCC** | 5V | Power (Up to 12V for range) |
| **Transmitter GND** | GND | Ground |
| **Receiver DATA** | D11 | Data Output |
| **Receiver VCC** | 5V | Power (Must be stable 5V) |
| **Receiver GND** | GND | Ground |


---

## Technical Implementation

The system uses the **RadioHead (RH_ASK)** library. It handles the physical layer bit-streaming, preamble, and CRC error checking.

### Key Concepts
* **Null Terminator (`\0`):** Used to close the character buffer upon reception to prevent memory "garbage" from being printed.
* **Tokenization (`strtok`):** Splits the received string into the ID segment and the Message segment.
* **String Comparison (`strcmp`):** Compares the incoming ID with the local constant to trigger actions.

---
