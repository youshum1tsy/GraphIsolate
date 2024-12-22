#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsLineItem>
#include <QListWidget>

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
    void createVerteciesArray();
    void deleteVerteciesArray();

    void setEdges(int edges);
    void createEdgesArray();
    void deleteEdgesArray();
    void setEdgeColor(int edgeIndex, const QColor& color);
    void setAllEdgeColorBlack();

    void createAdjacencyGraph();
    void createIncidenceGraph();
    void deleteAdjacencyGraph();
    void deleteIncidenceGraph();
    void drawGraph(QGraphicsScene *scene);
    void clear();

    void saveAdjacencyMatrixToJson(const QString& fileName);
    void saveIncidenceMatrixToJson(const QString& fileName);
    void uploadJsonToAdjacencyMatrix(const QString& filePath);
    void uploadJsonToIncidenceMatrix(const QString& filePath);

    void setIndependentSet(std::vector<std::vector<int>> set);
    std::vector<int> getIndependentItemSet(int index);
    void deleteIndependentSet();

    std::vector<std::vector<int>> findAllIndependentEdgeSets(QListWidget* listEdgesSet);


private:
    std::vector<Vertex> vertecies;
    std::vector<Edge> edges;
    int radius = 500;
    int vertexAmount;
    int edgesAmount;

    int** adjacencyMatrix;
    int** incidenceMatrix;

    std::vector<std::vector<int>> independentSet;

    void findIndependentEdgeSetsRecursive(int edge, std::vector<int>& currentSet,std::vector<bool>& used,std::vector<std::vector<int>>& allSets);
    void markAdjacentEdges(int edgeIndex, std::vector<bool>& used);
};


#endif // GRAPH_H
