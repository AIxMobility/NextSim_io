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

/**
 * @class InputMode
 * @brief Class for each simulation mode information
 */
class InputMode
{
private:
    /**
     * @details Period ID to change simulation level
    */
    // ??? 변경 주기 id 라는 개념이 약간 애매한듯? 변경 주기 숫자를 의미하는건지?
    int id;

    /**
     * @details Start cycle for applying the corresponding cycle
    */
    int scycle;

    /**
     * @details Sequence of microscopic link IDs
    */
    std::vector<int> microLinkArr;

    /**
     * @details Sequence of mesoscopic link IDs
    */
    std::vector<int> mesoLinkArr;

public:

    /**
     * @brief Constructor
     * @param id Period ID
     * @param scycle Start cycle
    */
    InputMode(int id, int scycle);

    // ???
    InputMode(const InputMode &other) = default;

    // string to vector
    /**
     * @brief Set sequence of micro link IDs
     * @param linkArr Sequence of microscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    void setMicroLinkArr(std::string linkArr);

    /**
     * @brief Set sequence of meso link IDs
     * @param linkArr Sequence of mesoscopic link IDs ("Link1 Link2 Link3 Link4")
    */
    // ??? 여기서는 string linkArr인데 아래에서는 vector<int> linkArr 인게 이상함
    void setMesoLinkArr(std::string linkArr);

    //access function
    /**
     * @brief Get period ID
     * @return Period ID to change simulation level
    */
    int getId()
    {
        return id;
    }

    /**
     * @brief Get start cycle
     * @return Start cycle for applying the corresponding cycle
    */
    int getScycle()
    {
        return scycle;
    }

    /**
     * @brief Get sequence of micro link IDs
     * @return Sequence of microscopic link IDs
    */
    std::vector<int> getMicroLinkArr()
    {
        return microLinkArr;
    }

    /**
     * @brief Get sequence of meso link IDs
     * @return Sequence of mesoscopic link IDs
    */
    std::vector<int> getMesoLinkArr()
    {
        return mesoLinkArr;
    }
};

#endif