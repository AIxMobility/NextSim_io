/**
 * NextSim Captain
 * @file : InputVehicleTypes.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <NextSim_io/inputclass/InputVehicleTypes.hpp>

namespace NextSimIO
{
InputVehicleTypes::InputVehicleTypes(
    std::string vehType, 
    int maxPax, 
    bool v2xActive, 
    InputDistribution vehLen, 
    InputDistribution vehWidth,
    InputDistribution jamgap, 
    InputDistribution vf, 
    InputDistribution reactionTime, 
    InputDistribution maxAcc, 
    InputDistribution maxDec,
    InputDistribution lcParam1,
    InputDistribution lcParam2,
    InputDistribution lcSensitivity,
    std::array<double, 3> powertrainRatios)
    : m_vehType(vehType),
      m_maxPax(maxPax),
      m_v2xActive(v2xActive),
      m_powertrainRatios(powertrainRatios),
      m_vehLen(vehLen),
      m_vehWidth(vehWidth),
      m_jamgap(jamgap),
      m_vf(vf),
      m_reactionTime(reactionTime),
      m_maxAcc(maxAcc),
      m_maxDec(maxDec),
      m_lcParam1(lcParam1),
      m_lcParam2(lcParam2),
      m_lcSensitivity(lcSensitivity) {};
} // namespace NextSimIO
