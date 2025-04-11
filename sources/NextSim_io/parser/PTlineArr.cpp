/**
 * NextSim Captain
 * @file : PTLineArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

 #include <iostream>
 #include <sstream>
 #include <string>
 #include <filesystem>
 #include <vector>
 
 #include <NextSim_io/parser/PTlineArr.hpp>
 #include <NextSim_io/tinyapi/tinystr.h>
 #include <NextSim_io/tinyapi/tinyxml.h>
 #include <NextSim_io/FilePath.hpp>
 
 namespace NextSimIO
 {
 PTlineArr::PTlineArr()
 {
     TiXmlDocument doc;
     bool loadSuccess = doc.LoadFile(NextSimIO::RoadPTlineXMLPath.string().c_str());
 
     if (!loadSuccess)
     {
         std::cerr << "Error: Failed to load PTline XML file (PTLineArr)" << std::endl;
         return;
     }

     std::cout << "PTLine XML file loaded successfully: " << NextSimIO::RoadPTlineXMLPath.string() << std::endl;
 
     TiXmlElement* root = doc.FirstChildElement(); 
     for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
     {
         // Get required attributes: id & interval
         std::string id;
         int interval = 0;
 
         if (elem->Attribute("id"))
             id = elem->Attribute("id");
         if (elem->Attribute("interval"))
             interval = std::stoi(elem->Attribute("interval"));
 
         InputPTline tPTline(id, interval);
         
         std::cout << "Processing PT line: " << id << ", interval: " << interval << std::endl;
 
         // Parse <link>
         TiXmlElement* e = elem->FirstChildElement("link");
         if (e && e->Attribute("seq"))
         {
             tPTline.SetLinkSeq(e->Attribute("seq"));
             std::cout << "  Link sequence parsed: " << e->Attribute("seq") << std::endl;
         }
 
         // Parse <node>
         e = elem->FirstChildElement("node");
         if (e && e->Attribute("seq"))
         {
             tPTline.SetNodeSeq(e->Attribute("seq"));
             std::cout << "  Node sequence parsed: " << e->Attribute("seq") << std::endl;
         }
 
         // Parse <station>
         e = elem->FirstChildElement("station");
         if (e)
         {
             if (e->Attribute("seq"))
             {
                 tPTline.SetStationSeq(e->Attribute("seq"));
                 std::cout << "  Station sequence parsed: " << e->Attribute("seq") << std::endl;
             }
 
             if (e->Attribute("distance"))
                 tPTline.SetStationDistanceSeq(e->Attribute("distance"));
         }
 
         // Optional: Parse <garage> (for rail transit)
         e = elem->FirstChildElement("garage");
         if (e)
         {
             // Check for both 'id' and 'seq' attributes
             if (e->Attribute("id"))
             {
                 tPTline.SetGarageSeq(e->Attribute("id"));
                 std::cout << "  Garage sequence parsed (id): " << e->Attribute("id") << std::endl;
             }
             else if (e->Attribute("seq"))
             {
                 tPTline.SetGarageSeq(e->Attribute("seq"));
                 std::cout << "  Garage sequence parsed (seq): " << e->Attribute("seq") << std::endl;
             }
             else
             {
                 std::cerr << "  Warning: garage element without id or seq attribute" << std::endl;
             }
         }
 
         m_ptLines.push_back(tPTline);
     }
     
     std::cout << "Total PT lines loaded: " << m_ptLines.size() << std::endl;
 }
 
 } // namespace NextSimIO
 