#include <string>
#include <iostream>

#include <gookto_io/InputEvent.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

InputEvent::InputEvent(int id, double pos, int lane, double stime, double etime, int type, int sern) : id(id), pos(pos), lane(lane), stime(stime), etime(etime), type(type), sern(sern) {};