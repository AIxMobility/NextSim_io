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
    : ID(id) {};

MetaData::MetaData(std::size_t id, double length) 
    : ID(id), Length(length) {};

MetaData::MetaData(std::size_t id, double length, double width)
    : ID(id), Length(length), Width(width) {};

MetaData::MetaData(std::size_t id, double length, double width, double stopline)
    : ID(id), Length(length), Width(width), StopLine(stopline) {};

MetaData::MetaData(std::size_t id, double length, double freeFlowSpeed,
                   double maxSpeed, double minSpeed, double waveSpeed,
                   std::size_t maxVehicle, double qMax)
    : ID(id),
    FreeFlowSpeed(freeFlowSpeed),
    MaxSpeed(maxSpeed),
    MinSpeed(minSpeed),
    WaveSpeed(waveSpeed),
    Length(length),
    Width(-1),
    Qmax(qMax),
    MaxVehicle(maxVehicle) {};
} // namespace NextSimIO