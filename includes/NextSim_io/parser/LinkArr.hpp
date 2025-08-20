/**
 * NextSim Captain
 * @file : LinkArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef LINKARR_H
#define LINKARR_H

#include <vector>
#include <NextSim_io/inputclass/InputLink.hpp>

namespace NextSimIO
{
/**
 * @class LinkArr
 * @brief Class for whole link information from network.xml
 */
class LinkArr
{
public:
    /**
     * @details Constructor (Parse link information from network.xml)
     */
    LinkArr();

    /**
     * @details Show vector of links
    */
    void ShowArr();

    /**
     * @details Get vector of links
     * @return Vector of links
    */
    std::vector<InputLink> GetLinks() const { return m_links; }

private:
    /**
     * @details Vector of links
    */
    std::vector<InputLink> m_links;
};
} // namespace NextSimIO

#endif