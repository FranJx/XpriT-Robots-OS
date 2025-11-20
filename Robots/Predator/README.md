# 🤖 Predator - Mini Sumo Autónomo Profesional

![Predator Robot](Docs/IMG/ppp%20(1).png)

## Descripción General

**Predator** es un robot Mini Sumo Autónomo de clase profesional, diseñado por **Marcelo D. Benítez**, co-líder de **XpriT Robotics**. Este robot ha participado en numerosas competencias de robótica autónoma, obteniendo satisfactorios resultados en las categorías de mini sumo.

Predator combina ingeniería mecánica de precisión, electrónica avanzada y algoritmos de reacción rápida para crear una máquina competitiva capaz de detectar, perseguir y empujar adversarios fuera del ring de competencia con efectividad.

### Características Principales

- ⚡ **Sistema de 4 sensores**: Detecta adversarios en múltiples direcciones
- 🎯 **Lógica de ataque**: Búsqueda y persecución automática
- 🔋 **Autonomía**: Duración completa de competencia (5 minutos de ronda)
- 🛠️ **Diseño optimizado**: Tras múltiples iteraciones competitivas
- 📐 **Dimensiones competitivas**: Dentro de especificaciones oficial
- 💪 **Motor diferencial**: Control de giros precisos y empuje

## Especificaciones Técnicas

### Hardware

| Parámetro | Valor |
|-----------|-------|
| Microcontrolador | Placa Xmotion Jsumo (Arduino Leonardo) |
| Sensores de Oponente | 4 (IR JS40F - rango ~40cm) |
| Sensores de Línea | 2 (Sensor ML1) |
| Motores | 2x Jsumo 750RPM @ 6V |
| Ruedas | JS2622 (26mm diámetro) |
| Batería | LiPo 3S 350mAh 11.1V |
| Sistema de Movimiento | Motor diferencial (tracción dual) |
| Botón de inicio | Cuenta regresiva 5s antes de competencia |
| Indicadores | 2 LEDs (naranja: espera, azul: countdown) |

### Especificaciones de Rendimiento

**A 12V (alimentación real con LiPo 3S):**

| Parámetro | Valor |
|-----------|-------|
| RPM (teórico) | 1500 RPM |
| Velocidad lineal máxima | 204 cm/s (2.04 m/s) |
| Velocidad en km/h | 7.35 km/h |
| Velocidad angular (rueda) | 157.08 rad/s |
| Velocidad de giro (robot) | 2925 °/s (51.05 rad/s) |
| Pines digitales | 8 |
| Pines analógicos | 2 |
| Velocidades PWM | 0-255 |
| Velocidad búsqueda | 30 PWM (configurable) |

## 📦 Contenido del Repositorio

```
Predator/
├── README.md                    # Este archivo
├── LICENCIA.md                  # Licencia de código abierto
├── src/
│   └── predator.ino             # Firmware principal del robot
├── Docs/
│   ├── IMG/                     # Fotografías del robot en acción
│   │   ├── ppp (1).png
│   │   └── ppp (2).png
│   └── Componentes.docx         # Lista de componentes
└── STL/                         # Archivos para impresión 3D
    ├── base.stl
    ├── bracket.stl
    └── chasis.stl
```

## 🏆 Logros y Participaciones

- ✅ Múltiples participaciones en competencias Mini Sumo profesionales
- ✅ Diseño robusto tras 7+ generaciones de prototipo
- ✅ Algoritmo de búsqueda y ataque refinado en campo real
- ✅ Sistema de seguridad de línea efectivo y rápido

## 🎯 Algoritmo de Comportamiento

Predator utiliza una máquina de estados reactiva con 4 sensores de oponente:

### Lógica de Detección (4 sensores)

```
Sensor Derecha         → Detección lateral derecha (A2)
Sensor Diagonal Der    → Detección 45° derecha (A4)
Sensor Diagonal Izq    → Detección 45° izquierda (pin 2)
Sensor Izquierda       → Detección lateral izquierda (pin 1)
```

**Sensores de línea (borde de pista):**
- Línea Izquierda (A5) → Detecta borde blanco
- Línea Derecha (A1) → Detecta borde blanco

### Estados de Comportamiento

| Estado | Acción | Condición |
|--------|--------|-----------|
| **IDLE** | Inmóvil, LED naranja | Esperando botón |
| **COUNTDOWN** | Parpadeo azul 5s | Cuenta regresiva antes de competencia |
| **RUN** | Búsqueda o ataque | Competencia en curso |

