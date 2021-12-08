#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "NxGroup";
const char pass[] = "cisneros530";
String IDS = "NO IDENTIFICADO";
String estado = "CORRECTO";

WiFiClient net;
MQTTClient client;

long duration;
float distanceCm;
#define SOUND_SPEED 0.034
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino")) { //, "public", "public")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("led");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic=="led") {
    if (payload=="on") digitalWrite(26, HIGH);
    if (payload=="off") digitalWrite(26, LOW);
  }
}

float medicion(){
    digitalWrite(12, LOW); // Clears the trigPin
    delayMicroseconds(2);
    digitalWrite(12, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(12, LOW);
    duration = pulseIn(13, HIGH);
    distanceCm = duration * SOUND_SPEED/2;
    if (distanceCm < 20.0)
    {
      estado = "BAJA";
    }
    else
    {
      if(distanceCm > 80.0)
      {
        estado = "ALTA";
      }
      else
      {
        estado = "NORMAL";
      }
    }
    return distanceCm;
}

void setup() {
  Serial.begin(115200);

  pinMode(26,OUTPUT); // LED2
  pinMode(13,INPUT);  // ECHO
  pinMode(12,OUTPUT); // pulse

  WiFi.begin(ssid, pass);
  client.begin("192.168.0.125", 1883, net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();              // Si o si tiene que estar en el loop
  if (!client.connected())    
  {
    connect();                // si se desconecta, intento conectar
  }

  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();
    String mensaje ="{\"temperature\":"+String(medicion())+",\"ID_SENSOR\":\""+String(IDS)+"\",\"state\":\""+String(estado)+"\"}";
    client.publish("temperatura", mensaje);
  }  
}