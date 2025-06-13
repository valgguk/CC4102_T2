#ifndef KRSUKAL_CON_FIND_H
#define KRSUKAL_CON_FIND_H

#include "estructuras.h"
#include <vector>

/**
 * Kruskal con optimización de find (compresión de rutas) usando arreglo ordenado de aristas.
 * @param edges Vector de todas las aristas del grafo.
 * @param num_nodes Número de nodos en el grafo.
 * @return Vector con las aristas del árbol de expansión mínima.
 */
std::vector<Edge> kruskal_sort_opti(std::vector<Edge> edges, int num_nodes);

/**
 * Kruskal con optimización de find (compresión de rutas) usando un heap clásico.
 * @param edges Vector de todas las aristas del grafo.
 * @param num_nodes Número de nodos en el grafo.
 * @return Vector con las aristas del árbol de expansión mínima.
 */
std::vector<Edge> kruskal_heap_opti(const std::vector<Edge>& edges, int num_nodes);

#endif // KRSUKAL_CON_FIND_H