### Lógica de Ataque

1. **Si detecta en ambos lados** → Atacar de frente (máxima velocidad: 255)
2. **Si detecta solo derecha** → Girar a derecha (velocidad 255/-255)
3. **Si detecta solo izquierda** → Girar a izquierda (velocidad -255/255)
4. **Si no detecta nada** → Búsqueda lenta (velocidad ~30)

### Seguridad de Línea

Si el robot detecta que está saliendo del ring:
- Retrocede a velocidad 120
- Gira 90° para alejarse del borde
- Retoma búsqueda automáticamente

## 🖼️ Galería

### Predator en Acción

![Predator Robot - Vista 1](Docs/IMG/ppp%20(1).png)

![Predator Robot - Vista 2](Docs/IMG/ppp%20(2).png)

## 💻 Código Fuente

El firmware de Predator está desarrollado en **C/C++** para Arduino, utilizando la librería **xmotion** para control de motores.

### Estructura Principal

```cpp
// SENSORES DE OPONENTE (4 puntos de detección)
int RightSensor         = A2;  // Derecha
int RightDiagonalSensor = A4;  // Diagonal derecha
int LeftDiagonalSensor  = 2;   // Diagonal izquierda
int LeftSensor          = 1;   // Izquierda

// SENSORES DE LÍNEA (Seguridad de borde)
int LeftLine  = A5;   // Línea izquierda
int RightLine = A1;   // Línea derecha

// CONTROLES
const int StartPin   = 10;  // Botón de inicio
const int LedNaranja = 8;   // LED de espera
const int LedAzul    = 9;   // LED de cuenta regresiva
```

### Máquina de Estados

El robot opera en 3 estados principales:

1. **IDLE**: Esperando que presionen botón (LED naranja fijo)
2. **COUNTDOWN**: Cuenta regresiva de 5 segundos (LED azul parpadeando)
3. **RUN**: En competencia (LEDs apagados)

### Lógica de Comportamiento

```cpp
// Prioridades de ataque:
if (detecta_ambos_lados) {
  atacar_de_frente();      // Velocidad máxima (255, 255)
} 
else if (detecta_derecha) {
  girar_a_derecha();       // Velocidad (-255, 255)
} 
else if (detecta_izquierda) {
  girar_a_izquierda();     // Velocidad (255, -255)
} 
else {
  buscar_lentamente();     // Velocidad (~30, ~30)
}

// Protección de línea:
if (sensor_linea_activo) {
  retroceder_y_girar();    // Velocidad (-120), giro 90°
}
```

### Variables Configurables

```cpp
// Velocidad de búsqueda (0-255)
int velBusqueda = 30;  // Ajustar según tatami

// Umbral de detección de línea
const int UMBRAL_LINEA = 700;  // Valores analógicos

// Antirrebote del botón
const unsigned long DEBOUNCE_MS = 30;  // milisegundos
```

### Compilación y Carga

```bash
# Abrir en Arduino IDE
1. Archivo → Abrir → src/predator.ino
2. Seleccionar placa: Arduino Leonardo
3. Seleccionar puerto COM
4. Cargar (Ctrl+U)
```

**Requisitos:**
- Arduino IDE instalado
- Librería `xmotion` disponible
- Placa Arduino Leonardo o compatible

## ⚙️ Configuración y Ajustes

### Parámetros Ajustables

Los siguientes parámetros pueden modificarse en `src/predator.ino` según tu tatami y preferencias:

#### Velocidades (0-255)

```cpp
int velBusqueda = 30;  // Velocidad de búsqueda
                       // Aumentar para buscar más rápido
                       // Reducir para búsqueda cautelosa
```

#### Umbrales de Línea

```cpp
const int UMBRAL_LINEA = 700;  // Valor para detectar línea blanca
                                // Probar en el tatami real
                                // Valores típicos: 600-800
```

#### Antirrebote

```cpp
const unsigned long DEBOUNCE_MS = 30;  // Tiempo antirrebote botón
```

### Calibración en el Tatami

1. **Ajustar velocidad de búsqueda**
   - Si el robot es muy lento: aumentar `velBusqueda`
   - Si es muy rápido: reducir `velBusqueda`

2. **Calibrar detectores de línea**
   - Poner sensor sobre línea blanca
   - Leer valor analógico con Serial Monitor
   - Ajustar `UMBRAL_LINEA` según sea necesario

3. **Probar velocidades de giro**
   - Valores actuales: ±255 giros máximos
   - ±100 giros suaves
   - Ajustar según respuesta deseada

