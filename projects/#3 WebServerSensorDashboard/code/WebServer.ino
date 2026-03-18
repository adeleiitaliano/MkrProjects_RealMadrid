#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;
const char* ssid = "TP-LINK_847074";
const char* password = "24703567";

WiFiServer server(80); // Avvia un server sulla porta 80

void setup() {
    Serial.begin(115200);
    while (!Serial);

    carrier.begin();
    Serial.println("Connessione al WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConnesso!");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());

    server.begin(); // Avvia il server
    
}

void loop() {
    WiFiClient client = server.available(); // Controlla se ci sono client connessi
    

    if (client) {
        Serial.println("Nuovo client connesso!");

        while (client.connected()) {
            if (client.available()) {
                float temperatura = carrier.Env.readTemperature();
                float humidity = carrier.Env.readHumidity();

                String richiesta = client.readStringUntil('\r');
                Serial.println(richiesta);
                client.flush();

                // Invia una risposta HTTP
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println();
                client.println("<!DOCTYPE html>");
                client.println("<html>");
                client.println("<head>");
                client.println("<meta http-equiv='refresh' content='2'>");
                client.println("<title>Stazione Meteo</title>");
                client.println("</head>");
                client.println("<body>");

                client.println("<h1>Stazione Meteo Arduino</h1>");
                client.print("<h2>Temperatura: ");
                client.print(temperatura);
                client.println(" &deg;C</h2>");
                client.print("<h2>Umidita': ");
                client.print(humidity);
                client.println(" %</h2>");

                client.println("</body>");
                client.println("</html>");
                client.println();
                break;
            }
        }
        client.stop();
        Serial.println("Client disconnesso");
    }
}