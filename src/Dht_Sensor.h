#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 25
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

class Dht_Sensor
{
private:
public:
    Dht_Sensor(/* args */);
    void iniciar_sensor();
    float leer_temperatura();
    float leer_humedad();
};

Dht_Sensor::Dht_Sensor()
{
}

void Dht_Sensor::iniciar_sensor()
{
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
}

float Dht_Sensor::leer_temperatura()
{   
    //sensors_event_t event;
    //dht.temperature().getEvent(&event);
    float temperature = dth.readTemperature();
    if (isnan(temperature)
    {   
        Serial.println("Failed to read from DHT sensor!");
        return -100;
    }
    else
    {
        return temperature;
    }
}


float Dht_Sensor::leer_humedad()
{   
    
    float humidity = dht.readHumidity();
    if (isnan(humidity)){
        Serial.println("Failed to read from DHT sensor!");
        return -100;
    }
    else
    {
        return humidity;   
    }
}
