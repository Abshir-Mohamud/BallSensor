#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://pingpongmachine-d18ca.firebaseio.com/"                         
#define FIREBASE_AUTH "MqwvpzIN6TCz2hSClMNG83UF33O9wtBjOKbt3tIa"                    
#define WIFI_SSID "Family"                                          
#define WIFI_PASSWORD "1005appleTORONTO5001" 

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

int fsrAnalogPin = 2; // FSR is connected to analog 0
int fsrReading;      // the analog reading from the FSR resistor divider
String path = "/Pressure/Pressure: ";
void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  }
void loop()
{
  fsrReading = analogRead(fsrAnalogPin);
  if(fsrReading<1){
  Firebase.setString(firebaseData, path, "true");
  Serial.println("Pressure Detected!");
 // digitalWrite(LEDpin, HIGH);
  }
  else
  Firebase.setString(firebaseData, path, "false");
}
