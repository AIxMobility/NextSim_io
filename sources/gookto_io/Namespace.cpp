#include <iostream>
#include <sstream>
#include <tuple>
#include <gookto_io/Namespace.hpp>
#include <filesystem>

std::tuple<std::string, std::string, std::string, std::string, std::string> Namespace(const char* userName)
{
    std::filesystem::path f_path1 = std::filesystem::current_path().parent_path().parent_path() / "SimulationOutput" / userName / "VehicleInfo.xml";
    std::filesystem::path f_path2 = std::filesystem::current_path().parent_path().parent_path() / "SimulationOutput" / userName / "UniformEvent.xml";
    std::filesystem::path f_path3 = std::filesystem::current_path().parent_path().parent_path() / "SimulationOutput" / userName / "StationEvent.xml";
    std::filesystem::path f_path4 = std::filesystem::current_path().parent_path().parent_path() / "SimulationOutput" / userName / "SinkEvent.xml";
    std::filesystem::path f_path5 = std::filesystem::current_path().parent_path().parent_path() / "SimulationOutput" / userName / "Vehicle.json";

    return std::make_tuple(f_path1, f_path2, f_path3, f_path4, f_path5);
}

