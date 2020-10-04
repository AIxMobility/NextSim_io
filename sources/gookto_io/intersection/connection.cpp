#include <string>
#include <iostream>

#include <gookto_io/intersection/connection.hpp>

connection::connection(long int id, long int fromLink, long int fromLane, long int toLink, long int toLane, float priority) : 
connectionId(id), from_link(fromLink), from_lane(fromLane), to_link(toLink), to_lane(toLane), priority(priority)
{};