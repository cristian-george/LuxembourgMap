#include "Node.h"

Node::Node()
{
    number = 0;
}

Node::Node(const size_t& number, const QPointF& coord) :
    number(number), coord(coord) {}

const QPointF& Node::GetCoord() const noexcept
{
    return coord;
}

const size_t& Node::GetNumber() const noexcept
{
    return number;
}

void Node::SetCoord(const QPointF &coord)
{
    this->coord = coord;
}

void Node::SetNumber(const size_t &number)
{
    this->number = number;
}
