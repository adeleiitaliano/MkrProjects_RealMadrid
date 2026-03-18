#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup()
{
    Serial.begin(9600);
    carrier.noCase();
    carrier.begin();
}

void loop()
{
    float temperature = carrier.Env.readTemperature(); // Reading the values
    float humidity = carrier.Env.readHumidity();
    float pressure = carrier.Pressure.readPressure();
    Serial.println("TEMPERATURA (°C):");
    Serial.println(temperature); // Write the values in Serial Monitor
    Serial.println("UMIDITÀ (%):");
    Serial.println(humidity);
    float conversion = pressure / 100;
    Serial.println("PRESSIONE (Bar):"); // Conversion kPa -- Bar
    Serial.println(conversion);

    delay(3000);
}
