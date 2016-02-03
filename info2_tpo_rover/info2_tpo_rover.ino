#include <AFMotor.h>

// buffer para darle formato al debug
char temp[64];

// MAQUINA DE ESTADOS
unsigned int timeout;
unsigned int estado;
char cambio_de_estado;
char alerta;
#define DELAY 50 // 1/20 segundo

// COMUNICACION
// serial para debug => Serial.
//#define BAUDRATE 38400
#define BAUDRATE 9600
char bufferSerie;

// ESTADOS == MENSAJES  
#define ESPERANDO 127 
#define ADELANTE 63
#define ATRAS 126
#define IZQUIERDA 31
#define DERECHA 125
#define ALERTA 62

#define TIMEOUT 20 // 1 segundo

void setup() {  

  // debug
  Serial.begin(BAUDRATE); Serial.println("Iniciando...");
  
  setupRadio();
  setupRover();
  setupProximidad();
  
  // maquina
  estado = ESPERANDO;
  cambio_de_estado = 1;
}

/* 
*
* MAQUINA Y MAIN
*
*
*/

void maquina() {
  // debug del estado actual de la maquina
  sprintf(temp,"ESTADO == %d\n", estado);
  Serial.write(temp);
    
  enviar(estado);
  cambio_de_estado = 0;
    
  switch(estado) {
    case ESPERANDO: detener(); break;
    case ADELANTE: adelante(); break;
    case ATRAS: atras(); break;
    case IZQUIERDA: izquierda(); break;
    case DERECHA: derecha(); break;
    default:
        estado = ESPERANDO;
      break; }
}
  
void loop() {

  // recepcion del mensajes
  if (recibir() ) {
    if (estado != bufferSerie) {
      estado = bufferSerie;
      cambio_de_estado = 1; 
      enviar(estado); }
  }
  else { //
    timeout++;
    // sprintf(temp,"timeout=%d\n", timeout);
    // Serial.write(temp);    

    // cada cierto periodo de tiempo envio a la base el estado del rover
    //if (timeout % BEACON == 0) { enviar(estado); }
      
    if (timeout % TIMEOUT == 0) {
      sprintf(temp,"Perdi la comunicacion [%d]!\n", timeout);
      Serial.write(temp);    
  
      if (estado != ESPERANDO) { estado = ESPERANDO; cambio_de_estado = 1; }
    }
  }
  
  // proximidad
  proximidad();  
  
  if (cambio_de_estado) { maquina(); }  
  delay(DELAY);
  
}
