#include <Adafruit_Sensor.h>
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "SPIFFS.h"
#include "Dht_Sensor.h"
#include "Capacitive.h"
#include "AsyncTCP.h"

Dht_Sensor sensor_dht;
Capacitive sensor_capacitive;
sensor_t sensor;

// network credentials
const char *ssid = "FLIAGONZALEZ";
const char *password = "10264928";

AsyncWebServer server(80);

String processor(const String &var)
{
    if (var == "TEMPERATURE")
    {
        return sensor_dht.leer_temperatura();
    }
    else if (var == "HUMIDITY")
    {
        return sensor_dht.leer_humedad();
    }
    else if (var == "HUMIDITYEART")
    {
        return sensor_capacitive.leer_humedad();
    }
    return String();
}

String verificar()
{
    float tem = sensor_dht.leer_temperatura().toFloat();
    float hum = sensor_dht.leer_humedad().toFloat();
    
    if (tem > 25 && hum > 30)
    {
        return "1";
    }
    else
    {
        return "0";
    }
}

void setup()
{
    Serial.begin(115200);
    sensor_dht.iniciar_sensor();

    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println(WiFi.localIP());

    // Route to load index.html file
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false, processor); });

    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    // Route to load app.js file
    server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/app.js", String(), false, processor);});

    // Events to change temperature and humidity
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(
                    200,
                    "text/plain",
                    sensor_dht.leer_temperatura().c_str()); });

    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(
                    200,
                    "text/plain",
                    sensor_dht.leer_humedad().c_str()); });

    server.on("/humidityeart", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(
                    200,
                    "text/plain",
                    sensor_capacitive.leer_humedad().c_str()); });
    
    /*server.on("/verificar", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(
                    200,
                    "text/plain",
                    verificar().c_str()); });*/
    server.begin();
}

void loop()
{
    String humedad_tierra = sensor_capacitive.leer_humedad();
    Serial.println("Humedad tierra: " + humedad_tierra + "%");

    String temperatura = sensor_dht.leer_temperatura();
    Serial.println("Temperatura: " + temperatura + "°C");

    String humedad = sensor_dht.leer_humedad();
    Serial.println("Humedad: " + humedad + "%");

    Serial.println("----------------------------------");  
    delay(1000);  
}
