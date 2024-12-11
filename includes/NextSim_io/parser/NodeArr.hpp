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
public:
    /**
     * @details Constructor (Parse node information from network.xml)
    */
    NodeArr();

    /**
     * @details Get vector of all nodes
     * @return Vector of all nodes
    */
    std::vector<InputNode> GetNodes() { return m_nodes; }

    /**
     * @details Get vector of normal nodes
     * @return Vector of normal nodes (node between connected two links)
    */
    std::vector<InputNode> GetNormalNodes() { return m_normalNodes; }

    /**
     * @details Get vector of intersection nodes
     * @return Vector of intersection nodes (node with signal)
    */
    std::vector<InputNode> GetIntersectionNodes() { return m_intersectionNodes; }

    /**
     * @details Get vector of diverging nodes
     * @return Vector of diverging nodes (node with multiple outgoing links)
    */
    std::vector<InputNode> GetDivergingNodes() { return m_divergingNodes; }

    /**
     * @details Get vector of merging nodes
     * @return Vector of merging nodes (node with multiple incoming links)
    */
    std::vector<InputNode> GetMergingNodes() { return m_mergingNodes; }

    /**
     * @details Get vector of terminal nodes
     * @return Vector of terminal nodes (source, sink node)
    */
    std::vector<InputNode> GetTerminalNodes() { return m_terminalNodes; }

    /**
     * @details Get vector of garage nodes
     * @return Vector of garage nodes (node with public transit garage)
    */
    std::vector<InputNode> GetGarageNodes() { return m_garageNodes; }

    /**
     * @details Show vector of total nodes
    */
    void ShowArr();

private:
    /**
     * @details Vector of all nodes
    */
    std::vector<InputNode> m_nodes;

    /**
     * @details Vector of normal nodes
    */
    std::vector<InputNode> m_normalNodes;

    /**
     * @details Vector of intersection nodes
    */
    std::vector<InputNode> m_intersectionNodes;

    /**
     * @details Vector of diverging nodes
    */
    std::vector<InputNode> m_divergingNodes;

    /**
     * @details Vector of merging nodes
    */
    std::vector<InputNode> m_mergingNodes;

    /**
     * @details Vector of terminal nodes
    */
    std::vector<InputNode> m_terminalNodes;

    /**
     * @details Vector of garage nodes
    */
    std::vector<InputNode> m_garageNodes;
};
} // namespace NextSimIO

#endif