const int dry = 595; // value for dry sensor
const int wet = 0; // value for wet sensor

class Capacitive
{
private:
public:
    Capacitive(/* args */);
    String leer_humedad();
};

Capacitive::Capacitive(/* args */){
}

String Capacitive::leer_humedad()
{
    int sensorVal = analogRead(A5);
    int percentageHumididy = map(sensorVal,dry, wet, 0, 100);
    return String(percentageHumididy);
}


