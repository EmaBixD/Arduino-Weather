////////////////////////////////
///  BIASI-WEATHER ETH v1.0  ///
///    by Ivan & Emanuele    ///
////////////////////////////////

// For Arduino UNO + BMP280 + AHT20 + Ethernet shield

#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <Ethernet.h>

Adafruit_BMP280 bmp; // Use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
Adafruit_AHTX0 aht;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 99);
EthernetServer server(80);

void setup() {
  Serial.begin(115200);
  bmp.begin();
  aht.begin();
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  sensors_event_t humidity, temp, temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event); bmp_pressure->getEvent(&pressure_event); // Ottieni dati dal sensore bmp
  aht.getEvent(&humidity, &temp);  // Ottieni dati dal sensore aht

  float h = humidity.relative_humidity;
  float p = pressure_event.pressure;
  float t1 = temp.temperature;
  float t2 = temp_event.temperature;
  float tavg = (t1+t2)/2;

  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char character = client.read();
        Serial.write(character);
        if (character == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<body>");

          client.print("<h1 style='color: orange;'>Temperature I: ");
          client.print(t1);
          client.print(" *C</h1>");

          client.print("<h1 style='color: orange;'>Temperature II: ");
          client.print(t2);
          client.print(" *C</h1>");

          client.print("<h1 style='color: red;'>Temperature AVG: ");
          client.print(tavg);
          client.print(" *C</h1>");

          client.print("<h1 style='color: blue;'>Humidity: ");
          client.print(h);
          client.print(" %</h1>");

          client.print("<h1 style='color: green;'>Pressure: ");
          client.print(p);
          client.print(" mBar</h1>");
          //client.print("<img src='https://s1.piq.land/2013/08/09/pNIRXHnlRONEKFmLzYN0U0fP_400x400.png' alt='Description of the image' width='16' height='16'>"); // Way to add images

          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (character == '\n') {
          currentLineIsBlank = true;
        } else if (character != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}
