/**
 * STS19 Captain
 * @file : InputAgentTypes.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <gookto_io/InputAgentTypes.hpp>
#include <gookto_io/InputDistribution.hpp>

InputAgentTypes::InputAgentTypes(std::string vehType, int max_pax, InputDistribution veh_len, InputDistribution jamgap, InputDistribution vf, InputDistribution reaction_time, InputDistribution max_acc, InputDistribution max_dec) : vehType { vehType }, max_pax ( max_pax ), veh_len { veh_len }, jamgap { jamgap }, vf { vf }, reaction_time { reaction_time }, max_acc { max_acc }, max_dec { max_dec } {};