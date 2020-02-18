#include <string>
#include <iostream>

#include <gookto_io/LinkArr.hpp>
#include <gookto_io/InputLink.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

//LinkArr Constructor
LinkArr::LinkArr()
{
    TiXmlDocument doc("./network_xml/network.xml");
    bool loadOkay = doc.LoadFile();

    std::cout << loadOkay << std::endl;

    std::cout << "Loading LinkArr" << std::endl;

    if (!loadOkay)
    {
        std::cout<< "loading failed" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        const char *attr;
        if (elemName == "links")
        {
            std::cout << "Got links" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    //std::cout << "Got A link" << std::endl;

                    InputLink demoLink(atoi(e->Attribute("id")), atoi(e->Attribute("num_lane")), atoi(e->Attribute("num_sect")));

                    //set the Link 2d, 1d values here.
                    demoLink.setLength(atof(e->Attribute("length")));

                    demoLink.setWidth(atof(e->Attribute("width")));

                    demoLink.setFreeFlowSpeed(atof(e->Attribute("ffspeed")));
                    demoLink.setQmax(atof(e->Attribute("qmax")));
                    demoLink.setWaveSpeed(atof(e->Attribute("waveSpd")));
                    demoLink.setMaxVehicle(atoi(e->Attribute("maxVeh")));


                    

                    Links.push_back(demoLink);
                    //perhaps need to free pointers here 
                        
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
        
        std::cout << Links[i].getLength() << " ";
        
        std::cout << std::endl;

        std::cout << "Width Values" << std::endl;
        
        std::cout << Links[i].getWidth() << " ";
        

        std::cout << "\n" << std::endl;
    }

}