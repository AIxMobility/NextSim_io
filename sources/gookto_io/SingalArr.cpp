#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/Signalplans.hpp>
#include <gookto_io/SignalArr.hpp>

#include <gookto_io/intersection/intersectionPhase.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

SignalArr::SignalArr()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::SignalXMLPath.string().c_str());
    std::cout << "Loading SignalArr" << std::endl;

    if (!doc.LoadFile(STSIO::SignalXMLPath.string().c_str()))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        std::string elemName2 = e->Value();

        if (elemName2 == "Signal_plans")
        {
            std::cout << "Got signal plan" << std::endl;

            for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL;
                 e2 = e2->NextSiblingElement())
            {
                const char *end = e2->Attribute("end");
                const char *id = e2->Attribute("id");
                const char *start = e2->Attribute("start");


                if (!end)   throw std::runtime_error ("Element should have 'end' attribute");
                if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                if (!start)   throw std::runtime_error ("Element should have 'start' attribute");

                Signalplans signal_node(
                    atoi(id),
                    atol(end),
                    atol(start));

                // TYPES OF NODES --> intersection, normal, terminal
                for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                        e3 = e3->NextSiblingElement())
                {
                    
                    // const char *nodeid = e3->Attribute("id");

                    for (TiXmlElement *e4 = e3->FirstChildElement(); e4 != NULL;
                        e4 = e4->NextSiblingElement())
                    {
                    
                    std::string val1 = e4->Value();

                    if (val1 == "phase")
                    {
                        const char *phaseId = e4->Attribute("id");

                        if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");

                        intersectionPhase single_phase(
                            atol(phaseId));

                        for (TiXmlElement *e5 = e4->FirstChildElement();
                                e5 != NULL; e5 = e5->NextSiblingElement())
                        {
                            std::string val2 = e5->Value();
                            if (val2 == "connection")
                            {
                                const char *id_ref = e5->Attribute("id_ref");
                                const char *priority = e5->Attribute("priority");
                                
                                if (!id_ref)   throw std::runtime_error ("Element should have 'id_ref' attribute");
                                if (!priority)   throw std::runtime_error ("Element should have 'priority' attribute");

                                single_phase.pushConnectionRef(
                                    atol(id_ref));
                                single_phase.pushPriority(
                                    atof(priority));
                            }
                        }
                        signal_node.pushPhase(single_phase);
                    }

                    else if (val1 == "signal_plan")
                    {
                        const char *phase_length = e4->Attribute("phase_length");
                        
                        if (!phase_length)   throw std::runtime_error ("Element should have 'phase_length' attribute");

                        auto iss1 = std::istringstream{ phase_length };
                        auto str1 = std::string{};
                        while (iss1 >> str1)
                        {
                            signal_node.pushPhaseLength(atoi(str1.c_str()));
                        }

                        const char *order = e4->Attribute("order");
                        
                        if (!order)   throw std::runtime_error ("Element should have 'order' attribute");

                        auto iss2 =
                            std::istringstream{ order };
                        auto str2 = std::string{};
                        while (iss2 >> str2)
                        {
                            signal_node.pushPhaseOrder(atoi(str2.c_str()));
                        }

                        const char *offset = e3->Attribute("offset");
                        
                        if (!offset)   throw std::runtime_error ("Element should have 'offset' attribute");

                        signal_node.setPhaseOffset(
                            atoi(offset));
                    }
                    }
                }
                Signals.push_back(signal_node);

                signal_node.freePhaseTable();
            
            }
        }
    }
    doc.Clear();
};
