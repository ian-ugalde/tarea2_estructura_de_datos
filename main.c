#include "cancion.h"
#include "database.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <string.h>

void mostrar_menu() {
  limpiarPantalla();
  puts("========================================");
  puts("              SPOTIFIND");
  puts("========================================");
  puts("1) Cargar Canciones");
  puts("2) Buscar por Género");
  puts("3) Buscar por Artista");
  puts("4) Buscar por Tempo");
  puts("5) Salir");
  printf("Ingrese su opción: ");
}

int main() {
  Database *db = database_create();
  int cargado = 0; // evita que busquen antes de cargar el CSV
  char opcion;

  do {
    mostrar_menu();
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1': {
      char ruta[256];
      printf("Ingrese la ruta del archivo CSV: ");
      scanf("%s", ruta);

      int n = database_cargar_csv(db, ruta);
      if (n > 0) {
        printf("Se cargaron %d canciones.\n", n);
        cargado = 1;
      }
      break;
    }
    case '2': {
      if (!cargado) {
        printf("Primero debes cargar las canciones (opción 1).\n");
        break;
      }
      char genero[100];
      printf("Ingrese el género: ");
      scanf("%s", genero);
      database_buscar_por_genero(db, genero);
      break;
    }
    case '3': {
      if (!cargado) {
        printf("Primero debes cargar las canciones (opción 1).\n");
        break;
      }
      char artista[200];
      printf("Ingrese el nombre del artista: ");
      scanf(" %[^\n]", artista);
      database_buscar_por_artista(db, artista);
      break;
    }
    case '4': {
      if (!cargado) {
        printf("Primero debes cargar las canciones (opción 1).\n");
        break;
      }
      printf("Seleccione velocidad:\n");
      printf("  l) Lenta    (< 80 BPM)\n");
      printf("  m) Moderada (80 - 120 BPM)\n");
      printf("  r) Rápida   (> 120 BPM)\n");
      printf("Opción: ");
      char categoria;
      scanf(" %c", &categoria);
      database_buscar_por_tempo(db, categoria);
      break;
    }
    case '5':
      printf("¡Hasta luego!\n");
      break;
    default:
      printf("Opción inválida.\n");
    }

    if (opcion != '5') presioneTeclaParaContinuar();

  } while (opcion != '5');

  return 0;
}