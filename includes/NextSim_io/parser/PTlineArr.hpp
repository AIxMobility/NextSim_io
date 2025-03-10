/**
 * NextSim Captain
 * @file : PTlineArr.hpp
 * @version : 1.0
 * @author : 
 */

 #ifndef PTROUTEARR_H
 #define PTROUTEARR_H
 
 #include <vector>
 #include <string>
 #include <NextSim_io/inputclass/InputPTline.hpp>
 #include <NextSim_io/util/XMLParser.hpp> // Include XML parser utility
 
 namespace NextSimIO
 {
 /**
  * @class PTlineArr
  * @brief Class for whole public transit line information from ptline.xml
 */
 class PTlineArr
 {
 public:
     /**
      * @details Constructor (Parses public transit line information from ptline.xml)
      * @param filename Path to the ptline.xml file
     */
     explicit PTlineArr(const std::string& filename)
     {
         ParseXML(filename);
     }
 
     /**
      * @details Get vector of public transit lines
      * @return Vector of public transit lines
     */
     std::vector<InputPTline> GetPTLines() const
     {
         return m_ptLines;
     }
 
 private:
     /**
      * @details Vector of public transit lines
     */
     std::vector<InputPTline> m_ptLines;
 
     /**
      * @details Parses public transit line information from an XML file
      * @param filename Path to the ptline.xml file
     */
     void ParseXML(const std::string& filename)
     {
         // Use XML parser utility to load transit lines
         m_ptLines = XMLParser::ParsePTLines(filename);
     }
 };
 } // namespace NextSimIO
 
 #endif
 