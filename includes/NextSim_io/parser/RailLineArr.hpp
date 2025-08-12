/**
 * NextSim Captain
 * @file : RailLineArr.hpp
 * @version : 1.1
 * @author : Yuseock Hwang, Yeonwoo Yu
 */


 #ifndef RAILLineARR_H
 #define RAILLineARR_H
 
 #include <NextSim_io/inputclass/InputRailLine.hpp>
 
 namespace NextSimIO
 {
 /**
  * @class RailLineArr
  * @brief Class for rail public transit line information from roadptline.xml
  */
 class RailLineArr
 {
 public:
     /**
      * @details Constructor 
     */
    RailLineArr();
 
     /**
      * @details Get vector of rail public transit lines
      * @return Vector of rail public transit lines
     */
    std::vector<InputRailLine> GetRailLines() const { return m_railLines; }
 
 
 private:
 
     /**
      * @details Vector of rail public transit lines
     */
    std::vector<InputRailLine> m_railLines;
 
 };
 } // namespace NextSimIO
 
 #endif