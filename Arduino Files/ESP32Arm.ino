#define Vcc 13
#define Vee 12
#define Claw 27
#define Wrist 33 
#define Elbow 15
#define Shoulder 32
#define Base 14
#define Ddelay 11

#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "YOURSSID";
const char* password =  "YOURPASSWORD";
const char* mqttServer = "m12.cloudmqtt.com";
const int mqttPort = 12345;// YOUR PORT
const char* mqttUser = "YOURUSER";
const char* mqttPassword = "YOURPASS";
bool sw = false;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  pinMode(Vcc,OUTPUT);  
  pinMode(Vee,OUTPUT); 
  pinMode(Claw,OUTPUT);
  pinMode(Wrist,OUTPUT);
  pinMode(Elbow,OUTPUT);
  pinMode(Shoulder,OUTPUT);
  pinMode(Base,OUTPUT);
  // Turning Off Everything
  digitalWrite(Vcc,HIGH); 
  digitalWrite(Vee,HIGH); 
  digitalWrite(Claw,HIGH);
  digitalWrite(Wrist,HIGH);
  digitalWrite(Elbow,HIGH);
  digitalWrite(Shoulder,HIGH);
  digitalWrite(Base,HIGH);
 
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
 
    if (client.connect("ESP32Client2", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32"); 
  client.subscribe("ArmTopic"); 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  String datas="";
  for (int i = 0; i < length; i++) 
  {
    datas+=char(payload[i]);
  }
  if(datas=="TR")
  {
    down(Base,Ddelay);
  }
  else if(datas=="TL")
  {
    up(Base,Ddelay);
  }
  else if(datas=="SD")
  {
    down(Shoulder,Ddelay);
  }
  else if(datas=="SU")
  {
    up(Shoulder,Ddelay);
  }
  else if(datas=="ED")
  {
    down(Elbow,Ddelay);
  }
    else if(datas=="EU")
  {
    up(Elbow,Ddelay);
  }
  else if(datas=="CD")
  {
    down(Wrist,Ddelay);
  }
  else if(datas=="CU")
  {
    up(Wrist,Ddelay);
  }
  else if(datas=="CO")
  {
    down(Claw,Ddelay);
  }
  else if(datas=="CC")
  {
    up(Claw,Ddelay);
  }
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
}

void up(int pin,int Delay)
{
  digitalWrite(Claw,HIGH);
  digitalWrite(Wrist,HIGH);
  digitalWrite(Elbow,HIGH);
  digitalWrite(Shoulder,HIGH);
  digitalWrite(Base,HIGH);
  digitalWrite(pin,LOW);
  digitalWrite(Vcc,LOW);  // +Vcc ON
  delay(Delay);
  digitalWrite(Vcc,HIGH);
  digitalWrite(pin,HIGH);
}

void down(int pin, int Delay)
{
  digitalWrite(Claw,LOW);
  digitalWrite(Wrist,LOW);
  digitalWrite(Elbow,LOW);
  digitalWrite(Shoulder,LOW);
  digitalWrite(Base,LOW);
  digitalWrite(pin,HIGH);
  digitalWrite(Vee,LOW); // -Vee ON
  delay(Delay);
  digitalWrite(Vee,HIGH);
  digitalWrite(Claw,HIGH);
  digitalWrite(Wrist,HIGH);
  digitalWrite(Elbow,HIGH);
  digitalWrite(Shoulder,HIGH);
  digitalWrite(Base,HIGH);
  
}
