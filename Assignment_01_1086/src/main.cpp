// Assignment # 01
// Embedded Systems of IoT
// 24_NTU_CS_FL_1086
// Noor Fatima Azam
// BSCS_B


#include <Arduino.h>
#include <Wire.h> // I2C library for ESP32
#include <Adafruit_GFX.h> // Core graphics library for displays
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#define BUTTON_PIN 18 // GPIO pin connected to the button

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET 
);

int pressCount = 0; // Variable to keep track of the number of button presses

bool lastButtonReading = HIGH; // Variable to store the last raw button reading
bool stableButtonState = HIGH; // Variable to store the stable button state after debouncing

unsigned long lastDebounceTime = 0; // Variable to store the last time the button state changed
const unsigned long debounceDelay = 50; // Debounce delay in milliseconds

void updateDisplay() { 
  display.clearDisplay(); // Clear the display buffer

  display.setTextColor(SSD1306_WHITE);   // Set text color to white

  display.setTextSize(1); // Set text size to 1 (default size)
  display.setCursor(0, 0); // Set cursor to the first line
  display.println("ESP32 Button Status");

  display.setCursor(0, 20); // set cursor to the second line
  display.print("Status: ");

  if (stableButtonState == LOW) { // If the button is pressed (active low), display "PRESSED"
    display.println("PRESSED");
  } else {
    display.println("RELEASED"); // If the button is not pressed, display "RELEASED"
  }

  display.setCursor(0, 40); // Set cursor to the third line
  display.print("Press Count: ");
  display.println(pressCount);

  display.display(); // Update the display with the new content
}

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with an internal pull-up resistor

  Wire.begin(21, 22); // Initialize I2C communication on ESP32 with SDA on GPIO 21 and SCL on GPIO 22

  if (!display.begin(
        SSD1306_SWITCHCAPVCC, // Use internal voltage regulator for the OLED
        OLED_ADDRESS // I2C address of the OLED display
      )) {
    Serial.println("OLED initialization failed!");
    while (true) {
      // Stop if OLED initialization fails
    }
  }

  display.clearDisplay(); // Clear the display buffer
  updateDisplay(); // Update the display with the initial content
 
  Serial.println("OLED initialized successfully.");
  Serial.println("Press the button to increase the count.");
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN); // Read the current state of the button (HIGH or LOW)

  // Detect a change in the raw button reading
  if (reading != lastButtonReading) {
    lastDebounceTime = millis(); // Reset the debounce timer if the button state has changed
  }

  // Accept the reading only after it remains stable
  if (millis() - lastDebounceTime >= debounceDelay) {

    if (reading != stableButtonState) {
      stableButtonState = reading;

      // Count only a valid press, not the release
      if (stableButtonState == LOW) {
        pressCount++;

         Serial.print("Accepted press count: "); //  Ye line count ka text print krti hai
         Serial.println(pressCount); // Ye line press count ka value print krti hai
      }

      updateDisplay(); // 
    }
  }

  lastButtonReading = reading; // Update the last button reading for the next loop iteration
}