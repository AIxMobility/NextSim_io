#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/ScenarioArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ScenarioArr::ScenarioArr()
{
    TiXmlDocument doc;

    doc.LoadFile(NextSimIO::ScenarioXMLPath.string().c_str());
    // std::cout << "Loading ODScenario" << std::endl;

    if (!doc.LoadFile(NextSimIO::ScenarioXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (ODScenario)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Scenario")
        {
            const char *id = elem->Attribute("id");
            const char *od_id = elem->Attribute("od_matrix_id");

            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");
            if (!od_id)
                throw std::runtime_error("Element should have 'od_matrix_id' attribute");
            

            ODscenario.emplace_back(std::make_pair(atoi(id), atoi(od_id)));
        }
    };
    doc.Clear();
}
} // namespace NextSimIO