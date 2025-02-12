/**
 * NextSim Captain
 * @file : InputRecordMode.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#ifndef INPUTRECORDMODE_H
#define INPUTRECORDMODE_H

#include <string>

namespace NextSimIO
{
/**
 * @class InputRecordMode
 * @brief Class for each record mode information
*/
class InputRecordMode
{
public:
    /**
     * @details Constructor
     * @param id Record mode id
     * @param activated Whether the record mode is activated
    */
    InputRecordMode(int id, bool activated);
    
    /**
     * @details Get record mode name
     * @return Record mode name
    */
    int GetID() { return m_id; }

    /**
     * @details Get whether the record mode is activated
     * @return Whether the record mode is activated
    */
    bool GetActivated() { return m_activated; }

private:
    /**
     * @details Record mode ID
    */
    int m_id;

    /**
     * @details Whether the record mode is activated
    */
    bool m_activated;
};
} // namespace NextSimIO

#endif