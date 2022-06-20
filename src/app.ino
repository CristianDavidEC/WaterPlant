#include <Adafruit_Sensor.h>
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "SPIFFS.h"

#include "Dht_Sensor.h"
#include "Capacitive.h"

Dht_Sensor sensor_dht;
Capacitive sensor_capacitive;
sensor_t sensor;


// network credentials
const char* ssid = "FLIAGONZALEZ";
const char* password = "10264928";

AsyncWebServer server(80);

void setup()
{   
    Serial.begin(105200);
    sensor_dht.iniciar_sensor();
}

void loop(){
    int humedad_tierra = sensor_capacitive.leer_humedad();
    Serial.println("Humedad tierra: " + String(humedad_tierra)+"%");

    float temperatura = sensor_dht.leer_temperatura();
    Serial.println("Temperatura: " + String(temperatura)+"°C");
    delay(1000);

    float humedad = sensor_dht.leer_humedad();
    Serial.println("Humedad: " + String(humedad)+"%");

    Serial.println("----------------------------------");
}