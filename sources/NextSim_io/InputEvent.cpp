/**
 * NextSim Captain
 * @file : InputEvent.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <NextSim_io/InputEvent.hpp>

InputEvent::InputEvent(int id, std::size_t link_id, double pos, 
                       int lane, double stime, double etime, 
                       int type, int sern) 
                       : id(id), link_id(link_id), pos(pos), 
                         lane(lane), stime(stime), etime(etime), 
                         type(type), sern(sern) {};