#include <string>
#include <iostream>

#include <gookto_io/InputMessage.hpp>

InputMessage::InputMessage(int id, int stime, int etime, int msg_type, int value) : id(id), stime(stime), etime(etime), msg_type(msg_type), value(value) {};