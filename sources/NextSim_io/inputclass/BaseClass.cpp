/**
 * NextSim Captain
 * @file : BaseClass.cpp
 * @version : 1.0
 * @author : Jae Hwan Jung, Justin Kim
 */

#include <NextSim_io/inputclass/BaseClass.hpp>

namespace NextSimIO
{
MetaData::MetaData(std::size_t id) 
    : id(id) {};

MetaData::MetaData(std::size_t id, double length) 
    : id(id), length(length) {};

MetaData::MetaData(std::size_t id, double length, double width)
    : id(id), length(length), width(width) {};

MetaData::MetaData(std::size_t id, double length, double width, double stopline)
    : id(id), length(length), width(width), stopLine(stopline) {};

MetaData::MetaData(std::size_t id, double length, double freeFlowSpeed,
                   double maxSpeed, double minSpeed, double waveSpeed,
                   std::size_t maxVehicle, double qMax)
    : id(id),
    freeFlowSpeed(freeFlowSpeed),
    maxSpeed(maxSpeed),
    minSpeed(minSpeed),
    waveSpeed(waveSpeed),
    length(length),
    width(-1),
    qMax(qMax),
    maxVehicle(maxVehicle) {};
} // namespace NextSimIO