#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Thermistor.h>
 
//temperatura
bool esp82 = true;       // mude para falso ao usar o Arduino
 
int ThermistorPin;
double adcMax, Vs;
 
String TempReal;
double R1 = 10000.0;   // resitor 10k
double Beta = 3950.0;  // Beta value
double To = 298.15;    // temperatura em kelvin Kelvin
double Ro = 10000.0;   // resitor 10k em C
 
//calibrando tenção esp
//const float ADC_LUT[4096] PROGMEM =
//////////////////
 
 
void setup() {
  Serial.begin(115200);
   
 
  ////////// temperatura
 
  ThermistorPin = 4;
  adcMax = 4095.0; // ADC 12-bit (0-4095)
  Vs = 3.3;        // voltagem
 
 
  ///////////
}
 
 
void loop() {
  uint32_t AD = 0;
  
 
  double Vout, Rt = 0;
  double T, Tc, Tf = 0;
 
  double adc = 0;
 
  adc = analogRead(ThermistorPin);
  adc = AD;
 
  Vout = adc * Vs / adcMax;
  Rt = R1 * Vout / (Vs - Vout);
 
  T = 1 / (1 / To + log(Rt / Ro) / Beta); //  Kelvin
  Tc = T - 273.15;                   // Celsius
  Tf = Tc * 9 / 5 + 32;              // Fahrenheit
  if (Tc > 0) Serial.print(Tc);
  Serial.println(" Celsius");
  Serial.print (temp);
  delay(2000);
  if (Tf > 0) Serial.print(Tf);
  Serial.println(" Fahrenheit");
  delay(2000);
}
