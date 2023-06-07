// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "SPIFFS.h"

//para hacer peticiones post
#include <ArduinoJson.h>//instalar si no está
#include <HTTPClient.h>//instalar si no está
#include <WiFiMulti.h>
 
WiFiMulti wifiMulti;//para hacer peticiones post

const char *ssid = "CRISTIAN-PC";
const char *password = "12345678";

const int dry = 3360;
const int wet = 1500;
const int pin_cap = 36;
const int pin_rele = 26;

#define DHTPIN 25
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);


// -------------- Functions --------------
String readDHTTemperature() {
  Serial.println(dht.read());

  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    Serial.println("Temperature: " + String(t) + " °C");
    return String(t);
  }
}

String readDHTHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    Serial.println("Humedad: " + String(h) + " %");
    return String(h);
  }
}

String leer_humedad_cap() {
  int sensorVal = analogRead(pin_cap);
  int percentageHumididy = map(sensorVal, dry, wet, 0, 100);
  Serial.println("Humedad Tierra: " + String(percentageHumididy) + " %");
  return String(percentageHumididy);
}

String verificar() {
  float tem = dht.readTemperature();
  float hum = dht.readHumidity();
  int sensorVal = analogRead(pin_cap);
  int perHumididyEar = map(sensorVal, dry, wet, 0, 100);

  if (tem >= 25 && hum < 30 && perHumididyEar < 20) {
    return "1";
  } else if (tem < 20 && hum > 50 || perHumididyEar > 70) {
    return "2";
  } else {
    return "0";
  }
}

String processor(const String &var) {
  if (var == "TEMPERATURE") {
    return readDHTTemperature();
  } else if (var == "HUMIDITY") {
    return readDHTHumidity();
  } else if (var == "HUMIDITYEART") {
    return leer_humedad_cap();
  }
  return String();
}

void postDataToServer() {
 
  Serial.println("Intentando conectar");
  if (wifiMulti.run() == WL_CONNECTED) {
     
    HTTPClient http;   
     
    http.begin("https://back-water-plant-production.up.railway.app/measurements");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;

    //datos
    doc["soilMoisture"] = leer_humedad_cap();
    doc["temperature"] = readDHTTemperature();
    doc["airHumidity"] = readDHTHumidity();
   
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
    else {
     Serial.println("Error al conectar");       
    }
     
  }
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(pin_cap, INPUT);
  pinMode(pin_rele, OUTPUT);
  dht.begin();

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  server.on("/eart", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", leer_humedad_cap().c_str());
  });

  server.on("/verificar", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", verificar().c_str());
  });

  server.begin();

  wifiMulti.addAP(ssid, password);//peticiones post
}

void loop() {
  if (verificar() == "1") {
    Serial.println("Activa Sistema de Riego");
    digitalWrite(pin_rele, HIGH);
    delay(2000);
  }
  else if (verificar() == "0") {
    Serial.println("Desactiva Sistema de Riego");
    digitalWrite(pin_rele, LOW);
    delay(2000);
  }
  else {
    // Lance una interrupción cuando haya demasiada humedad
    // Puede llamar la alarma de sonido aqui
  }

  postDataToServer();//peticiones post

  delay(1000);
}
