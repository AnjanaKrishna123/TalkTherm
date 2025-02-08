#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>

// Initialize the MLX90614 sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Initialize the LCD (I2C Address: 0x27, 16x2 Display)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to 0x3F if needed

void setup() {
    Wire.begin();       // Start I2C communication
    mlx.begin();        // Initialize MLX90614 sensor
    lcd.init();         // Initialize LCD
    lcd.backlight();    // Turn on backlight

    // Display a startup message
    lcd.setCursor(0, 0);
    lcd.print("Temp Sensor");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000); // Wait 2 seconds
    lcd.clear();
}

void loop() {
    // Read temperature values
    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();

    // Display temperature on LCD
    lcd.setCursor(0, 0);
    lcd.print("Ambient: ");
    lcd.print(ambientTemp);
    lcd.print("C  ");

    lcd.setCursor(0, 1);
    lcd.print("Object: ");
    lcd.print(objectTemp);
    lcd.print("C  ");

    delay(1000); // Update every second
}
