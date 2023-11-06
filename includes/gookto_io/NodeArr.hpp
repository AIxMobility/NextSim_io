#ifndef NODEARR_H
#define NODEARR_H

#include <vector>
#include "IntersectionNode.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"


class NodeArr
{
private:
    std::vector<IntersectionNode> Nodes;
    std::vector<IntersectionNode> NormalNodes;
    std::vector<IntersectionNode> IntersectionNodes;
    std::vector<IntersectionNode> DivergingNodes;
    std::vector<IntersectionNode> TerminalNodes;
    std::vector<IntersectionNode> GarageNodes;

public:
    NodeArr(const std::string& userName);

    //access functions
    std::vector<IntersectionNode> getNodes() { return Nodes; }
    std::vector<IntersectionNode> getNormalNodes() { return NormalNodes; }
    std::vector<IntersectionNode> getIntersectionNodes() { return IntersectionNodes; }
    std::vector<IntersectionNode> getDivergingNodes() { return DivergingNodes; }
    std::vector<IntersectionNode> getTerminalNodes() { return TerminalNodes; }
    std::vector<IntersectionNode> getGarageNodes() { return GarageNodes; }

    //check
    void showArr();
};

#endif