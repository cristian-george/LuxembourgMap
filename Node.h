#ifndef NODE_H
#define NODE_H

#include <QPoint>

class Node
{
public:
    Node();
    Node(const size_t&, const QPointF&);

    const QPointF& GetCoord() const noexcept;
    const size_t& GetNumber() const noexcept;

    void SetCoord(const QPointF&);
    void SetNumber(const size_t&);

private:
    size_t number;
    QPointF coord;
};

#endif // NODE_H
