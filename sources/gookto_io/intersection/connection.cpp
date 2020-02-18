#include <string>
#include <iostream>

#include <gookto_io/intersection/connection.hpp>

connection::connection(int id, int fromLink, int fromLane, int toLink, int toLane, float priority) : 
connectionId(id), from_link(fromLink), from_lane(fromLane), to_link(toLink), to_lane(toLane), priority(priority)
{};