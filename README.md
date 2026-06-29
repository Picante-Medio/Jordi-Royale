# Jordi Royale

*(No confundir con Jordi Royal, hipotética marca de gelatina)*

**Picante Medio**

**2025–2026**

## Inicializar repositorio

El proyecto está pensado para compilar junto al motor (por cuestiones de hacer todo lo más compatible posible). No es el mejor planteamiento pero quita dolores de cabeza.

Es importante si se clona el repositorio de 0 ejecutar `git submodule update --init --recursive --remote` (los `.bat` se aseguran de ejecutar este comando). En algunas ocasiones se ha visto que se genera un directorio `./HUGO/HUGO/` (como si se duplicara), en este caso habrá que borrar el directorio mas profundo porque la inicialización del submódulo puede fallar.

## Como generar ficheros de proyecto en Windows

Ejecutar `build.bat` disponible en la raíz 

Los ficheros de solución se generarán en la ruta `./build/Windows/x64`, ahí estará disponible la solución del proyecto.

## Como compilar

Se puede utilizar o bien el `.sln` y compilar desde visual studio mediante la interfaz gráfica, o ejecutando `compile_debug.bat` o `compile_release.bat`, según convenga.

Se generará un `HUGO.exe` (o `HUGOd.exe`) en el directorio `./bin` desde el que ejecutar el juego.