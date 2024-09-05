/**
 * NextSim Captain
 * @file : FilePath.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef GOOKTOIO_FILEPATH_HPP
#define GOOKTOIO_FILEPATH_HPP

#include <filesystem>

/**
 * @namespace NextSimIO
 * @brief Namespace for file path
 */

namespace NextSimIO
{

/**
 * @brief Network name
 */
static std::string network_name = "bucheon";

/**
 * @brief Current path
 */
static std::filesystem::path currentPath = std::filesystem::current_path();

/**
 * @brief Folder path for network xml files
 */
// ??? 이거랑 NetworkXMLPath 차이를 모르겠음 (전체 폴더 같긴 한데...)
static std::filesystem::path NetworkXmlFilePath =
    std::filesystem::current_path() / ("network_xml_" + network_name);

/**
 * @brief Folder path for parameter xml files
 */
static std::filesystem::path ParameterXmlFilePath =
    std::filesystem::current_path() / "parameter_xml";

// Network xml file path

/**
 * @brief File path for network.xml
*/
static std::filesystem::path NetworkXMLPath = NetworkXmlFilePath / "network.xml";

/**
 * @brief File path for odmatrix.xml
*/
static std::filesystem::path OdMatrixXMLPath = NetworkXmlFilePath / "odmatrix.xml";

/**
 * @brief File path for odscenario.xml
*/
static std::filesystem::path ScenarioXMLPath = NetworkXmlFilePath / "odscenario.xml";

/**
 * @brief File path for signal.xml
*/
static std::filesystem::path SignalXMLPath = NetworkXmlFilePath / "signal.xml";

/**
 * @brief File path for mode.xml
*/
static std::filesystem::path ModeXMLPath = NetworkXmlFilePath / "mode.xml";

/**
 * @brief File path for publicTransit.xml
*/
static std::filesystem::path StationXMLPath = NetworkXmlFilePath / "publicTransit.xml";

/**
 * @brief File path for ptline.xml
*/
static std::filesystem::path PTlineXMLPath = NetworkXmlFilePath / "ptline.xml";

/**
 * @brief File path for Route.json
*/
static std::filesystem::path RouteJSONPath = NetworkXmlFilePath / "Route.json";

/**
 * @brief File path for PaxRoute.json
*/
static std::filesystem::path PaxRouteJSONPath = NetworkXmlFilePath / "PaxRoute.json";

/**
 * @brief File path for agents.xml
*/
static std::filesystem::path AgentXMLPath = NetworkXmlFilePath / "agents.xml";

/**
 * @brief File path for agents_opt.xml
*/
static std::filesystem::path AgentOptXMLPath = NetworkXmlFilePath / "agents_opt.xml";

/**
 * @brief File path for eventdata.xml
*/
static std::filesystem::path EventXMLPath = NetworkXmlFilePath / "eventdata.xml";

/**
 * @brief File path for v2xdata.xml
*/
static std::filesystem::path V2XXMLPath = NetworkXmlFilePath / "v2xdata.xml";

/**
 * @brief File path for passenger.xml
*/
static std::filesystem::path PassengerXMLPath = NetworkXmlFilePath / "passenger.xml";

// Parameter xml file path

/**
 * @brief File path for agenttypes.xml
*/
static std::filesystem::path AgentTypeXMLPath = ParameterXmlFilePath / "agenttypes.xml";

/**
 * @brief File path for demand.xml
*/
static std::filesystem::path ParamXMLPath = ParameterXmlFilePath / "param.xml";
}

#endif
