#include <string>
#include <iostream>

#include <gookto_io/LinkArr.hpp>
#include <gookto_io/InputLink.hpp>
#include <gookto_io/Temporal.hpp>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

// tool functions
void ParseLane(InputLink *parent_link, InputLane *lane,  TiXmlElement *e_lane);
bool a_to_bool(const char * val);

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
        exit(EXIT_FAILURE);
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        
        std::string elemName = elem->Value();

        const char *attr;
        if (elemName == "links")
        {
            std::cout << "Got links" << std::endl;
            std::cout<<(elem->FirstChildElement())->Value()<<std::endl;
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    //std::cout << "Got A link" << std::endl;
                    
                    InputLink *demoLink = new InputLink( (u_ll) atoll(e->Attribute("id")), 
                                        atoi(e->Attribute("num_lane")), 
                                        atof(e->Attribute("length")), 
                                        atof(e->Attribute("width")));

                    //set the Link 2d, 1d values here.


                    demoLink->setFreeFlowSpeed(atof(e->Attribute("ffspeed")));
                    demoLink->setQmax(atof(e->Attribute("qmax")));
                    demoLink->setWaveSpeed(atof(e->Attribute("waveSpd")));
                    demoLink->setMaxVehicle(atoi(e->Attribute("maxVeh")));

                    //save lane infos for each link
                    // int lane_num = 0;
                    for (TiXmlElement *ele = e->FirstChildElement(); ele !=NULL; ele = ele->NextSiblingElement())
                    {
                        std::string elemName3 = ele->Value();
                        if (elemName3=="lane"){

                            // demoLink.pushLaneId(atol(ele->Attribute("id")));
                           
                            const char *leftLaneID = (ele->Attribute("left_lane_id"));
                            const char *rightLaneID = (ele->Attribute("right_lane_id"));
                            bool r_empty = false, l_empty = false ;
                            if (strcmp(leftLaneID,"") == 0){l_empty = true;}
                            if (strcmp(rightLaneID,"") == 0){r_empty = true;}


                            InputLane *demoLane = new InputLane((u_ll)atoll(ele->Attribute("id")), (u_ll)atoll(leftLaneID), (u_ll)atoll(rightLaneID), atoi(ele->Attribute("num_cell")), r_empty, l_empty);
                            // start here
                            for (TiXmlElement *e_lane = ele ->FirstChildElement(); e_lane != NULL; e_lane = e_lane->NextSiblingElement()){
                                // parse the lane
                                ParseLane(demoLink, demoLane, e_lane);
                            }

                            demoLink->pushLaneId(demoLane);
                        }           

                        
                    }


                    

                    Links.push_back(demoLink);
                    //perhaps need to free pointers here 
                        
                }
            }
        }
    }
    doc.Clear();
};




bool a_to_bool(const char * val){
    bool temp;
    if (strcmp(val, "true") == 0){ temp = true;}
    else if(strcmp(val, "false") == 0){temp = false;}
    else{ assert(false);} 
    return temp;

}

void ParseLane(InputLink *parent_link, InputLane *lane, TiXmlElement *e_lane){

    std::string elemName = e_lane ->Value();
    if (elemName == "cell"){
        InputCell  *demoCell = new InputCell((u_ll)atoll(e_lane->Attribute("id")), atof(e_lane->Attribute("offset")), atof(e_lane->Attribute("length")), (void*)parent_link);
        lane->pushCell(demoCell);

    }
    else if(elemName == "segment"){
        const char *block = e_lane->Attribute("block");
        bool blocked = a_to_bool(block);
        bool left_lc = a_to_bool(e_lane->Attribute("left_lc"));
        bool right_lc = a_to_bool(e_lane->Attribute("right_lc"));

        InputSegment *demoSegment =new InputSegment((u_ll)atoll(e_lane->Attribute("id")),
                                blocked, left_lc, right_lc,
                                atof(e_lane->Attribute("init_point")),
                                atof(e_lane->Attribute("end_point")));
        lane->pushSegment(demoSegment);    
    }
    else{
        assert(false);
    }


}
LinkArr::~LinkArr(){
    for (auto itr = Links.begin(); itr != Links.end(); itr++)
    {
        delete *itr;
    }
    
    Links.clear();
}
// void LinkArr::showArr() 
// {
//     if (Links.size() == 0)
//     {
//         std::cout << "ITS EMPTY" << std::endl;
//     }

//     for (int i=0; i< Links.size(); i++)
//     {
//         std::cout << Links[i].getId() << " " << Links[i].getNumLane() << " "  << std::endl;

//         // PRINT CELL INFORMATION
//         std::cout << "FFSpeed Values" << std::endl;
//         // for (int j = 0; j < Links[i].getNumLane(); j++)
//         // {
            
//         //     for (int k = 0; k < Links[i].getNumSect(); k++)
//         //     {
//         //         std::cout << Links[i].getFreeFlowSpeed()[j][k] << " ";
//         //     }
//         //     std::cout << std::endl;
//         // }

//         std::cout << "Qmax Values" << std::endl;
//         // for (int j = 0; j < Links[i].getNumLane(); j++)
//         // {

//         //     for (int k = 0; k < Links[i].getNumSect(); k++)
//         //     {
//         //         std::cout << Links[i].getQmax()[j][k] << " ";
//         //     }
//         //     std::cout << std::endl;
//         // }

//         std::cout << "WaveSpeed Values" << std::endl;
//         // for (int j = 0; j < Links[i].getNumLane(); j++)
//         // {

//         //     for (int k = 0; k < Links[i].getNumSect(); k++)
//         //     {
//         //         std::cout << Links[i].getWaveSpeed()[j][k] << " ";
//         //     }
//         //     std::cout << std::endl;
//         // }

//         std::cout << "MaxVehicle Values" << std::endl;
//         // for (int j = 0; j < Links[i].getNumLane(); j++)
//         // {

//         //     for (int k = 0; k < Links[i].getNumSect(); k++)
//         //     {
//         //         std::cout << Links[i].getMaxVehicle()[j][k] << " ";
//         //     }
//         //     std::cout << std::endl;
//         // }

//         std::cout << "Length Values" << std::endl;
        
//         std::cout << Links[i].getLength() << " ";
        
//         std::cout << std::endl;

//         std::cout << "Width Values" << std::endl;
        
//         std::cout << Links[i].getWidth() << " ";
        

//         std::cout << "\n" << std::endl;
//     }

// }