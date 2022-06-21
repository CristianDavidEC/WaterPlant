#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 25
#define DHTTYPE DHT11

DHT dht_sen(DHTPIN, DHTTYPE);
uint32_t delayMS;

class Dht_Sensor
{
private:
public:
    Dht_Sensor(/* args */);
    void iniciar_sensor();
    String leer_temperatura();
    String leer_humedad();
};

Dht_Sensor::Dht_Sensor()
{
}

void Dht_Sensor::iniciar_sensor()
{
    dht_sen.begin();
    sensor_t sensor;
}

String Dht_Sensor::leer_temperatura(){   
    float temperature = dht_sen.readTemperature();
    if (isnan(temperature)){   
        return "Failed to read from DHT sensor!";
    }
    else
    {
        return String(temperature);
    }
}

String Dht_Sensor::leer_humedad() {   
    float humidity = dht_sen.readHumidity();
    if (isnan(humidity)){
        return "Failed to read from DHT sensor!";
    }
    else
    {
        return String(humidity);   
    }
}
