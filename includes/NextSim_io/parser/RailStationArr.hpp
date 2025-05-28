/**
 * NextSim Captain
 * @file : RailStation.hpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

#ifndef RAILSTATIONARR_H
#define RAILSTATIONARR_H

#include <NextSim_io/inputclass/InputRailStation.hpp>

namespace NextSimIO
{
/**
 * @class RailStationArr
 * @brief 
 */
class RailStationArr
{
public:
    /**
     * @details Constructor (Parse signal information from network.xml)
    */
   RailStationArr();

    /**
     * @details Get vector of all signal plans
     * @return Vector of all signal plans
    */
   std::vector<InputRailStation> GetRailStations() { return m_railstations; }


private:

    /**
     * @details Vector of all signal plans
    */
   std::vector<InputRailStation> m_railstations;

};
} // namespace NextSimIO



#endif