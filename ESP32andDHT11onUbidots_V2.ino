
/****************************************
 * Include Libraries
 ****************************************/
 
#include "WiFi.h"
#include "UbidotsMicroESP32.h"
#include <Wire.h>
#include <Arduino.h>
#include "DHTesp.h"


/****************************************
 * Define Constants
 ****************************************/

#define DHTpin 4    //ขา DHT11
#define TOKEN  "A1E-dstwbgPaMMxcc53WdWtu1g7aOZfwng"  // Put here your Ubidots TOKEN
#define WIFISSID "iotworkshop" // Put here your Wi-Fi SSID
#define PASSWORD "123414321*" // Put here your Wi-Fi password


/****************************************
 * Used Lib
 ****************************************/
DHTesp dht;
Ubidots client(TOKEN);

/****************************************
 * Golbal Val
 ****************************************/
String getStatusDHT11;

void setup() {
  Serial.begin(115200);
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor 
  delay(100);
  client.wifiConnection(WIFISSID,PASSWORD);
  client.setDataSourceName("My test"); // ชื่อ Device
  client.setDataSourceLabel("my-test"); // ชื่อ variable ใน Device
   
/* ****************************** END *********************** */ 
 
}

void loop() {

  
  /* ********************* initial DHT11 ********************* */ 
  
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  getStatusDHT11 = String(dht.getStatusString());
  
   /* ****************************** END *********************** */     

// ตั้งเงื่อนไขว่า ถ้า Status ของ Sensor DHT11 พร้่อมทำงาน คือคำว่า OK จะส่งข้อมูล
  if(getStatusDHT11 == "OK") { 
    client.add("Humidity", humidity);
    client.add("Temperature", temperature);
    client.sendAll(true); 
    }

 /* ****************************** END *********************** */     
}
