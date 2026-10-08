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

// SimulationInput/config.txt 의 "network=<이름>" (옛 키 "network_name" 도 읽는다).
static std::string load_network_name() {
    std::filesystem::path simInputPath = get_simulation_input_path();
    std::ifstream file(simInputPath / "config.txt");
    std::string line, key, value;
    std::string network, legacyNetworkName;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();   // CRLF (Windows 에서 만든 파일)
        std::istringstream iss(line);
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "network") network = value;
            else if (key == "network_name") legacyNetworkName = value;
        }
    }

    return network.empty() ? legacyNetworkName : network;
}

static std::string network_name = load_network_name();

static std::filesystem::path simulationInputPath = get_simulation_input_path();

// 네트워크 하나 = 폴더 하나: SimulationInput/networks/<이름>/
static std::filesystem::path NetworkXmlFilePath =
    simulationInputPath / "networks" / network_name;

// 파라미터는 네트워크 폴더 안의 parameter_xml/. 없으면 SimulationInput/parameter_xml/ (공용 기본값).
static std::filesystem::path find_parameter_xml_path() {
    const auto perNetwork = NetworkXmlFilePath / "parameter_xml";
    if (std::filesystem::exists(perNetwork)) return perNetwork;
    const auto shared = simulationInputPath / "parameter_xml";
    if (std::filesystem::exists(shared)) return shared;
    return perNetwork;
}

static std::filesystem::path ParameterXmlFilePath = find_parameter_xml_path();

// Network xml file path
static std::filesystem::path ScenarioXMLPath = NetworkXmlFilePath / "scenario.xml";

static std::filesystem::path ScenarioJSONPath = NetworkXmlFilePath / "config_scenario.json";

static std::filesystem::path DTAConfigJSONPath = NetworkXmlFilePath / "config_dta.json";

static inline std::string GetEnvString(const char* name)
{
    const char* value = std::getenv(name);
    return value ? std::string(value) : std::string();
}

static inline bool IsDistributedEnabled()
{
    return GetEnvString("CAPTAIN_DISTRIBUTED") == "1";
}

static inline int GetInstanceIdFromEnv()
{
    const char* instanceEnv = std::getenv("CAPTAIN_INSTANCE_ID");
    if (instanceEnv)
        return std::atoi(instanceEnv);

    const char* mpiRankEnv = std::getenv("OMPI_COMM_WORLD_RANK");
    if (mpiRankEnv)
        return std::atoi(mpiRankEnv);

    const char* mpichRankEnv = std::getenv("PMI_RANK");
    if (mpichRankEnv)
        return std::atoi(mpichRankEnv);

    const char* pmixRankEnv = std::getenv("PMIX_RANK");
    if (pmixRankEnv)
        return std::atoi(pmixRankEnv);

    const char* slurmRankEnv = std::getenv("SLURM_PROCID");
    if (slurmRankEnv)
        return std::atoi(slurmRankEnv);
    return -1;
}

static inline std::filesystem::path ResolvePathOverride(
    const std::string& overrideValue,
    const std::filesystem::path& base)
{
    if (overrideValue.empty())
        return {};
    std::filesystem::path overridePath(overrideValue);
    if (overridePath.is_absolute())
        return overridePath;
    return base / overridePath;
}

static inline std::filesystem::path SelectNetworkXmlPath(
    const std::filesystem::path& base)
{
    auto overrideValue = GetEnvString("CAPTAIN_NETWORK_XML");
    if (!overrideValue.empty())
        return ResolvePathOverride(overrideValue, base);

    if (IsDistributedEnabled())
    {
        auto candidate = base / "partitioned_network_metis.xml";
        if (std::filesystem::exists(candidate))
            return candidate;
    }

    return base / "network.xml";
}

static inline std::filesystem::path SelectOdMatrixXmlPath(
    const std::filesystem::path& base)
{
    auto overrideValue = GetEnvString("CAPTAIN_ODMATRIX_XML");
    if (!overrideValue.empty())
        return ResolvePathOverride(overrideValue, base);

    if (IsDistributedEnabled())
    {
        int instanceId = GetInstanceIdFromEnv();
        if (instanceId >= 0)
        {
            auto candidate = base / ("odmatrix_part" + std::to_string(instanceId) + ".xml");
            if (std::filesystem::exists(candidate))
                return candidate;
        }
    }

    return base / "odmatrix.xml";
}

static std::filesystem::path NetworkXMLPath = SelectNetworkXmlPath(NetworkXmlFilePath);

static std::filesystem::path FootpathNetworkXMLPath = NetworkXmlFilePath / "footpathNetwork.xml";

static std::filesystem::path V2XConfigJSONPath = ParameterXmlFilePath / "config_v2x.json";

static std::filesystem::path LinkRangeJSONPath = NetworkXmlFilePath / "LinkRangeMap.json";

static std::filesystem::path SignalTODXMLPath = NetworkXmlFilePath / "signalTOD.xml";

static std::filesystem::path SignalXMLPath = NetworkXmlFilePath / "signal.xml";

static std::filesystem::path SignalControlXMLPath = NetworkXmlFilePath / "signalControl.xml";

static std::filesystem::path OdMatrixXMLPath = SelectOdMatrixXmlPath(NetworkXmlFilePath);

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
