#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>

// Initialize the MLX90614 sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Initialize the LCD (I2C Address: 0x27, 16x2 Display)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to 0x3F if needed 

// Declare the ISD1820 PLAY pin globally
  int isd1820Pin =2;// Change this to your ISD1820 control pin

void setup() {
    Wire.begin();       // Start I2C communication
    mlx.begin();        // Initialize MLX90614 sensor
    lcd.init();         // Initialize LCD
    lcd.backlight();    // Turn on backlight

    // Set ISD1820 play pin to output
    pinMode(isd1820Pin, OUTPUT);
    digitalWrite(isd1820Pin, LOW); // Ensure playback is off at the start
    Serial.begin(9600); 

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
    Serial.print("Ambient Temperature: ");
    Serial.println(ambientTemp);

    // Display temperature on LCD
    lcd.setCursor(0, 0);
    lcd.print("Ambient: ");
    lcd.print(ambientTemp);
    lcd.print("C  ");
    lcd.setCursor(0, 1);
    lcd.print("Object: ");
    lcd.print(objectTemp);
    lcd.print("C  ");

    // If ambient temperature is above 26°C, play the ISD1820 note
    if (objectTemp > 30) {
        lcd.setCursor(0, 1);
        lcd.print("Temp > 30C! Playing...");
        
        // Trigger ISD1820 to play the note
        digitalWrite(isd1820Pin, HIGH);  // Start playback
        delay(1000);
        digitalWrite(isd1820Pin, LOW);
        

        // Optional: Reset playback after a short delay, if needed
      // Optional: Reset delay before next check
    }

    delay(1000); // Update every second
}
