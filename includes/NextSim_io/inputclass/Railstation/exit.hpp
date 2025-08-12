/**
 * NextSim Captain
 * @file : exit.hpp
 * @version : 1.0
 * @author : YuseockHwang
 */

#pragma once
#ifndef Exit_H
#define Exit_H

#include <string>

namespace NextSimIO
{
/**
 * @class exit
 * @brief Class for exit information
 */
class exit
{
public:
    /**
     * @details Constructor
     * @param id Exit ID
     * @param link Link ID
     * @param offset Offset in the link
     * @param accesstime Access time
     */
    exit(int id, int link, int offset, double accesstime);

    /**
     * @details Get exit ID
     * @return Exit ID
     */
    int GetId() { return m_id; }

    /**
     * @details Get link ID
     * @return Link ID
     */
    int GetLink() { return m_link; }

    /**
     * @details Get offset in the link
     * @return Offset in the link
     */
    int GetOffset() { return m_offset; }

    /**
     * @details Get access time
     * @return Access time
     */
    double GetAccesstime() { return m_accesstime; }

private:
    /**
     * @details Exit ID
     */
    int m_id;

    /**
     * @details Link ID
     */
    int m_link;

    /**
     * @details Offset in the link
     */
    int m_offset;

    /**
     * @details Access time
     */
    double m_accesstime;

};
} // namespace NextSimIO

#endif