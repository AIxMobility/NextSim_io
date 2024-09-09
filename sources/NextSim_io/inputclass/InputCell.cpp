/**
 * NextSim Captain
 * @file : InputCell.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputCell.hpp>

namespace NextSimIO
{
InputCell::InputCell(std::size_t id_val, double offset_val, double length_val) 
    : MetaData(id_val, length_val)
{
    offset = offset_val;
}
} // namespace NextSimIO