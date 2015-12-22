
#include <NewPing.h>

#define triggerPin 44
#define echoPin 45
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(triggerPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setupProximidad() {
  Serial.println("Iniciando Proximidad...");
  
  alerta = 0; 
}

void proximidad() {
    
  int distancia = sonar.ping_cm();
  
  if (distancia != 0 && distancia < 30 && alerta == 0 && estado != ATRAS) {
    alerta=1;
    Serial.print("Alerta! Objeto a "); Serial.print(distancia); Serial.println(" cm");
    estado=ESPERANDO;
    cambio_de_estado=1;
  }
  else if (alerta == 1) {
    alerta=0;
  }

}
