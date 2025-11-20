# Modelos 3D - Predator Robot

Esta carpeta contiene los archivos STL (Stereolithography) para impresión 3D de las piezas estructurales del robot Predator.

## Archivos STL

### 📄 chasis.stl
Estructura principal del robot (chassis).
- Contiene montajes de motores
- Alojamiento de electrónica
- Conexiones estructurales

### 📄 base.stl
Base de soporte.
- Plataforma principal
- Distribuye peso

### 📄 bracket.stl
Soporte/bracket (puede ser para sensores, cables u otros).
- Accesorio de montaje
- Componente modular

## Cómo Imprimir

### Software Recomendado
- Cura (gratuito)
- PrusaSlicer (gratuito)
- Simplify3D (pago)

### Parámetros de Impresión Sugeridos

**Material**: PETG o ABS recomendados
- PLA también funciona, pero es más frágil
- PETG ofrece mejor resistencia a impactos

**Configuración**:
- Resolución (Layer Height): 0.2mm
- Relleno (Infill): 15-20%
- Velocidad: 50-60 mm/s
- Temperatura:
  - PETG: 230-240°C
  - ABS: 230-240°C
  - PLA: 200-210°C

**Soportes**: 
- Usar soportes donde sea necesario
- Generar automáticamente en slicer

**Placa de impresión**:
- Usar adhesivo o hairspray
- PETG necesita superficie caliente (70-80°C)

## Tiempo de Impresión Estimado

| Pieza | Tiempo | Peso |
|-------|--------|------|
| chasis.stl | 8-12h | 80-120g |
| base.stl | 3-5h | 30-50g |
| bracket.stl | 1-2h | 10-15g |
| **Total** | **12-19h** | **120-185g** |

## Guía de Uso

### 1. Descargar Archivo

- Descargar .stl a tu computadora

### 2. Abrir en Slicer

- Abrir software de slicing (Cura, etc.)
- Importar archivo STL
- Escala: Usar tamaño original (100%)

### 3. Verificar Orientación

- Pieza debe estar orientada para máxima estabilidad
- Usar vista previa para verificar
- Ajustar si es necesario

### 4. Generar Soportes

- Software generará automáticamente
- Revisar que no haya mucho material de soporte

### 5. Exportar G-code

- Generar archivo G-code para impresora
- Copiar a memoria SD o enviar por USB

### 6. Imprimir

- Cargar filamento
- Calentar placa y hot-end
- Comenzar impresión
- Monitorear primeras capas

### 7. Post-Procesamiento

- Remover soportes con cuidado
- Lijar bordes ásperos (papel 120-220)
- Limpiar residuos de filamento

## Calibración de Tolerancias

Si las piezas no encajan bien:

1. **Demasiado apretadas**:
   - Aumentar tamaño de agujeros en CAD
   - O lijar suavemente

2. **Muy sueltas**:
   - Usar pegamento (cianoacrilato) si es permanente
   - O usar tuerca-vástago para montaje ajustable

## Reemplazo de Piezas

Si una pieza se daña:

1. Anotar dimensiones de la dañada
2. Descargar STL original
3. Modificar en CAD si es necesario
4. Reimprimir siguiendo pasos anteriores

## Almacenamiento

Conservar archivos STL en:
- Dispositivo de almacenamiento local
- Nube (Google Drive, OneDrive, etc.)
- Repositorio GitHub

## Mejoras y Modificaciones

Si necesitas personalizar las piezas:

### Software de Modelado 3D (Gratuito)
- Fusion 360 (limitado gratis)
- FreeCAD (completamente gratis)
- Tinkercad (en línea, gratis)
- Blender (gratuito, complejo)

### Pasos para Modificar

1. Descargar STL
2. Importar en software CAD
3. Realizar cambios (agujeros, soportes, etc.)
4. Exportar como STL nuevo
5. Imprimir versión modificada

## Troubleshooting de Impresión

**Capas no se adhieren**:
- Limpiar placa
- Aumentar temperatura
- Reducir altura de capa

**Piezas deformadas**:
- Aumentar relleno
- Mejorar ventilación del hot-end
- Usar material con mejor temperatura

**Agujeros tapiados**:
- Aumentar altura de capa
- Usar soportes en agujeros

**Bordes ásperos**:
- Esto es normal en FDM
- Lijar después de imprimir

## Proveedores de Servicios de Impresión

Si no tienes impresora 3D:

| Servicio | País | Características |
|----------|-------|-----------------|
| Shapeways | Mundial | Múltiples materiales |
| Sculpteo | Europa | Buena calidad |
| Thingiverse Printify | Mundial | Económico |
| Tienda Local | Tu ciudad | Soporte local |

## Especificaciones de Archivo

```
Formato: STL (ASCII o Binary)
Escala: Milímetros (mm)
Unidades: 1 STL unit = 1 mm
```

---

Para más información, consultar el README principal.

**Última actualización**: Noviembre 20, 2025
