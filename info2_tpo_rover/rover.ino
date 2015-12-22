// MOTORES
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int estadoM[4];
int velocidadM[4];

void setupRover() {
  Serial.println("Iniciando Rover...");
  
  // motores 
  motor1.run(RELEASE); motor2.run(RELEASE);
  motor3.run(RELEASE); motor4.run(RELEASE);
  velocidadM[0] = 0;   velocidadM[2] = 0;
  velocidadM[2] = 0;   velocidadM[3] = 0;

}

void acelerar() {
    sprintf(temp,"Acelerar\n"); Serial.write(temp);  
    for (int i=0; i<256; i+=8) {      
      if (velocidadM[0] < i) { motor1.setSpeed(i); velocidadM[0] = i; }
      if (velocidadM[1] < i) { motor2.setSpeed(i); velocidadM[1] = i; }
      if (velocidadM[2] < i) { motor3.setSpeed(i); velocidadM[2] = i; }
      if (velocidadM[3] < i) { motor4.setSpeed(i); velocidadM[3] = i; }
    delay(10); }
}

void adelante() {
  if (alerta) { return; }
  
  sprintf(temp,"Adelante\n"); Serial.write(temp);  
  if (estadoM[0] != FORWARD) { motor1.run(FORWARD); estadoM[0] = FORWARD; }
  if (estadoM[1] != FORWARD) { motor2.run(FORWARD); estadoM[1] = FORWARD; }
  if (estadoM[2] != FORWARD) { motor3.run(FORWARD); estadoM[2] = FORWARD; }
  if (estadoM[3] != FORWARD) { motor4.run(FORWARD); estadoM[3] = FORWARD; }
  acelerar();
}

void atras() {
  sprintf(temp,"Atras\n"); Serial.write(temp);  
  if (estadoM[0] != BACKWARD) { motor1.run(BACKWARD); estadoM[0] = BACKWARD; }
  if (estadoM[1] != BACKWARD) { motor2.run(BACKWARD); estadoM[1] = BACKWARD; }
  if (estadoM[2] != BACKWARD) { motor3.run(BACKWARD); estadoM[2] = BACKWARD; }
  if (estadoM[3] != BACKWARD) { motor4.run(BACKWARD); estadoM[3] = BACKWARD; }
  acelerar();
}

void izquierda() {
  sprintf(temp,"Izquierda\n"); Serial.write(temp);  
  if (estadoM[0] != FORWARD)  { motor1.run(FORWARD);  estadoM[0] = FORWARD; }
  if (estadoM[1] != BACKWARD) { motor2.run(BACKWARD); estadoM[1] = BACKWARD; }
  if (estadoM[2] != BACKWARD) { motor3.run(BACKWARD); estadoM[2] = BACKWARD; }
  if (estadoM[3] != FORWARD)  { motor4.run(FORWARD);  estadoM[3] = FORWARD; }
  acelerar();
}

void derecha() {
  sprintf(temp,"Derecha\n"); Serial.write(temp);  
  if (estadoM[0] != BACKWARD) { motor1.run(BACKWARD); estadoM[0] = BACKWARD; }
  if (estadoM[1] != FORWARD)  { motor2.run(FORWARD);  estadoM[1] = FORWARD; }
  if (estadoM[2] != FORWARD)  { motor3.run(FORWARD);  estadoM[2] = FORWARD; }
  if (estadoM[3] != BACKWARD) { motor4.run(BACKWARD); estadoM[3] = BACKWARD; }
  acelerar();
}

void detener() {  
  sprintf(temp,"Detener\n"); Serial.write(temp);  
  motor1.run(RELEASE); estadoM[0] = RELEASE;   motor2.run(RELEASE); estadoM[1] = RELEASE;
  motor3.run(RELEASE); estadoM[2] = RELEASE;   motor4.run(RELEASE); estadoM[3] = RELEASE;
  
  for (int i=256; i>=0; i-=8) {      
      if (velocidadM[0] > i) { motor1.setSpeed(i); velocidadM[0] = i; }
      if (velocidadM[1] > i) { motor2.setSpeed(i); velocidadM[1] = i; }
      if (velocidadM[2] > i) { motor3.setSpeed(i); velocidadM[2] = i; }
      if (velocidadM[3] > i) { motor4.setSpeed(i); velocidadM[3] = i; }
  delay(10); }
  
}

