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
 
         // Parse <link>
         TiXmlElement* e = elem->FirstChildElement("link");
         if (e && e->Attribute("seq"))
         {
             tPTline.SetLinkSeq(e->Attribute("seq"));
         }
 
         // Parse <node>
         e = elem->FirstChildElement("node");
         if (e && e->Attribute("seq"))
         {
             tPTline.SetNodeSeq(e->Attribute("seq"));
         }
 
         // Parse <station>
         e = elem->FirstChildElement("station");
         if (e)
         {
             if (e->Attribute("seq"))
                 tPTline.SetStationSeq(e->Attribute("seq"));
 
             if (e->Attribute("distance"))
                 tPTline.SetStationDistanceSeq(e->Attribute("distance"));
         }
 
         // Optional: Parse <garage> (for rail transit)
         e = elem->FirstChildElement("garage");
         if (e && e->Attribute("id"))
         {
             tPTline.SetGarageSeq(e->Attribute("id"));
         }
 
         m_ptLines.push_back(tPTline);
     }
 }
 
 } // namespace NextSimIO
 