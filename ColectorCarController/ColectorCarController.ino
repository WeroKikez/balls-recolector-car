
// Back Motors H Bridge Signal Pins 
int moveForwardLeftBackMotor = 2;     // Señal para mover hacia adelante motor trasero izquierdo
int moveBackwardLeftBackMotor = 3;    // Señal para mover hacia atras motor trasero izquierdo
int moveForwardRightBackMotor = 4;    // Señal para mover hacia adelante motor trasero derecho
int moveBackwardRightBackMotor = 5;   // Señal para mover hacia atras motor trasero derecho

// Back Motors H Bridge Signal Pins 
int moveForwardLeftFrontMotor = 6;     // Señal para mover hacia adelante motor delantero izquierdo
int moveBackwardLeftFrontMotor = 7;    // Señal para mover hacia atras motor delantero izquierdo
int moveForwardRightFrontMotor = 8;    // Señal para mover hacia adelante motor delantero derecho
int moveBackwardRightFrontMotor = 9;   // Señal para mover hacia atras motor delantero derecho

// TODO: Using logic gates, make it just 3 signals for each back motors and front motors

// Output Signal Pins
int activateColector = 10;
int activateSorter = 11;
int openLeftGate = 12;
int openRightGate = 13;

// General Settings
int gateState = 0;  // (Estado de la puerta). 0: cerrada; 1: Izquierda Abierta; 2: Derecha Abierta
int delayTime = 20;

void setup() {
  Serial.begin(9600);
  Serial.println("====================");
}

void loop() {
  if(conditionForColector) {                    // Condición bluetooth para activar el motor colector
    digitalWrite(activateColector, HIGH);
  } else if(conditionForTurningOffColector) {   // Condición bluetooth para desactivar el motor colector
    digitalWrite(activateColector, LOW);
  }

  if(conditionForSorter) {                      // Condición bluetooth para activar el clasificador de pelotas
    digitalWrite(activateSorter, HIGH);
  } else if(conditionForTurningOffSorter) {     // Condición bluetooth para desactivar el clasificador de pelotas
    digitalWrite(activateSorter, LOW);
  }

  // Actualiza el estado global de la puerta
  if(conditionForOpenLeftGate) {                // Condición bluetooth para abrir la puerta izquierda
    gateState = 1;
  } else if (conditionForOpenRightGate) {       // Condición bluetooth para abrir la puerta derecha
    gateState = 2;  
  } else {                                      // Cerrar automáticamente cuando no se quiere abrir ningúna
    gateState = 0;
  }

  // Abre la puerta correspondiente o la cierra
  swtich (gateState) {
    case 0:
      CloseGate();
      break;
    case 1: 
      digitalWrite(openRightGate, LOW);
      digitalWrite(openLeftGate, HIGH);
      break;
    case 2: 
      digitalWrite(openLeftGate, LOW);
      digitalWrite(openRightGate, HIGH);
      break;
  }

  delay(20);
}

// Función para apagar señales; cierra la puerta
void CloseGate() {
  digitalWrite(openLeftGate, LOW);
  digitalWrite(openRightGate, LOW);
}
