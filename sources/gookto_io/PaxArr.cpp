#include <string>
#include <iostream>
#include <sstream>

#include <gookto_io/PaxArr.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

PaxArr::PaxArr()
{
    TiXmlDocument doc("./network_xml/pax.xml");
    bool loadOkay = doc.LoadFile();

    std::cout << "Loading LinkArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "loading failed" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        //const char *attr;
        if (elemName == "nv_pax")
        {
            std::cout << "Got NV pax" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "pax")
                {

                    InputPax demoPax(atol(e->Attribute("id")), 0, atof(e->Attribute("dpt_time")));

                    //set the Link 2d, 1d values here.
                    demoPax.setReactionTime(atof(e->Attribute("reaction_time")));
                    demoPax.setJamGap(atof(e->Attribute("jamgap")));
                    demoPax.setMaxAcc(atof(e->Attribute("max_acc")));
                    demoPax.setMaxDec(atof(e->Attribute("max_dec")));
                    demoPax.setVehLen(atof(e->Attribute("vehlength")));
                    demoPax.setVFree(atof(e->Attribute("vfree")));

                    int found;

                    std::stringstream links;
                    std::stringstream nodes;

                    links << e->Attribute("link_seq");
                    nodes << e->Attribute("node_seq");

                    std::string temp_links;
                    std::string temp_nodes;

                    // add Links
                    while (!links.eof())
                    {
                        links >> temp_links;
                        if (std::stringstream(temp_links) >> found)
                        {
                            demoPax.addLink(found);
                        }
                        temp_links = "";
                    }

                    //add Nodes
                    while (!nodes.eof())
                    {
                        nodes >> temp_nodes;
                        if (std::stringstream(temp_nodes) >> found)
                        {
                            demoPax.addNode(found);
                        }
                        temp_nodes = "";
                    }

                    Pax.push_back(demoPax);
                    //perhaps need to free pointers here
                }
            }
        }

        else if (elemName == "pub_pax")
        {
            std::cout << "Got Public pax" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "pax")
                {

                    
                }
            }
        }
    }
    doc.Clear();
};