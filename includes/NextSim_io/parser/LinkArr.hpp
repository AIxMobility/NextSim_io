/**
 * NextSim Captain
 * @file : LinkArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef LINKARR_H
#define LINKARR_H

#include <vector>
#include <NextSim_io/inputdata/InputLink.hpp>

namespace NextSimIO
{
/**
 * @class LinkArr
 * @brief Class for whole link information from network.xml
 */
class LinkArr
{
private:
    /**
     * @details Vector of links
    */
    std::vector<InputLink> Links;

public:
    /**
     * @details Constructor (Parse link information from network.xml)
     */
    LinkArr();

    /** @cond EXCLUDE */
    ~LinkArr() = default;
    LinkArr(const LinkArr &link) = default;
    LinkArr &operator=(const LinkArr &link) = default;
    /** @endcond */

    /**
     * @details Show vector of links
    */
    void showArr();

    /**
     * @details Get vector of links
     * @return Vector of links
    */
    std::vector<InputLink> getLinks() { return Links; }
};
} // namespace NextSimIO

#endif