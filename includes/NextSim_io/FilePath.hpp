/**
 * NextSim Captain
 * @file : FilePath.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef NEXTSIMIO_FILEPATH_HPP
#define NEXTSIMIO_FILEPATH_HPP

#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace NextSimIO
{
static std::filesystem::path get_simulation_input_path() {
    // Try to find SimulationInput directory relative to executable location
    std::filesystem::path currentPath = std::filesystem::current_path();
    
    // Go up from build/bin to project root, then to SimulationInput
    std::filesystem::path simulationInput = currentPath / ".." / ".." / ".." / ".." / "SimulationInput";
    
    if (std::filesystem::exists(simulationInput)) {
        return std::filesystem::canonical(simulationInput);
    }
    
    // Fallback to direct path if relative path doesn't work
    return "/home/wjstnwp/NextSim/SimulationInput";
}

static std::pair<std::string, std::string> load_network_name() {
    std::filesystem::path simInputPath = get_simulation_input_path();
    std::ifstream file(simInputPath / "config.txt");
    std::string line, key, value;
    std::string network_name, branch, version;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "network_name") network_name = value;
            else if (key == "branch") branch = value;
        }
    }

    return std::make_pair(branch, network_name);
}

static std::pair<std::string, std::string> networkID = load_network_name();

static std::string branch = networkID.first;

static std::string network_name = networkID.second;

static std::filesystem::path simulationInputPath = get_simulation_input_path();

static std::filesystem::path NetworkXmlFilePath =
    simulationInputPath / ("datasets/" + branch + "/network_xml_" + network_name);

static std::filesystem::path ParameterXmlFilePath =
    simulationInputPath / ("datasets/" + branch + "/parameter_xml");

// Network xml file path
static std::filesystem::path ScenarioXMLPath = NetworkXmlFilePath / "scenario.xml";

static std::filesystem::path NetworkXMLPath = NetworkXmlFilePath / "network.xml";

static std::filesystem::path FootpathNetworkXMLPath = NetworkXmlFilePath / "footpathNetwork.xml";

static std::filesystem::path SignalTODXMLPath = NetworkXmlFilePath / "signalTOD.xml";

static std::filesystem::path SignalXMLPath = NetworkXmlFilePath / "signal.xml";

static std::filesystem::path SignalControlXMLPath = NetworkXmlFilePath / "signalControl.xml";

static std::filesystem::path OdMatrixXMLPath = NetworkXmlFilePath / "odmatrix.xml";

static std::filesystem::path AgentXMLPath = NetworkXmlFilePath / "agents.xml";

static std::filesystem::path PassengerXMLPath = NetworkXmlFilePath / "passenger.xml";

static std::filesystem::path ModeXMLPath = NetworkXmlFilePath / "mode.xml";

static std::filesystem::path RoadStationXMLPath = NetworkXmlFilePath / "roadStation.xml";

static std::filesystem::path RailStationXMLPath = NetworkXmlFilePath / "railStation.xml";

static std::filesystem::path RoadPTlineXMLPath = NetworkXmlFilePath / "roadPTline.xml";

static std::filesystem::path RailPTlineXMLPath = NetworkXmlFilePath / "railPTline.xml";

static std::filesystem::path RouteJSONPath = NetworkXmlFilePath / "Route.json";

static std::filesystem::path PTRouteJSONPath = NetworkXmlFilePath / "PTRoute.json";

static std::filesystem::path PaxRouteJSONPath = NetworkXmlFilePath / "PaxRoute.json";

static std::filesystem::path EventXMLPath = NetworkXmlFilePath / "events.xml";

static std::filesystem::path V2XXMLPath = NetworkXmlFilePath / "v2xdata.xml";

static std::filesystem::path BackgroundTrafficXMLPath = NetworkXmlFilePath / "backgroundTraffic.xml";

static std::filesystem::path RailStationNewXMLPath = NetworkXmlFilePath / "railStation.xml";

static std::filesystem::path RailLineNewXMLPath = NetworkXmlFilePath / "railLine.xml";

static std::filesystem::path VehicleTypeXMLPath = ParameterXmlFilePath / "vehicletypes.xml";

static std::filesystem::path RecordModeXMLPath = ParameterXmlFilePath / "recordMode.xml";

static std::filesystem::path ParamXMLPath = ParameterXmlFilePath / "param.xml";
}

#endif
