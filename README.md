# Frogger Simulator

Versión simplificada del clásico **Frogger**, hecha en **C++** con **[raylib](https://www.raylib.com/)**.

## ¿De dónde sale este proyecto?

Este repositorio es la entrega de la **CAA 1 (PAC1)** de la asignatura **Programación gráfica** (UOC). Parte de:

- La plantilla [raylib-quickstart](https://github.com/raylib-extras/raylib-quickstart)
- Los recursos y esqueleto de pantallas del material *InitialResourcesPAC1_Frogger*

La idea del enunciado: guiar una rana desde abajo hasta las “homes” de arriba, cruzando carretera (camiones) y río (tortugas y troncos), con vidas, tiempo, puntuación y pantallas de menú / fin de partida.

## Requisitos

- Windows
- Visual Studio 2022 (o compatible) con workload de C++
- Solución `.sln` del proyecto (incluye el subproyecto raylib)

## Cómo compilar y ejecutar

1. Abre el archivo `.sln` en Visual Studio.
2. Elige configuración **Debug** o **Release** y plataforma **x64**.
3. Compila y ejecuta (F5 / Ctrl+F5).
4. Asegúrate de que la carpeta `resources/` esté accesible desde el directorio de trabajo del ejecutable (normalmente la raíz del proyecto o `bin\Debug` / `bin\Release` según tu `OutDir`). Si el juego no carga texturas o sonidos, copia `resources` junto al `.exe`.

## Cómo jugar

### Controles

| Tecla | Acción |
|--------|--------|
| **W / ↑** | Saltar arriba |
| **S / ↓** | Saltar abajo |
| **A / ←** | Saltar izquierda |
| **D / →** | Saltar derecha |
| **Enter** | Empezar partida (Title) / replay (Ending) |
| **O** | Options (desde Title/Ending) / volver a Title (desde Options) |
| **F1** | Activar/desactivar grid de debug (solo en Gameplay) |

### Objetivo

Llena todas las bahías de llegada (homes) en la fila superior sin quedarte sin vidas ni sin tiempo.

- **Camiones y tortugas:** te quitan una vida al tocarlos.
- **Troncos:** te llevan; muévete encima de ellos. Si te sacan del mapa, pierdes una vida.
- **Homes vacías:** dan puntos. Bushes / homes ya llenas no cuentan (el salto se cancela).

### Flujo de pantallas

```
LOGO → TITLE ⇄ OPTIONS
         ↓
      GAMEPLAY → ENDING → TITLE / OPTIONS
```

## Estructura relevante

```
src/
  Frogger.cpp                 # main
  Game/                       # Player, Lane, Sprite, defines, Managers
  Menu/                       # pantallas (Logo, Title, Options, Gameplay, Ending)
resources/
  Game/                       # tiles, player, enemigos
  Menu/                       # logos, fuentes
  Sounds/                     # música y SFX
```

## Audio

- Menú: `Lily_Islands.mp3` (Title / Options, sin cortar al cambiar entre ellas)
- Ending: `Game_Over.mp3`
- Gameplay: hop / plunk (home) / squash (muerte)

## Licencia / créditos

- Motor: raylib (zlib/libpng)
- Juego y código de la práctica: Alvar Dalda (UOC)
- Assets: material de la PAC + recursos propios del menú (logo robot, fuente Hercules, etc.)
