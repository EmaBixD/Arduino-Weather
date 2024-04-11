////////////////////////////
///  BIASI-WEATHER v1.0  ///
///  by Ivan & Emanuele  ///
////////////////////////////

// This code is for an Arduino UNO that reads data from a BMP280 pressure and temperature sensor
// and an AHT20 humidity and temperature sensor. It prints the sensor readings to the serial
// monitor every 5 seconds.

#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

// Initialize the BMP280 sensor using the I2C interface
Adafruit_BMP280 bmp;

// Create sensor objects for temperature and pressure readings from the BMP280 sensor
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

// Initialize the AHT20 sensor
Adafruit_AHTX0 aht;

void setup() {
  // Set up the serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Initialize the BMP280 sensor
  bmp.begin();

  // Initialize the AHT20 sensor
  aht.begin();

  // Configure the BMP280 sensor with the following settings:
  // - Operating Mode: NORMAL
  // - Temperature oversampling: x2
  // - Pressure oversampling: x16
  // - Filtering: x16
  // - Standby time: 500 ms
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  // Print sensor details for the BMP280 temperature sensor
  //bmp_temp->printSensorDetails();
}

void loop() {
  // Create sensor event objects to store the sensor readings
  sensors_event_t humidity, temp, temp_event, pressure_event;

  // Get the sensor readings from the BMP280 sensor
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);

  // Get the sensor readings from the AHT20 sensor
  aht.getEvent(&humidity, &temp);

  // Print the sensor readings to the serial monitor
 
