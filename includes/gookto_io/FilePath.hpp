#ifndef GOOKTOIO_FILEPATH_HPP
#define GOOKTOIO_FILEPATH_HPP

#include <filesystem>

namespace STSIO
{
static std::filesystem::path XmlFilePath =
    // std::filesystem::current_path() / "network_xml";
    "/home/wjstnwp/ubuntu/STS19/build/bin/network_xml";
    
static std::filesystem::path NetworkXMLPath = XmlFilePath / "network.xml";

static std::filesystem::path AgentXMLPath = XmlFilePath / "agents.xml";

static std::filesystem::path AgentOptXMLPath = XmlFilePath / "agents_opt.xml";

static std::filesystem::path OdMatrixXMLPath = XmlFilePath / "odmatrix.xml";

static std::filesystem::path ScenarioXMLPath = XmlFilePath / "odscenario.xml";

static std::filesystem::path ParamXMLPath = XmlFilePath / "param.xml";

static std::filesystem::path AgentTypeXMLPath = XmlFilePath / "agenttypes.xml";

static std::filesystem::path EventXMLPath = XmlFilePath / "eventdata.xml";

static std::filesystem::path PassengerXMLPath = XmlFilePath / "pax.xml";

static std::filesystem::path V2XXMLPath = XmlFilePath / "v2xdata.xml";

static std::filesystem::path ModeXMLPath = XmlFilePath / "mode.xml";

static std::filesystem::path VehicleJSONPath = XmlFilePath / "Vehicle.json";

static std::filesystem::path TotalRouteJSONPath = XmlFilePath / "TotalRoute.json";

static std::filesystem::path InterRouteJSONPath = XmlFilePath / "IntersectionRoute.json";
}

#endif
