#include "Edge.h"

Edge::Edge() : Edge(0, 0, 0) {}

Edge::Edge(size_t firstNode, size_t lastNode, size_t length) :
    firstNode(firstNode), lastNode(lastNode), length(length) {}

void Edge::SetFirstNode(const size_t& firstNode)
{
    this->firstNode = firstNode;
}

void Edge::SetLastNode(const size_t& lastNode)
{
    this->lastNode = lastNode;
}

void Edge::SetLength(const size_t& length)
{
    this->length = length;
}

const size_t& Edge::GetFirstNode() const noexcept
{
    return firstNode;
}

const size_t& Edge::GetLastNode() const noexcept
{
    return lastNode;
}

const size_t& Edge::GetLength() const noexcept
{
    return length;
}
