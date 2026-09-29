# Spotifind
 
## Descripción
 
Spotifind es una herramienta de consola escrita en C que permite cargar una base de datos de canciones (a partir de un archivo CSV) y buscarlas rápidamente por género, artista o tempo (velocidad). Está pensada como una forma simple y eficiente de explorar un catálogo musical de gran tamaño (en este caso, más de 114.000 canciones) directamente desde la terminal.

### TDAs utilizados

El proyecto usa dos TDAs: **Lista** (`List`) y **Mapa** (`Map`).

- **`Lista enlazada`**: se usa de dos formas.
  1. Cada canción guarda sus artistas en una `List` de strings (`cancion->artists`), ya que una canción puede tener uno o varios artistas colaboradores (separados por `;` en el CSV original).
  2. La base de datos completa se guarda en una `List` (`Database->todas`) con todas las canciones cargadas, en el orden en que aparecen en el CSV. Esta lista se recorre completa para la búsqueda por tempo (que filtra por rango numérico) y para la búsqueda por artista (ver más abajo por qué).
- **`Map`**: indexa las canciones **por género** (`Database->por_genero`), como `Map<género, List de canciones>`. Al cargar el CSV, cada canción se agrega a la lista de su género. Así, buscar por género es directo con `map_search`, en vez de recorrer las 114.000 canciones.
  No se indexó por artista con un `Map` porque el `Map` de los TDAs es una lista enlazada por dentro (cada búsqueda recorre nodo por nodo), y con mas o menos 30.000 artistas distintos eso resultaba muy lento al cargar. Los géneros son pocos en comparacion, así que ahí sí conviene. Por eso la búsqueda por artista recorre `Database->todas` directamente
 
## Cómo compilar y ejecutar
 
Este proyecto fue desarrollado en Replit y se ejecuta desde la **Shell** 
 
### Requisitos previos
 
- Replit.
- El archivo `data/song_dataset_.csv` debe existir dentro del proyecto (no se incluye en el repositorio por su tamaño, debe descargarse aparte y ubicarse en esa ruta).

### Pasos para compilar y ejecutar
 
1. Descarga o clona el repositorio completo. 
2. Abre una terminal (Shell).
3. Compila con el siguiente comando:
```bash
    gcc tdas/*.c cancion.c database.c main.c -Wno-unused-result -o spotifind
```
 
4. Ejecuta el programa con:
```bash
    ./spotifind
```
 
5. Al ejecutarlo, lo primero que debes hacer es cargar las canciones (opción `1`) e ingresar la ruta del archivo CSV:
```
    data/song_dataset_.csv
```
 
    La carga de las 114.000 canciones toma menos de 1 segundo.
 
## Funcionalidades
 
### Funcionando correctamente:
 
- **Cargar Canciones**: lee el CSV y carga todas las canciones en memoria, indexándolas por género para búsquedas rápidas.
- **Buscar por Género**: muestra todas las canciones que coinciden con el género ingresado (ej. `acoustic`, `samba`, `soul`).
- **Buscar por Artista**: muestra todas las canciones de un artista, incluso cuando la canción tiene varios artistas colaboradores.
- **Buscar por Tempo**: clasifica y muestra canciones como Lentas (< 80 BPM), Moderadas (80-120 BPM) o Rápidas (> 120 BPM).
- **Salir**: finaliza la ejecución correctamente.
### Problemas conocidos:
 
- La búsqueda por género y por artista es sensible a mayúsculas/minúsculas y requiere el nombre exacto tal como aparece en el CSV (no hay búsqueda parcial ni tolerancia a errores de tipeo).
- La búsqueda por artista ingresa el nombre completo en una sola línea (soporta espacios), pero no permite buscar por coincidencia parcial del nombre.
### A mejorar:
 
- Agregar búsqueda insensible a mayúsculas/minúsculas.
- Permitir coincidencias parciales (ej. buscar "Beatles" y encontrar "The Beatles").

 
## Ejemplo de uso
 
**Paso 1: Cargar las canciones**
 
```
========================================
              SPOTIFIND
========================================
1) Cargar Canciones
2) Buscar por Género
3) Buscar por Artista
4) Buscar por Tempo
5) Salir
Ingrese su opción: 1
Ingrese la ruta del archivo CSV: data/song_dataset_.csv
Se cargaron 114000 canciones.
```
 
**Paso 2: Buscar por género**
 
```
Ingrese su opción: 2
Ingrese el género: acoustic
ID: 0
Título: Comedy
Álbum: Comedy
Artistas: Gen Hoshino
Género: acoustic
Tempo: 87.92 BPM
-------------------------------
...
Total: 1000 canción(es) encontradas.
```
 
**Paso 3: Buscar por artista**
 
```
Ingrese su opción: 3
Ingrese el nombre del artista: Gen Hoshino
ID: 0
Título: Comedy
Álbum: Comedy
Artistas: Gen Hoshino
Género: acoustic
Tempo: 87.92 BPM
-------------------------------
Total: 10 canción(es) encontradas.
```
 
**Paso 4: Buscar por tempo**
 
```
Ingrese su opción: 4
Seleccione velocidad:
  l) Lenta    (< 80 BPM)
  m) Moderada (80 - 120 BPM)
  r) Rápida   (> 120 BPM)
Opción: l
...
Total: 7893 canción(es) encontradas.
```
 
**Paso 5: Salir**
 
```
Ingrese su opción: 5
¡Hasta luego!
```
 
## Autor
 
Trabajo individual — Ian Ugalde, PUCV, Estructura de Datos (ICI2240).