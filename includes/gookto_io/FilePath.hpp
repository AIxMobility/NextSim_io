#ifndef GOOKTOIO_FILEPATH_HPP
#define GOOKTOIO_FILEPATH_HPP

#include <filesystem>

namespace STSIO
{
static std::filesystem::path XmlFilePath =
    std::filesystem::current_path() / "network_xml";

static std::filesystem::path NetworkXMLPath = XmlFilePath / "network.xml";

static std::filesystem::path AgentXMLPath = XmlFilePath / "agents.xml";

static std::filesystem::path OdMatrixXMLPath = XmlFilePath / "odmatrix.xml";

static std::filesystem::path ParamXMLPath = XmlFilePath / "param.xml";

static std::filesystem::path AgnetTypeXMLPath = XmlFilePath / "agenttypes.xml";

static std::filesystem::path PassengerXMLPath = XmlFilePath / "pax.xml";
}

#endif
