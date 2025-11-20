#include <xmotion.h>

// ====== Pines de Oponente (0 = detecta) ======
int RightSensor         = A2; // Derecha
int RightDiagonalSensor = A4; // Diagonal derecha
int LeftDiagonalSensor  = 2;  // Diagonal izquierda
int LeftSensor          = 1;  // Izquierda

// ====== Pines Sensores de Línea (analógicos) ======
int LeftLine  = A5; // Línea izquierda
int RightLine = A1; // Línea derecha

// ====== Botón y LEDs ======
const int StartPin   = 10; // INPUT_PULLUP
const int LedNaranja = 8;  // LED reposo
const int LedAzul    = 9;  // LED cuenta 5s

// ====== Parámetros ======
int velBusqueda = 30; // velocidad de búsqueda lenta (0..255)

// ====== Estado del sistema ======
enum Estado { IDLE, COUNTDOWN, RUN };
Estado estado = IDLE;

// ====== Antirrebote & clic ======
bool prevBtn = HIGH; // INPUT_PULLUP -> reposo en HIGH
bool btnStable = HIGH;
unsigned long lastDebounce = 0;
const unsigned long DEBOUNCE_MS = 30;

bool buttonClicked() {
  bool reading = digitalRead(StartPin);
  if (reading != btnStable && (millis() - lastDebounce) > DEBOUNCE_MS) {
    btnStable = reading;
    lastDebounce = millis();
    if (prevBtn == LOW && btnStable == HIGH) { // flanco de subida = clic
      prevBtn = btnStable;
      return true;
    }
    prevBtn = btnStable;
  }
  return false;
}

// ====== LEDs ======
void ledsReposo() { digitalWrite(LedNaranja, HIGH); digitalWrite(LedAzul, LOW); }
void ledsOff()    { digitalWrite(LedNaranja, LOW);  digitalWrite(LedAzul, LOW); }

void parpadearAzul(unsigned long msTot, unsigned long blinkMs = 250) {
  unsigned long t0 = millis();
  bool estado = false;
  while (millis() - t0 < msTot) {
    estado = !estado;
    digitalWrite(LedAzul, estado);
    delay(blinkMs);
  }
  digitalWrite(LedAzul, LOW);
}

// ====== Seguridad por línea ======
bool safetyLinea() {
  const int UMBRAL_LINEA = 700;  // ajustá a tu tatami
  int l = analogRead(LeftLine);
  int r = analogRead(RightLine);

  if (l < UMBRAL_LINEA && r > UMBRAL_LINEA) {
    xmotion.Backward(120, 100);
    xmotion.Right0(120, 100);
    return true;
  } else if (l > UMBRAL_LINEA && r < UMBRAL_LINEA) {
    xmotion.Backward(120, 100);
    xmotion.Left0(120, 100);
    return true;
  } else if (l < UMBRAL_LINEA && r < UMBRAL_LINEA) {
    xmotion.Backward(120, 100);
    xmotion.Right0(120, 100);
    return true;
  }
  return false;
}

void setup() {
  pinMode(LedNaranja, OUTPUT);
  pinMode(LedAzul, OUTPUT);
  pinMode(StartPin, INPUT_PULLUP);

  pinMode(RightSensor,         INPUT);
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(LeftDiagonalSensor,  INPUT);
  pinMode(LeftSensor,          INPUT);

  pinMode(LeftLine,  INPUT);
  pinMode(RightLine, INPUT);

  Serial.begin(9600);
  xmotion.StopMotors(100);
  xmotion.MotorControl(0, 0);

  estado = IDLE;
  ledsReposo();
}

void loop() {
  // === Botón ===
  if (buttonClicked()) {
    if (estado == IDLE) {
      estado = COUNTDOWN;
    } else if (estado == RUN) {
      xmotion.MotorControl(0, 0);
      estado = IDLE;
      ledsReposo();
      return;
    }
  }

  // === Máquina de estados ===
  switch (estado) {
    case IDLE: {
      xmotion.MotorControl(0, 0); // inmóvil, naranja fijo
    } break;

    case COUNTDOWN: {
      digitalWrite(LedNaranja, LOW);
      parpadearAzul(5000, 250);   // 5 segundos
      estado = RUN;
      ledsOff();
    } break;

    case RUN: {
      // Seguridad línea
      if (safetyLinea()) return;

      // Lecturas de oponente
      int sR  = digitalRead(RightSensor);
      int sRD = digitalRead(RightDiagonalSensor);
      int sLD = digitalRead(LeftDiagonalSensor);
      int sL  = digitalRead(LeftSensor);

      // ====== Lógica de ataque con 4 sensores (0 = detecta) ======
      // Prioridades: detección bilateral -> frente; detección lateral -> giros; si no ve -> búsqueda lenta
      bool veDerecha = (sR == 1)  || (sRD == 0);
      bool veIzquierda = (sL == 1) || (sLD == 0);

      if (veDerecha && veIzquierda) {
        // Algo frente / ambos lados: atacar de frente
        xmotion.MotorControl(255, 255);
      }
      else if (veDerecha) {
        // Solo derecha: girar a la derecha (acercarse)
        if (sR == 0) {
          xmotion.MotorControl(-255, 255);   // giro fuerte derecha
        } else {
          xmotion.MotorControl(-100, 255);    // corrección suave derecha
        }
      }
      else if (veIzquierda) {
        // Solo izquierda: girar a la izquierda (acercarse)
        if (sL == 0) {
          xmotion.MotorControl(255, -255);   // giro fuerte izquierda
        } else {
          xmotion.MotorControl(255, -100);    // corrección suave izquierda
        }
      }
      else {
        // No ve a nadie: búsqueda lenta
        xmotion.MotorControl(velBusqueda, velBusqueda);
      }
    } break;
  }
}
