/**
 * NextSim Captain
 * @file : Exit.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */

 #include <sstream>

 #include <NextSim_io/inputclass/Railstation/Exit.hpp>
 
 namespace NextSimIO
 {
    Exit::Exit(int id, int link, int offset, double accesstime) 
    : m_id(id), m_link(link), m_offset(offset), m_accesstime(accesstime) {};
 } // namespace NextSimIO