#include <WiFiMulti.h>
#include <WebSocketsClient.h>
#include "Color.h"
#include "LedRGB.h"

// Settings
#define SSID ""
#define PASSWORD ""

#define SOCKET_HOST ""
#define SOCKET_RES "/"
#define SOCKET_PORT 80

#define R_PIN 13
#define G_PIN A1
#define B_PIN A0
#define SHAKE_PIN A3

#define DEFAULT_COLOR "#FF3000"



// Globals
WiFiMulti wifiMulti;
WebSocketsClient webSocket;

Color userColor = Color::hex(DEFAULT_COLOR);
LedRGB ledRGB;

float brightness = 0;

float t_fade_ms = 60000;
unsigned long dt_ms = 10;
float d_bright = 1.0 / (t_fade_ms / dt_ms);




void webSocketCallback(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_CONNECTED:
      Serial.println("Connected to socket.");
      break;

    case WStype_TEXT:
      Serial.printf("New message: %s\n", payload);

      // New Color command
      if (payload[0] == '#')
      {
        userColor = Color::hex((const char *)payload);
        brightness = 1;
      }
      else if (payload[0] == '1')
        brightness = 1;

      // Action commands
      switch (payload[0])
      {
        case '#':
          userColor = Color::hex((const char *)payload);
        case '1':
          brightness = 1;
          break;
        case '2':
          brightness -= 0.5;
          if(brightness < 0)
            brightness = 0;
          break;
        case '3':
          flash();
          brightness = 1;
          break;
        case '4':
          cycle();
          brightness = 1;
          break;
      }

  }
}

void flash()
{
  auto time = millis();
  while(millis() < time  + 500)
  {
    auto rand = random(5, 50);
    ledRGB.write(userColor, rand%2);
    delay(rand);
  }
}

void cycle()
{
  auto time = millis();
  double hue = 0;
  while(millis() < time  + 3000)
  {
    hue += 3;
    ledRGB.write(Color::hsv(hue, 1, 1));
    delay(dt_ms);
  }
}

void setup()
{
  // Serial setup
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("Staff start\n");

  // Setting up RGB leds
  ledRGB.begin(R_PIN, G_PIN, B_PIN, Color::hex(DEFAULT_COLOR));

  pinMode(SHAKE_PIN, INPUT_PULLUP);

  // Wifi Setup
  Serial.println("Connecting to WiFi ...");
  wifiMulti.addAP(SSID, PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED)
    delay(100);
  Serial.println("Success!\n");

  // Websocket setup
  webSocket.begin(SOCKET_HOST, SOCKET_PORT, SOCKET_RES);
  webSocket.onEvent(webSocketCallback);
  webSocket.setReconnectInterval(1000);
}

void loop()
{
  webSocket.loop();

  if (digitalRead(SHAKE_PIN) == LOW)
    brightness = 1;

  ledRGB.write(userColor, brightness);

  brightness -= d_bright;
  if (brightness < 0)
    brightness = 0;

  // Hard reset every hour
  if (millis() > 1000 * 1800)
    ESP.restart();

  delay(dt_ms);
}
