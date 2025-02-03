/**
 * NextSim Captain
 * @file : InputTOD.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTTOD_H
#define INPUTTOD_H

#include <vector>
#include <string>

#include "signal/table.hpp"

namespace NextSimIO
{
/**
 * @class InputTOD
 * @brief Class for signal TOD information
*/
class InputTOD
{
public:
    /**
     * @details Constructor
     * @param nodeId Node ID
    */
    InputTOD(int nodeId, std::vector<table> table);

    /**
     * @details Get node ID
     * @return Node ID
    */
    int GetNodeId() const { return m_nodeId; }

    /**
     * @details Get signal plan table
     * @return Signal plan table
    */
    std::vector<table> GetTable() const { return m_table; }

private:
    /**
     * @details Node ID
    */
    int m_nodeId;

    /**
     * @details Vector of signal plan table
    */
    std::vector<table> m_table;
};
} // namespace NextSimIO

#endif