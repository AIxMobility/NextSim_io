#ifndef GOOKTOIO_FILEPATH_HPP
#define GOOKTOIO_FILEPATH_HPP

#include <filesystem>

namespace STSIO
{
static std::string network_name = "intersection";
static std::filesystem::path currentPath = std::filesystem::current_path();

// static std::filesystem::path NetworkXmlFilePath =
//     std::filesystem::current_path() / ("network_xml_" + network_name);
static std::filesystem::path ParameterXmlFilePath =
    std::filesystem::current_path() / "parameter_xml";


// Network xml file path
inline std::string NetworkXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path NetworkXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "network.xml";
    return NetworkXMLPath;
}

// OD Matrix xml file path
inline std::string OdMatrixXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path OdMatrixXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "odmatrix.xml";
    return OdMatrixXMLPath;
}

// Scenario xml file path
inline std::string ScenarioXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path ScenarioXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "odscenario.xml";
    return ScenarioXMLPath;
}

// Station xml file path
inline std::string StationXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path StationXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "publicTransit.xml";
    return StationXMLPath;
}

// Mode xml file path
inline std::string ModeXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path ModeXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "mode.xml";
    return ModeXMLPath;
}

// Event xml file path
inline std::string EventXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path EventXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "eventdata.xml";
    return EventXMLPath;
}

// PT line xml file path
inline std::string PTlineXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path PTlineXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "ptline.xml";
    return PTlineXMLPath;
}

// Route JSON path
inline std::string RouteJSON(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path RouteJSONPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "Route.json";
    return RouteJSONPath;
}

inline std::string PaxRouteJSON(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path PaxRouteJSONPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "PaxRoute.json";
    return PaxRouteJSONPath;
}


// Agent xml file path
inline std::string AgentXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path AgentXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "agents.xml";
    return AgentXMLPath;
}

// Agent opt type xml file path
inline std::string AgentOptXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path AgentOptXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "agents_opt.xml";
    return AgentOptXMLPath;
}

// V2X xml file path
inline std::string V2XXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path V2XXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "v2xdata.xml";
    return V2XXMLPath;
}

// Passenger xml file path
inline std::string PassengerXML(const std::string& userName) {
    // Define the function implementation here
    // You can use userName and otherArg to calculate the user directory
    std::filesystem::path PassengerXMLPath = std::filesystem::current_path() / userName / ("network_xml_" + network_name) / "passenger.xml";
    return PassengerXMLPath;
}


static std::filesystem::path RouteJSONPathPrev = std::filesystem::current_path() / ("network_xml_" + network_name) / "Route.json";

static std::filesystem::path PaxRouteJSONPathPrev = std::filesystem::current_path() / ("network_xml_" + network_name) / "PaxRoute.json";

// Parameter xml file path
static std::filesystem::path AgentTypeXMLPath = ParameterXmlFilePath / "agenttypes.xml";

static std::filesystem::path ParamXMLPath = ParameterXmlFilePath / "param.xml";
}

#endif
