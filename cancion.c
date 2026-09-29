#include "cancion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cancion *cancion_create(int id, const char *track_name, const char *album_name,
                   List *artists, float tempo, const char *track_genre) {
  Cancion *cancion = (Cancion *)malloc(sizeof(Cancion));

  cancion->id = id;
  cancion->track_name = strdup(track_name);
  cancion->album_name = strdup(album_name);
  cancion->artists = artists;
  cancion->tempo = tempo;
  cancion->track_genre = strdup(track_genre);

  return cancion;
}

void cancion_print(Cancion *cancion) {
  if (cancion == NULL) return;

  printf("ID: %d\n", cancion->id);
  printf("Título: %s\n", cancion->track_name);
  printf("Álbum: %s\n", cancion->album_name);

  printf("Artistas: ");
  int primero = 1;
  for (char *artista = list_first(cancion->artists); artista != NULL;
       artista = list_next(cancion->artists)) {
    if (!primero) printf(", ");
    printf("%s", artista);
    primero = 0;
  }
  printf("\n");

  printf("Género: %s\n", cancion->track_genre);
  printf("Tempo: %.2f BPM\n", cancion->tempo);
  printf("-------------------------------\n");
}

void cancion_free(Cancion *cancion) {
  if (cancion == NULL) return;

  free(cancion->track_name);
  free(cancion->album_name);
  free(cancion->track_genre);

  // Libera cada string de artistas y luego la lista
  char *artista = list_first(cancion->artists);
  while (artista != NULL) {
    free(artista);
    artista = list_next(cancion->artists);
  }
  list_clean(cancion->artists);
  free(cancion->artists);

  free(cancion);
}