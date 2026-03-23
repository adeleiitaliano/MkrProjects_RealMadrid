#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

const char *ssid = "TP-LINK_847074";
const char *password = "24703567";

WiFiServer server(80);

bool ledAcceso = false;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    carrier.begin();

    carrier.leds.setBrightness(50);
    carrier.leds.fill(0, 0, 0);
    carrier.leds.show();

    Serial.println("Connessione WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnesso!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop()
{
    uint32_t rosso = carrier.leds.Color(255, 0, 0);
    uint32_t spento = carrier.leds.Color(0, 0, 0);

    if (ledAcceso) {
        carrier.leds.fill(rosso);
    } else {
        carrier.leds.fill(spento);
    }
    carrier.leds.show();

    WiFiClient client = server.available();
    if (client)
    {
        Serial.println("Client connesso");
        String richiesta = "";
        while (client.connected())
        {
            if (client.available())
            {
                richiesta = client.readStringUntil('\n');
                Serial.println(richiesta);
                break;
            }
        }

        if (richiesta.indexOf("/LED=ON") >= 0) ledAcceso = true;
        if (richiesta.indexOf("/LED=OFF") >= 0) ledAcceso = false;

        float temperatura = carrier.Env.readTemperature();
        float umidita = carrier.Env.readHumidity();
        float pressione = carrier.Pressure.readPressure() * 10;

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();

        client.print(R"rawliteral(
<!doctype html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="refresh" content="2">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Stazione Metereologica RealMadrid</title>
    <style>
      *{ margin: 0; padding: 0; box-sizing: border-box; font-family: "SF Pro Display", "Inter", sans-serif; }
      body {
        background: linear-gradient(135deg, #89cff0 0%, #a2d9ff 50%, #bfe9ff 100%);
        background-attachment: fixed; min-height: 100vh; display: flex;
        justify-content: center; align-items: center; color: white; position: relative; overflow: hidden;
      }
      .wrapper { width: 90vw; height: 75vh; display: flex; flex-direction: column; justify-content: center; position: relative; z-index: 1; }
      header h1 { font-size: 4.5vw; font-weight: 600; margin-bottom: 3vh; padding-left: 20px; color: white; }
      .dashboard { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 2vw; height: 50vh; }
      .card {
        background: rgba(255, 255, 255, 0.2); backdrop-filter: blur(30px);
        -webkit-backdrop-filter: blur(30px); border: 2px solid rgba(255, 255, 255, 0.4);
        border-radius: 20px; padding: 3vh 3vw; display: flex; flex-direction: column;
        justify-content: center; align-items: center; box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
        transition: transform 0.2s ease; text-decoration: none; color: white;
      }
      .card:hover { transform: translateY(-5px); }
      .card-header { font-size: 1.5vw; font-weight: 500; display: flex; align-items: center; gap: 10px; opacity: 0.9; }
      .main-stat { font-size: 6vw; font-weight: 400; line-height: 0.9; display: flex; align-items: baseline; }
      .unit { font-size: 2vw; margin-left: 5px; }
      .unit-alt { font-size: 1.5vw; margin-left: 10px; opacity: 0.8; }
      .wave-line { width: 100%; height: 8vh; filter: drop-shadow(0 5px 15px rgba(255, 255, 255, 0.4)); }
      
      /* Stile Bottone LED */
      .btn-container { display: flex; justify-content: flex-end; margin-top: 3vh; }
      .card-btn { height: 12vh; width: 22vw; font-size: 1.4vw; font-weight: 600; cursor: pointer; }
      .led-status-on { background: rgba(255, 255, 255, 0.4); border: 2px solid #fff; }

      @media (max-width: 768px) {
        body { overflow-y: auto; } .wrapper { height: auto; padding: 40px 20px; }
        .dashboard { grid-template-columns: 1fr; height: auto; }
        header h1 { font-size: 10vw; } .main-stat { font-size: 25vw; }
        .card-btn { width: 100%; height: 80px; font-size: 5vw; }
      }
    </style>
  </head>
  <body>
    <div class="wrapper">
      <header><h1 id="greeting">Buongiorno RealMadrid!</h1></header>
      <main class="dashboard">
        <section class="card">
          <div class="card-header">🌡 Indoor</div>
          <div class="main-stat"><span>)rawliteral");
        client.print(temperatura, 1);
        client.print(R"rawliteral(</span><span class="unit">°C</span></div>
        </section>

        <section class="card">
          <div class="card-header">☁︎ Humidity</div>
          <div class="main-stat"><span>)rawliteral");
        client.print(umidita, 1);
        client.print(R"rawliteral(</span><span class="unit">%</span></div>
        </section>

        <section class="card">
          <div class="card-header">⛰︎ Barometer</div>
          <div class="main-stat"><span>)rawliteral");
        client.print(pressione, 0);
        client.print(R"rawliteral(</span><span class="unit-alt">kPa</span></div>
        </section>
      </main>

      <div class="btn-container">
)rawliteral");

        if (ledAcceso) {
            client.print("<a href=\"/LED=OFF\" class=\"card card-btn led-status-on\">LED: ACCESO</a>");
        } else {
            client.print("<a href=\"/LED=ON\" class=\"card card-btn\">LED: SPENTO</a>");
        }

        client.print(R"rawliteral(
      </div>
    </div>
    <script>
      const greeting = document.getElementById("greeting");
      const hour = new Date().getHours();
      if (hour >= 5 && hour < 12) greeting.textContent = "Buongiorno RealMadrid!";
      else if (hour >= 12 && hour < 18) greeting.textContent = "Buon pomeriggio RealMadrid!";
      else greeting.textContent = "Buonasera RealMadrid!";
    </script>
  </body>
</html>
)rawliteral");

        delay(100);
        client.stop();
        Serial.println("Client disconnesso");
    }
}