## 🛠️ Mantenimiento y Reparación

### Antes de Cada Competencia

- [ ] Verificar que el botón responde correctamente
- [ ] Probar LED naranja y LED azul
- [ ] Limpiar lentes de sensores IR
- [ ] Verificar que los motores responden a comandos
- [ ] Revisar tensión correcta entre ruedas (no muy apretadas)
- [ ] Cargar batería completamente

### Solución de Problemas Comunes

**El robot no se mueve**
- Verificar conexión de batería
- Comprobar que Arduino cargó el firmware
- Usar Serial Monitor para debug (9600 baud)

**El robot tuerce a un lado**
- Motor derecho e izquierdo pueden tener potencias diferentes
- Ajustar velocidades en los giros
- Revisar si las ruedas están alineadas

**No detecta al oponente**
- Revisar que sensores no están sucios o bloqueados
- Verificar lecturas analógicas en Serial Monitor
- Probar que los sensores devuelven 0 (detectan) cuando activan

**Se cae del ring**
- Revisar umbral de línea en código
- Probar que sensores de línea funcionan
- Calibrar `UMBRAL_LINEA` en el tatami real

### Piezas de Repuesto Comúnmente Requeridas

- Llantas (desgaste de competencia)
- Sensores (golpes o desconexiones)
- Conectores y cables (tracción o daño)
- Piezas impresas (fracturas por impacto)

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el repositorio
2. Crea una rama para tu mejora (`git checkout -b feature/MiMejora`)
3. Commit tus cambios (`git commit -m 'Agregar MiMejora'`)
4. Push a la rama (`git push origin feature/MiMejora`)
5. Abre un Pull Request

## 📚 Referencias y Recursos

- [Pagina Oficial de XpriT Robotics](http://xprit-robotics.com/)
- [Pagina de Instagram p/ consultas](https://www.instagram.com/xprit_robotics/)


## 📊 Bill of Materials (BOM)

Para la lista completa actualizada, ver `Docs/Componentes.md`

| Componente | Cantidad | Enlace |
|---|---|---|
| Placa Xmotion | 1 | [JsumoRobots](https://www.jsumo.com/xmotion-robot-controller) |
| Motores Jsumo 750RPM | 2 | [JsumoRobots](https://www.jsumo.com/core-dc-motor-6v-750rpm) |
| Sensores JS40F (IR) | 4 | [JsumoRobots](https://www.jsumo.com/js40f-digital-infrared-ir-distance-sensor-min-40-cm-range) |
| Ruedas JS2622 (Par) | 1 | [JsumoRobots](https://www.jsumo.com/js2622-aluminum-silicone-wheel-pair) |
| Sensores Línea ML1 | 2 | [JsumoRobots](https://www.jsumo.com/micro-line-sensor-ml1) |
| Batería LiPo 3S 350mAh | 1 | - |

**Proveedor principal:** [JsumoRobots](https://www.jsumo.com/) - Todos los componentes electrónicos disponibles en este sitio.

## 🎯 Roadmap Futuro

### Versión 1.1
- [ ] Optimización de velocidades basada en tatami
- [ ] Mejora de algoritmo de búsqueda
- [ ] Documentación de calibración completa

### Versión 2.0 (Futuro)
- [ ] Integración de sensores ultrasónicos
- [ ] Sistema mejorado de detección multirrango
- [ ] Modo de radio control remoto para debug
- [ ] Telemetría en tiempo real

### Ideas de Mejora
- Detectores de colisión para absorber impactos
- Sistema de peso distribuido optimizado
- Variante con mayor potencia de motor
- Interfaz de configuración inalámbrica

## ⚖️ Licencia

Este proyecto está bajo la **Licencia de Código Abierto por Mención de Autor**.

Ver `LICENCIA.md` para términos completos y legales.

```
Predator Robot - Mini Sumo Autónomo Profesional
Diseño original: Marcelo D. Benítez
Organización: XpriT Robotics
Licencia: Código Abierto por Mención de Autor
Año: 2024-2025
```

## 📞 Contacto y Soporte

- **Diseñador**: Marcelo D. Benítez (co-líder XpriT Robotics)
- **Organización**: [XpriT Robotics](https://xpritrobotics.org)
- **Email**: contact@xpritrobotics.org
- **Issues y Soporte**: GitHub Issues en este repositorio

---

**Predator Robot** © 2024-2025 XpriT Robotics  
Licencia: Código Abierto por Mención de Autor

*Última actualización: Noviembre 20, 2025*
