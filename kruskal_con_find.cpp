// kruskal_con_opti.cpp
// Implementaciones de Kruskal con optimización de find usando arreglo ordenado y heap clásico

#include "estructuras.h"
#include <algorithm>
#include <queue>
#include <chrono>
#include <vector>
#include <iostream>
#include <string>

/**
 * Union-Find (Disjoint Set Union) con compresión de rutas y unión por tamaño.
 */
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    // Inicializa n conjuntos disjuntos [0 .. n-1]
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    // Encuentra el representante con compresión de rutas
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Une dos conjuntos por tamaño; devuelve true si se unieron, false si ya estaban conectados
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (size[u] < size[v])
            std::swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        return true;
    }
};

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
            if (mst.size() == (size_t)num_nodes - 1)
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

    while (!pq.empty() && mst.size() < (size_t)num_nodes - 1) {
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

/**
 * Ejemplo de uso en main: genera nodos, aristas y mide tiempos de ambas implementaciones.
 */
int main(int argc, char* argv[]) {
    int n = 1000;  // por defecto, número de nodos
    if (argc > 1) {
        n = std::stoi(argv[1]);
    }
    // Generar nodos y aristas
    auto nodes = generate_nodes(n);
    auto edges = generate_edges(nodes);

    // Medir implementación con sort
    {
        auto edges_copy = edges;
        auto start = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_sort_opti(edges_copy, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Kruskal (sort + compresión de rutas): " << elapsed.count() << " s\n";
    }

    // Medir implementación con heap
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_heap_opti(edges, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Kruskal (heap + compresión de rutas): " << elapsed.count() << " s\n";
    }

    return 0;
}
