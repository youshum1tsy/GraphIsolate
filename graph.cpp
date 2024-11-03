#include <QDebug>
#include <QGraphicsItem>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QFile>
#include <QFileDialog>

#include <QRegularExpression>

#include "graph.h"

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
}

void Graph::saveAdjacencyMatrixToJson(const QString& fileName)
{
    static const QRegularExpression reSpace("\\s+(?=\\d)");
    static const QRegularExpression reBracket("\\s+\\]");
    static const QRegularExpression reDoubleBracket("\\]\\]");

    QJsonObject json;
    QJsonArray data;
    for (int i = 0; i < vertexAmount; i++) {
        QJsonArray jsonRow;
        for (int j = 0; j < vertexAmount; j++) {
            jsonRow.append(adjacencyMatrix[i][j]);
        }
        data.append(jsonRow);
    }
    json["data"] = data;

    QJsonDocument doc(json);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QString jsonString = "{\n";

        jsonString += QString("    \"vertex\": %1,\n").arg(vertexAmount);
        jsonString += QString("    \"edges\": %1,").arg(edgesAmount);
        jsonString += QString::fromUtf8(doc.toJson()).mid(1);

        jsonString.replace(reSpace, "");
        jsonString.replace(reBracket, "]");
        jsonString.replace(reDoubleBracket, "]\n    ]");

        file.write(jsonString.toUtf8());
        file.close();
    }
}

void Graph::saveIncidenceMatrixToJson(const QString &fileName)
{
    static const QRegularExpression reSpace("\\s+(?=\\d)");
    static const QRegularExpression reBracket("\\s+\\]");
    static const QRegularExpression reDoubleBracket("\\]\\]");

    QJsonObject json;
    QJsonArray data;

    for (int vertex = 0; vertex < vertexAmount; vertex++) {
        QJsonArray jsonRow;
        for (int edje = 0; edje < edgesAmount; edje++) {
            jsonRow.append(incidenceMatrix[vertex][edje]);
        }
        data.append(jsonRow);
    }
    json["data"] = data;

    QJsonDocument doc(json);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QString jsonString = "{\n";

        jsonString += QString("    \"vertex\": %1,\n").arg(vertexAmount);
        jsonString += QString("    \"edges\": %1,").arg(edgesAmount);
        jsonString += QString::fromUtf8(doc.toJson()).mid(1);

        jsonString.replace(reSpace, "");
        jsonString.replace(reBracket, "]");
        jsonString.replace(reDoubleBracket, "]\n    ]");

        file.write(jsonString.toUtf8());
        file.close();
    }
}

void Graph::uploadJsonToAdjacencyMatrix(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file:" << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject()) {
        qDebug() << "JSON is not an object";
        return;
    }

    QJsonObject jsonObject = document.object();
    if (!jsonObject.contains("vertex") ||
        !jsonObject.contains("edges") ||
        !jsonObject.contains("data")) {
        qDebug() << "Missing required keys";
        return;
    }

    vertexAmount = jsonObject["vertex"].toInt();
    edgesAmount = jsonObject["edges"].toInt();

    deleteAdjacencyGraph();

    adjacencyMatrix = (int**) malloc(sizeof(int*) * vertexAmount);
    for (int i = 0; i < vertexAmount; i++) {
        adjacencyMatrix[i] = (int*) calloc(vertexAmount, sizeof(int));
    }

    QJsonArray matrixArray = jsonObject["data"].toArray();

    if (matrixArray.size() != vertexAmount) {
        qDebug() << "Matrix size does not match vertex count";
        return;
    }

    for (int i = 0; i < vertexAmount; i++) {
        QJsonArray rowArray = matrixArray[i].toArray();
        if (rowArray.size() != vertexAmount) {
            qDebug() << "Row size does not match vertex count";
            return;
        }
        for (int j = i; j < vertexAmount; j++) {
            int value = rowArray[j].toInt();

            if (value != 0 && value != 1) {
                qDebug() << "Matrix elements must be 0 or 1";
                return;
            }

            if (i == j) {
                if (value != 0) {
                    qDebug() << "Diagonal elements must be 0";
                    return;
                }
            } else {
                int symmetricValue = matrixArray[j].toArray()[i].toInt();
                if (value != symmetricValue) {
                    qDebug() << "Matrix is not symmetric";
                    return;
                }
            }

            adjacencyMatrix[i][j] = value;

            if (i != j) {
                adjacencyMatrix[j][i] = value;
            }
        }
    }
}

void Graph::uploadJsonToIncidenceMatrix(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file:" << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (!document.isObject()) {
        qDebug() << "JSON is not an object";
        return;
    }

    QJsonObject jsonObject = document.object();
    if (!jsonObject.contains("vertex") ||
        !jsonObject.contains("edges") ||
        !jsonObject.contains("data")) {
        qDebug() << "Missing required keys";
        return;
    }

    vertexAmount = jsonObject["vertex"].toInt();
    edgesAmount = jsonObject["edges"].toInt();

    deleteIncidenceGraph();

    incidenceMatrix = (int**) malloc(sizeof(int*) * vertexAmount);
    for (int i = 0; i < vertexAmount; i++) {
        incidenceMatrix[i] = (int*) calloc(vertexAmount, sizeof(int));
    }

    QJsonArray matrixArray = jsonObject["data"].toArray();

    if (matrixArray.size() != vertexAmount) {
        qDebug() << "Matrix size does not match vertex count";
        return;
    }

    int edgeSum = 0;

    for (int i = 0; i < vertexAmount; i++) {
        QJsonArray rowArray = matrixArray[i].toArray();
        if (rowArray.size() != edgesAmount) {
            qDebug() << "Row size does not match edges count";
            return;
        }
        for (int j = 0; j < edgesAmount; j++) {
            int value = rowArray[j].toInt();

            if (value != 0 && value != 1) {
                qDebug() << "Matrix elements must be 0 or 1";
                return;
            }

            incidenceMatrix[i][j] = value;
            edgeSum += value;
        }
    }
    if (edgeSum != edgesAmount * 2) {
        qDebug() << "Invalid incidence matrix: incorrect number of connections";
        return;
    }
}




