#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <vector>
#include <queue>

/**
 * @struct Node
 * Representa un nodo en el grafo, con identificador y coordenadas.
 */
struct Node {
    int id;
    double x, y;
};

/**
 * @struct Edge
 * Representa una arista ponderada entre dos nodos.
 */
struct Edge {
    Node* u;
    Node* v;
    double weight;
    /**
     * Operador para heap mínimo.
     * @param other La otra arista con la que comparar peso.
     * @return true si esta arista tiene mayor peso (inversión para min-heap).
     */
    bool operator<(const Edge& other) const;
};

/**
 * Genera un vector de N nodos con posiciones aleatorias en [0,1]^2.
 * @param n Número de nodos a generar.
 * @return Vector de nodos con campos id, x, y inicializados.
 */
std::vector<Node> generate_nodes(int n);

/**
 * Calcula el peso de la arista entre dos nodos (distancia euclídea al cuadrado).
 * @param a Primer nodo.
 * @param b Segundo nodo.
 * @return Peso de la arista entre a y b.
 */
double edge_weight(const Node& a, const Node& b);

/**
 * Genera la lista de todas las aristas de un grafo completo.
 * @param nodes Vector de nodos existentes. Se asume IDs 0..n-1.
 * @return Vector con todas las aristas (i<j) y sus pesos.
 */
std::vector<Edge> generate_edges(std::vector<Node>& nodes);


#endif // ESTRUCTURAS_H
