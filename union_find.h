// union_find.h
#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>


/**
 * @class UnionFind
 * Estructura Disjoint Set Union (DSU) con compresión de rutas y unión por tamaño.
 */
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    /* Inicializa n conjuntos disjuntos [0 .. n-1] */
    explicit UnionFind(int n);

    /* Encuentra el representante con compresión de rutas */
    int find(int u);

    /* Une dos conjuntos por tamaño; devuelve true si se unieron, false si ya estaban conectados */
    bool unite(int u, int v);
};

#endif // UNION_FIND_H
