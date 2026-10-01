#include "database.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparadores para los Map 
static int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

Database *database_create() {
  Database *db = (Database *)malloc(sizeof(Database));
  db->por_genero = map_create(is_equal_str);
  db->todas = list_create();
  return db;
}


static void agregar_a_indice(Map *mapa, const char *clave, Cancion *cancion) {
  MapPair *par = map_search(mapa, (void *)clave);
  if (par == NULL) {
    List *lista = list_create();
    list_pushBack(lista, cancion);
    map_insert(mapa, strdup(clave), lista);
  } else {
    List *lista = (List *)par->value;
    list_pushBack(lista, cancion);
  }
}

int database_cargar_csv(Database *db, const char *ruta) {
  FILE *archivo = fopen(ruta, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return 0;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ',');

  int contador = 0;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    int id = atoi(campos[0]);
    List *artistas = split_string(campos[2], ";");
    float tempo = atof(campos[18]);

    Cancion *cancion =
        cancion_create(id, campos[4], campos[3], artistas, tempo, campos[20]);

    list_pushBack(db->todas, cancion);
    agregar_a_indice(db->por_genero, cancion->track_genre, cancion);

    contador++;
  }

  fclose(archivo);
  return contador;
}

void database_buscar_por_genero(Database *db, const char *genero) {
  MapPair *par = map_search(db->por_genero, (void *)genero);
  if (par == NULL) {
    printf("No se encontraron canciones del género \"%s\".\n", genero);
    return;
  }

  List *lista = (List *)par->value;
  int encontradas = 0;
  for (Cancion *c = list_first(lista); c != NULL; c = list_next(lista)) {
    cancion_print(c);
    encontradas++;
  }
  printf("Total: %d canción(es) encontradas.\n", encontradas);
}

void database_buscar_por_artista(Database *db, const char *artista) {
  int encontradas = 0;
  for (Cancion *c = list_first(db->todas); c != NULL;
       c = list_next(db->todas)) {
    for (char *a = list_first(c->artists); a != NULL;
         a = list_next(c->artists)) {
      if (strcmp(a, artista) == 0) {
        cancion_print(c);
        encontradas++;
        break; // si ya se imprimio: no ver otros artistas
      }
    }
  }

  if (encontradas == 0)
    printf("No se encontraron canciones del artista \"%s\".\n", artista);
  else
    printf("Total: %d canción(es) encontradas.\n", encontradas);
}

void database_buscar_por_tempo(Database *db, char categoria) {
  int encontradas = 0;
  for (Cancion *c = list_first(db->todas); c != NULL;
       c = list_next(db->todas)) {
    int coincide = 0;
    if (categoria == 'l' && c->tempo < 80)
      coincide = 1;
    else if (categoria == 'm' && c->tempo >= 80 && c->tempo <= 120)
      coincide = 1;
    else if (categoria == 'r' && c->tempo > 120)
      coincide = 1;

    if (coincide) {
      cancion_print(c);
      encontradas++;
    }
  }
  printf("Total: %d canción(es) encontradas.\n", encontradas);
}