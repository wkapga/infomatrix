/*
D1	 data pin to ws2812

D2	Button1	
D3	Button2

D5	Led1 
D6	Led2
*/

#include "secret.h" 
#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <Bounce2.h>
//#include <NTPClient.h>
#include <ezTime.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include <FastLED_GFX.h>
#include <LEDMatrix.h>

#define BUTTON_PIN1 D2
#define BUTTON_PIN2 D3
#define LED_PIN1 D5
#define LED_PIN2 D6
#define MATRIXPIN D1

// WIFI parameters from "secret.h"
const char* SSID = MYWIFISSID;
const char* PASSWORD = MYWIFIPASS;

// MQTT Config
const char* BROKER_MQTT = MYMQTTBROKER; // MQTT Broker IP 
int BROKER_PORT = 1883;
WiFiClient espClient;
PubSubClient MQTT(espClient); 

long lastMsg = 0;
char msg[50];
/*
// ntp 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 60000);
*/
Timezone Austria;

// bounce
Bounce debouncer1 = Bounce(); // Instantiate a Bounce object
Bounce debouncer2 = Bounce(); // Instantiate a Bounce object

// machine state
int state = 0; //state of the machine
const int maxstate = 1; // highest possible state

//matrix
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MATRIX_WIDTH   8 // width of matrix
#define MATRIX_HEIGHT  32 // height of matrix

// #define MATRIX_TYPE    (MTX_MATRIX_TOP + MTX_MATRIX_RIGHT + MTX_MATRIX_COLUMNS +MTX_MATRIX_ZIGZAG ) // matrix layout flags, add together as needed

#define MATRIX_TYPE         HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS MATRIX_SIZE

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> matrix;

void setup() {
   
  initPins();
  initSerial();
  initWiFi();
  initNTP();
  initMQTT();
  initMatrix();
}


void initPins() {
  pinMode(LED_PIN1,OUTPUT); // Setup the LED
//  digitalWrite(LED_PIN1,ledState1);
  pinMode(LED_PIN2,OUTPUT); // Setup the LED
//  digitalWrite(LED_PIN2,ledState2);
  
// pinMode(RELAY1,OUTPUT); 
//  digitalWrite(RELAY1,ledState1);

  debouncer1.attach(BUTTON_PIN1,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer1.interval(25); // Use a debounce interval of 25 milliseconds
  debouncer2.attach(BUTTON_PIN2,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer2.interval(25); // Use a debounce interval of 25 milliseconds
}

void initSerial() {
  Serial.begin(115200);
}

void initWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting: ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD); // Wifi Connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print(SSID);
  Serial.println(" | IP ");
  Serial.println(WiFi.localIP());
}

void initNTP() {
   //timeClient.begin();
   waitForSync();

  Serial.println("UTC: " + UTC.dateTime());
  
  
  Austria.setLocation("Europe/Vienna");
  Serial.println("Vienna time: " + Austria.dateTime());
}

void initMatrix() {
   FastLED.addLeds<CHIPSET, MATRIXPIN, COLOR_ORDER>(matrix[0], matrix.Size());
   FastLED.setBrightness(17);
   FastLED.clear(true);
}

// MQTT Broker connection
void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}

// Receive messages
void mqtt_callback(char* topic, byte* payload, unsigned int length) {

  String message;
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    message += c;
  }
  Serial.print("Topic ");
  Serial.print(topic);
  Serial.print(" | ");
  Serial.println(message);
 
/*
  if (strcmp(topic,"haus/light/lamp1")==0){ // 0 means there is a match
    if ((message == "1") && (ledState1 == LOW)  ) {    toggle1(); Serial.println("debug1"); }
    if ((message == "0") && (ledState1 == HIGH)) {    toggle1();  }
  }
  if (strcmp(topic,"haus/light/lamp2")==0){ // 0 means there is a match
    if ((message == "1") && (ledState2 == LOW)) {    toggle2();  }
    if ((message == "0") && (ledState2 == HIGH)) {    toggle2();  }
  }
*/  

  message = "";
    Serial.println();
    Serial.flush();
}

void reconnectMQTT() {
    while (!MQTT.connected()) {
      Serial.print("Connection to MQTT Broker: ");
      Serial.println(BROKER_MQTT);
      if (MQTT.connect("ESP8266")) {
        Serial.println("Connected");
      MQTT.subscribe("haus/light/lamp1"); 
      MQTT.subscribe("haus/light/lamp2"); 
      } else {
        Serial.println("Connection failed");
        Serial.println("Retry in 2 secs");
        delay(2000);
      }
    }
  }

  void recconectWiFi() {
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
  }

void toggle1(){
   state = state +1;
 if (state > maxstate) { state = 0;}
   Serial.println("toggle1");
} 

void toggle2(){
  /* ledState2 = !ledState2;
   digitalWrite(LED_PIN2,ledState2); // Apply new LED state
   digitalWrite(RELAY2,ledState2); // Apply new LED state
   Serial.println("toggle2"); */
}


void publishmqtt() {
/*   long now = millis();
   if (now - lastMsg > 2000) {
      lastMsg = now;
      if (ledState1 == HIGH) {
         msg = "ON";
      } else {
         msg = "OFF";
      }
      client.publish("haus/light/lamp1/", msg);

   }
*/}


void loop() {

   debouncer1.update(); // Update the Bounce instance
   debouncer2.update(); // Update the Bounce instance
   
   if ( debouncer1.fell() ) { toggle1(); } // Call code if button transitions from HIGH to LOW
   if ( debouncer2.fell() ) { toggle2(); } // Call code if button transitions from HIGH to LOW
   if (!MQTT.connected()) {
         reconnectMQTT(); // Retry Worker MQTT Server connection
   }
   recconectWiFi(); // Retry WiFi Network connection
   MQTT.loop();
   
   switch (state) {
	case 0:
	   showtime();
	   delay(1000);
           break;
	case 1:
	   showweather();
	   break;
	default:
	   showtime();
	   break;
   }


}
