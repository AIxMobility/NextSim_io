/**
 * NextSim Captain
 * @file : VehicleTypesArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef VEHICLETYPESARR_H
#define VEHICLETYPESARR_H

#include <map>
#include <NextSim_io/inputdata/InputVehicleTypes.hpp>

namespace NextSimIO
{
/**
 * @class VehicleTypesArr
 * @brief Class for whole vehicle types from vehicleTypes.xml
 */
class VehicleTypesArr
{
private:

    /**
     * @details Map of vehicle type <vehicle type ID, info per type>
    */
    std::map<int, InputVehicleTypes> vehTypes;

public:

    /**
     * @details Constructor (Parse vehicle type information from vehicleTypes.xml)
    */
    VehicleTypesArr();

    /**
     * @details Get vehicle type map
     * @return Vehicle type map <vehicle type ID, info per type>
    */
    std::map<int, InputVehicleTypes> getVehicleTypeMap() { return vehTypes; }
    
    /**
     * @details Get vehicle type from vehicle type map
     * @param type Vehicle type ID
     * @return Vehicle type info (parameters)
    */
    InputVehicleTypes getVehicleType(int type) { return vehTypes.find(type)->second; }
};
} // namespace NextSimIO

#endif