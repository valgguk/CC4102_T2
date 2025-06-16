#include "estructuras.h"
#include "kruskal_sin_opti.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <string>

/**
 * @brief Implementación de la estructura Union-Find sin optimización de compresión de caminos.
 * 
 * Esta estructura permite gestionar conjuntos disjuntos, útil para algoritmos como Kruskal.
 */
class UnionFindNoOpt {
private:
    std::vector<int> parent; ///< Vector que almacena el padre de cada nodo.
    std::vector<int> rank;   ///< Vector que almacena el rango (aproximación a la altura) de cada árbol.
public:
    /**
     * @brief Constructor de la clase UnionFindNoOpt.
     * 
     * @param n Número de nodos en el conjunto disjunto.
     */
    UnionFindNoOpt(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    /**
     * @brief Encuentra el representante del conjunto al que pertenece x.
     * 
     * Versión sin compresión de caminos.
     * @param x Elemento a buscar.
     * @return Representante del conjunto.
     */
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    /**
     * @brief Une los conjuntos a los que pertenecen x e y.
     * 
     * Utiliza unión por rango, pero sin compresión de caminos.
     * @param x Primer elemento.
     * @param y Segundo elemento.
     * @return true si se unieron los conjuntos, false si ya estaban unidos.
     */
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
        return true;
    }
};


/**
 * @brief Algoritmo de Kruskal usando ordenamiento para encontrar el árbol de expansión mínima.
 * 
 * @param edges Vector de aristas del grafo.
 * @param n Número de nodos.
 * @return Vector de aristas que forman el árbol de expansión mínima.
 */
std::vector<Edge> 
kruskal_sort(std::vector<Edge>& edges, int n) {
    // Ordenar las aristas por peso ascendente
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight; // Ordenar por peso
    });

    
    UnionFindNoOpt uf(n);
    std::vector<Edge> mst; // Arbol cobertor mínimo
    mst.reserve(n - 1); // Reservar espacio para n-1 aristas

    for (const Edge& e : edges) {
        int u = e.u->id, v = e.v->id;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v); // Unir los conjuntos
            mst.push_back(e);
            // Si ya tenemos n-1 aristas, terminamos
            if (mst.size() == n - 1) break; 
        }
    }

    return mst; // Retorna el árbol de expansión mínima

}

/**
 * @brief Algoritmo de Kruskal usando un heap (priority_queue) para seleccionar la arista de menor peso.
 * 
 * @param edges Vector de aristas del grafo.
 * @param n Número de nodos.
 * @return Vector de aristas que forman el árbol de expansión mínima.
 */
 std::vector<Edge> 
 kruskal_heap(const std::vector<Edge>& edges, int n) {
    //
    std::priority_queue<Edge> pq(edges.begin(), edges.end());
    UnionFindNoOpt uf(n);
    std::vector<Edge> mst; // Arbol cobertor mínimo
    mst.reserve(n - 1); // Reservar espacio para n-1 aristas

    while (!pq.empty() && mst.size() < n - 1) {
        Edge e = pq.top(); pq.pop();
        int u = e.u->id, v = e.v->id;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(e);
        }
    }

    return mst; // Retorna el árbol de expansión mínima
}


/**
 * @brief Función principal. Genera un grafo y ejecuta Kruskal con dos métodos distintos.
 * 
 * Permite especificar el número de nodos por línea de comandos.
 */
int main(int argc, char* argv[]) {
    //definir nodos
    int n = 1000;
    if (argc > 1) {
        n = std::stoi(argv[1]); // Leer el número de nodos desde la línea de comandos
    }
    auto nodes = generate_nodes(n);
    auto edges = generate_edges(nodes);

    // Ejecutar Kruskal con ordenamiento y con heap

    {
        auto edges_copy = edges; // Copiar los edges para el primer test
        auto start = std::chrono::high_resolution_clock::now(); // Iniciar el cronómetro
        auto mst_sort = kruskal_sort(edges, n);
        auto end = std::chrono::high_resolution_clock::now(); // Finalizar el cronómetro
        // Calcular la duración
        std::chrono::duration<double> duration = end - start;
        std::cout << "Kruskal (sort): " << duration.count() << " segundos" << "\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now(); // Iniciar el cronómetro
        auto mst_heap = kruskal_heap(edges, n);
        auto end = std::chrono::high_resolution_clock::now(); // Finalizar el cronómetro
        // Calcular la duración
        std::chrono::duration<double> duration = end - start;
        std::cout << "Kruskal (heap): " << duration.count() << " segundos" << "\n";
    
    }

    return 0;
}