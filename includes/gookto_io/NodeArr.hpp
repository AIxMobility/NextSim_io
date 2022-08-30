#ifndef NODEARR_H
#define NODEARR_H

#include <vector>
#include "IntersectionNode.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"


class NodeArr
{
private:
    std::vector<IntersectionNode> Nodes;

public:
    NodeArr();

    //access functions
    std::vector<IntersectionNode> getNodes() { return Nodes; }

    //check
    void showArr();
};

#endif