#include <FastLED.h>
#define NUM_LEDS 37
CRGB leds[NUM_LEDS];

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "WLAN NAME";
const char* password = "WLAN PASSWORD";

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML>
  <html>
    <head>
      <title>
        HTML Form to Input Data
      </title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body {
          width: 100vw;
          height: 100vh;
          overflow: hidden
        }
        body,form {
          display:flex;
          align-items:center;
          justify-content:center;
          flex-direction:column
        }
        div>input {
          width: 40px;
          height: 40px;
        }
        input:checked {
          background: red;
        }
      </style>
    </head>
    <body>
      <form action="/get">
        <div>
          <input type="checkbox" name="led0">
          <input type="checkbox" name="led1">
          <input type="checkbox" name="led2">
          <input type="checkbox" name="led3">
        </div>
        <div>
          <input type="checkbox" name="led4">
          <input type="checkbox" name="led5">
          <input type="checkbox" name="led6">
          <input type="checkbox" name="led7">
          <input type="checkbox" name="led8">
        </div>
        <div>
          <input type="checkbox" name="led9">
          <input type="checkbox" name="led10">
          <input type="checkbox" name="led11">
          <input type="checkbox" name="led12">
          <input type="checkbox" name="led13">
          <input type="checkbox" name="led14">
        </div>
        <div>
          <input type="checkbox" name="led15">
          <input type="checkbox" name="led16">
          <input type="checkbox" name="led17">
          <input type="checkbox" name="led18">
          <input type="checkbox" name="led19">
          <input type="checkbox" name="led20">
          <input type="checkbox" name="led21">
        </div>
        <div>
          <input type="checkbox" name="led22">
          <input type="checkbox" name="led23">
          <input type="checkbox" name="led24">
          <input type="checkbox" name="led25">
          <input type="checkbox" name="led26">
          <input type="checkbox" name="led27">
        </div>
        <div>
          <input type="checkbox" name="led28">
          <input type="checkbox" name="led29">
          <input type="checkbox" name="led30">
          <input type="checkbox" name="led31">
          <input type="checkbox" name="led32">
        </div>
        <div>
          <input type="checkbox" name="led33">
          <input type="checkbox" name="led34">
          <input type="checkbox" name="led35">
          <input type="checkbox" name="led36">
        </div>
        <input type="color" name="colorPicker">
        <input type="submit" value="Submit">
      </form>
    </body>
  </html>
)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Connected");
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String hexstring = request->getParam("colorPicker")->value();
    long number = strtol( &hexstring[1], NULL, 16);
    long r = number >> 16;
    long g = number >> 8 & 0xFF;
    long b = number & 0xFF;
    
    for (int i=0;i<NUM_LEDS;i++) {
        if (request->hasParam("led"+String(i))) {
          String param = request->getParam("led"+String(i))->value();
          if (param == "on") {
            leds[i].setRGB(r, g, b);
          }
        }
    }
    FastLED.show();
    request->redirect("/");
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
