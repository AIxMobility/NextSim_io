/**
 * NextSim Captain
 * @file : exit.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/exit.hpp>
 
 namespace NextSimIO
 {
    exit::exit(int id, int link, int offset, int accesstime) 
    : m_id(id), m_link(link), m_offset(offset), m_accesstime(accesstime) {};
 } // namespace NextSimIO