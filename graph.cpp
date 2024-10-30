#include "graph.h"
#include <QDebug>
#include <QGraphicsItem>

Graph::Graph() : vertexAmount(0), edgesAmount(0), adjacencyMatrix(nullptr), incidenceMatrix(nullptr) {

}

Graph::~Graph()
{
    deleteAdjacencyGraph();
    deleteIncidenceGraph();
    deleteVerteciesArray();
    deleteEdgesArray();
}

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
    while (currentEdges < edgesAmount) {
        int i = rand() % vertexAmount;
        int j = rand() % vertexAmount;

        if (i != j && adjacencyMatrix[i][j] == 0) {
            adjacencyMatrix[i][j] = 1;
            adjacencyMatrix[j][i] = 1;
            currentEdges++;
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
        double x = 5000 + radius * cos(angle);
        double y = 5000 + radius * sin(angle);
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
            if (incidenceMatrix[v][e] == 1) {
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
        }
        edges.push_back(edge);
    }
}

void Graph::deleteAdjacencyGraph()
{
    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < vertexAmount; i++) {
            free(adjacencyMatrix[i]);
        }
        free(adjacencyMatrix);
        adjacencyMatrix = nullptr;
    }

}

void Graph::deleteIncidenceGraph()
{
    if (incidenceMatrix != nullptr) {
        for (int i = 0; i < vertexAmount; i++) {
            free(incidenceMatrix[i]);
        }
        free(incidenceMatrix);
        incidenceMatrix = nullptr;
    }
}

void Graph::deleteVerteciesArray()
{
    vertecies.clear();
}

void Graph::deleteEdgesArray()
{
    edges.clear();
}

void Graph::drawGraph(QGraphicsScene *scene)
{
    scene->clear();


    for (Vertex vertex : vertecies) {
        vertex.ellipse = new QGraphicsEllipseItem(vertex.coordinates.x() - 15, vertex.coordinates.y() - 15, 30, 30);
        vertex.ellipse->setBrush(QBrush(Qt::green));
        vertex.ellipse->setPen(QPen(Qt::black, 2));
        scene->addItem(vertex.ellipse);
    }

    for (Edge edge : edges) {
        edge.line = new QGraphicsLineItem(edge.startX, edge.startY, edge.endX, edge.endY);
        qDebug() << edge.startX << " " << edge.startY << " | "<< edge.endX << " " << edge.endY;
        edge.line->setPen(QPen(Qt::black, 2));
        scene->addItem(edge.line);
    }
    //node->textItem = new QGraphicsTextItem(QString::number(node->data));
    //node->textItem->setPos(x - 10, y - 10);
    //scene->addItem(node->textItem);
}




