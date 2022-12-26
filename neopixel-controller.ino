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

const char* ssid = "WLAN ADDRESS";
const char* password = "WLAN PASSWORD";  
String hexstring;
int number;
int r;
int g;
int b;
int i;

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
          <input type="checkbox" name="0">
          <input type="checkbox" name="1">
          <input type="checkbox" name="2">
          <input type="checkbox" name="3">
        </div>
        <div>
          <input type="checkbox" name="4">
          <input type="checkbox" name="5">
          <input type="checkbox" name="6">
          <input type="checkbox" name="7">
          <input type="checkbox" name="8">
        </div>
        <div>
          <input type="checkbox" name="9">
          <input type="checkbox" name="10">
          <input type="checkbox" name="11">
          <input type="checkbox" name="12">
          <input type="checkbox" name="13">
          <input type="checkbox" name="14">
        </div>
        <div>
          <input type="checkbox" name="15">
          <input type="checkbox" name="16">
          <input type="checkbox" name="17">
          <input type="checkbox" name="18">
          <input type="checkbox" name="19">
          <input type="checkbox" name="20">
          <input type="checkbox" name="21">
        </div>
        <div>
          <input type="checkbox" name="22">
          <input type="checkbox" name="23">
          <input type="checkbox" name="24">
          <input type="checkbox" name="25">
          <input type="checkbox" name="26">
          <input type="checkbox" name="27">
        </div>
        <div>
          <input type="checkbox" name="28">
          <input type="checkbox" name="29">
          <input type="checkbox" name="30">
          <input type="checkbox" name="31">
          <input type="checkbox" name="32">
        </div>
        <div>
          <input type="checkbox" name="33">
          <input type="checkbox" name="34">
          <input type="checkbox" name="35">
          <input type="checkbox" name="36">
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
    request->send_P(200, "text/html", index_html);
  });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    hexstring = request->getParam("colorPicker")->value();
    number = strtol( &hexstring[1], NULL, 16);
    r = number >> 16;
    g = number >> 8 & 0xFF;
    b = number & 0xFF;
    
    for (i=0;i<NUM_LEDS;i++) {
        if (request->hasParam(String(i))) {
          leds[i].setRGB(r, g, b);
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
