/**
 * NextSim Captain
 * @file : InputAgentTypes.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <gookto_io/InputAgentTypes.hpp>
#include <gookto_io/InputDistribution.hpp>

InputAgentTypes::InputAgentTypes(std::string vehType, 
                                 int max_pax, 
                                 bool v2xActive, 
                                 InputDistribution veh_len, 
                                 InputDistribution jamgap, 
                                 InputDistribution vf, 
                                 InputDistribution reaction_time, 
                                 InputDistribution max_acc, 
                                 InputDistribution max_dec,
                                 InputDistribution lc_param1,
                                 InputDistribution lc_param2,
                                 InputDistribution lc_sensitivity)
                                 : vehType { vehType }, 
                                   max_pax ( max_pax ), 
                                   v2xActive ( v2xActive ), 
                                   veh_len { veh_len }, 
                                   jamgap { jamgap }, 
                                   vf { vf }, 
                                   reaction_time { reaction_time }, 
                                   max_acc { max_acc }, 
                                   max_dec { max_dec },
                                   lc_param1 { lc_param1 },
                                   lc_param2 { lc_param2 },
                                   lc_sensitivity { lc_sensitivity } {};