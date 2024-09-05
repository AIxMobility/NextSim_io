/**
 * NextSim Captain
 * @file : NodeArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef NODEARR_H
#define NODEARR_H

#include <vector>
#include "IntersectionNode.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

/**
 * @class NodeArr
 * @brief Class for whole node information
 */
class NodeArr
{
private:

    /**
     * @details Sequence of all nodes
    */
    std::vector<IntersectionNode> Nodes;

    /**
     * @details Sequence of normal nodes
    */
    std::vector<IntersectionNode> NormalNodes;

    /**
     * @details Sequence of intersection nodes
    */
    std::vector<IntersectionNode> IntersectionNodes;

    /**
     * @details Sequence of diverging nodes
    */
    std::vector<IntersectionNode> DivergingNodes;

    /**
     * @details Sequence of merging nodes
    */
    std::vector<IntersectionNode> MergingNodes;

    /**
     * @details Sequence of terminal nodes
    */
    std::vector<IntersectionNode> TerminalNodes;

    /**
     * @details Sequence of garage nodes
    */
    std::vector<IntersectionNode> GarageNodes;

public:

    /**
     * @details Constructor
    */
    NodeArr();

    /**
     * @details Get sequence of all nodes
     * @return Sequence of all nodes
    */
    std::vector<IntersectionNode> getNodes() { return Nodes; }

    /**
     * @details Get sequence of normal nodes
     * @return Sequence of normal nodes (node between connected two links)
    */
    std::vector<IntersectionNode> getNormalNodes() { return NormalNodes; }

    /**
     * @details Get sequence of intersection nodes
     * @return Sequence of intersection nodes (node with signal)
    */
    std::vector<IntersectionNode> getIntersectionNodes() { return IntersectionNodes; }

    /**
     * @details Get sequence of diverging nodes
     * @return Sequence of diverging nodes (node with multiple outgoing links)
    */
    std::vector<IntersectionNode> getDivergingNodes() { return DivergingNodes; }

    /**
     * @details Get sequence of merging nodes
     * @return Sequence of merging nodes (node with multiple incoming links)
    */
    std::vector<IntersectionNode> getMergingNodes() { return MergingNodes; }

    /**
     * @details Get sequence of terminal nodes
     * @return Sequence of terminal nodes (source, sink node)
    */
    std::vector<IntersectionNode> getTerminalNodes() { return TerminalNodes; }

    /**
     * @details Get sequence of garage nodes
     * @return Sequence of garage nodes (???)
    */
    std::vector<IntersectionNode> getGarageNodes() { return GarageNodes; }

    //check
    void showArr();
};

#endif