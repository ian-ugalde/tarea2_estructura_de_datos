#ifndef DATABASE_H
#define DATABASE_H

#include "cancion.h"
#include "tdas/map.h"

typedef struct {
  Map *por_genero;
  List *todas;
} Database;

// Crea una base de datos vacía
Database *database_create();

// Carga las canciones y retorna la cantidad de canciones cargadas (0 si el archivo no existe).
int database_cargar_csv(Database *db, const char *ruta);

// Busca todas las canciones de un género.
void database_buscar_por_genero(Database *db, const char *genero);

// Busca todas las canciones de un artista.
void database_buscar_por_artista(Database *db, const char *artista);

// Busca canciones por categoría de tempo.
void database_buscar_por_tempo(Database *db, char categoria);

#endif