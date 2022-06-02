#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LuxembourgMap.h"
#include "Graph.h"

class LuxembourgMap : public QMainWindow
{
    Q_OBJECT

public:
    LuxembourgMap(QWidget *parent = Q_NULLPTR);

    void AddNodesToGraph(const std::string&);
    void AddEdgesToGraph(const std::string&);

    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);

    void DrawNode(const Node&, Qt::GlobalColor, qreal);
    void DrawEdge(const Edge&, Qt::GlobalColor, qreal);

    size_t FindNodeCloseToClick(const QPointF&);
    qreal EuclideanDistance(const QPointF&, const QPointF&);

private slots:
    void on_loadMap_clicked();
    void on_drawMap_clicked();
    void on_applyDijkstra_clicked();
    void on_clearMap_clicked();

private:
    Ui::MainWindow ui;
    Graph graph;
    bool drawMap;
    size_t firstNode, lastNode;
    std::vector<size_t> minimumPath;
};
