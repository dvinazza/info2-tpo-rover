#include <SPI.h>
#include "RF24.h"

/* Conexiones del modulo nRF24L01+ al Arduino Mega
Line    Arduino Pin  Modulo   Color
GND      GND         1        NEGRO
3V3      3V3         2        ROJO
CE       53          3        BLANCO
CSN      48          4        NARANJA
SCK      52          5        GRIS
MOSI     51          6        AMARILLO
MISO     50          7        VIOLETA
*/  

RF24 radio(53,48); // MEGA
#define TIMEOUT_RADIO 20000
bool role = 0;

bool radioNumber = 1;
byte addresses[][6] = {"Base","Rover"};

#define BEACON 40 // 2 segundos

void setupRadio() {
  Serial.println("Iniciando Radio...");
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  //radio.setPALevel(RF24_PA_LOW);
  
  if (radioNumber) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]); }
  else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]); }
  
  radio.startListening();
}

void enviar(unsigned int mensaje) {
  // debug
  sprintf(temp,"Enviando [%d]\n", mensaje); Serial.write(temp);  
  
  radio.stopListening();

  if (radio.write(&mensaje, sizeof(mensaje)) ) {
    Serial.println(F("Se envio correctamente")); }
  else {
    Serial.println(F("El envio fallo")); }
}

int recibir() { //Devuelve -1 si no hubo comunicacion, 1 si recibio datos

  radio.startListening();                                    
    
  unsigned long started_waiting_at = micros();               
  boolean timeout_radio = false;                             
    
  while ( ! radio.available() ) {                            
    if (micros() - started_waiting_at > TIMEOUT_RADIO ){           
        timeout_radio = true;
        break; }      
  }
        
  if ( timeout_radio ) {
    return 0;  }
  else {
    Serial.println(F("Hay datos en la radio!"));
    timeout = 0;
        
    while ( radio.available() ) {
      
      radio.read( &bufferSerie, sizeof(bufferSerie) );        
      
      if (bufferSerie != 0) {
        Serial.print(F("Obtuve: "));
        Serial.println(bufferSerie); 
        return 1;   
      } 
    }
  }
}
