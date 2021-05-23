#include <string>
#include <iostream>

#include <gookto_io/InputEvent.hpp>

InputEvent::InputEvent(int id, double pos, int lane, double stime, double etime, int type, int sern) : id(id), pos(pos), lane(lane), stime(stime), etime(etime), type(type), sern(sern) {};