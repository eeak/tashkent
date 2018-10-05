/*
https://esp8266.ru/forum/threads/majordomo-i-esp8266.2242/
 Basic MQTT example with Authentication

  - connects to an MQTT server, providing username
    and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#define RELE_1 14                               // Реле №1
#define RELE_2 12                               // Реле №2
#define RELE_3 13                               // Реле №3
#define BUTTON_1 16                               // Кнопочный выключатель №1
#define BUTTON_2 5                                // Кнопочный выключатель №2
#define BUTTON_3 4                                // Кнопочный выключатель №3
#define relays_topic1 "ESP01/RELE_1"              // Топик реле №1
#define relays_topic2 "ESP01/RELE_2"              // Топик реле №2
#define relays_topic3 "ESP01/RELE_3"            // Топик реле №3

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

long last_mls = millis();
char msg[50];
boolean rState1 = false;
boolean rState2 = false;
boolean rState3 = false;
boolean btnPress1 = false;
boolean btnPress2 = false;
boolean btnPress3 = false;
boolean lastbtnStat1 = false;
boolean lastbtnStat2 = false;
boolean lastbtnStat3 = false;

void setup()
{
  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this,
  // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
  // PubSubClient.h
  
  if (client.connect("arduinoClient", "testuser", "testpass")) {
    client.publish("outTopic","hello world");
    client.subscribe("inTopic");
  }
}

void loop()
{
  client.loop();
}
