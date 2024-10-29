#include "graph.h"
#include <iostream>

Graph::Graph() {}

void Graph::setVertex(int vertex)
{
    this->vertexAmount = vertex;
}

void Graph::setEdges(int edges)
{
    this->edgesAmount = edges;
}

void Graph::createAdjacencyGraph()
{
    adjacencyMatrix = (int**)malloc(vertexAmount * sizeof(int*));
    for (int v = 0; v < vertexAmount; v++) {
        adjacencyMatrix[v] = (int*)calloc(vertexAmount, sizeof(int));
    }
    srand(time(NULL));

    int currentEdges = 0;
    for (int i = 0; i < vertexAmount && currentEdges < edgesAmount; i++) {
        for (int j = i + 1; j < vertexAmount && currentEdges < edgesAmount; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0;
            }
            else {
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1;
                currentEdges++;
            }
        }
    }
}

void Graph::createIncidenceGraph()
{
    incidenceMatrix = (int**)malloc(vertexAmount * sizeof(int*));
    for (int v = 0; v < vertexAmount; v++) {
        incidenceMatrix[v] = (int*)calloc(edgesAmount, sizeof(int));
    }

    int currentEdge = 0;
    for (int i = 0; i < vertexAmount; i++) {
        for (int j = i + 1; j < vertexAmount; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                incidenceMatrix[i][currentEdge] = 1;
                incidenceMatrix[j][currentEdge]= 1;
                currentEdge++;
            }
        }
    }
}

void Graph::createVerteciesArray()
{
    for (int v = 0; v < vertexAmount; v++) {
        Vertex vertex;
        vertex.index = v;
        double angle = 2 * M_PI * v / vertexAmount;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        vertex.coordinates.setX(x);
        vertex.coordinates.setY(y);
        vertecies.push_back(vertex);
    }
}

void Graph::createEdgesArray()
{
    for (int e = 0; e < edgesAmount; e++) {
        Edge edge;
        int count = 0;
        for (int v = 0; v < vertexAmount; v++) {
            if (incidenceMatrix[e][v] == 1) {
                if (count == 0) {
                    edge.startX = vertecies[v].coordinates.x();
                    edge.startY = vertecies[v].coordinates.y();
                    count++;
                }
                else {
                    edge.endX = vertecies[v].coordinates.x();
                    edge.endY = vertecies[v].coordinates.y();
                }
            }
            edges.push_back(edge);
        }
    }
}




