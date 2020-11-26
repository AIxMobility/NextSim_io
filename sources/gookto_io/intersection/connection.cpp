#include <iostream>
#include <string>

#include <gookto_io/intersection/connection.hpp>

connection::connection(int id, int fromLink, int fromLane, int toLink,
                       int toLane, double priority, double length)
    : connectionId(id),
      from_link(fromLink),
      from_lane(fromLane),
      to_link(toLink),
      to_lane(toLane),
      priority(priority),
      length(length){};