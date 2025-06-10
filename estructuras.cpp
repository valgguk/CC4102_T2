#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// -----------------------------
// Estructuras básicas
struct Node {
    int id;
    double x, y;
};

struct Edge {
    Node* u;
    Node* v;
    double weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight; // para min-heap con priority_queue
    }
};

// -----------------------------
// Generación de nodos aleatorios
vector<Node> generate_nodes(int n) {
    vector<Node> nodes(n);
    mt19937_64 rng(random_device{}());
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        nodes[i] = {i, dist(rng), dist(rng)};
    }
    return nodes;
}

// Cálculo del peso (distancia euclidiana al cuadrado)
double edge_weight(const Node& a, const Node& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Generación de todas las aristas posibles
vector<Edge> generate_edges(vector<Node>& nodes) {
    vector<Edge> edges;
    int n = nodes.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edges.push_back({&nodes[i], &nodes[j], edge_weight(nodes[i], nodes[j])});
    return edges;
}

// -----------------------------
// Medición de estructuras

void construir_con_sort(vector<Edge> edges) {
    auto start = chrono::high_resolution_clock::now();

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = end - start;
    cout << "Tiempo sort: " << duracion.count() << " segundos" << endl;
}

void construir_con_heap(vector<Edge> edges) {
    auto start = chrono::high_resolution_clock::now();

    priority_queue<Edge> heap(edges.begin(), edges.end());

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = end - start;
    cout << "Tiempo heap: " << duracion.count() << " segundos" << endl;
}

// -----------------------------
// Main para prueba

int main() {
    int n = 512; // ejemplo para 512 nodos
    auto nodes = generate_nodes(n);
    auto edges = generate_edges(nodes);

    auto edges_copy1 = edges;
    auto edges_copy2 = edges;

    construir_con_sort(edges_copy1);
    construir_con_heap(edges_copy2);

    return 0;
}
