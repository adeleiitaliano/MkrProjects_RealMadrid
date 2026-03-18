#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

float tempMin = 0;
float tempMax = 60;
float humMin = 0;
float humMax = 100;
float presMin = 0.95;
float presMax = 1.05;

int lastTempWidth = -1;
int lastHumWidth = -1;
int lastPresWidth = -1;

float lastTemp = -100;
float lastHum = -100;
float lastPres = -100;

void setup()
{
    carrier.begin();
    carrier.display.fillScreen(0x0000);
    carrier.display.setTextSize(2);
    carrier.display.setTextColor(0xFFFF, 0x0000);

    carrier.display.drawRect(20, 35, 200, 15, 0xFFFF);
    carrier.display.drawRect(20, 85, 200, 15, 0xFFFF);
    carrier.display.drawRect(20, 135, 200, 15, 0xFFFF);
}

void loop()
{

    float temperature = carrier.Env.readTemperature();
    float humidity = carrier.Env.readHumidity();
    float pressure_bar = carrier.Pressure.readPressure() / 100.0;

    if ((temperature - lastTemp) > 0.1)
    {

        carrier.display.setCursor(20, 10);
        carrier.display.print("TEMP: ");
        carrier.display.print(temperature, 1);
        carrier.display.print(" C ");

        int tempWidth = (temperature - tempMin) / (tempMax - tempMin) * 198;

        if (tempWidth < 0)
        {
            tempWidth = 0;
        }
        else if (tempWidth > 198)
        {
            tempWidth = 198;
        }
        else
        {
            tempWidth = tempWidth;
        }

        uint16_t color;

        if (temperature <= 20)
        {
            color = 0x07FF;
        }
        else if (temperature > 20 && temperature <= 30)
        {
            color = 0x07E0;
        }
        else
        {
            color = 0xF800;
        }

        if (lastTempWidth != -1)
        {
            carrier.display.fillRect(21, 36, lastTempWidth, 13, 0x0000);
        }
        else
        {
            lastTempWidth = lastTempWidth;
        }

        carrier.display.fillRect(21, 36, tempWidth, 13, color);

        lastTempWidth = tempWidth;
        lastTemp = temperature;
    }

    if ((humidity - lastHum) > 0.2)
    {

        carrier.display.setCursor(20, 60);
        carrier.display.print("HUM: ");
        carrier.display.print(humidity, 1);
        carrier.display.print(" % ");

        int humWidth = (humidity - humMin) / (humMax - humMin) * 198;

        if (humWidth < 0)
        {
            humWidth = 0;
        }
        else if (humWidth > 198)
        {
            humWidth = 198;
        }
        else
        {
            humWidth = humWidth;
        }

        uint16_t color;

        if (humidity < 40)
        {
            color = 0xF800;
        }
        else if (humidity >= 40 && humidity <= 70)
        {
            color = 0x07E0;
        }
        else
        {
            color = 0x07FF;
        }

        if (lastHumWidth != -1)
        {
            carrier.display.fillRect(21, 86, lastHumWidth, 13, 0x0000);
        }
        else
        {
            lastHumWidth = lastHumWidth;
        }

        carrier.display.fillRect(21, 86, humWidth, 13, color);

        lastHumWidth = humWidth;
        lastHum = humidity;
    }

    if ((pressure_bar - lastPres) > 0.002)
    {

        carrier.display.setCursor(20, 110);
        carrier.display.print("PRES: ");
        carrier.display.print(pressure_bar, 3);
        carrier.display.print(" bar ");

        int presWidth = (pressure_bar - presMin) / (presMax - presMin) * 198;

        if (presWidth < 0)
        {
            presWidth = 0;
        }
        else if (presWidth > 198)
        {
            presWidth = 198;
        }
        else
        {
            presWidth = presWidth;
        }

        uint16_t color;

        if (pressure_bar < 1.0)
        {
            color = 0xF800;
        }
        else if (pressure_bar >= 1.0 && pressure_bar <= 1.02)
        {
            color = 0x07E0;
        }
        else
        {
            color = 0xFFE0;
        }

        if (lastPresWidth != -1)
        {
            carrier.display.fillRect(21, 136, lastPresWidth, 13, 0x0000);
        }
        else
        {
            lastPresWidth = lastPresWidth;
        }

        carrier.display.fillRect(21, 136, presWidth, 13, color);

        lastPresWidth = presWidth;
        lastPres = pressure_bar;
    }

    delay(200);
}