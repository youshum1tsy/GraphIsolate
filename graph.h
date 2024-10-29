#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <vector>

struct Vertex {
    QPointF coordinates;
    QGraphicsEllipseItem* ellipse;
    int index;
};

struct Edge {
    QGraphicsLineItem* line;
    double startX;
    double startY;
    double endX;
    double endY;
};

class Graph
{
public:
    Graph();
    ~Graph();

    void setVertex(int vertex);
    void setEdges(int edges);

    void createAdjacencyGraph();
    void createIncidenceGraph();

    void createVerteciesArray();
    void createEdgesArray();

private:
    int** adjacencyMatrix;
    int** incidenceMatrix;

    std::vector<Vertex> vertecies;
    std::vector<Edge> edges;
    int radius = 500;

    int vertexAmount;
    int edgesAmount; // при вызове не давать пользователю ввести больше вершин чем vertex * (vertex - 1) / 2
};


#endif // GRAPH_H
