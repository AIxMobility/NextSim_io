/**
 * NextSim Captain
 * @file : NodeArr.hpp
 * @version : 1.0
 * @author : ???
*/

#ifndef NODEARR_H
#define NODEARR_H

#include <NextSim_io/inputclass/InputNode.hpp>

namespace NextSimIO
{
/**
 * @class NodeArr
 * @brief Class for whole node information from network.xml
 */
class NodeArr
{
private:

    /**
     * @details Vector of all nodes
    */
    std::vector<InputNode> Nodes;

    /**
     * @details Vector of normal nodes
    */
    std::vector<InputNode> NormalNodes;

    /**
     * @details Vector of intersection nodes
    */
    std::vector<InputNode> IntersectionNodes;

    /**
     * @details Vector of diverging nodes
    */
    std::vector<InputNode> DivergingNodes;

    /**
     * @details Vector of merging nodes
    */
    std::vector<InputNode> MergingNodes;

    /**
     * @details Vector of terminal nodes
    */
    std::vector<InputNode> TerminalNodes;

    /**
     * @details Vector of garage nodes
    */
    std::vector<InputNode> GarageNodes;

public:

    /**
     * @details Constructor (Parse node information from network.xml)
    */
    NodeArr();

    /**
     * @details Get vector of all nodes
     * @return Vector of all nodes
    */
    std::vector<InputNode> getNodes() { return Nodes; }

    /**
     * @details Get vector of normal nodes
     * @return Vector of normal nodes (node between connected two links)
    */
    std::vector<InputNode> getNormalNodes() { return NormalNodes; }

    /**
     * @details Get vector of intersection nodes
     * @return Vector of intersection nodes (node with signal)
    */
    std::vector<InputNode> getIntersectionNodes() { return IntersectionNodes; }

    /**
     * @details Get vector of diverging nodes
     * @return Vector of diverging nodes (node with multiple outgoing links)
    */
    std::vector<InputNode> getDivergingNodes() { return DivergingNodes; }

    /**
     * @details Get vector of merging nodes
     * @return Vector of merging nodes (node with multiple incoming links)
    */
    std::vector<InputNode> getMergingNodes() { return MergingNodes; }

    /**
     * @details Get vector of terminal nodes
     * @return Vector of terminal nodes (source, sink node)
    */
    std::vector<InputNode> getTerminalNodes() { return TerminalNodes; }

    /**
     * @details Get vector of garage nodes
     * @return Vector of garage nodes (node with public transit garage)
    */
    std::vector<InputNode> getGarageNodes() { return GarageNodes; }

    /**
     * @details Show vector of total nodes
    */
    void showArr();
};
} // namespace NextSimIO

#endif