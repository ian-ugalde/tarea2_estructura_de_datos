#ifndef CANCION_H
#define CANCION_H

#include "tdas/list.h"


typedef struct {
  int id;
  char *track_name;
  char *album_name;
  List *artists;
  float tempo;
  char *track_genre;
} Cancion;

// Crea una canción reservando memoria propia para cada campo (copia los strings).
Cancion *cancion_create(int id, const char *track_name, const char *album_name,
                   List *artists, float tempo, const char *track_genre);

// Imprime la información de una canción con un formato consistente.
void cancion_print(Cancion *cancion);

// Libera la memoria de una canción (incluye sus strings y la lista de artistas).
void cancion_free(Cancion *cancion);

#endif
