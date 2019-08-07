#include "LinkArr.hpp"
#include <string>
#include <iostream>
#include "InputLink.hpp"

#include "tinyxml.h"
#include "tinystr.h"

//LinkArr Constructor
LinkArr::LinkArr()
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
        if (elemName == "roads")
        {
            std::cout << "Got roads" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "links")
                {
                    std::cout << "Got links" << std::endl;

                    for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
                    {
                        InputLink demoLink(atoi(e2->Attribute("id")), atoi(e2->Attribute("num_lane")), atoi(e2->Attribute("num_sect")));
                        std::cout << demoLink.getId() << std::endl;

                        //set the Link 2d, 1d values here.
                        demoLink.setLength(atof(e2->Attribute("length")));
                        demoLink.setWidth(atof(e2->Attribute("width")));

                        demoLink.setFreeFlowSpeed(atof(e2->Attribute("ffspeed")));
                        demoLink.setQmax(atof(e2->Attribute("qmax")));
                        demoLink.setWaveSpeed(atof(e2->Attribute("waveSpd")));
                        demoLink.setMaxVehicle(atof(e2->Attribute("maxVeh")));

                        Links.push_back(demoLink);
                        //perhaps need to free pointers here 
                        
                    }
                }
            }
        }
    }
    doc.Clear();
};






void LinkArr::showArr() 
{
    if (Links.size() == 0)
    {
        std::cout << "ITS EMPTY" << std::endl;
    }

    for (int i=0; i< Links.size(); i++)
    {
        std::cout << Links[i].getId() << " " << Links[i].getNumLane() << " " << Links[i].getNumSect() << std::endl;

        // PRINT CELL INFORMATION
        std::cout << "FFSpeed Values" << std::endl;
        for (int j = 0; j < Links[i].getNumLane(); j++)
        {
            
            for (int k = 0; k < Links[i].getNumSect(); k++)
            {
                std::cout << Links[i].getFreeFlowSpeed()[j][k] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Qmax Values" << std::endl;
        for (int j = 0; j < Links[i].getNumLane(); j++)
        {

            for (int k = 0; k < Links[i].getNumSect(); k++)
            {
                std::cout << Links[i].getQmax()[j][k] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "WaveSpeed Values" << std::endl;
        for (int j = 0; j < Links[i].getNumLane(); j++)
        {

            for (int k = 0; k < Links[i].getNumSect(); k++)
            {
                std::cout << Links[i].getWaveSpeed()[j][k] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "MaxVehicle Values" << std::endl;
        for (int j = 0; j < Links[i].getNumLane(); j++)
        {

            for (int k = 0; k < Links[i].getNumSect(); k++)
            {
                std::cout << Links[i].getMaxVehicle()[j][k] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Length Values" << std::endl;
        for (int j = 0; j < Links[i].getNumSect(); j++)
        {
            std::cout << Links[i].getLength()[j] << " ";
        }
        std::cout << std::endl;

        std::cout << "Width Values" << std::endl;
        for (int j = 0; j < Links[i].getNumLane(); j++)
        {
            std::cout << Links[i].getWidth()[j] << " ";
        }

        std::cout << "\n" << std::endl;
    }

}