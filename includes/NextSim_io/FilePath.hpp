/**
 * NextSim Captain
 * @file : FilePath.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef GOOKTOIO_FILEPATH_HPP
#define GOOKTOIO_FILEPATH_HPP

#include <filesystem>

namespace NextSimIO
{
static std::string network_name = "intersection2";

static std::filesystem::path currentPath = std::filesystem::current_path();

static std::filesystem::path NetworkXmlFilePath =
    std::filesystem::current_path() / ("network_xml_" + network_name);

static std::filesystem::path ParameterXmlFilePath =
    std::filesystem::current_path() / "parameter_xml";

// Network xml file path
static std::filesystem::path NetworkXMLPath = NetworkXmlFilePath / "network.xml";

static std::filesystem::path OdMatrixXMLPath = NetworkXmlFilePath / "odmatrix.xml";

static std::filesystem::path ScenarioXMLPath = NetworkXmlFilePath / "scenario.xml";

static std::filesystem::path OdScenarioXMLPath = NetworkXmlFilePath / "odscenario.xml";

static std::filesystem::path SignalTODXMLPath = NetworkXmlFilePath / "signalTOD.xml";

static std::filesystem::path SignalXMLPath = NetworkXmlFilePath / "signal.xml";

static std::filesystem::path SignalNewXMLPath = NetworkXmlFilePath / "signal_new.xml";

static std::filesystem::path ModeXMLPath = NetworkXmlFilePath / "mode.xml";

static std::filesystem::path StationXMLPath = NetworkXmlFilePath / "publicTransit.xml";

static std::filesystem::path PTlineXMLPath = NetworkXmlFilePath / "ptline.xml";

static std::filesystem::path RouteJSONPath = NetworkXmlFilePath / "Route.json";

static std::filesystem::path PaxRouteJSONPath = NetworkXmlFilePath / "PaxRoute.json";

static std::filesystem::path AgentXMLPath = NetworkXmlFilePath / "agents.xml";

static std::filesystem::path EventXMLPath = NetworkXmlFilePath / "eventdata.xml";

static std::filesystem::path V2XXMLPath = NetworkXmlFilePath / "v2xdata.xml";

static std::filesystem::path PassengerXMLPath = NetworkXmlFilePath / "passenger.xml";

static std::filesystem::path BackgroundTrafficXMLPath = NetworkXmlFilePath / "backgroundTraffic.xml";

// Parameter xml file path
static std::filesystem::path VehicleTypeXMLPath = ParameterXmlFilePath / "vehicletypes.xml";

static std::filesystem::path RecordModeXMLPath = ParameterXmlFilePath / "recordMode.xml";

static std::filesystem::path ParamXMLPath = ParameterXmlFilePath / "param.xml";
}

#endif
