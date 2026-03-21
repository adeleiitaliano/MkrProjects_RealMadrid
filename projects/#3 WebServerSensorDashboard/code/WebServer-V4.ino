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

        if (richiesta.indexOf("/LED=ON") >= 0)
            ledAcceso = true;
        if (richiesta.indexOf("/LED=OFF") >= 0)
            ledAcceso = false;

        float temperatura = carrier.Env.readTemperature();
        float umidita = carrier.Env.readHumidity();
        float pressione = carrier.Pressure.readPressure() * 10;

        // Invia tutta la pagina HTML in un solo client.println usando String() per i valori
        client.println(R"rawliteral(
HTTP/1.1 200 OK
Content-type:text/html

<!doctype html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Stazione Metereologica RealMadrid</title>
    <style>
*{
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family:
    "SF Pro Display",
    "Inter",
    -apple-system,
    BlinkMacSystemFont,
    "Segoe UI",
    Roboto,
    sans-serif;
}

body {
  background: linear-gradient(135deg, #89cff0 0%, #a2d9ff 50%, #bfe9ff 100%);
  background-attachment: fixed;
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  color: white;
  position: relative;
  overflow: hidden;
}

.wrapper {
  width: 90vw;
  height: 70vh;
  display: flex;
  flex-direction: column;
  justify-content: center;
  position: relative;
  z-index: 1;
}

header h1 {
  font-size: 4.5vw;
  font-weight: 600;
  margin-bottom: 3vh;
  padding-left: 20px;
  text-shadow: none;
  color: white;
}

.dashboard {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr;
  gap: 2vw;
  height: 50vh;
}

.card {
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(30px);
  -webkit-backdrop-filter: blur(30px);
  border: 2px solid rgba(255, 255, 255, 0.4);
  border-radius: 20px;
  padding: 3vh 3vw;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
  transition: transform 0.2s ease;
}

.card:hover {
  transform: translateY(-5px);
}

.card-header {
  font-size: 1.5vw;
  font-weight: 500;
  display: flex;
  align-items: center;
  gap: 10px;
  opacity: 0.9;
  color: white;
}

.main-stat {
  font-size: 6vw;
  font-weight: 400;
  line-height: 0.9;
  display: flex;
  align-items: baseline;
  color: white;
}

.unit {
  font-size: 2vw;
  margin-left: 5px;
}
.unit-alt {
  font-size: 1.5vw;
  margin-left: 10px;
  opacity: 0.8;
}

.chart-box {
  margin-top: 2vh;
}

.wave-line {
  width: 100%;
  height: 8vh;
  filter: drop-shadow(0 5px 15px rgba(255, 255, 255, 0.4));
}

@media (max-width: 768px) {
  body { overflow-y: auto; }
  .wrapper { height: auto; padding: 40px 20px; }
  .dashboard { grid-template-columns: 1fr; height: auto; }
  .card { height: 400px; margin-bottom: 20px; }
  header h1 { font-size: 10vw; }
  .main-stat { font-size: 25vw; }
  .card-header { font-size: 6vw; }
}
    </style>
  </head>
  <body>
    <div class="wrapper">
      <header>
        <h1 id="greeting">Buongiorno RealMadrid!</h1>
      </header>

      <main class="dashboard">

        <section class="card">
          <div class="card-header"><span class="icon">❤</span> Indoor</div>
          <div class="card-content">
            <div class="main-stat">
              <span class="thermometer">🌡</span>
              <span class="value">)" + String(temperatura, 1) + R"rawliteral(</span><span class="unit">°C</span>
            </div>
          </div>
        </section>

        <section class="card">
          <div class="card-header"><span class="icon">💧</span> Humidity</div>
          <div class="card-content">
            <div class="main-stat">
              <span class="value">)" + String(umidita, 1) + R"rawliteral(</span><span class="unit">%</span>
            </div>
          </div>
        </section>

        <section class="card">
          <div class="card-header"><span class="icon">🔘</span> Barometer</div>
          <div class="card-content">
            <div class="main-stat">
              <span class="drop-outline">⚖️</span>
              <span class="value">)" + String(pressione, 1) + R"rawliteral(</span><span class="unit-alt">Hg</span>
            </div>
            <div class="chart-box">
              <svg viewBox="0 0 200 40" class="wave-line">
                <path d="M0,25 C20,20 40,30 60,25 C80,20 100,35 120,25 C140,15 160,30 180,25 L200,20"
                      fill="none" stroke="white" stroke-width="3" stroke-linecap="round"/>
                <circle cx="10" cy="25" r="3" fill="white" />
                <circle cx="190" cy="22" r="3" fill="white" />
              </svg>
            </div>
          </div>
        </section>

      </main>
    </div>

    <script>
      const greeting = document.getElementById("greeting");
      const hour = new Date().getHours();
      if (hour >= 5 && hour < 12) greeting.textContent = "Good morning";
      else if (hour >= 12 && hour < 18) greeting.textContent = "Good afternoon";
      else greeting.textContent = "Good evening";
    </script>
  </body>
</html>
)rawliteral");

        delay(1);
        client.stop();
        Serial.println("Client disconnesso");
    }
}
