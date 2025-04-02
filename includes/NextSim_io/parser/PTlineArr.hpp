/**
 * NextSim Captain
 * @file : PTlineArr.hpp
 * @version : 1.0
 * @author : ???
 */

 #ifndef PTROUTEARR_H
 #define PTROUTEARR_H
 
 #include <vector>
 #include <NextSim_io/inputclass/InputPTline.hpp>
 
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
      * @details Constructor (Parse public transit line information from ptline.xml)
     */
     PTlineArr();
     
     /**
      * @details Get vector of public transit lines
      * @return Vector of public transit lines
     */
     std::vector<InputPTline> GetPTLines()
     {
         return m_ptLines;
     }
 
 private:
     /**
      * @details Vector of public transit lines
     */
     std::vector<InputPTline> m_ptLines;
 };
 } // namespace NextSimIO
 
 #endif