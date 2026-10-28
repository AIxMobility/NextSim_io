/**
 * NextSim Captain
 * @file : VehicleTypesArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef VEHICLETYPESARR_H
#define VEHICLETYPESARR_H

#include <map>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <NextSim_io/inputclass/InputVehicleTypes.hpp>

namespace NextSimIO
{
/**
 * @class VehicleTypesArr
 * @brief Class for whole vehicle types from vehicleTypes.xml
 */
class VehicleTypesArr
{
public:
    /**
     * @details Constructor (Parse vehicle type information from vehicleTypes.xml)
    */
    VehicleTypesArr();
    explicit VehicleTypesArr(const std::filesystem::path& path);

    /**
     * @details Get vehicle type map
     * @return Vehicle type map <vehicle type ID, info per type>
    */
    std::map<int, InputVehicleTypes> GetVehicleTypeMap() { return m_vehTypes; }
    
    /**
     * @details Get vehicle type from vehicle type map
     * @param type Vehicle type ID
     * @return Vehicle type info (parameters)
    */
    InputVehicleTypes GetVehicleType(int type)
    {
        const auto it = m_vehTypes.find(type);
        if (it == m_vehTypes.end())
            throw std::runtime_error("Vehicle type " + std::to_string(type) + " is not in vehicletypes.xml");
        return it->second;
    }

private:
    /**
     * @details Map of vehicle type <vehicle type ID, info per type>
    */
    std::map<int, InputVehicleTypes> m_vehTypes;

};
} // namespace NextSimIO

#endif