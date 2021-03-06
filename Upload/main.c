#include <Energia.h>
#include "BMP180.h"
#include <Wire.h>
#include <SIM800l.h>
//#include "DHT11.h"
//#include <OPT3001.h>
#include <Time.h>
//#include "SDL_Weather_80422.h"

/*
String id = "ICAIRO9";
String PASSWORD = "cccfshon";
String URL = "https://weatherstation.wunderground.com/weatherstation/updateweatherstation.php?";

SIM800l SIM800l;
HardwareSerial Serial1;
*/


//#define pinAnem    18  //Uno pin 2
//#define pinRain    2  // Uno Pin 3 
//#define intAnem    5  // int 0 (check for Uno)
//#define intRain    1  // int 1
#define soil = PB_5;
//SDL_Weather_80422 weatherStation(pinAnem, pinRain, intAnem, intRain, A0, SDL_MODE_INTERNAL_AD);
TwoWire i2c_port(2);
//uint8_t i;
//float currentWindSpeed;
//float currentWindGust;
//float totalRain;
//opt3001 opt3001;
char tem,hum;
int32_t temperature = 0;
int32_t pressure = 0;
int soilData;



void setup()
{
  Serial.begin(9600);
 // SIM800l(Serial1);
 // SIM800l.init(9600);
  
  init_BMP180();
  //dht.dht_init();
  //init_OPT3001();
  //init_rain_wind();
  init_soil();
}

void loop()
{
String data = URL;
data.concat("ID=");
data.concat(id);
data.concat("&");
data.concat("PASSWORD=");
data.concat(PASSWORD);
data.concat("&dateutc=now&");
data.concat(get_BMP180());
data.concat("&");
data.concat(get_soil());
//data.concat("&");
//data.concat(get_DHT11());
//data.concat("&");
//data.concat(get_OPT3001());
//data.concat("&");
//data.concat(get_rain_wind());
data.concat("&softwaretype=vws%20versionxx&action=updateraw");

Serial.println(data);
delay(5000);
//if(SIM800l.checkNetworkRegistration()==0)
//SIM800l.httpPost(data);

//  sleep(3600000);
}

void init_soil(){
	 pinMode(soil,INPUT);
}
/*
void init_OPT3001(){
	delay(100);
  opt3001.begin(); 
}
*/
void init_BMP180(){
  i2c_port.begin();
  delay(10);
  getCalibrationData();
  readSensor();
}
/*
void init_rain_wind(){     
      weatherStation.setWindMode(SDL_MODE_SAMPLE, 5.0);
      //weatherStation.setWindMode(SDL_MODE_DELAY, 5.0);
      totalRain = 0.0;
}
*/
String get_soil(){ //ID:1
  String data ="soilmoisture=";
  data.concat(analogRead(soil));
  return data;
  delay(100);
}
/*
String get_rain_wind(){ // rain ID:2, wind ID:3
  String data;
  currentWindSpeed = weatherStation.current_wind_speed()/1.6;
  currentWindGust = weatherStation.get_wind_gust()/1.6;
  totalRain = totalRain + weatherStation.get_current_rain_total()/25.4;
  data = "rainin=";
  data.concat(totalRain);
  data.concat("&windspeedmph=");
  data.concat(currentWindSpeed);
  data.concat("&windgustmph_10m=");
  data.concat(currentWindGust);
  data.concat("&winddir=");
  data.concat(weatherStation.current_wind_direction());
  return data;
  delay(100);
}
*/
String get_BMP180(){ //ID:4
  String data = "baromin=";
  readSensor(temperature,pressure);
 data.concat(pressure);                               
  return data;
}
/*
String get_DHT11(){ //ID:5
String data = "tempf=";
  delay(200);
  dht.start_test();
  tem=dht.get_Temp();
  hum=dht.get_Hum();
  data.concat(tem);
  data.concat("&humidity=");
  data.concat(hum);
  return data;
  delay(700);
}
*/
/*
String get_OPT3001(){ //ID:6
String data = "visibility=";
  uint32_t readings;
  readings = opt3001.readResult();  
  data.concat(readings);
  return data;
  delay(800);
}
*/

