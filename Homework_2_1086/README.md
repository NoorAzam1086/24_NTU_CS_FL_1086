# ESP32 Dual LED PWM Projects

## 1. Project Overview

### Task 1: Dual LED PWM Fading

This task demonstrates independent brightness control of two LEDs using Pulse Width Modulation (PWM) on an ESP32. Both LEDs continuously fade in and out at different speeds using separate PWM channels and frequencies. Non-blocking timers allow both LEDs to operate independently.

### Task 2: Dual LED PWM with OLED Monitoring

This task extends the dual LED PWM project by adding an SSD1306 OLED display. The display shows the brightness percentages and PWM frequencies of both LEDs while they fade independently. The OLED refreshes periodically without stopping the LED fading operations.

## 2. Hardware Requirements

### Task 1

- ESP32 DevKit V4
- One red LED
- One green LED
- Two 220Ω resistors
- Jumper wires

### Task 2

- ESP32 DevKit V4
- One red LED
- One green LED
- Two 220Ω resistors
- SSD1306 OLED display (128 × 64 pixels, I2C)
- Jumper wires

## 3. Wiring Connections

### Task 1

**Red LED:**
- Anode (A) → 220Ω resistor → GPIO 18
- Cathode (C) → GND

**Green LED:**
- Anode (A) → 220Ω resistor → GPIO 19
- Cathode (C) → GND

### Task 2

**Red LED:**
- Anode (A) → 220Ω resistor → GPIO 18
- Cathode (C) → GND

**Green LED:**
- Anode (A) → 220Ω resistor → GPIO 19
- Cathode (C) → GND

**OLED Display:**
- VCC → ESP32 3V3
- GND → ESP32 GND
- SDA → GPIO 21
- SCL → GPIO 22

The OLED uses the I2C interface with address `0x3C`. Each LED must have its own 220Ω current-limiting resistor.

**Wiring Note:** In both supplied Wokwi diagrams, the red and green LEDs are connected to GPIO pins opposite to those assigned in the code. Connect the red LED to GPIO 18 and the green LED to GPIO 19, or modify the code to match the diagram.

## 4. PWM Configuration

### Task 1

- LED 1: GPIO 18, PWM channel 0, frequency 10 kHz.
- LED 2: GPIO 19, PWM channel 1, frequency 5 kHz.
- PWM resolution: 8-bit.
- Duty-cycle range: 0–255.
- LED 1 fade interval: 12 milliseconds.
- LED 2 fade interval: 20 milliseconds.
- Serial Monitor baud rate: 115200.

### Task 2

- LED 1: GPIO 18, PWM channel 0, frequency 1 kHz.
- LED 2: GPIO 19, PWM channel 1, frequency 5 kHz.
- PWM resolution: 8-bit.
- Duty-cycle range: 0–255.
- LED 1 fade interval: 12 milliseconds.
- LED 2 fade interval: 20 milliseconds.
- OLED resolution: 128 × 64 pixels.
- OLED I2C address: `0x3C`.
- SDA pin: GPIO 21.
- SCL pin: GPIO 22.
- OLED refresh interval: 150 milliseconds.
- Serial Monitor baud rate: 115200.

## 5. Implementation Details

### Task 1

**PWM Initialization:** The `setup()` function initializes Serial communication and configures two PWM channels with separate frequencies and 8-bit resolution.

**Duty-Cycle Control:** The `updateFade()` function increases or decreases the duty-cycle value. When the value reaches 255, the direction reverses. When it reaches 0, the direction changes again.

**Non-Blocking Timing:** The `millis()` function tracks the elapsed time for each LED. LED 1 updates every 12 milliseconds, while LED 2 updates every 20 milliseconds.

**Main Loop:** The `loop()` function checks both timers and updates the corresponding LED when its interval has elapsed. The fading process continues repeatedly without long blocking delays.

### Task 2

**PWM Initialization:** The `setup()` function configures the PWM channels, attaches the LED pins, and initializes both LEDs at zero brightness. It also checks for PWM initialization failure.

**OLED Initialization:** The `Wire.begin(21, 22)` function initializes I2C communication. The `display.begin()` function initializes the SSD1306 display at address `0x3C`.

**Brightness Calculation:** The expression `(duty * 100 + 127) / 255` converts the current duty-cycle value into an approximate percentage.

**OLED Monitoring:** The `updateOLED()` function displays the project title, both LED brightness percentages, their PWM frequencies, and the 8-bit resolution.

**Independent Fading:** The `updateFade()` function adjusts each LED's duty cycle independently using separate directions and timers.

**Non-Blocking Updates:** The OLED refreshes every 150 milliseconds using `lastOLED` and `OLED_INTERVAL`. The LED fading operations continue independently while the display updates.

## 6. Testing Notes

### Task 1

- Start the Wokwi simulation or upload the program to the ESP32.
- Verify that both LEDs start with zero brightness.
- Observe both LEDs fading in and out continuously.
- Confirm that LED 1 is configured for 10 kHz and LED 2 for 5 kHz.
- Verify that the LEDs operate independently.
- Open the Serial Monitor at 115200 baud.

**Expected Serial Monitor Output:**

    Task 1: Dual LED PWM started
    LED 1: GPIO 18, Frequency: 10000 Hz
    LED 2: GPIO 19, Frequency: 5000 Hz
    Resolution: 8-bit

### Task 2

- Start the Wokwi simulation or upload the program to the ESP32.
- Verify that both LEDs initialize with zero brightness.
- Confirm that the OLED displays the title and PWM information.
- Observe the brightness percentages changing as the LEDs fade.
- Confirm that LED 1 is configured for 1 kHz and LED 2 for 5 kHz.
- Verify that the OLED refreshes periodically while both LEDs continue fading.
- Check the SDA, SCL, VCC, and GND connections.
- Open the Serial Monitor at 115200 baud.

**Expected Serial Monitor Output:**

    Dual LED PWM and OLED monitor ready.
    LED1 frequency: 1000 Hz
    LED2 frequency: 5000 Hz

The Serial Monitor confirms program initialization and reports the configured frequencies. Actual PWM frequencies require an oscilloscope or logic analyzer for independent hardware verification.

## 7. Software Requirements

### Task 1

- Visual Studio Code
- PlatformIO IDE extension
- Arduino framework for ESP32
- Wokwi Simulator (optional)

### Task 2

- Visual Studio Code
- PlatformIO IDE extension
- Arduino framework for ESP32
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Wokwi Simulator (optional)

Both implementations use the Arduino-ESP32 core 2.x LEDC API, including `ledcSetup()` and `ledcAttachPin()`. Task 2 also uses the `Wire`, `Adafruit_GFX`, and `Adafruit_SSD1306` libraries.

## 8. Project Structure

    ESP32-Dual-LED-PWM/
    ├── src/
    │   └── main.cpp
    ├── diagram.json
    ├── platformio.ini
    └── README.md

The `main.cpp` file contains the program logic, `diagram.json` defines the Wokwi circuit, `platformio.ini` stores the PlatformIO configuration, and `README.md` documents both tasks.

## 9. Conclusion

Task 1 demonstrates independent LED fading using different PWM frequencies, duty-cycle control, and non-blocking timers.

Task 2 extends the same functionality with an SSD1306 OLED display that monitors LED brightness percentages and PWM frequencies.

Together, both tasks demonstrate PWM signal generation, GPIO control, timer-based programming, I2C communication, and OLED integration using the ESP32.
