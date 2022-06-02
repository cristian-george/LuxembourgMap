#include "LuxembourgMap.h"
#include <fstream>
#include <QMouseEvent>
#include <QPainter>

LuxembourgMap::LuxembourgMap(QWidget* parent)
    : QMainWindow(parent)
{
    drawMap = false;
    firstNode = lastNode = SIZE_MAX;
    ui.setupUi(this);

}

void LuxembourgMap::AddNodesToGraph(const std::string& fileName)
{
    const size_t min_latitude = 4945029;
    const size_t max_latitude = 5018275;
    const size_t min_longitude = 573929;
    const size_t max_longitude = 652685;

    QSize size = this->size();
    size_t height = size.height();
    size_t width = size.width();
    width -= 2 * width / 3;

    size_t number, latitude, longitude;

    std::ifstream fin(fileName);

    while (!fin.eof())
    {
        fin >> number >> latitude >> longitude;

        qreal x = width * (longitude - min_longitude) / (max_longitude - min_longitude) + width;
        qreal y = height * (max_latitude - latitude) / (max_latitude - min_latitude);

        graph.InsertNode(Node(number, QPointF(std::move(x), std::move(y))));
    }

    fin.close();
}

void LuxembourgMap::AddEdgesToGraph(const std::string& fileName)
{
    size_t number1, number2, length;

    std::ifstream fin(fileName);

    while (!fin.eof())
    {
        fin >> number1 >> number2 >> length;
        graph.InsertEdge(Edge(number1, number2, length));
    }

    fin.close();
}

void LuxembourgMap::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && drawMap)
    {
        QPointF point = event->pos();
        if (firstNode == SIZE_MAX)
        {
            firstNode = FindNodeCloseToClick(point);
        }
        else if (lastNode == SIZE_MAX)
        {
            lastNode = FindNodeCloseToClick(point);
        }

        update();
    }
}

void LuxembourgMap::DrawNode(const Node& node, Qt::GlobalColor color, qreal width)
{
    QPainter painter(this);

    const qreal radiusSize = 10;
    QRect rectangle(node.GetCoord().x() - radiusSize, node.GetCoord().y() - radiusSize, 2 * radiusSize, 2 * radiusSize);

    painter.setPen(QPen(color, width));
    painter.drawEllipse(rectangle);
}

void LuxembourgMap::DrawEdge(const Edge& edge, Qt::GlobalColor color, qreal width)
{
    QPainter painter(this);

    const auto& firstNode = graph.GetNode(edge.GetFirstNode());
    const auto& lastNode = graph.GetNode(edge.GetLastNode());

    QLineF line(firstNode.GetCoord(), lastNode.GetCoord());

    painter.setPen(QPen(color, width));
    painter.drawLine(line);
}

void LuxembourgMap::paintEvent(QPaintEvent* event)
{
    if (drawMap == true)
    {
        for (const auto& edge : graph.GetEdges())
        {
            DrawEdge(edge, Qt::darkGray, 1);
        }
    }

    if (firstNode != SIZE_MAX)
        DrawNode(graph.GetNode(firstNode), Qt::darkGreen, 5);

    if (lastNode != SIZE_MAX)
        DrawNode(graph.GetNode(lastNode), Qt::darkRed, 5);

    if (!minimumPath.empty())
    {
        for (size_t index = 0; index < minimumPath.size() - 1; ++index)
        {
            Edge edge;
            edge.SetFirstNode(minimumPath[index]);
            edge.SetLastNode(minimumPath[index + 1]);
            DrawEdge(edge, Qt::GlobalColor::darkCyan, 3);
        }
    }
}

size_t LuxembourgMap::FindNodeCloseToClick(const QPointF& point)
{
    size_t foundNode = SIZE_MAX;
    qreal minimumDistance = FLT_MAX;

    for (const auto& node : graph.GetNodes())
    {
        qreal euclideanDistance = EuclideanDistance(point, node.GetCoord());
        if (minimumDistance > euclideanDistance)
            minimumDistance = euclideanDistance, foundNode = node.GetNumber();
    }

    return foundNode;
}

qreal LuxembourgMap::EuclideanDistance(const QPointF& p1, const QPointF& p2)
{
    return sqrt(pow((p2.x() - p1.x()), 2) + pow((p2.y() - p1.y()), 2));
}

void LuxembourgMap::on_loadMap_clicked()
{
    AddNodesToGraph("nodes.txt");
    AddEdgesToGraph("edges.txt");
    graph.GenerateAdjacencyLists();

    ui.loadMap->setDisabled(true);
    update();
}

void LuxembourgMap::on_drawMap_clicked()
{
    drawMap = true;
    ui.drawMap->setDisabled(true);
    update();
}

void LuxembourgMap::on_applyDijkstra_clicked()
{
    if (firstNode != SIZE_MAX && lastNode != SIZE_MAX)
    {
        minimumPath = graph.DijkstraAlgorithm(firstNode, lastNode);

        std::ofstream out("selectedNodes.txt");
        out << firstNode << " " << lastNode << std::endl;

        for (size_t index = 0; index < minimumPath.size(); ++index)
            out << minimumPath[index] << " ";
        out.close();

        ui.applyDijkstra->setDisabled(true);
        update();
    }
}

void LuxembourgMap::on_clearMap_clicked()
{
    firstNode = lastNode = SIZE_MAX;
    minimumPath.clear();
    ui.applyDijkstra->setDisabled(false);
    update();
}