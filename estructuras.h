#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <vector>
#include <queue>

struct Node {
    int id;
    double x, y;
};

struct Edge {
    Node* u;
    Node* v;
    double weight;

    bool operator<(const Edge& other) const;
};

std::vector<Node> generate_nodes(int n);
double edge_weight(const Node& a, const Node& b);
std::vector<Edge> generate_edges(std::vector<Node>& nodes);


#endif // ESTRUCTURAS_H
