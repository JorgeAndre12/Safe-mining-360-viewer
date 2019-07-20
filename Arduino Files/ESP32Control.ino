#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "YOURSSID";
const char* password =  "YOURPASSWORD";
const char* mqttServer = "m12.cloudmqtt.com";
const int mqttPort = 12345; // Your PORT
const char* mqttUser = "YOURUSER";
const char* mqttPassword = "YOURPASSWORD";
bool sw = false;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32"); 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(analogRead(A0)<4000 && analogRead(36)>10)
  {
   sw=true; 
  }
  else
  {
    sw=false;
  }
  if(sw)
  {
    if(analogRead(A1)>4000)
  {
    client.publish("ArmTopic", "TR");
    Serial.println("Turn Right"); 
  }
    else if(analogRead(A1)<4000 && analogRead(A5)>10)
  {
    client.publish("ArmTopic", "TL");
    Serial.println("Turn Left"); 
  }
    if(analogRead(A2)>4000)
  {
    client.publish("ArmTopic", "SD");
    Serial.println("Shoulder Down"); 
  }
    else if(analogRead(A2)<4000 && analogRead(34)>10)
  {
    client.publish("ArmTopic", "SU");
    Serial.println("Shoulder Up"); 
  }
    if(analogRead(A3)>4000)
  {
    client.publish("ArmTopic", "ED");
    Serial.println("Elbow Down"); 
  }
    else if(analogRead(A3)<4000 && analogRead(35)>10)
  {
    client.publish("ArmTopic", "EU");
    Serial.println("Elbow Up"); 
  }
    if(analogRead(A4)>4000)
  {
    client.publish("ArmTopic", "CD");
    Serial.println("Claw Down"); 
  }
    else if(analogRead(A4)<4000 && analogRead(32)>10)
  {
    client.publish("ArmTopic", "CU");
    Serial.println("Claw Up"); 
  }
    if(analogRead(A5)>4000)
  {
    client.publish("ArmTopic", "CO");
    Serial.println("Claw Open");
  }
    else if(analogRead(A5)<4000 && analogRead(33)>10)
  {
    client.publish("ArmTopic", "CC");
    Serial.println("Claw Close");
  }
  }
  delay(10);
  
}
