# Código Fuente - Predator Robot

Este directorio contiene el firmware (código) principal de Predator.

## Archivo Principal

### 📄 predator.ino

Firmware completo de Predator Robot desarrollado en C/C++ para Arduino.

**Requisitos:**
- Arduino IDE (descarga gratuita en arduino.cc)
- Librería `xmotion` para control de motores
- Placa Arduino Leonardo o compatible

**Contenido:**
- Configuración de pines de sensores
- Máquina de estados (IDLE, COUNTDOWN, RUN)
- Lógica de detección de oponentes
- Lógica de seguridad de línea
- Funciones de control de LEDs
- Funciones de detección de botón

## Cómo Compilar y Cargar

### En Arduino IDE

1. **Abrir el archivo:**
   - Ir a Archivo → Abrir
   - Seleccionar `predator.ino`

2. **Configurar placa:**
   - Herramientas → Placa → Arduino Leonardo
   - Herramientas → Puerto → Seleccionar puerto COM

3. **Compilar:**
   - Presionar Ctrl+R o Verificar/Compilar

4. **Cargar:**
   - Presionar Ctrl+U o Upload
   - Esperar a que se complete

### En Línea de Comandos (Arduino CLI)

```bash
# Compilar
arduino-cli compile --fqbn arduino:avr:leonardo .

# Cargar
arduino-cli upload -p COM3 --fqbn arduino:avr:leonardo .
```

## Estructura del Código

```
┌─ CONFIGURACIÓN
│  ├─ Pines de sensores
│  ├─ Pines de controles
│  └─ Variables globales
│
├─ FUNCIONES AUXILIARES
│  ├─ Detección de botón
│  ├─ Control de LEDs
│  └─ Seguridad de línea
│
├─ SETUP()
│  ├─ Inicialización de pines
│  ├─ Configuración serial
│  └─ Estado inicial
│
└─ LOOP()
   ├─ Lectura de botón
   ├─ Máquina de estados
   └─ Control de motores
```

## Parámetros Configurables

### Velocidad de Búsqueda

```cpp
int velBusqueda = 30;  // Cambiar entre 0-255
```

Aumentar para búsqueda rápida, reducir para cautelosa.

### Umbral de Línea

```cpp
const int UMBRAL_LINEA = 700;  // Valores típicos 600-800
```

Calibrar según tu tatami real.

### Tiempo de Antirrebote

```cpp
const unsigned long DEBOUNCE_MS = 30;  // Milisegundos
```

### Pines de Sensores

```cpp
int RightSensor         = A2;   // Derecha
int RightDiagonalSensor = A4;   // Diagonal derecha
int LeftDiagonalSensor  = 2;    // Diagonal izquierda
int LeftSensor          = 1;    // Izquierda
int LeftLine            = A5;   // Línea izquierda
int RightLine           = A1;   // Línea derecha
```

### Pines de Control

```cpp
const int StartPin   = 10;  // Botón de inicio
const int LedNaranja = 8;   // LED indicador reposo
const int LedAzul    = 9;   // LED cuenta regresiva
```

## Debugging

### Serial Monitor

Para ver mensajes de debug, abrir Serial Monitor (9600 baud):

```
Herramientas → Serial Monitor
```

O agregar código para imprimir valores:

```cpp
Serial.print("Sensor IR: ");
Serial.println(sR);
```

## Máquina de Estados

El robot opera en 3 estados:

### IDLE (Espera)
- LED naranja encendido
- Esperando que presionen el botón
- Motores detenidos

### COUNTDOWN (Cuenta Regresiva)
- LED azul parpadeando 5 segundos
- Preparando competencia
- Transición a RUN después

### RUN (Competencia)
- LEDs apagados
- Buscando y atacando adversarios
- Detectando bordes

## Lógica de Ataque

```
SI detecta en ambos lados → Atacar de frente
SINO SI detecta derecha → Girar derecha
SINO SI detecta izquierda → Girar izquierda
SINO → Buscar lentamente
```

Si detecta línea → Retroceder y girar

## Velocidades

```
Ataque máximo (ambos sensores):  255, 255
Giro fuerte derecha:           -255, 255
Giro fuerte izquierda:          255, -255
Corrección suave derecha:       -100, 255
Corrección suave izquierda:      255, -100
Búsqueda lenta:                  ~30,  ~30
Retroceso defensa:             -120, -120
```

## Notas Importantes

1. **Librería xmotion**: Debe estar instalada en Arduino IDE
2. **Velocidades PWM**: 0-255, donde 255 es máxima
3. **Sensores**: Retornan 0 cuando detectan, 1 cuando no
4. **Línea blanca**: UMBRAL_LINEA debe ser >700 para detectarla
5. **Botón**: INPUT_PULLUP, activa en flanco de subida

## Modificaciones Comunes

### Cambiar velocidad de búsqueda

```cpp
// Línea 17 - cambiar de 30 a otro valor
int velBusqueda = 50;  // Más rápido
```

### Cambiar velocidad de ataque

Línea 149 en comportamiento RUN:
```cpp
xmotion.MotorControl(255, 255);  // Cambiar 255 a otro valor
```

### Agregar Serial Debug

En setup():
```cpp
Serial.begin(9600);
```

En loop():
```cpp
Serial.print("Estado: ");
Serial.println(estado);
```

---

Para más información, consultar el README principal.

**Última actualización**: Noviembre 20, 2025
