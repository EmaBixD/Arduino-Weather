////////////////////////////
///  BIASI-WEATHER v1.0  ///
///  by Ivan & Emanuele  ///
////////////////////////////

// For Arduino UNO + AHT20 + BMP280

#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

// INIZIALIZZAZIONE SENSORI
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
Adafruit_AHTX0 aht;

void setup() {
  // CONFIGURAZIONE
  Serial.begin(115200);
  bmp.begin();
  aht.begin();

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //bmp_temp->printSensorDetails();  
}

void loop() {
  sensors_event_t humidity, temp, temp_event, pressure_event;
  
  bmp_temp->getEvent(&temp_event); bmp_pressure->getEvent(&pressure_event); // Ottieni dati dal sensore bmp
  aht.getEvent(&humidity, &temp);  // Ottieni dati dal sensore aht

  // SERIAL PRINT DEBUG
  Serial.print("Temperature 1: "); Serial.print(temp.temperature); Serial.println(" *C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  Serial.println();
  Serial.print(F("Temperature 2: ")); Serial.print(temp_event.temperature); Serial.println(" *C");
  Serial.print(F("Pressure: ")); Serial.print(pressure_event.pressure); Serial.println(" hPa");
  Serial.println("------------------------------");
  
  delay(5000);
}
