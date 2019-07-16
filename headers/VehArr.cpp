#include <string>
#include <iostream>
#include <sstream>

#include "InputVeh.hpp"
#include "VehArr.hpp"

#include "tinyxml.h"
#include "tinystr.h"

VehArr::VehArr()
{
    TiXmlDocument doc;

    doc.LoadFile("simple_network.xml");
    std::cout << "got xml file loaded" << std::endl;

    if (!doc.LoadFile("simple_network.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        const char *attr;
        if (elemName == "agents")
        {
            std::cout << "Got Agents" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    std::cout << "Got Vehicle" << std::endl;
                    
                    int type = -1;
                    std::string att = e->Attribute("type");
                    if (att == "normal")
                    {
                        type = 1;
                    }


                    //Intialize single Vehicle
                    InputVeh single_veh(atoi(e->Attribute("id")), type);


                    //parse the Link Seq of each vehicles:
                    // String Stream --> Extract Integer
                    std::stringstream ss;     
                     
                    ss << e->Attribute("link_seq"); 
                    std::string temp2; 
                    int found; 

                    while (!ss.eof()) { 
                        ss >> temp2; 
                        if (std::stringstream(temp2) >> found)
                        {
                            single_veh.addLink(found);
                        }
                        temp2 = ""; 
                    }
                    //need to check that this has been stored properly

                    Vehicles.push_back(single_veh);

                }
            }
        }
    }
    doc.Clear();
};


void VehArr::showArr()
{
    for (int i=0; i < Vehicles.size(); i++)
    {
        for (int j=0; j < Vehicles[i].getLinkSeq().size(); j++)
        {
            std::cout << Vehicles[i].getLinkSeq()[j] << " ";
        }
        std::cout << std::endl;
    }
};