#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge
{
public:
    Edge();
    Edge(size_t, size_t, size_t);

    void SetFirstNode(const size_t&);
    void SetLastNode(const size_t&);
    void SetLength(const size_t&);

    const size_t& GetFirstNode() const noexcept;
    const size_t& GetLastNode() const noexcept;
    const size_t& GetLength() const noexcept;

private:
    size_t firstNode;
    size_t lastNode;
    size_t length;
};

#endif // EDGE_H
