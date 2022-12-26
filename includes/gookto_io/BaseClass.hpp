//! STS19 Captain
//! Copyright (c) 2019 Justin Kim, Kaist
//! Copying, reproducing and commercial use is not allowed.
//! We are not conveying any rights to any intellectual property of any third
//! parties
//!
//! \file : BaseClass.hpp
//! \version : 1.0
//! \author : Jae Hwan Jung, Justin Kim

#ifndef BASECLASS_HPP
#define BASECLASS_HPP

#include <vector>

class MetaData
{

public:
   std::size_t ID = 0;
   double FreeFlowSpeed = 0, MaxSpeed = 0, MinSpeed = 0, WaveSpeed = 0;
   double Length = 0, Width = 0;  // m
   double Qmax = 0;
   size_t MaxVehicle = 0;


    MetaData() = default;

    MetaData(std::size_t id) : ID(id)
    {
    }

    MetaData(std::size_t id, double length)
        : ID(id),
          Length(length)
    {
    }

    MetaData(std::size_t id_val, double length_val, double width_val)
    {
        ID = id_val;
        Length = length_val;
        Width = width_val;
    }

    MetaData(std::size_t id, double length, double freeFlowSpeed,
                 double maxSpeed, double minSpeed, double waveSpeed,
                 size_t maxVehicle, double qMax)
        : ID(id),
          FreeFlowSpeed(freeFlowSpeed),
          MaxSpeed(maxSpeed),
          MinSpeed(minSpeed),
          WaveSpeed(waveSpeed),
          Length(length),
          Width(-1),
          Qmax(qMax),
          MaxVehicle(maxVehicle)

    {
    }

    virtual ~MetaData() = default;
    MetaData(const MetaData& metaData) = default;
    MetaData& operator=(const MetaData& metaData) = default;


};


#endif
