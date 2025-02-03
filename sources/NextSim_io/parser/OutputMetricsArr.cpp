/**
 * NextSim Captain
 * @file : OutputMetricsArr.cpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/OutputMetricsArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
OutputMetricsArr::OutputMetricsArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::OutputMetricsXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (OutputMetrics)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "VehicleEvent")
        {
            std::vector<std::pair<std::string, bool>> recordMode;
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();
                if (elemName2 == "Debugging" || elemName2 == "Visualizer" || elemName2 == "Statistics")
                {
                    for (TiXmlElement* m = e->FirstChildElement(); m != NULL;
                         m = m->NextSiblingElement())
                    {
                        std::string mName = m->Value();
                        if (mName == "record_mode")
                        {
                            const char *RecordMode = m->Attribute("output");
                            if (!RecordMode)
                                throw std::runtime_error("Element should have 'record_mode' attribute");
                            
                            recordMode.emplace_back(std::pair<std::string, bool> (elemName2, (std::string(RecordMode) == "t")));
                        }
                        // else // need to change (for variables export true or false)
                        // {
                        // }
                    }
                    
                }
            }
            SetRecordMode(recordMode);

        }
    }
    doc.Clear();
};
} // namespace NextSimIO