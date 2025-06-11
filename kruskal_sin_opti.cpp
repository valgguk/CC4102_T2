#include "estructuras.h"
#include "kruskal_sin_opti.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>

void kruskal_con_sort(std::vector<Edge>& edges, int n) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar temporizador

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight; // Ordenar por peso
    });

    auto end = std::chrono::high_resolution_clock::now(); // Finalizar temporizador
    std::cout << "Tiempo Kruskal sin optimización: " 
              << std::chrono::duration<double>(end - start).count()
              << " segundos\n";
    UnionFind uf(n);
    std::vector<Edge> mst; // Arbol cobertor mínimo

    for (const Edge& e : edges) {
        if (uf.unite(e.u->id, e.v->id)) {
            mst.push_back(e);
            // Si ya tenemos n-1 aristas, terminamos
            if (mst.size() == n - 1) break; 
        }
    }

    std::cout << "Arbol cobertor mínimo con sort tiene " << mst.size() << " aristas. \n";
}

//void kruskal_con_heap(std::vector<Edge>& edges, int n)