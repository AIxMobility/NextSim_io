/**
 * NextSim Captain
 * @file : InputODMatrix.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputODMatrix.hpp>

namespace NextSimIO
{
InputODMatrix::InputODMatrix(int id, std::vector<InputFlow> odMatrix)
    : m_id(id), m_odMatrix(odMatrix) {};
} // namespace NextSimIO