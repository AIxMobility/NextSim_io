/**
 * NextSim Captain
 * @file : turn.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef TURN_H
#define TURN_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class turn
 * @brief Class for turn information
 */
class turn
{
public:
    /**
     * @details Constructor
     * @param id turn ID
     * @param turning turn direction (-1 : left, 0 : straight, 1 : right)
     * @param type turn type (None, RTOR)
     */
    turn(int id, int turning, std::string type);

    /**
     * @details Get turn ID
     * @return Turn ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get direction of the turn
     * @return Turn direction (-1 : left, 0 : straight, 1 : right)
     */
    int GetTurning() { return m_turning; }

    /**
     * @details Get type of the turn
     * @return Turn type (None, RTOR)
     */
    std::string GetType() { return m_type; }

    /**
     * @details Get connection List
     * @return Connection List
     */
    std::vector<int> GetConnList() { return m_connList; }

    /**
     * @brief Set list of connection ids 
     * @param connString List of connection ids as a string
    */
    void SetConnList(std::string connString);

private:
    /**
     * @details Turn ID
    */
    int m_id;
    
    /**
     * @details Turn direction
    */
    int m_turning;

    /**
     * @details Type of the turn
    */
    std::string m_type;

    /**
     * @details Connection List
    */
    std::vector<int> m_connList;
};
} // namespace NextSimIO

#endif