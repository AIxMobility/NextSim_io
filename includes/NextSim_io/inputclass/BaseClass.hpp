/**
 * NextSim Captain
 * @file : BaseClass.hpp
 * @version : 1.0
 * @author : Jae Hwan Jung, Justin Kim
 */

#pragma once
#ifndef BASECLASS_HPP
#define BASECLASS_HPP

#include <vector>

namespace NextSimIO
{
/**
 * @class MetaData
 * @brief Class for metadata of network units
 */
class MetaData
{

public:
    /** @cond EXCLUDE */
    MetaData() = default;
    virtual ~MetaData() = default;
    MetaData(const MetaData& metaData) = default;
    MetaData& operator=(const MetaData& metaData) = default;
    /** @endcond */

    /** 
     * @details Constructor with ID
     * @param id ID of the unit
     */
    MetaData(std::size_t id);

    /** 
     * @details Constructor with ID and length
     * @param id ID of the unit
     * @param length Length of the unit
     */
    MetaData(std::size_t id, double length);

    /** 
     * @details Constructor with ID, length, and width
     * @param id ID of the unit
     * @param length Length of the unit
     * @param width Width of the unit
     */
    MetaData(std::size_t id, double length, double width);

    /** 
     * @details Constructor with ID, length, width, and stopline
     * @param id ID of the unit
     * @param length Length of the unit
     * @param width Width of the unit
     * @param stopline Stop line distance of the unit
     */
    MetaData(std::size_t id, double length, double width, double stopline);

    /** 
     * @details Constructor with ID, length, freeflowSpeed, 
     * maxSpeed, minSpeed, waveSpeed, 
     * maxVehicle, and qmax
     * @param id ID of the unit
     * @param length Length of the unit
     * @param freeFlowSpeed Free flow speed of the unit
     * @param maxSpeed Maximum speed of the unit
     * @param minSpeed Minimum speed of the unit
     * @param waveSpeed Wave speed of the unit
     * @param maxVehicle Maximum number of vehicles of the unit
     * @param qMax Maximum flow of the unit
     */
    MetaData(std::size_t id, double length, double freeFlowSpeed,
                 double maxSpeed, double minSpeed, double waveSpeed,
                 std::size_t maxVehicle, double qMax);

    /** 
     * @details ID of the unit
     */
    std::size_t id = 0;

    /** 
     * @details Free flow speed of the unit [km/h]
     */
    double freeFlowSpeed = 0;
    
    /** 
     * @details Maximum speed of the unit [km/h]
     */
    double maxSpeed = 0;
    
    /** 
     * @details Minimum speed of the unit [km/h]
     */
    double minSpeed = 0;
    
    /** 
     * @details Wave speed of the unit [km/h]
     */
    double waveSpeed = 0;

    /** 
     * @details Length of the unit [m]
     */
    double length = 0;
    
    /** 
     * @details Width of the unit [m]
     */
    double width = 0;
    
    /** 
     * @details Stop line distance of the unit [m]
     */
    double stopLine = 0;

    /** 
     * @details Maximum flow of the unit [veh/h]
     */
    double qMax = 0;

    /** 
     * @details Maximum number of vehicles of the unit [veh]
     */
    std::size_t maxVehicle = 0;
};
} // namespace NextSimIO

#endif
