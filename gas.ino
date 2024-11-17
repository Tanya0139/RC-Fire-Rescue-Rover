#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MQUnifiedsensor.h>

// Define SSID and Password for AP
const char *ssid = "ESP32_AP";
const char *password = "123456789";

// Pin Definitions
#define ONE_WIRE_BUS 4  // DS18B20 temperature sensor
#define MQ2_PIN 2       // MQ2 Gas sensor analog pin (D2)
#define IR_PIN 5        // IR sensor pin
#define LASER_PIN 13    // Laser module pin (D13)

// Temperature Sensor setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// MQ2 Sensor Constants
#define Board "ESP-32"
#define Type "MQ-2"
#define Voltage_Resolution 5.0
#define ADC_Bit_Resolution 10
#define RatioMQ2CleanAir 9.83
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, MQ2_PIN, Type);

// Variables for sensor data
float temperature;
float gas_lpg, gas_methane, gas_butane, gas_hydrogen, gas_smoke, gas_alcohol;
bool object_detected = false;

// HTML for Web Page
String htmlPage = "";

// Create Access Point and Web Server
WiFiServer server(80);

void setup() {
  // Serial Communication
  Serial.begin(115200);
  
  // Start temperature sensor
  sensors.begin();

  // MQ2 Sensor initialization
  MQ2.setRegressionMethod(1);  // Set the regression method to MQUnifiedsensor
  MQ2.init();
  
  // Set gas curves for different gases
  MQ2.setA(574.25); MQ2.setB(-2.222);  // LPG
  MQ2.setA(375.34); MQ2.setB(-3.178);  // Methane
  MQ2.setA(685.83); MQ2.setB(-2.431);  // Butane
  MQ2.setA(102.2); MQ2.setB(-2.473);   // Hydrogen
  MQ2.setA(48.64); MQ2.setB(-3.363);   // Alcohol
  MQ2.setA(2.3); MQ2.setB(-0.43);      // Smoke
  
  // Configure IR and Laser pin
  pinMode(IR_PIN, INPUT);
  pinMode(LASER_PIN, OUTPUT);
  digitalWrite(LASER_PIN, LOW);  // Turn off the laser at the start
  
  // Create Access Point
  WiFi.softAP(ssid, password);
  Serial.print("Access Point started. IP: ");
  Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
}

void loop() {
  // Read temperature data
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  
  // Read gas levels
  MQ2.update();
  gas_lpg = MQ2.readSensor();     // LPG
  gas_methane = MQ2.readSensor(); // Methane
  gas_butane = MQ2.readSensor();  // Butane
  gas_hydrogen = MQ2.readSensor();// Hydrogen
  gas_alcohol = MQ2.readSensor(); // Alcohol
  gas_smoke = MQ2.readSensor();   // Smoke
  
  // Read IR sensor for object detection
  object_detected = digitalRead(IR_PIN);

  // Handle client connections
  WiFiClient client = server.available();
  if (client) {
    // Read the client request
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/findme") != -1) {
      activateLaser(client);  // Activate the laser when the "Find Me" button is pressed
    } else if (request.indexOf("/data") != -1) {
      sendSensorData(client); // Send sensor data in JSON format for real-time updates
    } else {
      htmlPage = prepareHTMLPage();
      
      // Send the response to the client
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println("Connection: close");
      client.println();
      client.println(htmlPage);
      client.println();
    }
    delay(1);
    client.stop();
  }
}

// Function to send sensor data in JSON format (for real-time updates)
void sendSensorData(WiFiClient client) {
  String jsonResponse = "{";
  jsonResponse += "\"temperature\":" + String(temperature) + ",";
  jsonResponse += "\"gas_lpg\":" + String(gas_lpg) + ",";
  jsonResponse += "\"gas_methane\":" + String(gas_methane) + ",";
  jsonResponse += "\"gas_butane\":" + String(gas_butane) + ",";
  jsonResponse += "\"gas_hydrogen\":" + String(gas_hydrogen) + ",";
  jsonResponse += "\"gas_alcohol\":" + String(gas_alcohol) + ",";
  jsonResponse += "\"gas_smoke\":" + String(gas_smoke) + ",";
  jsonResponse += "\"object_detected\":" + String(object_detected ? 1 : 0);
  jsonResponse += "}";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: application/json");
  client.println("Connection: close");
  client.println();
  client.println(jsonResponse);
}

