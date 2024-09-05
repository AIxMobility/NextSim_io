/**
* NextSim Captain
* @file InputMode.hpp
* @version 1.0
* @author Jae Hwan Jung, Justin Kim
*/

#ifndef MODE_H
#define MODE_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputMode
 * @brief Class for each simulation mode information
 */
class InputMode
{
private:
    /**
     * @details Period ID of mode setting application
    */
    int id;

    /**
     * @details Start cycle for applying the corresponding mode setting
    */
    int scycle;

    /**
     * @details Vector of microscopic link IDs
    */
    std::vector<int> microLinkArr;

    /**
     * @details Vector of mesoscopic link IDs
    */
    std::vector<int> mesoLinkArr;

public:

    /**
     * @brief Constructor
     * @param id Period ID
     * @param scycle Application Start cycle
    */
    InputMode(int id, int scycle);

    /** @cond EXCLUDE */
    ~InputMode() = default;
    InputMode(const InputMode &other) = default;
    InputMode &operator=(const InputMode &other) = default;
    /** @endcond */

    /**
     * @brief Set vector of micro link IDs
     * @param linkArr Vector of microscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    void setMicroLinkArr(std::string linkArr);

    /**
     * @brief Set vector of meso link IDs
     * @param linkArr Vector of mesoscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    void setMesoLinkArr(std::string linkArr);

    /**
     * @brief Get period ID
     * @return Period ID of mode setting application
    */
    int getId() { return id; }

    /**
     * @brief Get start cycle
     * @return Start cycle for applying the corresponding mode setting
    */
    int getScycle() { return scycle; }

    /**
     * @brief Get vector of micro link IDs
     * @return Vector of microscopic link IDs
    */
    std::vector<int> getMicroLinkArr() { return microLinkArr; }

    /**
     * @brief Get vector of meso link IDs
     * @return Vector of mesoscopic link IDs
    */
    std::vector<int> getMesoLinkArr() { return mesoLinkArr; }
};
} // namespace NextSimIO

#endif