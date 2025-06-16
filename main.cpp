// Tests

// main.cpp
// Ejecuta las cuatro variantes de Kruskal: sort/opti, heap/opti, sort/sin-opti, heap/sin-opti.

#include "estructuras.h"
#include "kruskal_con_find.h"
#include "kruskal_sin_opti.h"
#include "union_find.h"     // necesario para DSU en las variantes
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    // Parámetro n: número de nodos
    int n = 1000;
    if (argc > 1) {
        try {
            n = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "Advertencia: argumento inválido, usando n = 1000\n";
        }
    }

    // Generar grafo completo con pesos aleatorios
    auto nodes = generate_nodes(n);
    auto edges = generate_edges(nodes);

    // 1) Kruskal con sort + compresión de rutas
    {
        auto edges_copy = edges;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_sort_opti(edges_copy, n);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = t1 - t0;
        std::cout << "Kruskal (sort + compresión de rutas): "
                  << dt.count() << " s, aristas = " << mst.size() << "\n";
    }

    // 2) Kruskal con heap + compresión de rutas
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_heap_opti(edges, n);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = t1 - t0;
        std::cout << "Kruskal (heap + compresión de rutas): "
                  << dt.count() << " s, aristas = " << mst.size() << "\n";
    }

    // 3) Kruskal con sort sin optimización de find
    {
        auto edges_copy = edges;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_sort(edges_copy, n);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = t1 - t0;
        std::cout << "Kruskal (sort sin optimización): "
                  << dt.count() << " s, aristas = " << mst.size() << "\n";
    }

    // 4) Kruskal con heap sin optimización de find
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto mst = kruskal_heap(edges, n);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = t1 - t0;
        std::cout << "Kruskal (heap sin optimización): "
                  << dt.count() << " s, aristas = " << mst.size() << "\n";
    }

    return 0;
}
