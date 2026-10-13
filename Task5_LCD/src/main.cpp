//24_NTU_CS_FL_1086
//Noor Fatima Azam
// BSCS_B

#include <Arduino.h>
#include <Wire.h>
// I2C library for ESP32
#include <Adafruit_GFX.h>
// display library for graphics
#include <Adafruit_SSD1306.h>

// Display ka size set karna hai
#define SCREEN_WIDTH 128 // OLED display ka width hai px ma
#define SCREEN_HEIGHT 64  // OLED display ka height hai px ma

// ESP32 KI PINS jo display ka sath data exchange krnay ka liya hai
#define OLED_SDA 21
#define OLED_SCL 22

#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

void setup() {
    Serial.begin(115200);

// OLED display ko initialize karna hai.
    Wire.begin(OLED_SDA, OLED_SCL);

    // yeh check karna hai ke display sahi se initialize hua hai ya nahi
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) {
            delay(100);
        }
    }

// Display ko clear karna hai aur text ka size aur color set karna hai
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
// Display ka cursor set karna hai aur text print karna hai
    display.setCursor(0, 0);
    display.println("ESP32 + OLED");

    display.println("PlatformIO Ready!");
    display.println("I2C Address: 0x3C");

    display.display();

    Serial.println("OLED initialized successfully.");
    delay(3000);
}

void loop() {
    // Add your application code here.
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 20);
    display.println("ESP32 + OLED");
    display.println("Welcome to Embedded Systems!");
    
    display.display();
    delay(1000);
}
