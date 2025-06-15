#ifndef KRUSKAL_SIN_OPTI_H
#define KRUSKAL_SIN_OPTI_H

#include <vector>

/**
 * @file kruskal_sin_opti.h
 * @brief Declaraciones para el algoritmo de Kruskal sin optimización de compresión de caminos.
 *
 * Este archivo contiene las declaraciones de las funciones que implementan el algoritmo de Kruskal
 * utilizando una estructura Union-Find sin compresión de caminos.
 */

/**
 * @brief Algoritmo de Kruskal usando ordenamiento para encontrar el árbol de expansión mínima.
 * 
 * @param edges Vector de aristas del grafo.
 * @param n Número de nodos en el grafo.
 * @return Vector de aristas que forman el árbol de expansión mínima.
 */
std::vector<Edge> kruskal_sort(std::vector<Edge>& edges, int n);

/**
 * @brief Algoritmo de Kruskal usando un heap (priority_queue) para seleccionar la arista de menor peso.
 * 
 * @param edges Vector de aristas del grafo.
 * @param n Número de nodos en el grafo.
 * @return Vector de aristas que forman el árbol de expansión mínima.
 */
std::vector<Edge> kruskal_heap(const std::vector<Edge>& edges, int n);

#endif