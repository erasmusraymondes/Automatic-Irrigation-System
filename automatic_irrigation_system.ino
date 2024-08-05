#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int soilMoisture = 0;
int moisturePercentage = 0;

// Define the pins
int soilMoisturePin = A0;   // Analog pin for soil moisture sensor
int relayPin = 3;           // Digital pin for the relay module

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Set the relay pin as output
  pinMode(relayPin, OUTPUT);

  // Initialize the LCD
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Initializing ");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("On");
  delay(2000);  // Display the initialization message for 2 seconds
  Serial.begin(9600);
  lcd.clear();

  // Read soil moisture level
  soilMoisture = analogRead(soilMoisturePin);

  // Map the moisture level to a range between 0 and 100
  moisturePercentage = map(soilMoisture, 0, 1023, 0, 100);

  // Print initial moisture level to Serial Monitor
  Serial.println(moisturePercentage);
}

void loop() {
  // Read soil moisture level
  soilMoisture = analogRead(soilMoisturePin);

  // Map the moisture level to a range between 0 and 100
  moisturePercentage = map(soilMoisture, 0, 1023, 0, 100);

  // Display moisture level on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.print(moisturePercentage);

  // Print moisture level to Serial Monitor
  Serial.print("Moisture Percentage: ");
  Serial.println(moisturePercentage);

  // Check if watering is needed
  if (moisturePercentage < 100) {
    lcd.setCursor(0, 1);
    lcd.print("Watering...");

    // Activate the relay (and, in turn, the water pump will light up)
    digitalWrite(relayPin, HIGH);

    // Simulate watering for 5 seconds (adjust as needed)
    delay(5000);
    lcd.clear();

    // Deactivate the relay (and, in turn, the water pump will shut down)
    digitalWrite(relayPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Done!");
    delay(2000);
    
  } else if (moisturePercentage > 100) {  // Removed the extra semicolon
    // If moisture is sufficient, display "Off"
    lcd.setCursor(0, 1);
    lcd.print("Standby");
    delay(10000); // Delay for a longer period before the next reading
    digitalWrite(relayPin, LOW);
  }
}
