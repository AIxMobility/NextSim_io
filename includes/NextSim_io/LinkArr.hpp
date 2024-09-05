/**
 * NextSim Captain
 * @file : LinkArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef LINKARR_H
#define LINKARR_H

#include <vector>
#include "InputLink.hpp"

/**
 * @class LinkArr
 * @brief Class for whole link information
 */
class LinkArr
{
private:
    /**
     * @details Sequence of links
    */
    std::vector<InputLink> Links;

public:
    /**
     * @details Constructor
     */
    LinkArr();

    // ???
    ~LinkArr() = default;
    LinkArr(const LinkArr &link) = default;
    LinkArr &operator=(const LinkArr &link) = default;

    /**
     * @details Show sequence of links
    */
    void showArr();

    /**
     * @details Get sequence of links
     * @return Sequence of links
    */
    std::vector<InputLink> getLinks() { return Links; }
};

#endif