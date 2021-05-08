#include "DHT.h"

/************************** Config. comunicacion ***********************************/
/************************ Adafruit IO Config *******************************/

#define IO_USERNAME "xxxxxxxxxx" // Nombre de usuario // NO QUITAR ""
#define IO_KEY "xxxxxxxxxxxxxxxx" // Clave activa // NO QUITAR ""

/******************************* WIFI **************************************/

#define WIFI_SSID "XXXXXXXX" // SSID del wifi al que conectaremos el modulo ESP8266 // NO QUITAR ""
#define WIFI_PASS "xxxxxxxxxxxxxxxx" // Password de la wifi // NO QUITAR ""

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Example Starts Here *******************************/

#define DHTPIN D1 // Pin digital al que conectaremos el DHT11
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

AdafruitIO_Feed *temperatura = io.feed("temperatura");
AdafruitIO_Feed *humedad = io.feed("humedad");

void setup() {
  
  Serial.begin(115200);
  while(! Serial);
  Serial.print("Conectando a Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  
  dht.begin();
}

void loop() {
  delay(5000); // Frecuencia a la que se suben los datos a adafruit. 
  io.run();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("temperatura: ");
  Serial.print(t);
  Serial.print(" humedad: ");
  Serial.println(h);
  temperatura->save(t);
  humedad->save(h); 
 
}
