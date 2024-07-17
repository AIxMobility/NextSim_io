/**
 * NextSim Captain
 * @file : InputMessage.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <gookto_io/InputMessage.hpp>

InputMessage::InputMessage(int id, double stime, double etime, int msg_type, int value) : id(id), stime(stime), etime(etime), msg_type(msg_type), value(value) {};