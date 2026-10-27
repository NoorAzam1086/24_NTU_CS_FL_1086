# Dual LED PWM Fading Using ESP32

## Task 1
## Project Overview

This project demonstrates how to control the brightness of two LEDs independently using Pulse Width Modulation (PWM) with an ESP32 microcontroller. Both LEDs continuously fade in and out at different speeds using separate PWM channels and frequencies.

## Hardware Requirements

- ESP32 DevKit V4
- Red LED
- Green LED
- Two 220Ω resistors
- Jumper wires

## Wiring Connections

**Red LED:**
- Anode (A) → 220Ω resistor → GPIO 18
- Cathode (C) → GND

**Green LED:**
- Anode (A) → 220Ω resistor → GPIO 19
- Cathode (C) → GND

Each LED uses a separate 220Ω resistor to limit current and protect the LED.

**Note:** The original Wokwi `diagram.json` has the red and green LEDs connected to opposite GPIO pins compared with the code. Update the wiring or change the code so that both match.

## PWM Configuration

- Red LED uses GPIO 18 and PWM channel 0.
- Green LED uses GPIO 19 and PWM channel 1.
- Red LED PWM frequency is 10 kHz.
- Green LED PWM frequency is 5 kHz.
- PWM resolution is 8-bit.
- Duty-cycle range is 0–255.
- Red LED fade interval is 12 milliseconds.
- Green LED fade interval is 20 milliseconds.
- Serial Monitor baud rate is 115200.

## Implementation Details

### PWM Initialization

The `setup()` function initializes Serial communication and configures two separate PWM channels with different frequencies. Both LEDs are initially set to zero brightness.

### Duty-Cycle Control

The `updateFade()` function changes the duty-cycle value gradually. When the value reaches 255, the direction reverses and brightness begins to decrease. When it reaches 0, the direction changes again and brightness starts increasing.

### Non-Blocking Timing

The program uses `millis()` to track the elapsed time for each LED. The red LED updates every 12 milliseconds, while the green LED updates every 20 milliseconds.

This approach avoids long blocking delays and allows both LEDs to fade independently.

### Main Loop

The `loop()` function checks the timers for both LEDs. When an LED's specified interval has elapsed, its duty cycle is updated. This process continues repeatedly while the ESP32 is running.

## Testing Notes

The project can be tested using the Wokwi simulator or a physical ESP32 board.

- Start the simulation and verify that both LEDs initialize to OFF.
- Observe the red LED gradually fading in and out.
- Observe the green LED fading independently.
- Confirm that the red LED is configured for 10 kHz and the green LED for 5 kHz.
- Verify that both LEDs continue fading without long blocking delays.
- Open the Serial Monitor and select a baud rate of 115200.

### Expected Serial Monitor Output

    Task 1: Dual LED PWM started
    LED 1: GPIO 18, Frequency: 10000 Hz
    LED 2: GPIO 19, Frequency: 5000 Hz
    Resolution: 8-bit

The Serial Monitor confirms that the program has initialized and printed its configuration. Actual PWM frequencies require measurement with an oscilloscope or logic analyzer for hardware-level verification.

## Software Requirements

- Visual Studio Code
- PlatformIO IDE extension
- ESP32 platform support
- Wokwi Simulator (optional)

## Project Structure

    Dual-LED-PWM/
    ├── src/
    │   └── main.cpp
    ├── diagram.json
    ├── platformio.ini
    └── README.md

## Conclusion

This project demonstrates independent LED brightness control using ESP32 PWM. Separate PWM channels, different frequencies, variable duty cycles, and non-blocking timers produce continuous fading effects and demonstrate fundamental embedded programming concepts.
