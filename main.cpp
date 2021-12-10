#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "webpage.h"
#include "webpage2.h"
#include <string.h>
#include <iostream>

//VARIABLES GLOBALES-------------------
const char* ssid     = "ESP32DIPLO";
const char* password = "123456789";
int8_t ESTADOESP = 0;           //0 para modo accespoint - 3 para modo station
int8_t carga=0;
const char ssidsm[] = "NxGroup";
const char pass[]= "cisneros530";
const char* deviceName="ESP32_THING";
String IPSERVER = "123";
String IDS = "ESP 1";
String PAS;
String SSI;
long duration;
float distanceCm;
#define SOUND_SPEED 0.034
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
String estado = "CORRECTO";
String header;

MQTTClient client;
WiFiServer server(80);
WebServer server2(80);
WiFiClient net;


void extraccion ();
void setupsoftap();
void softap ();
void setupstationmode();
void connect();
void messageReceived(String &topic, String &payload);
void handleRoot();
void modostation();
float medicion();
void handlePOT();
void handlename();
void handleestado();

void setup() {
  Serial.begin(115200);
  pinMode(26,OUTPUT); // LED2
  pinMode(13,INPUT);  // ECHO
  pinMode(12,OUTPUT); // pulse
}

void loop() {
  if (ESTADOESP==0)     //Configuro el esp en modo accespoint
  {
    Serial.print("...SOFTAP...");
    setupsoftap();
    ESTADOESP=1;
  }
  
  if (ESTADOESP==1)     //corro el esp en modo accespoint
  {
    softap ();
  }
  
  if (ESTADOESP==2)     //desconecto el modo accespoint
  {
    Serial.println("-----------------DESCONECTO SOFTAP----------------");
    WiFi.softAPdisconnect (true);
    server.stop();
    server.stopAll();
    server.end();
    ESTADOESP=3;
  }

   if (ESTADOESP==3)    //Configuro el esp en modo station
  {
    Serial.println("-----------------CONECTO EN MODO STATION----------------");
    setupstationmode();  
    ESTADOESP=4;  
  }
  if (ESTADOESP==4)     //corro el esp en modo station
  {
    //Serial.println("-----------------MODO STATION FUNCIONANDO----------------");
    modostation();  
    ESTADOESP=4;  
  }
}

void setupsoftap()
{
   Serial.print("Setting AP (Access Point)…");
  //WiFi.softAP(ssid, password);
  delay(100);
          Serial.println("Set softAPConfig");
          IPAddress Ip(192, 168, 1, 44);
          IPAddress NMask(255, 255, 255, 0);
          WiFi.softAPConfig(Ip, Ip, NMask);
  delay(100); 
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  //server.on("/", handleRoot);
  server.begin();
}

void softap ()
{
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();  // linea en blanco importante
            
            if (header.indexOf("/get?ssid=") >= 0)
            {
              
              //Serial.println(header);
              extraccion();
              break;
              
            }

            // Display the HTML web page
            client.println(webpageCode);
            
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void extraccion ()
{
  if(carga==0)
  {
int posini = header.indexOf("?ssid=");
int posfin = header.indexOf("&pass=");
SSI = header.substring(posini+6,posfin);
//const char *CC = SS.c_str(); //VER ESTOOOOOO
Serial.println (".....");
Serial.println (SSI);
Serial.println (".....");
posini = header.indexOf("&pass=");
posfin = header.indexOf("&iddispositivo=");
PAS = header.substring(posini+6,posfin);
Serial.println (".....");
Serial.println (PAS);
Serial.println (".....");
posini = header.indexOf("&iddispositivo=");
posfin = header.indexOf("&ipserver=");
IDS = header.substring(posini+15,posfin);
Serial.println (".....");
Serial.println (IDS);
Serial.println (".....");
posini = header.indexOf("&ipserver=");
posfin = header.indexOf(" HTTP");
IPSERVER = header.substring(posini+10,posfin);
Serial.println (".....");
Serial.println (IPSERVER);
Serial.println (".....");
carga=1;
  }
  ESTADOESP=2;
}

void setupstationmode ()
{
  //WiFi.hostname(deviceName);
  WiFi.hostname(deviceName);
  WiFi.mode(WIFI_STA);

  //const char *ssidsm = SSI.c_str(); //VER ESTOOOOOO
  //const char *pass = PAS.c_str(); //VER ESTOOOOOO

  WiFi.begin(ssidsm, pass);
  client.begin("192.168.0.111", 1883, net);
  client.onMessage(messageReceived);
  connect();
  server2.on("/", handleRoot);
  server2.on("/readPOT", handlePOT);
  server2.on("/readname", handlename);
  server2.on("/readestado", handleestado);
  server2.begin();
  Serial.println("HTTP server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

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

void modostation()
{
  client.loop();              // Si o si tiene que estar en el loop
  if (!client.connected())    
  {
    connect();                // si se desconecta, intento conectar
  }


  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();
    String mensaje ="{\"temperature\":"+String(medicion())+",\"id_sensor\":\""+String(IDS)+"\",\"state\":\""+String(estado)+"\"}";
    client.publish("temperatura", mensaje);
  }
  server2.handleClient(); 
  vTaskDelay(10 / portTICK_RATE_MS); 
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

void handleRoot()
{
 server2.send(200, "text/html", webpage2Code);
 Serial.println("enviando codigod de pagina");
}

void handlePOT()
{
 String POTval= String(medicion());   
 server2.send(200, "text/plane", POTval);
}

void handlename()
{
 String name= String(IDS);   
 server2.send(200, "text/plane", name);
}

void handleestado()
{
 String estd= String(estado);   
 server2.send(200, "text/plane", estd);
}