const int dry = 595; // value for dry sensor
const int wet = 200; // value for wet sensor

class Capacitive
{
private:
public:
    Capacitive(/* args */);
    int leer_humedad();
};

Capacitive::Capacitive(/* args */){
}

int Capacitive::leer_humedad()
{
    int sensorVal = analogRead(A5);
    int percentageHumididy = map(sensorVal, wet, dry, 100, 0);
    return percentageHumididy;
}


