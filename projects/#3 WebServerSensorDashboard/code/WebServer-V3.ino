#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

const char* ssid = "TP-LINK_847074";
const char* password = "24703567";

WiFiServer server(80);

bool ledAcceso = false;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    carrier.begin();

    carrier.leds.setBrightness(50);
    carrier.leds.fill(0, 0, 0);
    carrier.leds.show();

    Serial.println("Connessione WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConnesso!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {

    uint32_t rosso = carrier.leds.Color(255, 0, 0);
    uint32_t spento = carrier.leds.Color(0, 0, 0);

if (ledAcceso) {
    carrier.leds.fill(rosso);
} else {
    carrier.leds.fill(spento);
}
carrier.leds.show();


    WiFiClient client = server.available();

    if (client) {
        Serial.println("Client connesso");

        String richiesta = "";

        while (client.connected()) {
            if (client.available()) {
                richiesta = client.readStringUntil('\n');
                Serial.println(richiesta);
                break;
            }
        }

        if (richiesta.indexOf("/LED=ON") >= 0) {
            ledAcceso = true;
            
        }

        if (richiesta.indexOf("/LED=OFF") >= 0) {
            ledAcceso = false;
          
        }

        float temperatura = carrier.Env.readTemperature();
        float umidita = carrier.Env.readHumidity();
        float pressione = carrier.Pressure.readPressure() * 10;

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();

        client.println("<!DOCTYPE html><html>");

        client.println("<head>");
        client.println("<meta http-equiv='refresh' content='2'>");
        client.println("<title>Stazione Meteo</title>");

        client.println("<style>");
        client.println("body {font-family: Arial; background: linear-gradient(to right, #ffffff, #e6e6e6); text-align: center; margin: 0;}");
        client.println("h1 {background-color: #0a1f44; color: white; padding: 20px;}");
        client.println(".card {background: white; margin: 20px auto; padding: 20px; border-radius: 15px; width: 80%; box-shadow: 0 4px 10px rgba(0,0,0,0.2);}");
        client.println(".btn {background-color: #d4af37; border: none; color: white; padding: 12px 20px; margin: 10px; font-size: 16px; border-radius: 8px; cursor: pointer;}");
        client.println("</style>");
        client.println("</head>");

        client.println("<body>");
        client.println("<h1>Stazione Meteo del Real Madrid</h1>");

        client.println("<div class='card'>");

        client.print("<h2>Temperatura: ");
        client.print(temperatura);
        client.println(" &deg;C</h2>");

        client.print("<h2>Umidita: ");
        client.print(umidita);
        client.println(" %</h2>");

        client.print("<h2>Pressione: ");
        client.print(pressione);
        client.println(" mBar</h2>");

        client.print("<h2>LED: ");
        client.print(ledAcceso ? "ACCESO" : "SPENTO");
        client.println("</h2>");

        client.println("</div>");

        client.println("<a href=\"/LED=ON\"><button class='btn'>Accendi LED</button></a>");
        client.println("<a href=\"/LED=OFF\"><button class='btn'>Spegni LED</button></a>");

        client.println("</body></html>");

        delay(1);
        client.stop();
        Serial.println("Client disconnesso");
    }
}
