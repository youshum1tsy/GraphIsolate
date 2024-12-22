#include <QDebug>
#include <QGraphicsItem>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QRegularExpression>
#include "graph.h"

Graph::Graph() : vertexAmount(0), edgesAmount(0), adjacencyMatrix(nullptr), incidenceMatrix(nullptr) {

}

Graph::~Graph()
{
    clear();
}

void Graph::setVertex(int vertex)
{
    this->vertexAmount = vertex;
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

void Graph::deleteVerteciesArray()
{
    vertecies.clear();
}


void Graph::setEdges(int edges)
{
    this->edgesAmount = edges;
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

void Graph::deleteEdgesArray()
{
    edges.clear();
}

void Graph::setEdgeColor(int edgeIndex, const QColor& color)
{
    edges[edgeIndex].line->setPen(QPen(color));
}

void Graph::setAllEdgeColorBlack()
{
    for (Edge edge : edges) {
        edge.line->setPen(QPen(Qt::black));
    }
}

// исправить что главная диагональ всегда 0
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

void Graph::drawGraph(QGraphicsScene *scene)
{
    scene->clear();


    for (Vertex vertex : vertecies) {
        vertex.ellipse = new QGraphicsEllipseItem(vertex.coordinates.x() - 15, vertex.coordinates.y() - 15, 30, 30);
        vertex.ellipse->setBrush(QBrush(Qt::green));
        vertex.ellipse->setPen(QPen(Qt::black, 2));
        scene->addItem(vertex.ellipse);
    }

    for (int i = 0; i < edges.size(); ++i) {
        Edge& edge = edges[i];
        edge.line = new QGraphicsLineItem(edge.startX, edge.startY, edge.endX, edge.endY);
        edge.line->setPen(QPen(Qt::black, 2));
        scene->addItem(edge.line);

        QGraphicsTextItem* edgeNumberText = new QGraphicsTextItem(QString::number(i));

        qreal midX = edge.startX + 0.25 * (edge.endX - edge.startX);
        qreal midY = edge.startY + 0.25 * (edge.endY - edge.startY);

        edgeNumberText->setPos(midX, midY);
        edgeNumberText->setDefaultTextColor(Qt::black);

        QFont font = edgeNumberText->font();
        font.setPointSize(12);
        edgeNumberText->setFont(font);

        scene->addItem(edgeNumberText);
    }
}

void Graph::clear()
{
    deleteAdjacencyGraph();
    deleteIncidenceGraph();
    deleteVerteciesArray();
    deleteEdgesArray();
    deleteIndependentSet();
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
// обработать ошибки через QMessageBox;
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


void Graph::setIndependentSet(std::vector<std::vector<int>> set)
{
    independentSet = set;
}

std::vector<int> Graph::getIndependentItemSet(int index)
{
    return independentSet[index];
}

void Graph::deleteIndependentSet()
{
    for (std::vector<int> set : independentSet) {
        set.clear();
    }
    independentSet.clear();
}


std::vector<std::vector<int>> Graph::findAllIndependentEdgeSets(QListWidget* listEdgesSet)
{
    std::vector<std::vector<int>> allSets;
    std::vector<int> currentSet;
    std::vector<bool> used(edgesAmount, false);

    findIndependentEdgeSetsRecursive(0, currentSet, used, allSets);

    // Обновляем QListWidget
    listEdgesSet->clear();
    for (const auto& set : allSets) {
        QString setStr;
        for (int edge : set) {
            setStr += QString::number(edge) + " ";
        }
        listEdgesSet->addItem(setStr);
    }

    return allSets;
}

void Graph::markAdjacentEdges(int edgeIndex, std::vector<bool>& used)
{
    used[edgeIndex] = true;
    for (int i = 0; i < vertexAmount; i++) {
        if (incidenceMatrix[i][edgeIndex] != 0) {
            for (int j = 0; j < edgesAmount; j++) {
                if (incidenceMatrix[i][j] != 0) {
                    used[j] = true;
                }
            }
        }
    }
}

void Graph::findIndependentEdgeSetsRecursive(int edge, std::vector<int>& currentSet, std::vector<bool>& used, std::vector<std::vector<int>>& allSets)
{
    // Добавляем текущее множество в результат
    if (currentSet.size() > 1) {
        allSets.push_back(currentSet);
    }

    for (int i = edge; i < edgesAmount; i++) {
        if (!used[i]) {
            // Пробуем добавить ребро i
            currentSet.push_back(i);
            std::vector<bool> newUsed = used;
            markAdjacentEdges(i, newUsed);

            // Рекурсивно ищем дальше
            findIndependentEdgeSetsRecursive(i + 1, currentSet, newUsed, allSets);

            // Убираем ребро i (backtracking)
            currentSet.pop_back();
        }
    }
}

