/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include <PubSubClient.h>

const char* networkName = ""; //Constchar network name
String networkNameString = "";//String network name
const char* password = ""; //password net
const char* mqtt_server = "192.168.1.3";

const int mqttPort = 1883;
const char* mqttUser = "yourMQTTuser";
const char* mqttPassword = "yourMQTTpassword";

const char*clientName = "ESP32Client";

long unsigned int timeBetweenSendPackages = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    while(!clientConnetion());
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    //WiFi.mode(WIFI_STA);
    //WiFi.disconnect();
    delay(100);
  
    Serial.println("Setup done");

   
}

void setup_wifi() 
{
   Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
   int n;
   bool findNetwork = false;
   IPAddress ip;  
   while(findNetwork == false)
   {
      n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0) {
          Serial.println("no networks found");
      } 
      else 
      {
          Serial.print(n);
          Serial.println(" networks found");
          for (int i = 0; i < n; ++i) {
              // Print SSID and RSSI for each network found
              Serial.print(i + 1);
              Serial.print(": ");
              Serial.println(WiFi.SSID(i));
              if(networkNameString == WiFi.SSID(i))
              {
                findNetwork = true;
                Serial.println("Encontrou o wifi");
                break;
                
              }
              delay(10);
          }
        }
        
        Serial.println("");
  
        // Wait a bit before scanning again
        delay(5000);
   }
   if(findNetwork)
   {
      WiFi.begin(networkName, password);
      while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }
      ip = WiFi.localIP();
      Serial.println(ip);
      
   }
}

bool clientConnetion()
{
  client.setServer(mqtt_server, mqttPort);
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect(clientName, mqttUser, mqttPassword )) 
    {
 
      Serial.println("connected");  
 
    } 
    else 
    {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
    client.publish("PT1000/Temperature", "55.22");
    delay(5000);
  }
}

void publishe(float sensorValure)
{
   char stringSensorValue[6];
   sprintf(stringSensorValue, "%f", sensorValure);
   stringSensorValue[5] = '\0';
   client.publish("PT1000/Temperature", stringSensorValue);
   Serial.println(stringSensorValue);
}

void loop()
{
     client.loop();
     if(millis() - timeBetweenSendPackages >=5000)
     {
       publishe(25.2);
       timeBetweenSendPackages = millis();
     }
     
    //WiFi.disconnect();
}
