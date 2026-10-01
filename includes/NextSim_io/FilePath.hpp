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
#include <cstdlib>

namespace NextSimIO
{
// Windows: 엔진은 파일을 좁은 문자열(.string() → ANSI 코드페이지)로 연다. 경로에 한글 등
// 비ASCII 문자가 있으면(사용자 이름, 폴더 이름) 파일을 열지 못하거나 죽는다. 웹 서버/실행기는
// 엔진을 workspace 를 작업 폴더로 두고 실행하므로, 작업 폴더 아래의 경로는 상대경로
// ("SimulationInput\\...") 로 바꿔 ASCII 만 남긴다. 다른 플랫폼은 그대로 둔다.
static std::filesystem::path portable_path(const std::filesystem::path& path) {
#if defined(_WIN32)
    std::error_code ec;
    const auto relative = std::filesystem::relative(path, std::filesystem::current_path(), ec);
    if (!ec && !relative.empty() && *relative.begin() != "..") {
        return relative;
    }
#endif
    return path;
}

static std::filesystem::path get_simulation_input_path() {
    if (const char* projectRoot = std::getenv("NEXTSIM_PROJECT_ROOT")) {
        std::filesystem::path simulationInput = std::filesystem::path(projectRoot) / "SimulationInput";
        if (std::filesystem::exists(simulationInput / "config.txt")) {
            return portable_path(std::filesystem::canonical(simulationInput));
        }
    }

    std::filesystem::path currentPath = std::filesystem::current_path();
    while (!currentPath.empty()) {
        std::filesystem::path simulationInput = currentPath / "SimulationInput";
        if (std::filesystem::exists(simulationInput / "config.txt")) {
            return portable_path(std::filesystem::canonical(simulationInput));
        }

        const auto parent = currentPath.parent_path();
        if (parent == currentPath) {
            break;
        }
        currentPath = parent;
    }

    return std::filesystem::current_path() / "SimulationInput";
}

static std::pair<std::string, std::string> load_network_name() {
    std::filesystem::path simInputPath = get_simulation_input_path();
    std::ifstream file(simInputPath / "config.txt");
    std::string line, key, value;
    std::string network_name, branch, network;
    auto trim = [](const std::string& text) {
        const auto first = text.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return std::string{};
        return text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
    };
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            key = trim(key);
            value = trim(value);
            if (key == "network") network = value;
            else if (key == "network_name") network_name = value;
            else if (key == "branch") branch = value;
        }
    }

    // The current layout takes precedence even if legacy keys remain.
    if (!network.empty()) return std::make_pair(std::string{}, network);
    return std::make_pair(branch, network_name);
}

static std::pair<std::string, std::string> networkID = load_network_name();

static std::string branch = networkID.first;

static std::string network_name = networkID.second;

static std::filesystem::path simulationInputPath = get_simulation_input_path();

// Accept migrated folders with legacy config keys as well as network=<name>.
static bool modernNetworkLayout = branch.empty() ||
    std::filesystem::is_directory(simulationInputPath / "networks" / network_name);

static std::filesystem::path NetworkXmlFilePath = modernNetworkLayout
    ? simulationInputPath / "networks" / network_name
    : simulationInputPath / "datasets" / branch / ("network_xml_" + network_name);

static std::filesystem::path ParameterXmlFilePath = modernNetworkLayout
    ? NetworkXmlFilePath / "parameter_xml"
    : simulationInputPath / "datasets" / branch / "parameter_xml";

// Network xml file path
static std::filesystem::path ScenarioXMLPath = NetworkXmlFilePath / "scenario.xml";

static std::filesystem::path ScenarioJSONPath = NetworkXmlFilePath / "config_scenario.json";

static std::filesystem::path DTAConfigJSONPath = NetworkXmlFilePath / "config_dta.json";

static std::filesystem::path NetworkXMLPath = NetworkXmlFilePath / "network.xml";

static std::filesystem::path FootpathNetworkXMLPath = NetworkXmlFilePath / "footpathNetwork.xml";

static std::filesystem::path V2XConfigJSONPath = ParameterXmlFilePath / "config_v2x.json";

static std::filesystem::path LinkRangeJSONPath = NetworkXmlFilePath / "LinkRangeMap.json";

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

static std::filesystem::path BackgroundTrafficXMLPath = NetworkXmlFilePath / "backgroundTraffic.xml";

static std::filesystem::path RailStationNewXMLPath = NetworkXmlFilePath / "railStation.xml";

static std::filesystem::path RailLineNewXMLPath = NetworkXmlFilePath / "railLine.xml";

static std::filesystem::path DetectorXMLPath = NetworkXmlFilePath / "detector.xml";

// Parameter xml file path
static std::filesystem::path VehicleTypeXMLPath = ParameterXmlFilePath / "vehicletypes.xml";

static std::filesystem::path RecordModeXMLPath = ParameterXmlFilePath / "recordMode.xml";

static std::filesystem::path ParamXMLPath = ParameterXmlFilePath / "param.xml";
}

#endif
