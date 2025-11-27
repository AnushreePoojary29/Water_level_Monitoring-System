#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h" // Import the HTML web page

// ---------------------------------------------------------
// CONFIGURATION
// ---------------------------------------------------------
const char* ssid = "YOUR_WIFI_SSID";         // <--- CHANGE THIS
const char* password = "YOUR_WIFI_PASSWORD"; // <--- CHANGE THIS

// Pin Definitions
#define TRIG_PIN D1  // GPIO 5
#define ECHO_PIN D2  // GPIO 4

// Tank Configuration
const int TANK_HEIGHT_CM = 20; // Total height of the tank in cm (Adjust as needed)
const int SENSOR_OFFSET_CM = 2; // Distance from sensor to max water level (gap)

// ---------------------------------------------------------
// GLOBALS
// ---------------------------------------------------------
ESP8266WebServer server(80);
long duration;
int distance;
int waterLevelPercent;

// ---------------------------------------------------------
// SENSOR FUNCTIONS
// ---------------------------------------------------------
void measureWaterLevel() {
  // Clear Trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Trigger Pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read Echo
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate Distance (Speed of sound = 0.034 cm/us)
  distance = duration * 0.034 / 2;
  
  // Calculate Percentage
  // Level = Total Height - (Measured Distance - Offset)
  // Note: As water rises, distance decreases.
  
  int waterHeight = TANK_HEIGHT_CM - distance;
  if (waterHeight < 0) waterHeight = 0;
  
  waterLevelPercent = (waterHeight * 100) / TANK_HEIGHT_CM;
  
  // Clamp values
  if (waterLevelPercent > 100) waterLevelPercent = 100;
  if (waterLevelPercent < 0) waterLevelPercent = 0;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Level: ");
  Serial.print(waterLevelPercent);
  Serial.println("%");
}

// ---------------------------------------------------------
// WEB SERVER HANDLERS
// ---------------------------------------------------------
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void handleData() {
  measureWaterLevel(); // Get fresh reading
  
  String json = "{";
  json += "\"distance\":" + String(distance) + ",";
  json += "\"level\":" + String(waterLevelPercent);
  json += "}";
  
  server.send(200, "application/json", json);
}

// ---------------------------------------------------------
// SETUP
// ---------------------------------------------------------
void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Setup Server
  server.on("/", handleRoot);
  server.on("/data", handleData);
  
  server.begin();
  Serial.println("HTTP server started");
}

// ---------------------------------------------------------
// LOOP
// ---------------------------------------------------------
void loop() {
  server.handleClient();
}
