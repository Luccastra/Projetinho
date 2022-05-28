//vao criar um programa q recebe LEDON, LEDOFF e STATUS onde
//o status devolve o status de algum sensor ou botao
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index_html.h"
#include <Thermistor.h>


#define DHTPIN 2
#define DHTTYPE DHT22
const int pinTermistor = A0;


void loop() {
  int temperature = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(temperature); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
int temperatura = 26;

// Porta do pino de sinal do DS18B20




//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 5 /*"pino"*/ ;
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;

//Porta ligada ao termometro
int porta_term =  3;/*"pino"*/
//Armazena o valor lido do termometro
int leitura= 0;


DeviceAddress endereco_temp;

ESP8266WebServer server(80);
String page=INDEX_HTML;


void setup() {
 
  {
     Serial.begin(9600); //INICIALIZA A SERIAL
     delay(1000);
  }
Serial.begin(115200);
WiFi.mode(WIFI_STA);
WiFi.begin("LABBIB01-28 6800","v=52H789");
Serial.println("");
// espera a conexao
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Conectado ");
Serial.println(WiFi.localIP());

server.on("/",Chamaeu);
server.on("/LED",ChamaLed);
server.begin();
pinMode(LED_BUILTIN, OUTPUT);
//pinMode(A0, OUTPUT);

 //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT);
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);
  //Define pinos dos botoes como entrada
  pinMode(porta_term, INPUT); 


  Serial.begin(115200); // Inicia a porta serial
  Serial.println("Medindo Temperatura"); // Imprime a mensagem inicial
  sensors.begin(); ; // Inicia o sensor
}



void Chamaeu(){
//server.send(200,"text/plain", "ola");
server.send(200,"text/html", page);
}
void ChamaLed(){
digitalWrite(LED_BUILTIN, HIGH);
}
void loop() {
server.handleClient();

sensors.requestTemperatures(); // Envia comando para realizar a conversão de temperatura
  if (!sensors.getAddress(endereco_temp,0)) { // Encontra o endereco do sensor no barramento
    Serial.println("SENSOR NAO CONECTADO"); // Sensor conectado, imprime mensagem de erro
  } else {
    Serial.print("Temperatura = "); // Imprime a temperatura no monitor serial
    Serial.println(sensors.getTempC(endereco_temp), 1); // Busca temperatura para dispositivo
  }
  delay(1000);



}
