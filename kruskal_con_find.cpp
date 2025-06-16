// kruskal_con_find.cpp
// Implementaciones de Kruskal con optimización de find usando arreglo ordenado y heap clásico

#include "estructuras.h"
#include "kruskal_con_find.h"
#include "union_find.h"
#include <algorithm>
#include <queue>
#include <chrono>
#include <vector>
#include <iostream>
#include <string>

/**
 * Kruskal con arreglo ordenado de aristas y optimización de find (compresión de rutas).
 * @param edges Vector de todas las aristas.
 * @param num_nodes Número de nodos en el grafo.
 * @return Vector con las aristas del árbol de expansión mínima.
 */
std::vector<Edge> kruskal_sort_opti(std::vector<Edge> edges, int num_nodes) {
    // Ordenar aristas por peso ascendente
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    UnionFind uf(num_nodes);
    std::vector<Edge> mst;
    mst.reserve(num_nodes - 1);

    for (const Edge& e : edges) {
        int u = e.u->id;
        int v = e.v->id;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(e);
            if (mst.size() == static_cast<size_t>(num_nodes - 1))
                break;
        }
    }
    return mst;
}

/**
 * Kruskal con heap clásico y optimización de find (compresión de rutas).
 * @param edges Vector de todas las aristas.
 * @param num_nodes Número de nodos en el grafo.
 * @return Vector con las aristas del árbol de expansión mínima.
 */
std::vector<Edge> kruskal_heap_opti(const std::vector<Edge>& edges, int num_nodes) {
    // Construir heap mínimo (Edge::operator< invertido en "estructuras.cpp")
    std::priority_queue<Edge> pq(edges.begin(), edges.end());

    UnionFind uf(num_nodes);
    std::vector<Edge> mst;
    mst.reserve(num_nodes - 1);

    while (!pq.empty() && mst.size() < static_cast<size_t>(num_nodes - 1)) {
        Edge e = pq.top();
        pq.pop();
        int u = e.u->id;
        int v = e.v->id;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(e);
        }
    }
    return mst;
}