// Function to handle the 'Find Me' feature (turn laser on for a few seconds)
void activateLaser(WiFiClient client) {
  // Turn on the laser
  digitalWrite(LASER_PIN, HIGH);
  
  // Send a confirmation message
  String response = "{\"message\": \"Laser activated for 5 seconds!\"}";
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: application/json");
  client.println("Connection: close");
  client.println();
  client.println(response);

  // Keep laser on for 5 seconds then turn it off
  delay(5000);
  digitalWrite(LASER_PIN, LOW);
}

// Function to serve the HTML page
String prepareHTMLPage() {
  String page = "<html><head><title>ESP32 Gas and Temperature Monitoring</title>";
  
  // Improved CSS Styling
  page += "<style>";
  page += "body{font-family: Arial, sans-serif; margin: 0; padding: 0; background-color: #f4f4f4; color: #333;}";
  page += "h1{background-color: #4CAF50; color: white; padding: 15px; margin: 0;}";
  page += ".container{width: 90%; margin: 20px auto; max-width: 1200px;}";
  page += ".data-block{background-color: white; box-shadow: 0 0 10px rgba(0,0,0,0.1); padding: 20px; margin: 15px 0; border-radius: 10px;}";
  page += ".data-block p{font-size: 18px;}";
  page += ".red{color: red; font-weight: bold;}";
  page += "button{background-color: #4CAF50; color: white; border: none; padding: 10px 20px; font-size: 18px; cursor: pointer; border-radius: 5px;}";
  page += "button:hover{background-color: #45a049;}";
  page += "</style></head>";
  
  // Body and content
  page += "<body>";
  page += "<h1>ESP32 Gas and Temperature Monitoring System</h1>";
  page += "<div class='container'>";
  
  // Display temperature
  page += "<div class='data-block'><p>Temperature: <span id='temperature'></span> &#8451;</p></div>";
  
  // Display Gas Levels and mark red if detected
  page += "<div class='data-block'><p>LPG: <span id='gas_lpg'></span> ppm</p></div>";
  page += "<div class='data-block'><p>Methane: <span id='gas_methane'></span> ppm</p></div>";
  page += "<div class='data-block'><p>Butane: <span id='gas_butane'></span> ppm</p></div>";
  page += "<div class='data-block'><p>Hydrogen: <span id='gas_hydrogen'></span> ppm</p></div>";
  page += "<div class='data-block'><p>Alcohol: <span id='gas_alcohol'></span> ppm</p></div>";
  page += "<div class='data-block'><p>Smoke: <span id='gas_smoke'></span> ppm</p></div>";
  
  // Object detection alert
  page += "<div class='data-block'><p>IR Sensor: <span id='object_detected'></span></p></div>";

  // Find Me Button
  page += "<div class='data-block'><button onclick='findMe()'>Find Me</button></div>";
  
  // JavaScript to trigger the laser and real-time data updates
  page += "<script>";
  page += "setInterval(function() {fetch('/data').then(res => res.json()).then(data => {";
  page += "document.getElementById('temperature').innerHTML = data.temperature;";
  page += "document.getElementById('gas_lpg').innerHTML = data.gas_lpg;";
  page += "document.getElementById('gas_methane').innerHTML = data.gas_methane;";
  page += "document.getElementById('gas_butane').innerHTML = data.gas_butane;";
  page += "document.getElementById('gas_hydrogen').innerHTML = data.gas_hydrogen;";
  page += "document.getElementById('gas_alcohol').innerHTML = data.gas_alcohol;";
  page += "document.getElementById('gas_smoke').innerHTML = data.gas_smoke;";
  page += "document.getElementById('object_detected').innerHTML = data.object_detected ? 'Object Detected' : 'No Object Detected';";
  page += "});}, 1000);";
  page += "function findMe() { fetch('/findme'); }";
  page += "</script>";
  
  page += "</div></body></html>";
  return page;
}
