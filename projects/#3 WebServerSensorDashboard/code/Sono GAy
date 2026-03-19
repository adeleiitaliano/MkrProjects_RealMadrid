void loop() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("Nuovo client connesso!");

        String richiesta = "";

        while (client.connected()) {
            if (client.available()) {

                richiesta = client.readStringUntil('\r');
                Serial.println(richiesta);
                client.flush();

                // Controllo LED
                if (richiesta.indexOf("GET /LED=ON") >= 0) {
                    carrier.leds.fill(0, 0, 255);
                    carrier.leds.show();
                }

                if (richiesta.indexOf("GET /LED=OFF") >= 0) {
                    carrier.leds.fill(0, 0, 0);
                    carrier.leds.show();
                }

                // Lettura sensori
                float temperatura = carrier.Env.readTemperature();
                float humidity = carrier.Env.readHumidity();
                float pressione = carrier.Env.readPressure();

                // Risposta HTTP
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println();

                client.println("<!DOCTYPE html>");
                client.println("<html>");

                // HEAD + CSS
                client.println("<head>");
                client.println("<meta http-equiv='refresh' content='2'>");
                client.println("<title>Stazione Meteo</title>");

                client.println("<style>");
                client.println("body {");
                client.println("  font-family: Arial, sans-serif;");
                client.println("  background: linear-gradient(to right, #ffffff, #e6e6e6);");
                client.println("  text-align: center;");
                client.println("  margin: 0;");
                client.println("}");

                client.println("h1 {");
                client.println("  background-color: #0a1f44;"); // blu Real Madrid
                client.println("  color: white;");
                client.println("  padding: 20px;");
                client.println("  margin: 0;");
                client.println("}");

                client.println(".card {");
                client.println("  background: white;");
                client.println("  margin: 20px auto;");
                client.println("  padding: 20px;");
                client.println("  border-radius: 15px;");
                client.println("  width: 80%;");
                client.println("  box-shadow: 0 4px 10px rgba(0,0,0,0.2);");
                client.println("}");

                client.println("h2 {");
                client.println("  color: #0a1f44;");
                client.println("}");

                client.println(".btn {");
                client.println("  background-color: #d4af37;"); // oro
                client.println("  border: none;");
                client.println("  color: white;");
                client.println("  padding: 12px 20px;");
                client.println("  margin: 10px;");
                client.println("  font-size: 16px;");
                client.println("  border-radius: 8px;");
                client.println("  cursor: pointer;");
                client.println("  transition: 0.3s;");
                client.println("}");

                client.println(".btn:hover {");
                client.println("  background-color: #b8962e;");
                client.println("}");
                client.println("</style>");

                client.println("</head>");

                // BODY
                client.println("<body>");
                client.println("<h1> Stazione Meteo Real Madrid</h1>");

                client.println("<div class='card'>");

                client.print("<h2>🌡 Temperatura: ");
                client.print(temperatura);
                client.println(" &deg;C</h2>");

                client.print("<h2> Umidita': ");
                client.print(humidity);
                client.println(" %</h2>");

                client.print("<h2> Pressione: ");
                client.print(pressione);
                client.println(" hPa</h2>");

                client.println("</div>");

                // Pulsanti
                client.println("<a href=\"/LED=ON\"><button class='btn'>Accendi LED</button></a>");
                client.println("<a href=\"/LED=OFF\"><button class='btn'>Spegni LED</button></a>");

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
