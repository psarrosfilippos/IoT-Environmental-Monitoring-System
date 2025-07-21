#define THINGER_SERIAL_DEBUG
#include <Wire.h>
#include <ThingerESP32.h>
#include "arduino_secrets.h"
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Pin definition
#define DHTPIN 2 // The ESP32 pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // The type of DHT sensor
#define LED_PIN 16 // Pin for connecting the LED to the ESP32
#define MEASUREMENT_INTERVAL 300000

// LCD and DHT initialization
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD setup at address 0x27
DHT dht(DHTPIN, DHTTYPE); // DHT object for reading temperature and humidity

// Thinger.io Credentials
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Object for connecting to Thinger.io platform

// Variables for average temperature
float totalTemperature = 0; // Total temperature for calculating average
int temperatureReadings = 0; // Number of temperature readings
unsigned long lastMeasurementTime = 0; // Last average temperature submission time

void initializeDisplay() {
  // LCD screen initialization
  lcd.init();
  lcd.backlight(); // Turn on LCD backlight
  lcd.setCursor(0, 0); // Set cursor to first row
  lcd.print("Initializing..."); // Display initialization message
  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear screen
}

void connectToThinger() {
  // Connect to Wi-Fi via Thinger.io
  thing.add_wifi(SSID, SSID_PASSWORD);

  // Define Thinger.io resources for reading sensor data
  thing["TempHum"] >> [](pson &out) {
    float temperature = dht.readTemperature(); // Read temperature
    float humidity = dht.readHumidity(); // Read humidity

    // Check if readings are valid and store them
    if (!isnan(temperature)) out["temperature"] = temperature;
    if (!isnan(humidity)) out["humidity"] = humidity;
  };

  // Define LED control via dashboard on Thinger.io
  thing["LED_Control"] << digitalPin(LED_PIN); // LED connected to pin 16
}

void displaySensorData(float temperature, float humidity) {
  // Update LCD with temperature and humidity data
  lcd.setCursor(0, 0); // Set cursor to first row
  lcd.print("Temp: ");
  lcd.print(temperature, 1); // Display temperature with 1 decimal
  lcd.print("C  ");

  lcd.setCursor(0, 1); // Set cursor to second row
  lcd.print("Hum: ");
  lcd.print(humidity, 1); // Display humidity with 1 decimal
  lcd.print("%   ");
}

void displayError(const char* message) {
  // Display error message on LCD
  lcd.clear(); // Clear screen
  lcd.setCursor(0, 0); // Set cursor to first row
  lcd.print(message); // Show error message
}

void sendAverageTemperature() {
  // Calculate and send average temperature
  if (temperatureReadings > 0) {
    float averageTemperature = totalTemperature / temperatureReadings; // Calculate average

    // Create data and send to databucket
    pson data;
    data["average_temperature"] = averageTemperature;
    thing.write_bucket("BucketId", data); // Replace BucketId with the actual bucket ID

    // Print to serial console
    Serial.print("Average Temperature Sent: ");
    Serial.println(averageTemperature, 1);

    // Reset variables for next calculation cycle
    totalTemperature = 0;
    temperatureReadings = 0;
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize DHT, LCD and LED
  dht.begin(); // Start DHT sensor
  initializeDisplay(); // Setup and activate LCD
  pinMode(LED_PIN, OUTPUT); // Set LED as output
  digitalWrite(LED_PIN, LOW); // Initial LED state: OFF

  // Connect to Thinger.io
  connectToThinger();
}

void loop() {
  // Handle Thinger.io connection
  thing.handle();

  // Read data from DHT sensor
  float temperature = dht.readTemperature(); // Read temperature
  float humidity = dht.readHumidity(); // Read humidity

  // Check for measurement errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 Reading Error");
    displayError("Sensor Error"); // Show error message on LCD
    delay(2000); // Wait before next attempt
    return;
  }

  // Display data on LCD and serial console
  displaySensorData(temperature, humidity);

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  // Add temperature to total for average
  totalTemperature += temperature;
  temperatureReadings++;

  // Check if 5 minutes passed to send average temperature
  if (millis() - lastMeasurementTime >= MEASUREMENT_INTERVAL) {
    sendAverageTemperature(); // Send average temperature
    lastMeasurementTime = millis(); // Update last measurement time
  }

  // Delay before next sensor reading
  delay(2000);
}
