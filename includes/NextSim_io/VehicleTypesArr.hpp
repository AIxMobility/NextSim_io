/**
 * NextSim Captain
 * @file : VehicleTypesArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef VEHICLETYPESARR_H
#define VEHICLETYPESARR_H

#include <map>
#include "InputVehicleTypes.hpp"

/**
 * @class VehicleTypesArr
 * @brief Class for whole vehicle types from vehicleTypes.xml
 */
class VehicleTypesArr
{
private:

    /**
     * @details Vehicle type map <vehicle type ID, vehicle type> ???
    */
    std::map<int, InputVehicleTypes> vehTypes;

public:

    /**
     * @details Constructor
    */
    VehicleTypesArr();

    /**
     * @details Get vehicle type map
     * @return Vehicle type map <vehicle type ID, vehicle type> ???
    */
    std::map<int, InputVehicleTypes> getVehicleTypeMap() { return vehTypes; }
    
    /**
     * @details Get vehicle type from vehicle type map
     * @param type Vehicle type ID
     * @return Vehicle type ???
    */
    // ??? InputVehicleTypes 타입 자체를 적어줘야 할지 vehicle type이라고 적어야 할지 모르겠음
    InputVehicleTypes getVehicleType(int type) { return vehTypes.find(type)->second; }
};


#endif