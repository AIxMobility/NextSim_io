/**
 * NextSim Captain
 * @file : AgentTypesArr.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef AGENTTYPESARR_H
#define AGENTTYPESARR_H

#include <map>
#include "InputAgentTypes.hpp"

/**
 * @class AgentTypesArr
 * @brief Class for whole agent types from agentTypes.xml
 */
// ??? 뭐라고 설명해야 할지 잘 모르겠음
class AgentTypesArr
{
private:

    /**
     * @details Agent type map <agent type ID, agent type> ???
    */
    std::map<int, InputAgentTypes> vehTypes;

public:

    /**
     * @details Constructor
    */
    AgentTypesArr();

    //access function
    /**
     * @details Get agent type map
     * @return Agent type map <agent type ID, agent type> ???
    */
    std::map<int, InputAgentTypes> getAgentTypeMap() { return vehTypes; }
    
    /**
     * @details Get agent type from agent type map
     * @param type Agent type ID
     * @return Agent type ???
    */
    // ??? InputAgentTypes 타입 자체를 적어줘야 할지 agent type이라고 적어야 할지 모르겠음
    InputAgentTypes getAgentType(int type) { return vehTypes.find(type)->second; }
};


#endif